#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <chrono>
#include <string>
using namespace std;

class History {
public:
    History() = default;
    History(const bsoncxx::oid& id, string& callerName, string& callerSurname, string& callerPhoneNumber, string& date):
            callerId(id), callerName(std::move(callerName)), callerSurname(std::move(callerSurname)),
            callerPhoneNumber(std::move(callerPhoneNumber)),date(std::move(date)) {}

    bsoncxx::oid callerId;
    string callerName;
    string callerSurname;
    string callerPhoneNumber;
    string date;
};

#endif //HISTORY_HPP
