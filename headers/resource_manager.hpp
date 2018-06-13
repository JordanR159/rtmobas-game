//
// Created by Killian Le Clainche on 5/31/2018.
//

#ifndef RTMOBAS_GAME_RESOURCE_MANAGER_HPP
#define RTMOBAS_GAME_RESOURCE_MANAGER_HPP

#include "helper.hpp"

namespace resources {

    class SpriteCatalog {
    private:
        const char * folder_location;
        std::vector<sf::Texture *> catalog;
    public:
        SpriteCatalog(const char * folder);

        void load();

        void flush();

        sf::Texture * get_texture();
    };

    extern std::map<const char *, sf::Texture *> textures;
    extern std::vector<SpriteCatalog *> sprites;

    namespace ui {
        extern const char * INTERFACE_TEXTURE;
        extern const char * ENTITY_PANEL_TEXTURE;
        extern const char * MINIMAP_PANEL_TEXTURE;

        extern const char * COMMAND_BUTTONS_TEXTURE;

        extern const char * SELECT_BOX_TEXTURE;
        extern const char * MINIMAP_RETICLE_TEXTURE;
    }

    namespace terrain {

        extern const char * TERRAIN_TEXTURES;

        extern const char * PLAINS_TEXTURE;
        extern const char * DESERT_TEXTURE;
        extern const char * MOUNTAINS_TEXTURE;
        extern const char * WATER_TEXTURE;
    }

    namespace structure {
        extern const char * CASTLE_TEXTURE;

        extern SpriteCatalog FARM;
        extern SpriteCatalog GOLD_MINE;
        extern SpriteCatalog METAL_MINE;
        extern SpriteCatalog CRYSTAL_HARVESTER;
        extern SpriteCatalog OIL_DRILL;
    }

    namespace resource {
        extern const char * FOOD_TEXTURE;
        extern const char * TREE_TEXTURE;
        extern const char * GOLD_TEXTURE;
        extern const char * METAL_TEXTURE;
        extern const char * CRYSTAL_TEXTURE;
        extern const char * OIL_TEXTURE;
    }

    namespace unit {
        extern const char * PEASANT_TEXTURE;
    }

    namespace pblock {
        extern const char * pblocktexture;
    }

    sf::Texture * load(const char *);

    void flush(const char *);

    void flush();

}

#endif //RTMOBAS_GAME_RESOURCE_MANAGER_HPP
