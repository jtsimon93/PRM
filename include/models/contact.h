#ifndef PRM_CONTACT_H
#define PRM_CONTACT_H

#include <string>
#include <ctime>
#include <optional>

class Contact {
public:
    int id;
    std::string firstName;
    std::string lastName;
    std::optional<std::string> middleName;
    std::optional<std::string> nickName;
    std::optional<std::string> relationship;
    std::optional<std::tm> birthDate = {};
    std::time_t createdAt;
    std::optional<std::time_t> updatedAt;

    Contact();
    Contact(int id, const std::string& firstName, const std::string& lastName, const std::string& middleName,
            const std::string& nickName, const std::string& relationship, const std::optional<std::tm>& birthDate,
            std::time_t createdAt, std::time_t updatedAt);
};

#endif // PRM_CONTACT_H
