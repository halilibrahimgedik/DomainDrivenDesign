#ifndef CONTACT_FACTORY_HPP
#define CONTACT_FACTORY_HPP

#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include "contact.hpp"
#include <bsoncxx/json.hpp>

using namespace std;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

namespace ContactFactory {
    using Document = bsoncxx::builder::basic::document;

    std::vector<Contact> inline getContactList(mongocxx::cursor& cursor) {
        vector<Contact> contactList;

        for (auto& doc: cursor) {
            Contact contact;
            contact.id = doc["_id"].get_oid().value;
            contact.name = doc["name"].get_string().value;
            contact.surname = doc["surname"].get_string().value;
            contact.phoneNumber = doc["phoneNumber"].get_string().value;
            contact.email = doc["email"].get_string().value;
            contact.city = doc["city"].get_string().value;
            contact.country = doc["country"].get_string().value;
            contact.address = doc["address"].get_string().value;
            contactList.push_back(contact);
        }

        return contactList;
    }

    Document inline addContact(const Contact &contact) {
        Document doc{};
        doc.append(
            kvp("name", contact.name),
            kvp("surname", contact.surname),
            kvp("phoneNumber", contact.phoneNumber),
            kvp("email", contact.email),
            kvp("city", contact.city),
            kvp("country", contact.country),
            kvp("address", contact.address)
        );

        return doc;
    }

    Contact inline getContactById(const bsoncxx::document::value& document) {
            Contact contact;
            contact.id = document["_id"].get_oid().value;
            contact.name = document["name"].get_value().get_string().value;
            contact.surname = document["surname"].get_value().get_string().value;
            contact.phoneNumber = document["phoneNumber"].get_string().value;
            contact.email = document["email"].get_value().get_string().value;
            contact.city = document["city"].get_value().get_string().value;
            contact.country = document["country"].get_value().get_string().value;
            contact.address = document["address"].get_value().get_string().value;

        return contact;
    }

    std::optional<Contact> inline getContactByPhoneNumber(const bsoncxx::document::value& docValue) {
            const auto& doc = docValue;
            Contact contact;
            contact.id = doc["_id"].get_oid().value;
            contact.name = doc["name"].get_value().get_string().value;
            contact.surname = doc["surname"].get_value().get_string().value;
            contact.phoneNumber = doc["phoneNumber"].get_string().value;
            contact.email = doc["email"].get_value().get_string().value;
            contact.city = doc["city"].get_value().get_string().value;
            contact.country = doc["country"].get_value().get_string().value;
            contact.address = doc["address"].get_value().get_string().value;

            return contact;
    }

};

#endif //CONTACT_FACTORY_HPP
