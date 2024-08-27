#ifndef HISTORY_SERVICE_HPP
#define HISTORY_SERVICE_HPP

#include "history-factory.hpp"
#include "history-repository.hpp"
#include "list-history-dto.hpp"

using namespace std;

namespace HistoryService {

    using Document = bsoncxx::builder::basic::document;

    void inline addCallHistory(const History& history) {
        const Document document = HistoryFactory::addCallHistory(history);
        HistoryRepository::addCallHistory(document);
    }

    vector<ListHistoryDto> inline getCallHistoryByPhoneNumber(const string& phoneNumber) {
        const auto result = HistoryRepository::getCallHistoryListByPhoneNumber(phoneNumber);

        vector<ListHistoryDto> history_dtos;
        if(!result.empty()) {
            for (const auto& history : result) {
                ListHistoryDto history_dto;

                history_dto.callerName = history.dialedName;
                history_dto.callerSurname = history.dialedSurname;
                history_dto.dialedNumber = history.dialedNumber;
                history_dto.date = history.date;

                history_dtos.push_back(history_dto);
            }
        }

        return history_dtos;
    }

    void inline deleteCallHistoryById(const bsoncxx::oid& id) {
        HistoryRepository::deleteCallHistoryById(id);
    }
}

#endif //HISTORY_SERVICE_HPP
