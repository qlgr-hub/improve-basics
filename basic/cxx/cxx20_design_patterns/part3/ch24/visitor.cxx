#include <iostream>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <variant>



struct Expression {
    virtual ~Expression() = default;
    virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : Expression {
    double value;

    explicit DoubleExpression(double value) : value{ value } {
    }

    void print(std::ostringstream& oss) override {
        oss << value;
    }
};

struct AdditionExpression : Expression {
    Expression* left;
    Expression* right;

    AdditionExpression(Expression* const left, Expression* const right) 
        : left{ left }, right{ right } {
    }

    ~AdditionExpression() {
        delete left;
        delete right;
    }

    void print(std::ostringstream& oss) override {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};


int main1() {
    auto e{
        new AdditionExpression{
            new DoubleExpression{ 1 },
            new AdditionExpression{
                new DoubleExpression{ 2},
                new DoubleExpression{ 3 },
            }
        }
    };

    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << '\n';

    delete e;
    return 0;
}



struct Expression1 {
    virtual ~Expression1() = default;
};

struct DoubleExpression1 : Expression1 {
    double value;

    explicit DoubleExpression1(double value) : value{ value } {
    }
};

struct AdditionExpression1 : Expression1 {
    Expression1* left;
    Expression1* right;

    AdditionExpression1(Expression1* const left, Expression1* const right) 
        : left{ left }, right{ right } {
    }

    ~AdditionExpression1() {
        delete left;
        delete right;
    }
};


class ExpressionPrinter {
    std::ostringstream oss;

public:
    void print(Expression1* e) {
        if (auto de = dynamic_cast<DoubleExpression1*>(e)) {
            oss << de->value;
        }
        else if (auto ae = dynamic_cast<AdditionExpression1*>(e)) {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }

    std::string str() const {
        return oss.str();
    }


    // void print(DoubleExpression1* de, std::ostringstream& oss) const {
    //     oss << de->value;
    // }
    //
    // void print(AdditionExpression1* ae, std::ostringstream& oss) const {
    //     oss << "(";
    //     print(ae->left, oss);
    //     oss << "+";
    //     print(ae->right, oss);
    //     oss << ")";
    // }
};


int main2() {
    auto e{
        new AdditionExpression1{
            new DoubleExpression1{ 1 },
            new AdditionExpression1{
                new DoubleExpression1{ 2},
                new DoubleExpression1{ 3 },
            }
        }
    };

    ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.str() << '\n';

    delete e;
    return 0;
}



struct Stuff {};
struct Foo : Stuff {};
struct Bar : Stuff {};

void func(Foo* foo) {
    std::cout << "func(Foo*)\n";
}
void func(Bar* bar) {
    std::cout << "func(Bar*)\n";
}

int main3() {
    Foo* foo{ new Foo{} };
    func(foo);
    delete foo;

    // Stuff* stuff{ new Foo{} };
    // func(stuff); //no matching function for call to 'func'
    // delete stuff;
    return 0;
}



struct Foo1;
void func1(Foo1* foo) {
    std::cout << "func1(Foo*)\n";
}

struct Bar1;
void func1(Bar1* bar) {
    std::cout << "func1(Bar*)\n";
}

struct Stuff1 {
    virtual ~Stuff1() = default;
    virtual void call() = 0;
};

struct Foo1 : Stuff1 {
    void call() override {
        func1(this);
    }
};

struct Bar1 : Stuff1 {
    void call() override {
        func1(this);
    }
};


int main4() {
    Foo1* foo{ new Foo1{} };
    foo->call();
    delete foo;

    Stuff1* stuff{ new Foo1{} };
    stuff->call();
    delete stuff;
    return 0;
}




struct ExpressionVisitor;
struct Expression2 {
    virtual ~Expression2() = default;
    virtual void acccept(ExpressionVisitor& visitor) = 0;
};

struct DoubleExpression2;
struct AdditionExpression2;
struct ExpressionVisitor {
    virtual ~ExpressionVisitor() = default;

    virtual void visit(DoubleExpression2& de) = 0;
    virtual void visit(AdditionExpression2& de) = 0;
};

struct DoubleExpression2 : Expression2 {
    double value;

    explicit DoubleExpression2(double value) : value{ value } {
    }

