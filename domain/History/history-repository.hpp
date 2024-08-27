#ifndef HISTORY_REPOSITORY_HPP
#define HISTORY_REPOSITORY_HPP


#include "history-factory.hpp"
#include "history.hpp"
#include "../../Infrastructure/mongodb-connection.hpp"

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

        bsoncxx::builder::basic::document filterBy_phoneNumber{};

        filterBy_phoneNumber.append(
       kvp("$or",
           make_array(
               make_document(kvp("callerPhoneNumber", phoneNumber)),
               make_document(kvp("dialedPhoneNumber", phoneNumber))
           )
       )
   );

        auto cursor = collection.find(filterBy_phoneNumber.view());

        return  HistoryFactory::getCallHistoryList(cursor);
    }

    void inline deleteCallHistoryById(const bsoncxx::oid& id) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb","Call Histories");

        Document filter{};
        filter.append(kvp("_id", id));

        collection.delete_one(filter.view());
    }

}


#endif //HISTORY_REPOSITORY_HPP
