#ifndef CONTACT_SERVICE_HPP
#define CONTACT_SERVICE_HPP

#include "contact-repository.hpp"
#include "contact-factory.hpp"

namespace ContactService {
    using Document = bsoncxx::builder::basic::document;

    void inline addContact(const Contact& contact) {
        const Document document = ContactFactory::addContact(contact);
        ContactRepository::addContact(document);
    }

    vector<Contact> inline getContactList() {
        return ContactRepository::getContactList();
    }

    Contact inline getContactById(bsoncxx::oid& id) {
        return ContactRepository::getContactById(id);
    }

    void inline removeContactById(bsoncxx::oid& id) {
        ContactRepository::deleteContact(id);
    }

    void inline updateContact(Contact& contact, const bsoncxx::oid& id) {
        ContactRepository::updateContact(contact, id);
    }

    Contact inline getContactByPhoneNumber(const string& phoneNumber) {
        return ContactRepository::getContactByPhoneNumber(phoneNumber);
    }
};

#endif //CONTACT_SERVICE_HPP
