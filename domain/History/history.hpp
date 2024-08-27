#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
using namespace std;

class History {
public:
    History() = default;
    History(string& id, string& callerName, string& callerSurname, string& callerPhoneNumber, string dialedNumber, string& date):
            callerId(move(id)), callerName(std::move(callerName)), callerSurname(std::move(callerSurname)),
            callerPhoneNumber(std::move(callerPhoneNumber)), dialedNumber(move(dialedNumber)), date(std::move(date)) {}

    string callerId;
    string callerName;
    string callerSurname;
    string callerPhoneNumber;
    string dialedNumber;
    string date;
};

#endif //HISTORY_HPP
