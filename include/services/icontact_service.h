#ifndef PRM_ICONTACT_SERVICE_H
#define PRM_ICONTACT_SERVICE_H

#include "contact.h"
#include <vector>

class IContactService {
public:
    virtual ~IContactService() = default;

    virtual int addContact(const Contact& contact) = 0;
    virtual std::vector<Contact> getAllContacts() = 0;
    virtual Contact getContactById(int id) = 0;
    virtual void updateContact(const Contact& contact) = 0;
    virtual void removeContact(int id) = 0;
};

#endif // PRM_ICONTACT_SERVICE_H
