#ifndef PRM_CONTACT_REPOSITORY_H
#define PRM_CONTACT_REPOSITORY_H

#include "contact.h"
#include <vector>
#include <sqlite_modern_cpp.h>
#include <memory>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>

class ContactRepository {
public:
    ContactRepository(const std::string& db_path);

    void add(const Contact& contact);
    std::vector<Contact> getAll();
    Contact getById(int id);
    void update(const Contact& contact);
    void remove(int id);

private:
    std::shared_ptr<sqlite::database> db;

    std::string formatDate(const std::tm& tm);
    std::tm parseDate(const std::string& date);
};

#endif // PRM_CONTACT_REPOSITORY_H
