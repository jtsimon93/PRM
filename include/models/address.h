#ifndef PRM_ADDRESS_H
#define PRM_ADDRESS_H

#include <string>
#include <ctime>
#include <optional>

class Address {
public:
    int id;
    int contactId;
    std::string streetAddress1;
    std::optional<std::string> streetAddress2;
    std::optional<std::string> city;
    std::optional<std::string> state;
    std::optional<std::string> zip;
    std::time_t createdAt;
    std::optional<std::time_t> updatedAt;

    Address();

    Address(int id, int contactId, const std::string &streetAddress1, const std::optional<std::string> &streetAddress2,
            const std::optional<std::string> &city, const std::optional<std::string> &state,
            const std::optional<std::string> &zip,
            std::time_t createdAt, std::optional<std::time_t> updatedAt);
};


#endif // PRM_ADDRESS_H