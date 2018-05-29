//
// Created by jorda on 5/27/2018.
//

#ifndef RTMOBAS_GAME_TILE_H
#define RTMOBAS_GAME_TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>

using namespace sf;
using namespace std;

class Tile : public Drawable {

private:
    /** Allows window.draw(Tile) to be used in SFML */
    virtual void draw(RenderTarget &target, RenderStates states) const {
        states.texture = &texture;
        target.draw(vertices, states);
    }
    /** Position of corners for tile */
    VertexArray vertices;

    /** Path to the texture for the entity */
    Texture texture;

public:
    /** Size of tiles, which is the same for all tiles */
    static const int tile_size = 25;

    /** True if an entity can be drawn on top of this tile, false otherwise */
    bool is_passable;

    /** Modifier the the speed that entities move over this tile. Standard is 1.0 */
    double movement_multiplier;

    /** Amount of damage tile inflicts to units every tick */
    int damage_factor;

    /** Used in constructor for assigning several properties for each tile type */
    enum types{
        PLAINS, DESERT, MOUNTAIN
    };

    Tile() {
        Tile(0, 0, PLAINS);
    }

    /** Use the enum types for the type argument */
    Tile(int xposition, int yposition, int type) {
        switch(type) {
            case PLAINS: texture.loadFromFile("../resources/textures/pblock.png");
                is_passable = true;
                movement_multiplier = 1.0;
                damage_factor = 0;
                break;
            default: break;
        }
        vertices = VertexArray(Quads, 4);

        /** Corner positions for the rendering box */
        vertices[0].position = Vector2f(xposition, yposition);
        vertices[1].position = Vector2f(xposition, yposition + tile_size);
        vertices[2].position = Vector2f(xposition + tile_size, yposition + tile_size);
        vertices[3].position = Vector2f(xposition + tile_size, yposition);

        /** Designates area of the texture that is used */
        vertices[0].texCoords = Vector2f(0, 0);
        vertices[1].texCoords = Vector2f(0, texture.getSize().y);
        vertices[2].texCoords = Vector2f(texture.getSize().x, texture.getSize().y);
        vertices[3].texCoords = Vector2f(texture.getSize().x, 0);
    }
};


#endif //RTMOBAS_GAME_TILE_H
