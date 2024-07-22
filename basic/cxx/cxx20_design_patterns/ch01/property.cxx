
// class Person {
//     int age;
// public:
//     int get_age() const { return age; }
//     void set_age(int value) { age = value; }
//
//     // Non-standard, not recommended
//     __declspec(property(get=get_age, put=set_age)) int age;
// };
//
// int main() {
//     Person p;
//     p.age = 20; // calls p.set_age(20)
// }

class Person {
    int _age;
public:
    int get_age() const { return _age; }
    void set_age(int value) { _age = value; }
};

