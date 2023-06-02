#ifndef RAYCASTER_MAP_EDITOR_FILESYSTEM_HPP
#define RAYCASTER_MAP_EDITOR_FILESYSTEM_HPP

#include <cstdlib>
#include <iostream>
#include <string>

class FileSystem {
private:
    static std::string GetRoot() {
        const char* env = std::getenv("RAYCASTER_MAP_EDITOR_ROOT");

        if (!env) {
            std::cout << "ERROR::FILESYSTEM Error reading environment variable: RAYCASTER_MAP_EDITOR_ROOT" << std::endl;
            return NULL;
        }
        return std::string(env);
    }

public:
    static std::string GetPath(const char* path) {
        std::string root = GetRoot();

        if (root.empty())
            return NULL;

        return std::string(root + path);
    }
};

#endif