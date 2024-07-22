#pragma once

#include <array>
#include <cinttypes>
#include <string>
#include <unordered_map>
#include <sstream>

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
        static const uint32_t INDEX_EN_US{ static_cast<uint32_t>(Languages::EN_US) };
        m_StringPacks[INDEX_EN_US][STRING_COLOR] = "COLOR"s;

        static const uint32_t INDEX_EN_GB{ static_cast<uint32_t>(Languages::EN_GB) };
        m_StringPacks[INDEX_EN_GB][STRING_COLOR] = "COLOUR"s;

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