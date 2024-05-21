#ifndef PRM_CONTACT_REPOSITORY_H
#define PRM_CONTACT_REPOSITORY_H

#include "icontact_repository.h"
#include "contact.h"
#include <vector>
#include <sqlite_modern_cpp.h>
#include <memory>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>

class ContactRepository : public IContactRepository {
public:
    ContactRepository(const std::string& db_path);

    int add(const Contact& contact) override;
    std::vector<Contact> getAll() override;
    Contact getById(int id) override;
    void update(const Contact& contact) override;
    void remove(int id) override;

private:
    std::shared_ptr<sqlite::database> db;

    std::string formatDate(const std::optional<std::tm>& tm);
    std::tm parseDate(const std::string& date);
};

#endif // PRM_CONTACT_REPOSITORY_H
