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

    Document inline addCallHistory(History& history) {
        Document filter{};
        filter.append(
            kvp("callerId", history.callerId),
            kvp("callerName", history.callerName),
            kvp("callerSurname", history.callerSurname),
            kvp("callerPhoneNumber", history.callerPhoneNumber),
            kvp("dialedPhoneNumber", history.dialedNumber),
            kvp("date", history.date)
        );

        return filter;
    }

    vector<History> inline getCallHistoryList(mongocxx::collection& collection, const string& phoneNumber) {
        bsoncxx::builder::basic::document filterBy_phoneNumber{};
        filterBy_phoneNumber.append(kvp("callerPhoneNumber", phoneNumber));

        auto cursor = collection.find({filterBy_phoneNumber.view()});

        vector<HistoryDto> historyList{};
        for(auto&& document : cursor) {
            History history;
            history.callerId = document["_id"].get_oid().value.to_string();
            history.callerName = document["callerName"].get_string().value;
            history.callerSurname = document["callerSurname"].get_string().value;
            history.callerPhoneNumber = document["callerPhoneNumber"].get_string().value;
            history.date = document["date"].get_string().value;
            historyList.push_back(history);
        }

        return historyList;
    }

}

#endif //HISTORY_FACTORY_HPP
