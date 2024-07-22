#include <iostream>



class Game {
protected:
    int number_of_players;
    int current_player{ 0 };

private:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int  get_winner() = 0;

public:
    Game(int number_of_players) : number_of_players{ number_of_players } {
    }

public:
    void run() {
        start();

        while (!have_winner())
            take_turn();
        
        std::cout << "Player " << get_winner() << " wins.\n";
    }
};


class Chess : public Game {
    int turns{ 0 };
    int max_turns{ 10 };

private:
    void start() override {
        std::cout << "Starting a game of chess with " << number_of_players << " players\n";
    }

    bool have_winner() override {
        return turns == max_turns;
    }

    void take_turn() override {
        std::cout << "Turn " << turns++ << " taken by player " << current_player << '\n';
        current_player = (current_player + 1) % number_of_players;
    }

    int get_winner() override {
        return current_player;
    }

public:
    explicit Chess() : Game{ 2 } {
    }
};

int main1() {
    Chess chess;
    chess.run();
    return 0;
}



struct GameState {
    int current_player;
    int winning_player;

    int number_of_players;
};


template <typename FnStartAction, 
          typename FnTakeTurnAction, 
          typename FnHaveWinnerAction>
void run_game(GameState initial_state,
              FnStartAction start_action,
              FnTakeTurnAction take_turn_action,
              FnHaveWinnerAction have_winner_action) {
    GameState state{ initial_state };
    start_action(state);

    while (!have_winner_action(state)) {
        take_turn_action(state);
    }

    std::cout << "Player " << state.winning_player << " wins.\n";
}

int main() {
    int turns{ 0 };
    int max_turns{ 10 };
    GameState state{ 0, -1, 2 };

    auto start{[](GameState& state) {
        std::cout << "Starting a game of chess with " << state.number_of_players << " players\n";
    }};

    auto take_action{[&](GameState& state) {
        std::cout << "Turn " << turns++ << " taken by player " << state.current_player << '\n';
        state.current_player = (state.current_player + 1) % state.number_of_players;
        state.winning_player = state.current_player;
    }};

    auto have_winner{ [&](GameState& state) {
        return turns == max_turns;
    }};

    run_game(state, start, take_action, have_winner);
    return 0;
}
