//
// Created by jorda on 5/29/2018.
//

#ifndef RTMOBAS_GAME_ENTITY_HPP
#define RTMOBAS_GAME_ENTITY_HPP

#include "helper.hpp"

class Entity : public sf::Drawable {
private:

    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    sf::VertexArray destination_point;

    entity_info info;

    /** Position of entity on the map */
    float x_position;
    float y_position;

    /** Size of rendering box for entity */
    float width;
    float height;

    /** Point that entity is moving towards */
    float x_destination;
    float y_destination;

    /** Distance that unit moves on each update */
    float speed;

    /** Direction that unit is moving in, < 90 is towards bottom left, > 90 and < 180 is towards bottom right, and so on */
    double travel_direction;

    bool moving;

    static const int UNIT = 5;

    void moveCommand(sf::Vector2f point);
    void rightClickAction(sf::Vector2f point);

    void update(World * world);
};

class Unit : public Entity {

private:

public:
    /** True if unit can fly, thus collision detection doesn't apply to unit, false otherwise*/
    bool is_flying;

    /** Unit Types */
    static const int UNIT_BUILDER = 501;
    static const int UNIT_SQUIRE = 502;

    /** Constructors */
    Unit() = default;
    Unit(float x, float y, int type);
};


#endif //RTMOBAS_GAME_ENTITY_HPP
