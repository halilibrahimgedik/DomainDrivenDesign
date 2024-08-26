#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "../domain/contact-service.hpp"
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

};

#endif //SERVICE_HPP
