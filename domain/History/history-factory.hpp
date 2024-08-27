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
            kvp("dialedId", history.dialedId),
            kvp("dialedName", history.dialedName),
            kvp("dialedSurname", history.dialedSurname),
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

        vector<History> historyList{};
        for(auto&& document : cursor) {
            History history;
            history.dialedId = document["_id"].get_oid().value.to_string();
            history.dialedName = document["dialedName"].get_string().value;
            history.dialedSurname = document["dialedSurname"].get_string().value;
            history.dialedNumber = document["dialedPhoneNumber"].get_string().value;
            history.callerPhoneNumber = document["callerPhoneNumber"].get_string().value;
            history.date = document["date"].get_string().value;
            historyList.push_back(history);
        }

        return historyList;
    }

}

#endif //HISTORY_FACTORY_HPP
