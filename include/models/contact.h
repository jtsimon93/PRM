#ifndef PRM_CONTACT_H
#define PRM_CONTACT_H

#include <string>
#include <ctime>

class Contact {
public:
    int id;
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string nickName;
    std::string relationship;
    std::tm birthDate = {};
    std::time_t createdAt;
    std::time_t updatedAt;

    Contact();
    Contact(int id, const std::string& firstName, const std::string& lastName, const std::string& middleName,
            const std::string& nickName, const std::string& relationship, const std::tm& birthDate,
            std::time_t createdAt, std::time_t updatedAt);
};

#endif // PRM_CONTACT_H
