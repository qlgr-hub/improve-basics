
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

struct Journal {
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(const std::string& title) : title{ title } {
    }

    void add(const std::string& entry) {
        static int count{ 1 };
        entries.push_back(boost::lexical_cast<std::string>(count++)
            + ":" + entry);
    }

    // The journal class is only used to manage log entries, 
    // and persistence should not be its responsibility.
    //
    // void save(const std::string& filename) {
    //     std::ofstream ofs(filename);
    //     for (auto& s : entries)
    //         ofs << s << '\n';
    // }
};

struct PersistenceManager {
    static void save(const Journal& j, const std::string& filename) {
        std::ofstream ofs(filename);
        for (auto& s : j.entries)
            ofs << s << '\n';
    }
};
