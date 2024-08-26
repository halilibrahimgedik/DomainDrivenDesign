
#ifndef MONGODBCONNECTION_HPP
#define MONGODBCONNECTION_HPP

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

class MongoDBConnection {
public:
    static mongocxx::client& getClient() {
        static mongocxx::instance instance{};
        static mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
        return client;
    }

    static mongocxx::database getDatabase(const std::string& dbName) {
        return getClient().database(dbName);
    }
};


#endif //MONGODBCONNECTION_HPP
