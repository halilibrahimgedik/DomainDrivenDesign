#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
using namespace std;

class History {
public:
    History() = default;
    History(string& id, string& callerName, string& callerSurname, string& callerPhoneNumber, string dialedNumber, string& date):
            dialedId(move(id)), dialedName(std::move(callerName)), dialedSurname(std::move(callerSurname)),
            callerPhoneNumber(std::move(callerPhoneNumber)), dialedNumber(move(dialedNumber)), date(std::move(date)) {}

    string dialedId;
    string dialedName;
    string dialedSurname;
    string callerPhoneNumber;
    string dialedNumber;
    string date;
};

#endif //HISTORY_HPP
