#ifndef LIST_HISTORY_DTO_HPP
#define LIST_HISTORY_DTO_HPP

#include <string>
using namespace std;
class ListHistoryDto {
public:
    ListHistoryDto() = default;
    ListHistoryDto(string& callerName, string& callerSurname, string& dialedNumber, const chrono::system_clock::time_point date):
            callerName(std::move(callerName)), callerSurname(std::move(callerSurname)),
            dialedNumber(std::move(dialedNumber)), date(date) {}

    string callerName;
    string callerSurname;
    string dialedNumber;
    chrono::system_clock::time_point date;
};

#endif //LIST_HISTORY_DTO_HPP
