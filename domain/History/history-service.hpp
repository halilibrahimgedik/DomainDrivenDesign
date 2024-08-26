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
}

#endif //HISTORY_SERVICE_HPP
