#include "contact_service.h"
#include <iostream>

ContactService::ContactService(std::shared_ptr<IContactRepository> repository)
        : repository(std::move(repository)) {
    std::cout << "ContactService created" << std::endl;
}

int ContactService::addContact(const Contact& contact) {
    std::cout << "Adding contact: " << contact.firstName << " " << contact.lastName << std::endl;
    return repository->add(contact);
}

std::vector<Contact> ContactService::getAllContacts() {
    std::cout << "Getting all contacts..." << std::endl;
    return repository->getAll();
}

Contact ContactService::getContactById(int id) {
    std::cout << "Getting contact by ID: " << id << std::endl;
    return repository->getById(id);
}

void ContactService::updateContact(const Contact& contact) {
    std::cout << "Updating contact: " << contact.firstName << " " << contact.lastName << std::endl;
    repository->update(contact);
}

void ContactService::removeContact(int id) {
    std::cout << "Removing contact by ID: " << id << std::endl;
    repository->remove(id);
}
