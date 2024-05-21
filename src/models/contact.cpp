#include "contact.h"

Contact::Contact()
        : id(0), firstName(""), lastName(""), middleName(""), nickName(""), relationship(""), createdAt(0), updatedAt(0)
{
    std::time_t now = std::time(0);
    createdAt = now;
    updatedAt = now;
}

Contact::Contact(int id, const std::string& firstName, const std::string& lastName, const std::string& middleName,
                 const std::string& nickName, const std::string& relationship, const std::optional<std::tm>& birthDate,
                 std::time_t createdAt, std::time_t updatedAt)
        : id(id), firstName(firstName), lastName(lastName), middleName(middleName), nickName(nickName),
          relationship(relationship), birthDate(birthDate), createdAt(createdAt), updatedAt(updatedAt)
{
}
