//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "resource_manager.hpp"

namespace resources {
    std::map<const char *, sf::Texture *> resources::textures;

    const char * resources::PLAINS_TEXTURE = "../resources/textures/plains.png";
    const char * resources::DESERT_TEXTURE = "../resources/textures/desert.png";
    const char * resources::MOUNTAINS_TEXTURE = "../resources/textures/mountains.png";
    const char * resources::WATER_TEXTURE = "../resources/textures/water.png";

    Texture * load(const char * resource) {
        if(resource == nullptr)
            return nullptr;

        char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") && textures.find(resource) == textures.end()) {
                void * mem = rpmalloc(sizeof(sf::Texture));
                sf::Texture * texture = new(mem) sf::Texture();

                if((*texture).loadFromFile(resource)) {
                    textures[resource] = texture;

                    return texture;
                }

                texture->~Texture();
                rpfree(mem);
            }
        }
        return nullptr;
    }

    void flush(const char * resource) {
        if(resource == nullptr)
            return nullptr;

        char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") && textures.find(resource) != textures.end()) {
                sf::Texture * texture = textures[resource];

                textures.erase(resource);

                texture->~Texture();
                rpfree(mem);

            }
        }
    }
}