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
            kvp("date", history.date)
        );

        return filter;
    }

}

#endif //HISTORY_FACTORY_HPP
