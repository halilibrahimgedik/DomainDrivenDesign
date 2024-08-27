#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "../domain/Contact/contact-service.hpp"
#include "../domain/History/history-service.hpp"
#include "../domain/History/history.hpp"

namespace ContactApplicationService {

    void inline addContact(const Contact& contact) {
        ContactService::addContact(contact);
    }

    vector<Contact> inline getContactList() {
        return ContactService::getContactList();
    }

    optional<Contact> inline getContactById(bsoncxx::oid& id) {
        return ContactService::getContactById(id);
    }

    void inline removeContact(bsoncxx::oid& id) {
        ContactService::removeContactById(id);
    }

    void inline updateContact(Contact& contact, const bsoncxx::oid& id) {
        ContactService::updateContact(contact, id);
    }


    inline string getTime() {
        // 1. Şu anki zamanı al
        const auto now = std::chrono::system_clock::now();

        // 2. Zamanı std::time_t türüne dönüştür
        const auto time = std::chrono::system_clock::to_time_t(now);

        // 3. Zamanı formatla
        stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }

    void inline makeCall(const string& callerNumber, const string& dialedNumber) {
        const auto optionalContact = ContactService::getContactByPhoneNumber(callerNumber);
        const auto& contact = optionalContact.value();

        History history;
        history.callerId = contact.id.to_string();
        history.callerName = contact.name;
        history.callerSurname = contact.surname;
        history.callerPhoneNumber = contact.phoneNumber;
        history.dialedNumber = dialedNumber;
        history.date = getTime();

        HistoryService::addCallHistory(history);
    }

    vector<History> inline getCallHistoryByPhoneNumber(const string& phoneNumber) {
        return HistoryService::getCallHistoryByPhoneNumber(phoneNumber);
    }

};

#endif //SERVICE_HPP
