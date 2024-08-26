#ifndef CONTACT_REPOSITORY_HPP
#define CONTACT_REPOSITORY_HPP

#include "contact-factory.hpp"
#include "contact.hpp"
#include "../MongoDbConnection.hpp"

using namespace std;

namespace ContactRepository {
    using Document = bsoncxx::builder::basic::document;

    mongocxx::collection inline getContactCollection() {
        const auto database = MongoDBConnection::getDatabase("ContactDb");
        return database["Contacts"];
    }

    void inline addContact(const Document& document) {
        auto collection = getContactCollection();
        collection.insert_one(document.view());
    }

    vector<Contact> inline getContactList() {
        auto collection = getContactCollection();
        const auto contactList = ContactFactory::getContactList(collection);

        return contactList;
    }

    optional<Contact> inline getContactById(bsoncxx::oid& id) {
        auto collection = getContactCollection();
        auto contact = ContactFactory::getContactById(id, collection);

        if (contact)
            return contact.value();

        return nullopt;
    }

    void inline deleteContact(const Document& document) {
        auto collection = getContactCollection();
        collection.delete_one(document.view());
    }

    void inline updateContact(Contact& contact, const bsoncxx::oid id) {
        auto collection = getContactCollection();

        Document filter{};
        filter.append(kvp("_id", id));

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

};

#endif //CONTACT_REPOSITORY_HPP
