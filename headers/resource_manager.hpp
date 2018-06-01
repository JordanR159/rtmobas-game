//
// Created by Killian Le Clainche on 5/31/2018.
//

#ifndef RTMOBAS_GAME_RESOURCE_MANAGER_HPP
#define RTMOBAS_GAME_RESOURCE_MANAGER_HPP

#include "helper.hpp"

namespace resources {

    extern std::map<int, sf::Texture *> textures;

    extern const char * PLAINS_TEXTURE;
    extern const char * DESERT_TEXTURE;
    extern const char * MOUNTAINS_TEXTURE;
    extern const char * WATER_TEXTURE;

    Texture * load(const char *);

}

#endif //RTMOBAS_GAME_RESOURCE_MANAGER_HPP
