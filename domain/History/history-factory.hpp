#ifndef HISTORY_FACTORY_HPP
#define HISTORY_FACTORY_HPP


#include <mongocxx/client.hpp>
#include "history.hpp"

using namespace std;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

namespace HistoryFactory {
    using Document = bsoncxx::builder::basic::document;

    Document inline addCallHistory(const History& history) {
        Document filter{};
        filter.append(
            kvp("dialedId", history.dialedId),
            kvp("dialedName", history.dialedName),
            kvp("dialedSurname", history.dialedSurname),
            kvp("callerPhoneNumber", history.callerPhoneNumber),
            kvp("dialedPhoneNumber", history.dialedNumber),
            kvp("date", bsoncxx::types::b_date{std::chrono::system_clock::now()})
        );

        return filter;
    }

    vector<History> inline getCallHistoryList(mongocxx::cursor& cursor) {
        vector<History> historyList{};
        for(auto& document : cursor) {
            History history;
            history.dialedId = document["_id"].get_oid().value.to_string();
            history.dialedName = document["dialedName"].get_string().value;
            history.dialedSurname = document["dialedSurname"].get_string().value;
            history.dialedNumber = document["dialedPhoneNumber"].get_string().value;
            history.callerPhoneNumber = document["callerPhoneNumber"].get_string().value;
            history.date = document["date"].get_date();
            historyList.push_back(history);
        }

        return historyList;
    }

}

#endif //HISTORY_FACTORY_HPP
