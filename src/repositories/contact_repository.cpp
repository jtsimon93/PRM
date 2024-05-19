#include "contact_repository.h"

ContactRepository::ContactRepository(const std::string& db_path) {
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
}

void ContactRepository::add(const Contact& contact) {
    *db << R"(INSERT INTO contacts
              (firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt)
              VALUES (?, ?, ?, ?, ?, ?, ?, ?);)"
        << contact.firstName
        << contact.lastName
        << contact.middleName
        << contact.nickName
        << contact.relationship
        << formatDate(contact.birthDate)
        << contact.createdAt
        << contact.updatedAt;
}

std::vector<Contact> ContactRepository::getAll() {
    std::vector<Contact> contacts;
    *db << "SELECT id, firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt FROM contacts;"
        >> [&](int id, std::string firstName, std::string lastName, std::string middleName,
               std::string nickName, std::string relationship, std::string birthDate,
               std::time_t createdAt, std::time_t updatedAt) {
            contacts.emplace_back(id, firstName, lastName, middleName, nickName, relationship,
                                  parseDate(birthDate), createdAt, updatedAt);
        };
    return contacts;
}

Contact ContactRepository::getById(int id) {
    Contact contact;
    *db << "SELECT id, firstName, lastName, middleName, nickName, relationship, birthDate, createdAt, updatedAt FROM contacts WHERE id = ?;"
        << id
        >> [&](int id, std::string firstName, std::string lastName, std::string middleName,
               std::string nickName, std::string relationship, std::string birthDate,
               std::time_t createdAt, std::time_t updatedAt) {
            contact = Contact(id, firstName, lastName, middleName, nickName, relationship,
                              parseDate(birthDate), createdAt, updatedAt);
        };
    return contact;
}

void ContactRepository::update(const Contact& contact) {
    *db << R"(UPDATE contacts
              SET firstName = ?, lastName = ?, middleName = ?, nickName = ?,
                  relationship = ?, birthDate = ?, createdAt = ?, updatedAt = ?
              WHERE id = ?;)"
        << contact.firstName
        << contact.lastName
        << contact.middleName
        << contact.nickName
        << contact.relationship
        << formatDate(contact.birthDate)
        << contact.createdAt
        << contact.updatedAt
        << contact.id;
}

void ContactRepository::remove(int id) {
    *db << "DELETE FROM contacts WHERE id = ?;" << id;
}

std::string ContactRepository::formatDate(const std::tm& tm) {
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return std::string(buf);
}

std::tm ContactRepository::parseDate(const std::string& date) {
    std::tm tm = {};
    char* result = strptime(date.c_str(), "%Y-%m-%d", &tm);
    if (result == nullptr) {
        throw std::runtime_error("Failed to parse date: " + date);
    }
    return tm;
}
