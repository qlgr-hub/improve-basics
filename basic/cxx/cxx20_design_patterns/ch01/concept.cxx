
#include <string_view>

template <typename TImpl>
concept IsANotifier = requires(TImpl impl) {
    impl.AlertSMS(std::string_view{});
    impl.AlertEmail(std::string_view{});
};

template <IsANotifier TImpl>
void AlertAllChannels(TImpl& impl, std::string_view msg) {
    impl.AlertSMS(msg);
    impl.AlertEmail(msg);
}

struct TestNotifier {
    void AlertSMS(std::string_view msg) {}
    void AlertEmail(std::string_view msg) {}
};

int main() {
    TestNotifier tn;
    AlertAllChannels(tn, "testing!");
}
