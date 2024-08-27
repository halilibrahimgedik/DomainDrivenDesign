#ifndef LIST_HISTORY_DTO_HPP
#define LIST_HISTORY_DTO_HPP

#include <string>
using namespace std;
class ListHistoryDto {
public:
    ListHistoryDto() = default;
    ListHistoryDto(string& callerName, string& callerSurname, string& dialedNumber, string& date):
            callerName(std::move(callerName)), callerSurname(std::move(callerSurname)),
            dialedNumber(std::move(dialedNumber)), date(std::move(date)) {}

    string callerName;
    string callerSurname;
    string dialedNumber;
    string date;
};

#endif //LIST_HISTORY_DTO_HPP
