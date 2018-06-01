//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "resource_manager.hpp"

namespace resources {
    std::map<const char *, sf::Texture *> textures;

    const char * PLAINS_TEXTURE = "../resources/textures/plains.png";
    const char * DESERT_TEXTURE = "../resources/textures/desert.png";
    const char * MOUNTAINS_TEXTURE = "../resources/textures/mountains.png";
    const char * WATER_TEXTURE = "../resources/textures/water.png";

    Texture * load(const char * resource) {
        if(resource == nullptr)
            return nullptr;

        char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") == 0 && textures.find(resource) == textures.end()) {
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
            return;

        char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") == 0 && textures.find(resource) != textures.end()) {
                sf::Texture * texture = textures[resource];

                textures.erase(resource);

                texture->~Texture();
                rpfree(texture);

            }
        }
    }
}