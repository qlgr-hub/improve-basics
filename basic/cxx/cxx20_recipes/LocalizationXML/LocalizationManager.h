#pragma once

#include <array>
#include <cinttypes>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <rapidxml/rapidxml.hpp>

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
        ifstream xmlStringFile{ "strings.xml"s };
        xmlStringFile.seekg(0, ios::end);
        uint32_t size{ static_cast<uint32_t>(xmlStringFile.tellg()) + 1 };
        char* buffer{ new char[size]{} };
        xmlStringFile.seekg(0, ios::beg);
        xmlStringFile.read(buffer, size);
        xmlStringFile.close();

        rapidxml::xml_document<> document;
        document.parse<0>(buffer);

        rapidxml::xml_node<>* workbook{ document.first_node("Workbook") };
        if (workbook != nullptr) {

            rapidxml::xml_node<>* worksheet{ workbook->first_node("Worksheet") };
            if (worksheet != nullptr) {

                rapidxml::xml_node<>* table{ worksheet->first_node("Table") };
                if (table != nullptr) {
                    
                    rapidxml::xml_node<>* row{ table->first_node("Row") };
                    while (row != nullptr) {
                        uint32_t stringId{ UINT32_MAX };

                        rapidxml::xml_node<>* cell{ row->first_node("Cell") };
                        if (cell != nullptr) {

                            rapidxml::xml_node<>* data{ cell->first_node("Data") };
                            if (data != nullptr) {
                                stringId = static_cast<uint32_t>(atoi(data->value()));
                            }
                        }

                        if (stringId != UINT32_MAX) {
                            uint32_t languageIndex{ 0 };

                            cell = cell->next_sibling("Cell");
                            while (cell != nullptr) {

                                rapidxml::xml_node<>* data{ cell->first_node("Data") };
                                if (data != nullptr) {
                                    m_StringPacks[languageIndex++][stringId] = data->value();
                                }

                                cell = cell->next_sibling("Cell");
                            }
                        }

                        row = row->next_sibling("Row");
                    }
                }
            }
        }

        delete[] buffer;
        buffer = nullptr;

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