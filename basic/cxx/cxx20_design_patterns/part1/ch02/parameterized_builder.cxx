#include <functional>
#include <string>
#include <string_view>


class MailService {
    struct Email {
        std::string from;
        std::string to;
        std::string subject;
        std::string body;
    };

private:
    void send_email_impl(const Email& email) {
        // actually send the email
        // ...
    }

public:
    class EmailBuilder {
        Email& email;

    public:
        explicit EmailBuilder(Email& email) : email{ email } {
        }

        EmailBuilder& from(std::string_view from) {
            email.from = from;
            return *this;
        }

        EmailBuilder& to(std::string_view to) {
            email.to = to;
            return *this;
        }

        EmailBuilder& subject(std::string_view subject) {
            email.subject = subject;
            return *this;
        }

        EmailBuilder& body(std::string_view body) {
            email.body = body;
            return *this;
        }
    };

public:
    void send_email(std::function<void(EmailBuilder&)> builder) {
        Email email;
        EmailBuilder b{ email };
        builder(b);
        send_email_impl(email);
    }
};


int main() {
    MailService ms;
    ms.send_email([&](auto& eb) {
        eb.from("foo@bar.com")
            .to("bar@baz.com")
            .subject("hello")
            .body("Hello, how are you");
    });
}

