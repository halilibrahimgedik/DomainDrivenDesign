#include <iostream>
#include <vector>
#include "application/contact-application-service.hpp"
#include "domain/Contact/contact.hpp"

using namespace std;

void printContacts(const vector<Contact>& contacts) {
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
void printCallHistory(const vector<ListHistoryDto>& callHistory) {
    for(const auto& history : callHistory) {
        cout << endl;
        cout << "name: " << history.callerName << endl;
        cout << "surname: " << history.callerSurname << endl;
        cout << "dialed number: " << history.dialedNumber << endl;
        cout << "date: " << history.date << endl;
    }
}

void makeCall(const string& callerPhoneNumber, const string& dialedPhoneNumber) {
    Contact contact = ContactApplicationService::getContactByPhoneNumber(callerPhoneNumber); // dialed phone number
    History history{contact.id.to_string(),contact.name,contact.surname,dialedPhoneNumber,
                        contact.phoneNumber};
    ContactApplicationService::makeCall(history);
}

int main() {
    // ---Contact Ekleme---
    /*const Contact contact{"Hakan","Zengin", "0543 455 15 23", "hakanzengin@gmal.com","İstanbul","Türkiye","test adres"};
    ContactApplicationService::addContact(contact);*/


    // ---Contact Listesini getirme---
    // printContacts(ContactApplicationService::getContactList());


    // ---Contact Silme---
    /*auto id = bsoncxx::oid{"66cc4e6dcd73abdf4f69c555"};
    ContactApplicationService::removeContact(id);*/


    // ---id'ye göre Contact bilgilerini getirme---
    /*bsoncxx::oid contactId {"66cc4e6dcd73abdf4f69c283"};
    const auto contact = ContactApplicationService::getContactById(contactId);
    printContact(contact);*/


    // --- Contact Güncelleme ---
    /*Contact updateContact{"Halil İbrahim", "Gedik", "0589 000 00 00", "gedik@gmail.com","İstanbul","Türkiye", "qwer cad. / vadire sk. / no:87 / Ümraniye - Türkiye"};
    const bsoncxx::oid id{"66cc4e6dcd73abdf4f69c283"};
    ContactApplicationService::updateContact(updateContact, id);
    printContact(updateContact);*/


    // --- Arama Yapma ---
    makeCall("0533 333 33 33", "0542 222 22 22");


    // --- Arama Geçmişi Listeleme ---
    printCallHistory(ContactApplicationService::getCallHistoryByPhoneNumber("0533 333 33 33"));


    // --- Arama Geçmişi Silme ---
    /*const bsoncxx::oid id{"66cd8e70401b05a5f905c992"};
    ContactApplicationService::deleteCallHistoryById(id);
    printCallHistory(ContactApplicationService::getCallHistoryByPhoneNumber("0589 000 00 00"));*/

}