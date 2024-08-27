#ifndef HISTORY_REPOSITORY_HPP
#define HISTORY_REPOSITORY_HPP


#include "history-factory.hpp"
#include "history.hpp"
#include "../MongoDbConnection.hpp"

using namespace std;

namespace HistoryRepository {
    using Document = bsoncxx::builder::basic::document;

    void inline addCallHistory(const Document& addCallHistoryDocument) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb","Call Histories");

        collection.insert_one(addCallHistoryDocument.view());
    }

    vector<History> inline getCallHistoryListByPhoneNumber(const string& phoneNumber) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb","Call Histories");

        return  HistoryFactory::getCallHistoryList(collection, phoneNumber);
    }

}


#endif //HISTORY_REPOSITORY_HPP