    void acccept(ExpressionVisitor& visitor) override {
        visitor.visit(*this);
    }
};

struct AdditionExpression2 : Expression2 {
    Expression2* left;
    Expression2* right;

    AdditionExpression2(Expression2* const left, Expression2* const right) 
        : left{ left }, right{ right } {
    }

    ~AdditionExpression2() {
        delete left;
        delete right;
    }

    void acccept(ExpressionVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class ExpressionPrinter1 : public ExpressionVisitor {
    std::ostringstream oss;

public:
    void visit(DoubleExpression2& de) override {
        oss << de.value;
    }

    void visit(AdditionExpression2& ae) override {
        oss << "(";
        ae.left->acccept(*this);
        oss << "+";
        ae.right->acccept(*this);
        oss << ")";
    }

    std::string str() const {
        return oss.str();
    }
};

class ExpressionEvaluator : public ExpressionVisitor {
    double result;

public:
    void visit(DoubleExpression2& de) override {
        result = de.value;
    }

    void visit(AdditionExpression2& ae) override {
        ae.left->acccept(*this);
        auto temp{ result };

        ae.right->acccept(*this);
        result += temp;
    }

    double res() const {
        return result;
    }
};

int main5() {
    auto e{
        new AdditionExpression2{
            new DoubleExpression2{ 1 },
            new AdditionExpression2{
                new DoubleExpression2{ 2},
                new DoubleExpression2{ 3 },
            }
        }
    };

    ExpressionPrinter1 ep;
    ExpressionEvaluator ee;
    e->acccept(ep);
    e->acccept(ee);
    std::cout << ep.str() << " = " << ee.res() << '\n';

    delete e;
    return 0;
}




template <typename Visitable>
struct Visitor {
    virtual ~Visitor() = default;
    virtual void visit(Visitable& obj) = 0;
};


struct VisitorBase {
    virtual ~VisitorBase() = default;
};


struct Expression3 {
    virtual ~Expression3() = default;

    virtual void accept(VisitorBase& obj) {
        using Ev = Visitor<Expression3>;
        if (auto ev{ dynamic_cast<Ev*>(&obj) }) {
            ev->visit(*this);
        }
    }
};

struct DoubleExpression3 : Expression3 {
    double value;

    explicit DoubleExpression3(double value) : value{ value } {
    }

    void accept(VisitorBase& obj) override {
        using Ev = Visitor<DoubleExpression3>;
        if (auto ev{ dynamic_cast<Ev*>(&obj) }) {
            ev->visit(*this);
        }
    }
};

struct AdditionExpression3 : Expression3 {
    Expression3* left;
    Expression3* right;

    AdditionExpression3(Expression3* const left, Expression3* const right) 
        : left{ left }, right{ right } {
    }

    ~AdditionExpression3() {
        delete left;
        delete right;
    }

    void accept(VisitorBase& obj) override {
        using Ev = Visitor<AdditionExpression3>;
        if (auto ev{ dynamic_cast<Ev*>(&obj) }) {
            ev->visit(*this);
        }
    }
};


class ExpressionPrinter2 
    : public VisitorBase
    , public Visitor<DoubleExpression3>
    , public Visitor<AdditionExpression3> {

    std::ostringstream oss;

public:
    void visit(DoubleExpression3& obj) override {
        oss << obj.value;
    }

    void visit(AdditionExpression3& obj) override {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }

    std::string str() const {
        return oss.str();
    }
};

int main6() {
    auto e{
        new AdditionExpression3{
            new DoubleExpression3{ 1 },
            new AdditionExpression3{
                new DoubleExpression3{ 2},
                new DoubleExpression3{ 3 },
            }
        }
    };

    ExpressionPrinter2 ep;
    e->accept(ep);
    // ep.visit(*e);
    std::cout << ep.str() << '\n';

    delete e;
    return 0;
}


struct AddressPrinter {
    void operator()(std::string_view house_name) const {
        std::cout << "A house called " << house_name << '\n';
    }

    void operator()(int house_number) const {
        std::cout << "House number " << house_number << '\n';
    }
};

int main() {
    std::variant<std::string, int> house;
    house = 221;

    AddressPrinter ap;
    std::visit(ap, house);


    house = "Montefiore Castle";
    std::visit([](const auto& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "A house called " << arg.c_str() << '\n';
        }
        else {
            std::cout << "House number " << arg << '\n';
        }
    }, house);

    return 0;
}