#include <iostream>
#include <ostream>
#include <string>
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>
#include <string_view>


struct Creature {
    std::string name;
    int attack;
    int defense;

    friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
        return os << "name: " << obj.name << " attack: " << obj.attack << " defense: " << obj.defense;
    }
};

class CreatureModifier {
    CreatureModifier* next{ nullptr };

protected:
    Creature& creature;

public:
    explicit CreatureModifier(Creature& creature) 
        : creature{ creature } {
    }

    void add(CreatureModifier* cm) {
        if (next) 
            next->add(cm);
        else
            next = cm;
    }

    virtual void handle() {
        if (next)
            next->handle(); // critical!
    }
};


struct DoubleAttackModifier : public CreatureModifier {
    explicit DoubleAttackModifier(Creature& creature) 
        : CreatureModifier{ creature } {
    }

    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};


struct IncreaseDefenseModifier : public CreatureModifier {
    explicit IncreaseDefenseModifier(Creature& creature) 
        : CreatureModifier{ creature } {
    }

    void handle() override {
        if (creature.attack <= 2)
            creature.defense += 1;
        CreatureModifier::handle();
    }
};


struct NoBonusesModifier : public CreatureModifier {
    explicit NoBonusesModifier(Creature& creature) 
        : CreatureModifier{ creature } {
    }

    void handle() override {
        // nothing here!
    }
};


int main1() {
    Creature goblin{ "Goblin", 1, 1 };

    CreatureModifier root{ goblin };
    DoubleAttackModifier r1{ goblin };
    DoubleAttackModifier r1_2{ goblin };
    IncreaseDefenseModifier r2{ goblin };

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    std::cout << goblin << '\n';
    return 0;
}


struct Query {
    std::string creature_name;
    enum Argument { attack, defense } argument;
    int result;
};

struct Game {
    boost::signals2::signal<void(Query&)> queries;
};


class Creature1 {
    Game& game;
    int attack;
    int defense;

public:
    std::string name;

    Creature1(Game& game, std::string_view name, int attack, int defense) 
        : game{ game }, attack{ attack }, defense{ defense }, name{ name } {
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature1& obj) {
        return os << "name: " << obj.name << " attack: " << obj.get_attack() << " defense: " << obj.defense;
    }

    int get_attack() const {
        Query q{ name, Query::Argument::attack, attack };
        game.queries(q);
        return q.result;
    }
};


class CreatureModifier1 {
    Game& game;
    Creature1& creature;

public:
    CreatureModifier1(Game& game, Creature1& creature) 
        : game{ game }, creature{ creature } {
    }
};


class DoubleAttackModifier1 : public CreatureModifier1 {
    boost::signals2::connection conn;

public:
    DoubleAttackModifier1(Game& game, Creature1& creature) 
        : CreatureModifier1{ game, creature } {
        
        conn = game.queries.connect([&](Query& q) {
            if (q.creature_name == creature.name && q.argument == Query::Argument::attack)
                q.result *= 2;
        });
    }

    ~DoubleAttackModifier1() {
        conn.disconnect();
    }
};

int main() {
    Game game;
    Creature1 goblin{ game, "Strong Goblin", 2, 2 };
    std::cout << goblin << '\n';

    {
        DoubleAttackModifier1 dam{ game, goblin };
        std::cout << goblin << '\n';
    }

    std::cout << goblin << '\n';
    return 0;
}