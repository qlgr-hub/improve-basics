#include <iostream>
#include <list>
#include <queue>
#include <ranges>
#include <stack>
#include <vector>

auto pushElements = [](auto& stack) {
    for (auto i : std::views::iota(0, 10)) {
        stack.push(i);
        std::cout << stack.top() << ' ';
    }
};

auto popElements = [](auto& stack) {
    while (!stack.empty()) {
        std::cout << stack.top() << ' ';
        stack.pop();
    }
};

int main() {
    std::stack<int> dequeStack{};
    std::stack<int, std::vector<int>> vectorStack{};
    std::stack<int, std::list<int>> listStack{};

    std::cout << "Pushing onto dequeStack: ";
    pushElements(dequeStack);
    std::cout << "\nPushing onto vectorStack: ";
    pushElements(vectorStack);
    std::cout << "\nPushing onto listStack: ";
    pushElements(listStack);

    std::cout << "\n\nPopping from dequeStack: ";
    popElements(dequeStack);
    std::cout << "\nPopping from vectorStack: ";
    popElements(vectorStack);
    std::cout << "\nPopping from listStack: ";
    popElements(listStack);
    std::cout << "\n";

    std::cout << "\n\nqueue demos:\n";
    std::queue<double> values{};
    values.push(3.2);
    values.push(9.8);
    values.push(5.4);
    std::cout << "Popping from values: ";
    while (!values.empty()) {
        std::cout << values.front() << ' ';
        values.pop();
    }
    std::cout << "\n";

    std::cout << "\n\nqueue demos:\n";
    std::priority_queue<double> priorities{};
    priorities.push(3.2);
    priorities.push(9.8);
    priorities.push(5.4);
    std::cout << "Popping from priorities: ";
    while (!priorities.empty()) {
        std::cout << priorities.top() << ' ';
        priorities.pop();
    }
    std::cout << "\n";

    return 0;
}