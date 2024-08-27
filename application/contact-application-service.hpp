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

    Contact inline getContactById(bsoncxx::oid& id) {
        return ContactService::getContactById(id);
    }

    void inline removeContact(bsoncxx::oid& id) {
        ContactService::removeContactById(id);
    }

    void inline updateContact(Contact& contact, const bsoncxx::oid& id) {
        ContactService::updateContact(contact, id);
    }

    Contact inline getContactByPhoneNumber(const string& phoneNumber) {
        return ContactService::getContactByPhoneNumber(phoneNumber);
    }

    void inline makeCall(const History& history) {
        HistoryService::addCallHistory(history);
    }

    vector<ListHistoryDto> inline getCallHistoryByPhoneNumber(const string& phoneNumber) {
        return HistoryService::getCallHistoryByPhoneNumber(phoneNumber);
    }

    void inline deleteCallHistoryById(const bsoncxx::oid& id) {
        HistoryService::deleteCallHistoryById(id);
    }

};

#endif //SERVICE_HPP
