#ifndef PRM_CONTACT_SERVICE_H
#define PRM_CONTACT_SERVICE_H

#include "icontact_service.h"
#include "icontact_repository.h"
#include <memory>
#include <vector>

class ContactService : public IContactService {
public:
    explicit ContactService(std::shared_ptr<IContactRepository> repository);

    void addContact(const Contact& contact) override;
    std::vector<Contact> getAllContacts() override;
    Contact getContactById(int id) override;
    void updateContact(const Contact& contact) override;
    void removeContact(int id) override;

private:
    std::shared_ptr<IContactRepository> repository;
};

#endif // PRM_CONTACT_SERVICE_H
