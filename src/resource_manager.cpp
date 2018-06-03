//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

namespace resources {
    std::map<const char *, sf::Texture *> textures;

    namespace ui {
        const char * PANEL_TEXTURE = "../resources/textures/interface_panels.png";

        const char * BACK_COMMAND_TEXTURE = "../resources/textures/back_command.png";

        const char * BUILD_COLLECTORS_TEXTURE = "../resources/textures/build_collectors.png";
        const char * BUILD_FARM_TEXTURE = "../resources/textures/build_farm.png";

        const char * MOVE_COMMAND_TEXTURE = "../resources/textures/move_command.png";
    }

    namespace terrain {
        const char * TERRAIN_TEXTURES = "../resources/textures/terrain.png";

        const char * PLAINS_TEXTURE = "../resources/textures/plains.png";
        const char * DESERT_TEXTURE = "../resources/textures/desert.png";
        const char * MOUNTAINS_TEXTURE = "../resources/textures/mountains.png";
        const char * WATER_TEXTURE = "../resources/textures/water.png";
    }

    namespace structure {
        const char * CASTLE_TEXTURE = "../resources/sprites/castle.png";
        const char * FARM_TEXTURE = "../resources/sprites/food_collector.png";
    }

    namespace resource {
        const char * FOOD_TEXTURE = "../resources/sprites/food_resource.png";
        const char * TREE_TEXTURE = "../resources/sprites/wood_resource.png";
        const char * GOLD_TEXTURE = "../resources/sprites/gold_resource.png";
        const char * METAL_TEXTURE = "../resources/sprites/metal_resource.png";
        const char * CRYSTAL_TEXTURE = "../resources/sprites/crystal_resource.png";
        const char * OIL_TEXTURE = "../resources/sprites/oil_resource.png";
    }

    namespace unit {
        const char * PEASANT_TEXTURE = "../resources/sprites/peasant.png";
    }

    Texture * load(const char * resource) {
        if(resource == nullptr)
            return nullptr;

        const char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") == 0) {
                if(textures.find(resource) == textures.end()) {
                    void * mem = rpmalloc(sizeof(sf::Texture));
                    sf::Texture * texture = new(mem) sf::Texture();

                    if((*texture).loadFromFile(resource)) {
                        textures[resource] = texture;

                        return texture;
                    }

                    texture->~Texture();
                    rpfree(mem);
                }
                else
                    return textures[resource];
            }
        }
        return nullptr;
    }

    void flush(const char * resource) {
        if(resource == nullptr)
            return;

        const char * end_type = strrchr(resource, '.');

        if(end_type != nullptr) {
            if(strcmp(end_type, ".png") == 0 && textures.find(resource) != textures.end()) {
                sf::Texture * texture = textures[resource];

                textures.erase(resource);

                texture->~Texture();
                rpfree(texture);

            }
        }
    }

    void flush() {
        for(auto &iter : textures) {
            iter.second->~Texture();
            rpfree(iter.second);
        }

        textures.clear();
    }
}