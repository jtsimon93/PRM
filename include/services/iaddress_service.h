#ifndef PRM_IADDRESS_SERVICE_H
#define PRM_IADDRESS_SERVICE_H

#include "address.h"
#include <vector>

class IAddressService {
public:
    virtual ~IAddressService() = default;

    virtual int addAddress(const Address& address) = 0;
    virtual std::vector<Address> getAllAddresses() = 0;
    virtual Address getAddressById(int id) = 0;
    virtual std::vector<Address> getAddressesByContactId(int contactId) = 0;
    virtual void updateAddress(const Address& address) = 0;
    virtual void removeAddress(int id) = 0;
};

#endif // PRM_IADDRESS_SERVICE_H