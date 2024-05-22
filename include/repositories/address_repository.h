#ifndef PRM_ADDRESS_REPOSITORY_H
#define PRM_ADDRESS_REPOSITORY_H

#include "iaddress_repository.h"
#include "address.h"
#include <vector>
#include <sqlite_modern_cpp.h>
#include <memory>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
#include <iostream>

class AddressRepository : public IAddressRepository {
public:
    AddressRepository(const std::string& db_path);

    int add(const Address& address) override;
    std::vector<Address> getAll() override;
    Address getById(int id) override;
    std::vector<Address> getByContactId(int contactId) override;
    void update(const Address& address) override;
    void remove(int id) override;

private:
    std::shared_ptr<sqlite::database> db;

};

#endif // PRM_ADDRESS_REPOSITORY_H