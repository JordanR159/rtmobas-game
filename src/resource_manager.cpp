//
// Created by Killian Le Clainche on 5/31/2018.
//

#include "helper.hpp"

namespace resources {

    SpriteCatalog::SpriteCatalog(const char * folder) {
        this->folder_location = folder;

        sprites.emplace_back(this);
    }

    void SpriteCatalog::load() {
        tinydir_dir dir;

        tinydir_open(&dir, this->folder_location);

        sf::Texture * texture;

        while(dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);

            if(!file.is_dir) {
                texture = new(rpmalloc(sizeof(sf::Texture))) sf::Texture();

                texture->loadFromFile(file.path);

                this->catalog.emplace_back(texture);
            }
            tinydir_next(&dir);
        }
        tinydir_close(&dir);
    }

    void SpriteCatalog::flush() {
        for(auto &item : this->catalog) {
            item->~Texture();
            rpfree(item);
        }

        this->catalog.clear();
    }

    sf::Texture * SpriteCatalog::get_texture() {
        return this->catalog.at(rand() % (this->catalog.size()));
    }

    std::map<const char *, sf::Texture *> textures;
    std::vector<SpriteCatalog *> sprites;

    namespace ui {
        const char * INTERFACE_TEXTURE = "../resources/textures/interface_panels.png";
        const char * ENTITY_PANEL_TEXTURE = "../resources/textures/entity_panel.png";
        const char * MINIMAP_PANEL_TEXTURE = "../resources/textures/minimap_panel.png";

        const char * COMMAND_BUTTONS_TEXTURE = "../resources/textures/command_buttons.png";

        const char * SELECT_BOX_TEXTURE = "../resources/textures/select_box.png";
        const char * MINIMAP_RETICLE_TEXTURE = "../resources/textures/reticle.png";
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

        SpriteCatalog FARM("../resources/sprites/farm/");
        SpriteCatalog GOLD_MINE("../resources/sprites/gold_mine/");
        SpriteCatalog METAL_MINE("../resources/sprites/metal_mine/");
        SpriteCatalog CRYSTAL_HARVESTER("../resources/sprites/crystal_harvester/");
        SpriteCatalog OIL_DRILL("../resources/sprites/oil_drill/");
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

    namespace pblock {
        const char * pblocktexture = "../resources/textures/pblock.png";
    }

    sf::Texture * load(const char * resource) {
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

        for(auto &item : sprites) {
            item->flush();
        }
    }
}