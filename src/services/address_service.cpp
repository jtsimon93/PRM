#include "address_service.h"
#include <iostream>

AddressService::AddressService(std::shared_ptr<IAddressRepository> repository)
        : repository(std::move(repository)) {
    std::cout << "AddressService created" << std::endl;
}

int AddressService::addAddress(const Address& address) {
    std::cout << "Adding address: " << address.streetAddress1 << std::endl;
    return repository->add(address);
}

std::vector<Address> AddressService::getAllAddresses() {
    std::cout << "Getting all addresses..." << std::endl;
    return repository->getAll();
}

Address AddressService::getAddressById(int id) {
    std::cout << "Getting address by ID: " << id << std::endl;
    return repository->getById(id);
}

std::vector<Address> AddressService::getAddressesByContactId(int contactId) {
    std::cout << "Getting addresses by contact ID: " << contactId << std::endl;
    return repository->getByContactId(contactId);
}

void AddressService::updateAddress(const Address& address) {
    std::cout << "Updating address: " << address.streetAddress1 << std::endl;
    repository->update(address);
}

void AddressService::removeAddress(int id) {
    std::cout << "Removing address by ID: " << id << std::endl;
    repository->remove(id);
}