#include "contact_service.h"

ContactService::ContactService(std::shared_ptr<ContactRepository> repository)
        : repository(repository) {}

void ContactService::addContact(const Contact& contact) {
    repository->add(contact);
}

std::vector<Contact> ContactService::getAllContacts() {
    return repository->getAll();
}

Contact ContactService::getContactById(int id) {
    return repository->getById(id);
}

void ContactService::updateContact(const Contact& contact) {
    repository->update(contact);
}

void ContactService::removeContact(int id) {
    repository->remove(id);
}
