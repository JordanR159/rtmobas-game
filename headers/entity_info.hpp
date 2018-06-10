//
// Created by Killian Le Clainche on 6/7/2018.
//

#ifndef RTMOBAS_GAME_ENTITY_INFO_HPP
#define RTMOBAS_GAME_ENTITY_INFO_HPP

#include "helper.hpp"

class World;

struct entity_info {

    World * world;

    /** Position of corners for entity, only needs to change just before rendering */
    sf::VertexArray vao;

    sf::Texture * texture;

    /** Remaining lifepoints for an entity. For Resources, this is number of resources left */
    int curr_lifepoints;

    /** Maximum lifepoints that the entity can have */
    int max_lifepoints;

    /** Subtype for the entity, as defined in the subclasses */
    int entity_type;

    /** Used for determining if the entity is being managed by the player through selection */
    bool selected;

};

#endif //RTMOBAS_GAME_ENTITY_INFO_HPP
