#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/mpl/vector.hpp>
#include <boost/msm/back11/state_machine.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>


class LightSwitch;
struct State {
    virtual void on(LightSwitch* ls) {
        std::cout << "Light is already on\n";
    }

    virtual void off(LightSwitch* ls) {
        std::cout << "Light is already off\n";
    }
};

struct OnState final : State {
    OnState() { 
        std::cout << "Light turned on\n"; 
    }

    void off(LightSwitch* ls) override;
};

struct OffState final : State {
    OffState() { 
        std::cout << "Light turned off\n"; 
    }

    void on(LightSwitch* ls) override;
};


class LightSwitch {
    State* state{ nullptr };

public:
    LightSwitch() {
        state = new OffState{};
    }

    void set_state(State* state) {
        this->state = state;
    }

    void on() {
        state->on(this);
    }

    void off() {
        state->off(this);
    }
};

void OnState::off(LightSwitch* ls) {
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState{});
    delete this;
}

void OffState::on(LightSwitch* ls) {
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState{});
    delete this;
}


int main1() {
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
    return 0;
}



enum class PhoneState {
    off_hook,
    connecting,
    connected,
    on_hold,
    on_hook
};
static std::ostream& operator<<(std::ostream& os, PhoneState state) {

    switch (state) {
    case PhoneState::off_hook:
        os << "on hook";
        break;

    case PhoneState::connecting:
        os << "connecting";
        break;

    case PhoneState::connected:
        os << "connected";
        break;

    case PhoneState::on_hold:
        os << "on hold";
        break;
    case PhoneState::on_hook:
        os << "on hook";
        break;

    default: break;
    }

    return os;
}


enum class Trigger {
    call_dialed,
    hung_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};
static std::ostream& operator<<(std::ostream& os, Trigger trigger) {
    
    switch (trigger) {
    case Trigger::call_dialed:
        os << "call dialed";
        break;

    case Trigger::hung_up:
        os << "hung up";
        break;

    case Trigger::call_connected:
        os << "call connected";
        break;

    case Trigger::placed_on_hold:
        os << "placed on hold";
        break;

    case Trigger::taken_off_hold:
        os << "taken off hold";
        break;

    case Trigger::left_message:
        os << "left message";
        break;

    case Trigger::stop_using_phone:
        os << "putting phone on hook";
        break;

    default: break;
    }

    return os;
}

int main2() {
    std::map<PhoneState, std::vector<std::pair<Trigger, PhoneState>>> rules;

    rules[PhoneState::off_hook] = {
        { Trigger::call_dialed, PhoneState::connecting },
        { Trigger::stop_using_phone, PhoneState::on_hook }
    };

    rules[PhoneState::connecting] = {
        { Trigger::hung_up, PhoneState::off_hook },
        { Trigger::call_connected, PhoneState::connected }
    };

    rules[PhoneState::connected] = {
        { Trigger::left_message, PhoneState::off_hook },
        { Trigger::hung_up, PhoneState::off_hook },
        { Trigger::placed_on_hold, PhoneState::on_hold }
    };

    rules[PhoneState::on_hold] = {
        { Trigger::taken_off_hold, PhoneState::off_hook },
        { Trigger::hung_up, PhoneState::off_hook }
    };

    rules[PhoneState::on_hook] = {
        { Trigger::call_dialed, PhoneState::connecting },
        { Trigger::placed_on_hold, PhoneState::on_hold }
    };

    auto currentState{ PhoneState::off_hook };
    auto exitState{ PhoneState::on_hook };
    while (true) {
        std::cout << "The phone is currently " << currentState << '\n';
    
    select_trigger:
        std::cout << "Select a trigger:\n";

        int i{ 0 };
        for (auto item : rules[currentState]) {
            std::cout << i++ << ". " << item.first << '\n';
        }

        int input;
        std::cin >> input;
        if (input < 0 || (input + 1) > rules[currentState].size()) {
            std::cout << "Incorrect option. Please try again.\n";
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if (currentState == exitState)
            break;
    }

    return 0;
}



enum class State1 {
    locked,
    failed,
    unlocked
 };

 int main3() {
    std::string_view code{ "1234" };
    auto state{ State1::locked };

    std::string entry{};
    while (true) {
        switch (state) {
        case State1::locked:
            {
                entry += (char)getchar();
                getchar();

                if (entry == code) {
                    state = State1::unlocked;
                    break;
                }

                if (!code.starts_with(entry)) {
                    state = State1::failed;
                }
            }
            break;

        case State1::failed:
            std::cout << "FAILED\n";
            return 0;

        case State1::unlocked:
            std::cout << "UNLOCKED\n";
            return 0;
        }
    }

    return 0;
 }




 ///////////////////////////////////////////////////////////////////////////////////
 struct OffHook : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently off the hook" << '\n';
    }
 };

 struct Connecting : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently connecting" << '\n';
    }
 };

struct Connected : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently connected" << '\n';
    }
};

struct OnHold : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently on hold" << '\n';
    }
};

struct OnHook : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently on hook" << '\n';
    }
};

struct PhoneDestroyed : boost::msm::front::state<> {
    template <typename Event, typename FMS>
    void on_entry(Event const&, FMS&) {
        std::cout << "The phone is currently broken" << '\n';
    }
};

struct CallDialed {};
struct CallConnected {};
struct PlaceOnHold {};
struct PhoneThrowIntoWall {};


struct PhoneBeingDestroyed {
    template <typename EVT, typename FSM, typename SourceState, typename TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
        std::cout << "Phone breaks into a million pieces!!!\n";
    }
};

struct CanDestroyPhone {
    template <typename EVT, typename FSM, typename SourceState, typename TargetState>
    bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&) {
        return fsm.angry;
    }
};

struct PhoneStateMachine : boost::msm::front::state_machine_def<PhoneStateMachine> {
    bool angry{ true };

    using initial_state = OffHook;

    template <typename FSM, typename Event>
    void no_transition(Event const& e, FSM&, int state) {
        std::cout << "No transition from state " << state
            << " on event " << typeid(e).name() << '\n';
    }

    struct transition_table : boost::mpl::vector<
        boost::msm::front::Row<OffHook, CallDialed, Connecting>,
        boost::msm::front::Row<Connecting, CallConnected, Connected>,
        boost::msm::front::Row<Connected, PlaceOnHold, OnHold>,
        boost::msm::front::Row<OnHold, PhoneThrowIntoWall, PhoneDestroyed, 
            PhoneBeingDestroyed, CanDestroyPhone>
    > {};
};


int main() {
    boost::msm::back11::state_machine<PhoneStateMachine> phone;
    phone.start();

    phone.process_event(CallDialed{});
    phone.process_event(CallConnected{});
    phone.process_event(PlaceOnHold{});
    phone.process_event(PhoneThrowIntoWall{});
    phone.process_event(CallDialed{});

    return 0;
}