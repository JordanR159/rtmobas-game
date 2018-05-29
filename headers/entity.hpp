//
// Created by jorda on 5/29/2018.
//

#ifndef RTMOBAS_GAME_ENTITY_HPP
#define RTMOBAS_GAME_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;


class Entity : public Drawable {

    /** Position of entity on the map */
    int xposition;
    int yposition;

    /** Size of rendering box for entity */
    int box_size;

    /** Path to the texture for the entity */
    String texture_path;

    /** True if entity can stack with other entities, false otherwise */
    bool is_stackable;

};


#endif //RTMOBAS_GAME_ENTITY_HPP
