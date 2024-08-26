#include <iostream>

#include "application/contact-application-service.hpp"

using namespace std;

void printContacts(const vector<Contact> &contacts) {
    for(const auto& contact : contacts) {
        std::cout << endl;
        std::cout << contact.name << endl;
        std::cout << contact.surname << endl;
        std::cout << contact.phoneNumber << endl;
        std::cout << contact.email << endl;
        std::cout << contact.city << endl;
        std::cout << contact.country << endl;
        std::cout << contact.address << endl;
    }
}

void printContact(const Contact& contact) {
    std::cout << endl;
    std::cout << contact.name << endl;
    std::cout << contact.surname << endl;
    std::cout << contact.phoneNumber << endl;
    std::cout << contact.email << endl;
    std::cout << contact.city << endl;
    std::cout << contact.country << endl;
    std::cout << contact.address << endl;
}
int main() {
    // ---Contact Ekleme---
    /*const Contact contact{"Hakan","Zengin", "0543 455 15 23", "hakanzengin@gmal.com","İstanbul","Türkiye","test adres"};
    ContactApplicationService::addContact(contact);*/


    // ---Contact Listesini getirme---
    printContacts(ContactApplicationService::getContactList());
    cout << "\n----------------------------------------------------" << endl;


    // ---Contact Silme---
    /*auto id = bsoncxx::oid{"66cc4e6dcd73abdf4f69c555"};
    ContactApplicationService::removeContact(id);*/


    // ---id'ye göre Contact bilgilerini getirme---
    /*bsoncxx::oid contactId {"66cc4e6dcd73abdf4f69c283"};
    const auto contact = ContactApplicationService::getContactById(contactId);
    printContact(contact);*/


    // --- Contact Güncelleme ---
    /*Contact updateContact{"Halil İbrahim", "Gedik", "0589 444 85 21", "gedikhalil@gmail.com", "İstanbul",
                        "Türkiye", "qwer cad. / vadire sk. / no:87 / Çekmeköy - İstanbul"};

    const bsoncxx::oid id{"66cc4e6dcd73abdf4f69c283"};
    ContactApplicationService::updateContact(updateContact, id);
    printContact(updateContact);*/

}