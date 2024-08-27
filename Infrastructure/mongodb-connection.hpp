#ifndef MONGODB_CONNECTION_HPP
#define MONGODB_CONNECTION_HPP


#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <string>
using namespace std;

class MongoDBConnection {
public:
    static MongoDBConnection& getInstance() {
        static MongoDBConnection instance;
        return instance;
    }

    mongocxx::client& getClient() {
        return client;
    }

    [[nodiscard]] mongocxx::database getDatabase(const string& dbName) const{
        return client.database(dbName);
    }

    [[nodiscard]] mongocxx::collection getCollection(const string& databaseName, const string& collectionName) const{
        const auto database = getDatabase(databaseName);
        return database[collectionName];
    }

private:
    MongoDBConnection() : client{mongocxx::uri{"mongodb://localhost:27017"}} {}
    mongocxx::client client;
};

#endif //MONGODB_CONNECTION_HPP
