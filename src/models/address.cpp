#include "address.h"

Address::Address()
        : id(0), contactId(0), streetAddress1(""), streetAddress2(""), city(""), state(""), zip(""), createdAt(0),
          updatedAt(0) {
    std::time_t now = std::time(0);
    createdAt = now;
    updatedAt = now;
}

Address::Address(int id, int contactId, const std::string &streetAddress1,
                 const std::optional<std::string> &streetAddress2,
                 const std::optional<std::string> &city, const std::optional<std::string> &state,
                 const std::optional<std::string> &zip,
                 std::time_t createdAt, std::optional<std::time_t> updatedAt) : id(id), contactId(contactId),
                                                                                streetAddress1(streetAddress1),
                                                                                streetAddress2(streetAddress2),
                                                                                city(city), state(state), zip(zip),
                                                                                createdAt(createdAt),
                                                                                updatedAt(updatedAt) {

}

{
}