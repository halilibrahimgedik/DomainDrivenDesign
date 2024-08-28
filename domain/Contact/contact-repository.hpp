#ifndef CONTACT_REPOSITORY_HPP
#define CONTACT_REPOSITORY_HPP

#include "contact-factory.hpp"
#include "contact.hpp"
#include "../../Infrastructure/mongodb-connection.hpp"

using namespace std;

namespace ContactRepository {
    using Document = bsoncxx::builder::basic::document;

    void inline addContact(const Document& document) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        collection.insert_one(document.view());
    }

    vector<Contact> inline getContactList() {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        auto cursor = collection.find({});
        const auto contactList = ContactFactory::getContactList(cursor);

        return contactList;
    }

    Contact inline getContactById(const bsoncxx::oid& id) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        Document document{};
        document.append(kvp("_id", id));

        const auto result = collection.find_one(document.view());

        auto contact = ContactFactory::getContactById(result.value());

        return contact;
    }

    void inline deleteContact(bsoncxx::oid& id) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        Document filter{};
        filter.append(kvp("_id", id));

        collection.delete_one(filter.view());
    }

    void inline updateContact(Contact& contact) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        Document filter{};
        filter.append(kvp("_id", contact.id));

        Document update{};
        update.append(kvp("$set",
            make_document(
                    kvp("name", contact.name),
                    kvp("surname", contact.surname),
                    kvp("phoneNumber", contact.phoneNumber),
                    kvp("email", contact.email),
                    kvp("city", contact.city),
                    kvp("country", contact.country),
                    kvp("address", contact.address))
                ));

        collection.update_one(filter.view(), update.view());
    }

    Contact inline getContactByPhoneNumber(const string& phoneNumber) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        Document document{};
        document.append(kvp("phoneNumber", phoneNumber));

        const auto result = collection.find_one(document.view());

        auto contact = ContactFactory::getContactByPhoneNumber(result.value());

        return contact.value();
    }

    bool inline any(const bsoncxx::oid& id) {
        const MongoDBConnection& dbConnection = MongoDBConnection::getInstance();
        auto collection = dbConnection.getCollection("ContactDb", "Contacts");

        bsoncxx::builder::basic::document filter{};
        filter.append(kvp("_id", id));

        auto cursor = collection.find(filter.view());

        return cursor.begin() != cursor.end();
    }

};

#endif //CONTACT_REPOSITORY_HPP
