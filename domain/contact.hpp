#include <utility>

#ifndef CONTACT_HPP
#define CONTACT_HPP

class Contact {
public:
    Contact() = default;
    Contact(std::string name, const std::string& surname, const std::string& phoneNumber,
            const std::string& email, const std::string& city, const std::string& country,
            const std::string& address)
        : name(std::move(name)), surname(surname), phoneNumber(phoneNumber), email(email), city(city),
          country(country), address(address) {}

    std::string name;
    std::string surname;
    std::string phoneNumber;
    std::string email;
    std::string city;
    std::string country;
    std::string address;
};


#endif //CONTACT_HPP
