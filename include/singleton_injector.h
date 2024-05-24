#ifndef PRM_SINGLETON_INJECTOR_H
#define PRM_SINGLETON_INJECTOR_H

#include <boost/di.hpp>
#include <string>
#include <memory>
#include <filesystem>
#include "icontact_repository.h"
#include "icontact_service.h"
#include "contact_repository.h"
#include "contact_service.h"
#include "iaddress_repository.h"
#include "iaddress_service.h"
#include "address_repository.h"
#include "address_service.h"
#include "utility.h"

namespace di = boost::di;

class SingletonInjector {
public:
    static auto &getInjector() {
        static auto injector = di::make_injector(
                di::bind<std::string>.to(getDbPath()),
                di::bind<IContactRepository>().to<ContactRepository>(),
                di::bind<IContactService>().to<ContactService>(),
                di::bind<IAddressRepository>().to<AddressRepository>(),
                di::bind<IAddressService>().to<AddressService>()

        );
        return injector;
    }

private:
    static std::string getDbPath() {
        std::string homeDir = getHomeDirectory();
        std::string prmDir = homeDir + "/.PRM";
        if (!std::filesystem::exists(prmDir)) {
            std::filesystem::create_directory(prmDir);
        }
        return prmDir + "/prm.db";
    }

    SingletonInjector() = default;

    ~SingletonInjector() = default;

    SingletonInjector(const SingletonInjector &) = delete;

    SingletonInjector &operator=(const SingletonInjector &) = delete;
};

#endif // PRM_SINGLETON_INJECTOR_H
