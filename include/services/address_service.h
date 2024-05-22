#ifndef PRM_ADDRESS_SERVICE_H
#define PRM_ADDRESS_SERVICE_H

#include "iaddress_service.h"
#include "iaddress_repository.h"
#include <memory>
#include <vector>

class AddressService : public IAddressService {
public:
    explicit AddressService(std::shared_ptr<IAddressRepository> repository);

    int addAddress(const Address& address) override;
    std::vector<Address> getAllAddresses() override;
    Address getAddressById(int id) override;
    std::vector<Address> getAddressesByContactId(int contactId) override;
    void updateAddress(const Address& address) override;
    void removeAddress(int id) override;
};

#endif // PRM_ADDRESS_SERVICE_H