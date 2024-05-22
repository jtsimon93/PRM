#include "address_repository.h"

AddressRepository::AddressRepository(const std::string &db_path) {
    db = std::make_shared<sqlite::database>(db_path);
    *db << "create table if not exists addresses ("
           "id integer primary key autoincrement not null,"
           "contact_id integer not null,"
           "street_address1 text not null,"
           "street_address2 text,"
           "city text,"
           "state text,"
           "zip text,"
           "created_at integer not null,"
           "updated_at integer"
           ");";
}

int AddressRepository::add(const Address &address) {
    *db << "insert into addresses (contact_id, street_address1, street_address2, city, state, zip, created_at, updated_at) "
           "values (?, ?, ?, ?, ?, ?, ?, ?);"
        << address.contactId
        << address.streetAddress1
        << address.streetAddress2
        << address.city
        << address.state
        << address.zip
        << address.createdAt
        << address.updatedAt;

    int insertedId = db->last_insert_rowid();
    return insertedId;
}

std::vector<Address> AddressRepository::getAll() {
    std::vector<Address> addresses;
    *db << "select * from addresses;"
        >> [&](int id, int contact_id, std::string street_address1, std::string street_address2, std::string city,
               std::string state, std::string zip, int created_at, int updated_at) {
        Address address(id, contact_id, street_address1, street_address2, city, state, zip, created_at, updated_at);
        addresses.push_back(address);
    };

    return addresses;
}

Address AddressRepository::getById(int id) {
    Address address;
    *db << "select * from addresses where id = ?;"
        << id
        >> [&](int id, int contact_id, std::string street_address1, std::string street_address2, std::string city,
               std::string state, std::string zip, int created_at, int updated_at) {
        address = Address(id, contact_id, street_address1, street_address2, city, state, zip, created_at, updated_at);
    };

    return address;
}

std::vector<Address> AddressRepository::getByContactId(int contactId) {
    std::vector<Address> addresses;
    *db << "select * from addresses where contact_id = ?;"
        << contactId
        >> [&](int id, int contact_id, std::string street_address1, std::string street_address2, std::string city,
               std::string state, std::string zip, int created_at, int updated_at) {
        Address address(id, contact_id, street_address1, street_address2, city, state, zip, created_at, updated_at);
        addresses.push_back(address);
    };

    return addresses;
}

void AddressRepository::update(const Address &address) {
    *db << "update addresses set contact_id = ?, street_address1 = ?, street_address2 = ?, city = ?, state = ?, zip = ?, updated_at = ? where id = ?;"
        << address.contactId
        << address.streetAddress1
        << address.streetAddress2
        << address.city
        << address.state
        << address.zip
        << address.updatedAt
        << address.id;
}

void AddressRepository::remove(int id) {
    *db << "delete from addresses where id = ?;"
        << id;
}