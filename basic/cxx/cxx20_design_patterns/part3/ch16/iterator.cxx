#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


int main1() {
    using namespace std::string_literals;
    std::vector<std::string> names{ "john", "jane", "jill", "jack" };
    std::vector<std::string>::iterator it = names.begin();
    std::cout << "first name is " << *it << '\n';

    ++it;
    it->append(" goodall"s);
    std::cout << "second name is " << *it << '\n';

    while (++it != names.end()) {
        std::cout << "another name: " << *it << '\n';
    }

    for (auto ri{ names.rbegin() }; ri != names.rend(); ++ri) {
        std::cout << *ri;
        if (ri + 1 != std::rend(names))
            std::cout << ", ";
    }
    std::cout << '\n';


    // std::vector<std::string>::const_reverse_iterator jack = std::crbegin(names);
    // *jack += " reacher"; // error

    for (auto& name : names)
        std::cout << "name = " << name << '\n';

    return 0;
}



template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
    T value;

    Node<T>* left{ nullptr };
    Node<T>* right{ nullptr };
    Node<T>* parent{ nullptr };

    BinaryTree<T>* tree{ nullptr };

    explicit Node(const T& value) : value{ value } {
    }

    Node(const T& value, Node<T>* const left, Node<T>* const right) 
        : value{ value }, left{ left }, right{ right } {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* t) {
        tree = t;
        if (left)
            left->set_tree(t);
        if (right)
            right->set_tree(t);
    }
};


template <typename U>
struct PreOrderIterator;

template <typename T>
struct BinaryTree {
    using iterator = PreOrderIterator<T>;

    Node<T>* root{ nullptr };

    explicit BinaryTree(Node<T>* const root) 
        : root{ root }, pre_order{ *this } {
        root->set_tree(this);
    }

    iterator begin() {
        Node<T>* n{ root };
        if (n)
            while (n->left)
                n = n->left;
        return iterator{ n };
    }

    iterator end() {
        return iterator{ nullptr };
    }

public:
    class pre_order_traversal {
        BinaryTree<T>& tree;

    public:
        pre_order_traversal(BinaryTree<T>& tree) : tree{ tree } {
        }

        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } pre_order;


// The current version of gcc does not support std::generator yet
// private:
//     std::generator<Node<T>*> post_order_impl(Node<T>* node) const {
//         if (node) {
//             for (auto x : post_order_impl(node->left))
//                 co_yield x;
//             for (auto y : post_order_impl(node->right))
//                 co_yield y;
//
//             co_yield node;
//         }
//     }
//
// public:
//     std::generator<Node<T>*> post_order() const {
//         return post_order_impl(root);
//     }
};

template <typename U>
struct PreOrderIterator {
    Node<U>* current{ nullptr };

    explicit PreOrderIterator(Node<U>* current) 
        : current{ current } {
    }

    bool operator!=(const PreOrderIterator<U>& other) {
        return current != other.current;
    }

    Node<U>& operator*() {
        return *current;
    }

    PreOrderIterator<U>& operator++() {
        if (current->right) {
            current = current->right;
            while (current->left)
                current = current->left;
        }
        else {
            Node<U>* p{ current->parent };
            while (p && current == p->right) {
                current = p;
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
};

int main() {
    BinaryTree<std::string> family {
        new Node<std::string>{ "me",
            new Node<std::string>{ "mother",
                new Node<std::string>{ "mother's mother"},
                new Node<std::string>{ "mother's father"}
            },
            new Node<std::string>{ "father" }
        }
    };

    // for (auto it{ family.begin() }; it != family.end(); ++it)
    //     std::cout << (*it).value << '\n';

    for (const auto& it : family.pre_order) {
        std::cout << it.value << '\n';
    }

    // for (const auto& it : family.post_order()) {
    //     std::cout << it.value << '\n';
    // }

    return 0;
}