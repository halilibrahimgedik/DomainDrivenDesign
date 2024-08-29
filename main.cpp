#include <iostream>
#include <vector>
#include "application/contact-application-service.hpp"
#include "domain/Contact/contact.hpp"
#include <crow.h>
#include <string>

#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#include <valijson/adapters/rapidjson_adapter.hpp>


using namespace std;

int main() {
    crow::SimpleApp app;

    // --- Contact Ekleme ---
    CROW_ROUTE(app, "/contacts").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        const auto values = crow::json::load(req.body);
        if (!values) {
            return crow::response{400, "Bad Request !!!"};
        }

        if (!values.has("name") || !values.has("surname") || !values.has("phoneNumber") ||
            !values.has("email") || !values.has("city") || !values.has("country") || !values.has("address")) {
            return crow::response{400, "Bad Request !"};
        }

        if (values["name"] == "" || values["surname"] == "" || values["phoneNumber"] == "" || values["email"] == "" ||
            values["city"] == "" || values["country"] == "" || values["address"] == "") {
            return crow::response{400, "Bad Request !. Empty field error."};
        }

        const Contact newContact{
            values["name"].s(), values["surname"].s(), values["phoneNumber"].s(),
            values["email"].s(), values["city"].s(), values["country"].s(), values["address"].s()
        };

        ContactApplicationService::addContact(newContact);

        return crow::response{201, "Created a contact"};
    });

    // --- Contact Listesi ---
    CROW_ROUTE(app, "/contacts").methods(crow::HTTPMethod::Get)([]() {
        std::vector<crow::json::wvalue> contactList;
        crow::json::wvalue contactJson;

        for (const auto &contact: ContactApplicationService::getContactList()) {
            contactJson["id"] = contact.id.to_string();
            contactJson["name"] = contact.name;
            contactJson["surname"] = contact.surname;
            contactJson["phoneNumber"] = contact.phoneNumber;
            contactJson["email"] = contact.email;
            contactJson["city"] = contact.city;
            contactJson["country"] = contact.country;
            contactJson["address"] = contact.address;

            contactList.push_back(contactJson);
        }
        const auto response = crow::json::wvalue(contactList);

        return response;
    });

    // --- id ile Contact Bilgisini Getirme ---
    CROW_ROUTE(app, "/contacts/<string>").methods(crow::HTTPMethod::Get)([](const string &id) {
        const bsoncxx::oid bsonId{id};

        auto contact = ContactApplicationService::getContactById(bsonId);
        crow::json::wvalue response;

        response["id"] = contact.id.to_string();
        response["name"] = contact.name;
        response["surname"] = contact.surname;
        response["phoneNumber"] = contact.phoneNumber;
        response["email"] = contact.email;
        response["city"] = contact.city;
        response["country"] = contact.country;
        response["address"] = contact.address;

        return crow::response{200, response};
    });

    // ---Contact Silme---
    CROW_ROUTE(app, "/contacts/<string>").methods(crow::HTTPMethod::Delete)([](const string &id) {
        if (id.empty()) {
            return crow::response{400, "Bad Request"};
        }

        bsoncxx::oid bsonId{id};
        if (!ContactApplicationService::any(bsonId)) {
            return crow::response{404, "Contact Not Found"};
        }

        ContactApplicationService::removeContact(bsonId);

        return crow::response{204, "Contact Deleted"};
    });

    // --- Contact Güncelleme ---
    CROW_ROUTE(app, "/contacts").methods(crow::HTTPMethod::Put)([](const crow::request &req) {
        const auto contact = crow::json::load(req.body);
        if (!contact) {
            return crow::response{400, "Bad Request !"};
        }

        const string id = contact["id"].s();
        const bsoncxx::oid bsonId{id};

        Contact updatedContact{
            bsonId, contact["name"].s(), contact["surname"].s(),
            contact["phoneNumber"].s(), contact["email"].s(),
            contact["city"].s(), contact["country"].s(), contact["address"].s()
        };

        ContactApplicationService::updateContact(updatedContact);

        return crow::response{204, "User with id:" + bsonId.to_string() + "has been updated"};
    });


    // --- Arama Yapma ---
    CROW_ROUTE(app, "/makecalls").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        const auto values = crow::json::load(req.body);
        if (!values) {
            return crow::response{400, "Bad Request !"};
        }

        const string dialedNumber = values["dialedNumber"].s();
        const string callerNumber = values["callerNumber"].s();
        Contact contact = ContactApplicationService::getContactByPhoneNumber(dialedNumber);

        History history{
            contact.id.to_string(), contact.name, contact.surname, callerNumber,
            contact.phoneNumber, chrono::system_clock::now()
        };

        ContactApplicationService::makeCall(history);

        return crow::response(200, "calling" + contact.name + "(" + contact.phoneNumber + ")");
    });

    // --- Arama Geçmişi Listeleme ---
    CROW_ROUTE(app, "/histories").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        const auto value = crow::json::load(req.body);
        if (!value) {
            return crow::response{400, "Bad Request!"};
        }

        const std::string phoneNumber = value["phoneNumber"].s();
        std::vector<crow::json::wvalue> historyList;

        for (const auto &history: ContactApplicationService::getCallHistoryByPhoneNumber(phoneNumber)) {
            historyList.emplace_back(
                crow::json::wvalue{
                {"callerName", history.callerName},
                {"callerSurname", history.callerSurname},
                {"dialedNumber", history.dialedNumber},
                {"date", history.date.time_since_epoch().count()}
            });
        }

        crow::json::wvalue response;
        response["CallHistory"] = std::move(historyList);

        return crow::response{response};
    });

    // --- Arama Geçmişi Silme ---
    CROW_ROUTE(app, "/histories").methods(crow::HTTPMethod::Delete)([](const crow::request &req) {
        const auto value = crow::json::load(req.body);
        if (!value) {
            return crow::response{400, "Bad Request !"};
        }
        const string id = value["id"].s();
        const bsoncxx::oid bsonId{id};

        ContactApplicationService::deleteCallHistoryById(bsonId);

        return crow::response{204, "Call Deleted"};
    });

    app.port(5001).multithreaded().run();
}
