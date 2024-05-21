#include "contact_repository.h"
#include <iostream>

ContactRepository::ContactRepository(const std::string& db_path) {
    std::cout << "Opening database: " << db_path << "\n";
    db = std::make_shared<sqlite::database>(db_path);
    *db << R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            firstName TEXT,
            lastName TEXT,
            middleName TEXT,
            nickName TEXT,
            relationship TEXT,
            birthDate TEXT,
            createdAt INTEGER,
            updatedAt INTEGER
        );
    )";
    std::cout << "Database opened." << std::endl;
}

int ContactRepository::add(const Contact& contact) {
    *db << R"(INSERT INTO contacts
              (firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt)
              VALUES (?, ?, ?, ?, ?, ?, ?, ?);)"
        << contact.firstName
        << contact.lastName
        << contact.middleName
        << contact.nickName
        << contact.relationship
        << (contact.birthDate ? formatDate(*contact.birthDate) : nullptr)
        << contact.createdAt
        << contact.updatedAt;

    int insertedId = db->last_insert_rowid();
    return insertedId;
}

std::vector<Contact> ContactRepository::getAll() {
    std::vector<Contact> contacts;
    std::cout << "Retrieving all contacts..." << std::endl;
    *db << "SELECT id, firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt FROM contacts;"
        >> [&](int id, std::string firstName, std::string lastName, std::string middleName,
               std::string nickName, std::string relationship, std::string birthDate,
               std::time_t createdAt, std::time_t updatedAt) {
            contacts.emplace_back(id, firstName, lastName, middleName, nickName, relationship,
                                  parseDate(birthDate), createdAt, updatedAt);
        };
    std::cout << "Contacts retrieved: " << contacts.size() << std::endl;
    return contacts;
}

Contact ContactRepository::getById(int id) {
    std::cout << "Getting contact by ID: " << id << std::endl;
    Contact contact;
    *db << "SELECT id, firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt FROM contacts WHERE id = ?;"
        << id
        >> [&](int id, std::string firstName, std::string lastName, std::string middleName,
               std::string nickName, std::string relationship, std::string birthDate,
               std::time_t createdAt, std::time_t updatedAt) {
            contact = Contact(id, firstName, lastName, middleName, nickName, relationship,
                              parseDate(birthDate), createdAt, updatedAt);
        };
    std::cout << "Contact retrieved: " << contact.firstName << " " << contact.lastName << std::endl;
    return contact;
}

void ContactRepository::update(const Contact& contact) {
    std::cout << "Updating contact: " << contact.firstName << " " << contact.lastName << std::endl;
    *db << R"(UPDATE contacts
              SET firstName = ?, lastName = ?, middleName = ?, nickName = ?,
                  relationship = ?, birthDate = ?, createdAt = ?, updatedAt = ?
              WHERE id = ?;)"
        << contact.firstName
        << contact.lastName
        << contact.middleName
        << contact.nickName
        << contact.relationship
        << (contact.birthDate ? formatDate(contact.birthDate) : nullptr)
        << contact.createdAt
        << contact.updatedAt
        << contact.id;
}

void ContactRepository::remove(int id) {
    std::cout << "Removing contact by ID: " << id << std::endl;
    *db << "DELETE FROM contacts WHERE id = ?;" << id;
    std::cout << "Contact removed." << std::endl;
}
std::string ContactRepository::formatDate(const std::optional<std::tm>& opt_tm) {
    if (opt_tm.has_value()) {
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", &(*opt_tm));
        return std::string(buf);
    } else {
        return "";
    }
}

std::tm ContactRepository::parseDate(const std::string& date) {
    // If the date is null in the DB, return an empty tm struct
    if (date.empty()) {
        return {};
    }

    std::tm tm = {};
    char* result = strptime(date.c_str(), "%Y-%m-%d", &tm);
    if (result == nullptr) {
        throw std::runtime_error("Failed to parse date: " + date);
    }
    return tm;
}