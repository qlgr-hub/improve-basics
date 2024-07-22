#include "cereal.hpp"
#include <json.hpp>
#include <string_view>
#include <vector.hpp>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class Record {
    template<typename Archive>
    friend void serialize(Archive& archive, Record& record);

public:
    explicit Record(int account = 0, std::string_view first = "",
        std::string_view last = "", double balance = 0.0)
        : m_account{account}, m_first{first}, m_last{last}
        , m_balance{balance} {}

    int getAccount() const { return m_account; }
    const std::string& getFirst() const { return m_first; }
    const std::string& getLast() const { return m_last; }
    double getBalance() const { return m_balance; }

private:
    int m_account{};
    std::string m_first{};
    std::string m_last{};
    double m_balance{};
};

template<typename Archive>
void serialize(Archive& archive, Record& record) {
    archive(cereal::make_nvp("account", record.m_account),
        cereal::make_nvp("first", record.m_first),
        cereal::make_nvp("last", record.m_last),
        cereal::make_nvp("balance", record.m_balance));
}

void displayRecords(const std::vector<Record>& records) {
    for (const auto& r : records) {
        std::cout << fmt::format("{} {} {} {:.2f}\n",
            r.getAccount(), r.getFirst(), r.getLast(), r.getBalance());
    }
}

int main() {
    std::vector records {
        Record{100, "Brain", "Blue", 123.45},
        Record{200, "Sue", "Green", 987.65}
    };

    std::cout << "Records to serialize:\n";
    displayRecords(records);

    if (std::ofstream output{"records.json"}) {
        cereal::JSONOutputArchive archive{output};
        archive(cereal::make_nvp("records", records));
    }

    if (std::ifstream input{"records.json"}) {
        cereal::JSONInputArchive archive{input};
        std::vector<Record> deserializedRecords{};
        archive(deserializedRecords);
        std::cout << "\nDeserialized records:\n";
        displayRecords(records);
    }

    return 0;
}