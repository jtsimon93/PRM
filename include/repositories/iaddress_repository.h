#ifndef PRM_IADDRESS_REPOSITORY_H
#define PRM_IADDRESS_REPOSITORY_H

#include "address.h"
#include <vector>

class IAddressRepository {
public:
    virtual ~IAddressRepository() = default;

    virtual int add(const Address& address) = 0;
    virtual std::vector<Address> getAll() = 0;
    virtual Address getById(int id) = 0;
    virtual std::vector<Address> getByContactId(int contactId) = 0;
    virtual void update(const Address& address) = 0;
    virtual void remove(int id) = 0;
};


#endif // PRM_IADDRESS_REPOSITORY_H