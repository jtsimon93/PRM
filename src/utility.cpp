#include "utility.h"
#include <cstdlib>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

std::string getHomeDirectory() {
#ifdef _WIN32
    char* homeDir = std::getenv("USERPROFILE");
    if (homeDir) {
        return std::string(homeDir);
    } else {
        char homePath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, homePath))) {
            return std::string(homePath);
        } else {
            throw std::runtime_error("Unable to determine home directory.");
        }
    }
#else
    char* homeDir = std::getenv("HOME");
    if (homeDir) {
        return std::string(homeDir);
    } else {
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            return std::string(pw->pw_dir);
        } else {
            throw std::runtime_error("Unable to determine home directory.");
        }
    }
#endif
}