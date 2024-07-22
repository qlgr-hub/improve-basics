

// struct Foo : SomeBase<Foo> {
//
// };

#include <string_view>
template <typename Derived>
struct SomeBase {
    void foo() {
        for (auto& item : *static_cast<Derived*>(this)) {
            // do something
        }
    }
};


struct MyClass : SomeBase<MyClass> {
    class itarator {

    };

    itarator begin() const {
        // do something
    }

    itarator end() const {
        // do something
    }
};



//
template <typename TImpl>
class Notifier {
    friend TImpl;

private:
    TImpl& impl() { return static_cast<TImpl>(*this) }

public:
    void AlertSMS(std::string_view msg) {
        impl().SendAlertSMS(msg);
    }

    void AlertEmail(std::string_view msg) {
        impl().SendAlertEmail(msg);
    }
};

template <typename TImpl>
void AlertAllChannels(Notifier<TImpl>& notifier, std::string_view msg) {
    notifier.AlertSMS(msg);
    notifier.AlertEmail(msg);
}

struct TestNotifier : public Notifier<TestNotifier> {
    void SendAlertSMS(std::string_view msg) {}
    void SendAlertEmail(std::string_view msg) {}
};

int main() {
    TestNotifier tn;
    AlertAllChannels(tn, "testing!");
}