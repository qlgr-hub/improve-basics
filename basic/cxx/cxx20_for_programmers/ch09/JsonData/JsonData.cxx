#include "cereal.hpp"
#include <json.hpp>
#include <vector.hpp>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Record {
    int account{};
    std::string first{};
    std::string last{};
    double balance{};
};

template<typename Archive>
void serialize(Archive& archive, Record& record) {
    archive(cereal::make_nvp("account", record.account),
        cereal::make_nvp("first", record.first),
        cereal::make_nvp("last", record.last),
        cereal::make_nvp("balance", record.balance));
}

void displayRecords(const std::vector<Record>& records) {
    for (const auto& r : records) {
        std::cout << fmt::format("{} {} {} {:.2f}\n",
            r.account, r.first, r.last, r.balance);
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