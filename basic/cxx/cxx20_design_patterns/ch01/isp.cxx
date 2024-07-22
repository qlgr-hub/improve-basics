
#include <vector>

struct Document {
};

// The interface is too bloated and inflexible to use.
// struct IMachine {
//     virtual void print(std::vector<Document*>& docs) = 0;
//     virtual void fax(std::vector<Document*>& docs) = 0;
//     virtual void scan(std::vector<Document*>& docs) = 0;
// };
//
//
// struct MyFavouritePrinter : public IMachine {
//     void print(std::vector<Document*>& docs) override;
//     void fax(std::vector<Document*>& docs) override;
//     void scan(std::vector<Document*>& docs) override;
// };


struct IPrinter {
    virtual void print(std::vector<Document*>& docs) = 0;
};

struct IScanner {
    virtual void scan(std::vector<Document*>& docs) = 0;
};

struct IMachine : public IPrinter, public IScanner {
};

struct Machine : public IMachine {
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner)
        : printer{ printer }, scanner{ scanner } {
    }

    void print(std::vector<Document*>& docs) override {
        printer.print(docs);
    }

    void scan(std::vector<Document*>& docs) override {
        scanner.scan(docs);
    }
};