//
// Created by jorda on 5/29/2018.
//

#ifndef RTMOBAS_GAME_ENTITY_HPP
#define RTMOBAS_GAME_ENTITY_HPP

class Tile;

class Entity : public Drawable {
private:
    /** Allows window.draw(Entity) to be used in SFML */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:

    Texture * texture;

public:
    /** Position of corners for entity, only needs to change just before rendering */
    VertexArray vao;

    /** Position of entity on the map */
    double x_position;
    double y_position;

    /** Size of rendering box for entity */
    double width;
    double height;

    /** Remaining lifepoints for an entity. For Resources, this is number of resources left */
    int curr_lifepoints;

    /** Maximum lifepoints that the entity can have */
    int max_lifepoints;

    /** Subtype for the entity, as defined in the subclasses */
    int entity_type;

    /** True if unit is currently being directed. False otherwise */
    bool selected;

    static const int PRODUCER = 1;
    static const int RESEARCHER = 2;
    static const int COLLECTOR = 3;
    static const int RESOURCE = 4;
    static const int UNIT = 5;
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
    Unit(double, double, int type);
};


#endif //RTMOBAS_GAME_ENTITY_HPP
