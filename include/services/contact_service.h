#ifndef PRM_CONTACT_SERVICE_H
#define PRM_CONTACT_SERVICE_H

#include "contact.h"
#include "contact_repository.h"
#include <memory>
#include <vector>

class ContactService {
public:
    ContactService(std::shared_ptr<ContactRepository> repository);

    void addContact(const Contact& contact);
    std::vector<Contact> getAllContacts();
    Contact getContactById(int id);
    void updateContact(const Contact& contact);
    void removeContact(int id);

private:
    std::shared_ptr<ContactRepository> repository;
};

#endif // PRM_CONTACT_SERVICE_H
