#pragma once

#include <array>
#include <cinttypes>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <cassert>

namespace Localization
{
    using namespace std;

    using StringID = int32_t;

    enum class Languages
    {
        EN_US,
        EN_GB,
        Number
    };

    const StringID STRING_COLOR{ 0 };

    class Manager
    {
    private:
        using Strings = std::unordered_map<StringID, std::string>;
        using StringPacks = std::array<Strings, static_cast<size_t>(Languages::Number)>;

        StringPacks m_StringPacks;
        Strings *m_CurrentStringPack{ nullptr };

        uint32_t m_LanguageIndex;

    public:
        Manager();

        void SetLanguage(Languages language);

        std::string GetString(StringID stringId) const;
    };

    Manager::Manager()
    {
        ifstream csvStringFile{ "strings.csv"s };
        assert(csvStringFile);

        if (csvStringFile) {
            while (!csvStringFile.eof()) {
                string line;
                getline(csvStringFile, line);

                if (line.size() > 0) {
                    stringstream lineStream{ line };

                    string stringIdText;
                    getline(lineStream, stringIdText, ',');

                    stringstream idStream{ stringIdText };
                    uint32_t stringId;
                    idStream >> stringId;

                    uint32_t languageId = 0;
                    string stringText;
                    while (getline(lineStream, stringText, ',')) {
                        m_StringPacks[languageId++][stringId] = stringText;
                    }
                }
            }
        }

        SetLanguage(Languages::EN_US);
    }

    void Manager::SetLanguage(Languages language)
    {
        m_CurrentStringPack = &(m_StringPacks[static_cast<uint32_t>(language)]);
    }

    std::string Manager::GetString(StringID stringId) const
    {
        stringstream resultStream;
        resultStream << "!!!"s;
        resultStream << stringId;
        resultStream << "!!!"s;
        string result{ resultStream.str() };

        auto iter = m_CurrentStringPack->find(stringId);
        if (iter != m_CurrentStringPack->end()) {
            result = iter->second;
        }

        return result;
    }
}