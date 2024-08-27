#ifndef HISTORY_SERVICE_HPP
#define HISTORY_SERVICE_HPP

#include "history-factory.hpp"
#include "history-repository.hpp"

using namespace std;

namespace HistoryService {

    using Document = bsoncxx::builder::basic::document;

    void inline addCallHistory(History& history) {
        const Document document = HistoryFactory::addCallHistory(history);
        HistoryRepository::addCallHistory(document);
    }

    vector<History> inline getCallHistoryByPhoneNumber(const string& phoneNumber) {
        return HistoryRepository::getCallHistoryListByPhoneNumber(phoneNumber);
    }
}

#endif //HISTORY_SERVICE_HPP
