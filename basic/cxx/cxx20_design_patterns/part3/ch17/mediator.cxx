#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>


struct ChatRoom;
struct Person {
    std::string name;
    ChatRoom* room{ nullptr };
    std::vector<std::string> chat_log;

    Person(std::string_view name) : name{ name } {
    }

    void receive(std::string_view origin, std::string_view message) {
        auto s{ std::string(origin) + ": \"" + message.data() + "\"" };
        std::cout << "[" << name << "'s chat session]" << s << '\n';
        chat_log.emplace_back(s);
    }

    void say(std::string_view message) const;
    void pm(std::string_view who, std::string_view message) const;
};


struct ChatRoom {
    std::vector<Person*> people;

    void join(Person* p) {
        std::string join_msg{ p->name + " joins the chat" };
        broadcast("room", join_msg);
        p->room = this;
        people.push_back(p); 
    }

    void broadcast(std::string_view origin, std::string_view message) {
        for (auto p : people)
            if (p->name != origin)
                p->receive(origin, message);
    }

    void message(std::string_view origin, std::string_view who, std::string_view message) {
        auto target{ std::find_if(std::begin(people), std::end(people), [&](const Person* p) {
            return p->name == who;
        }) };

        if (target != std::end(people))
            (*target)->receive(origin, message);
    }
};

void Person::say(std::string_view message) const {
    room->broadcast(name, message);
}

void Person::pm(std::string_view who, std::string_view message) const {
    room->message(name, who, message);
}

int main1() {
    ChatRoom room;

    Person john{ "john" };
    Person jane{ "jane" };
    room.join(&john);
    room.join(& jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon{ "simon" };
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("simon", "glad you could join us, simon");
    return 0;
}



struct EventData {
    virtual ~EventData() = default;
    virtual void print() const = 0;
};

struct PlayerScoredData : EventData {
    std::string player_name;
    int goals_scored_so_far;

    PlayerScoredData(std::string_view player_name, int goals_scored_so_far) 
        : player_name{ player_name }, goals_scored_so_far{ goals_scored_so_far } {
    }

    void print() const override {
        std::cout << player_name << " has scored! (their " << goals_scored_so_far << " goal)" << '\n';
    }
};

struct Game {
    boost::signals2::signal<void(EventData*)> events; // observer
};

struct Player {
    std::string name;
    int goals_scored{ 0 };
    Game& game;

    Player(std::string_view name, Game& game) 
        : name{ name }, game{ game } {
    }

    void score() {
        ++goals_scored;
        PlayerScoredData ps{ name, goals_scored };
        game.events(&ps);
    }
};

struct Coach {
    Game& game;

    explicit Coach(Game& game) : game{ game } {
        game.events.connect([](EventData* e) {
            PlayerScoredData* ps{ dynamic_cast<PlayerScoredData*>(e) };
            if (ps && ps->goals_scored_so_far < 3)
                std::cout << "coach says: well done, " << ps->player_name << '\n';
        });
    }
};

int main() {
    Game game;
    Player player{ "Sam", game };
    Coach coach{ game };

    player.score();
    player.score();
    player.score();

    return 0;
}
