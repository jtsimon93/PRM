#ifndef PRM_ICONTACT_REPOSITORY_H
#define PRM_ICONTACT_REPOSITORY_H

#include "contact.h"
#include <vector>

class IContactRepository {
public:
    virtual ~IContactRepository() = default;

    virtual int add(const Contact& contact) = 0;
    virtual std::vector<Contact> getAll() = 0;
    virtual Contact getById(int id) = 0;
    virtual void update(const Contact& contact) = 0;
    virtual void remove(int id) = 0;
};

#endif // PRM_ICONTACT_REPOSITORY_H
