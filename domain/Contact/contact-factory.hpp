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

    std::vector<Contact> inline getContactList(mongocxx::collection &collection) {
        auto cursor = collection.find({});

        vector<Contact> contactList;

        for (auto&& doc: cursor) {
            Contact contact;
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

    // Bunlar Gereksiz mi ?, Repository'de mi yapılmalı ?, çünkü nesne üretmiyoruz ?,
    // Update için yazmadım
    Document inline deleteContactById(bsoncxx::oid &id) {
        Document filter{};
        filter.append(kvp("_id", id));

        return filter;
    }

    std::optional<Contact> inline getContactById(bsoncxx::oid& id, mongocxx::collection& collection) {
        Document document{};
        document.append(kvp("_id", id));

        const auto result = collection.find_one(document.view());

        if (result) {
            const auto& doc = *result;
            Contact contact;
            contact.name = doc["name"].get_value().get_string().value;
            contact.surname = doc["surname"].get_value().get_string().value;
            contact.phoneNumber = doc["phoneNumber"].get_string().value;
            contact.email = doc["email"].get_value().get_string().value;
            contact.city = doc["city"].get_value().get_string().value;
            contact.country = doc["country"].get_value().get_string().value;
            contact.address = doc["address"].get_value().get_string().value;

            return contact;
        }

        return nullopt;
    }

};

#endif //CONTACT_FACTORY_HPP
