#ifndef CONTACT_HPP
#define CONTACT_HPP

using namespace std;

class Contact {
public:
    Contact() = default;
    Contact(string name, string surname, string phoneNumber,
            string email, string city, string country,
            string address)
        : name(std::move(name)), surname(std::move(surname)), phoneNumber(std::move(phoneNumber)), email(std::move(email)), city(std::move(city)),
          country(std::move(country)), address(std::move(address)) {}

    std::string name;
    std::string surname;
    std::string phoneNumber;
    std::string email;
    std::string city;
    std::string country;
    std::string address;
};


#endif //CONTACT_HPP
