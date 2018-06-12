//
// Created by jorda on 5/30/2018.
//

#ifndef RTMOBAS_GAME_HELPER_HPP
#define RTMOBAS_GAME_HELPER_HPP

//#include <gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <cmath>
#include <chrono>
#include <sstream>
#include <sys/stat.h>

#include <rpmalloc.h>

#ifdef IS_UNIX
#include <string.h>
#else
#include <mem.h>
#endif

#include "resource_manager.hpp"
#include "settings.hpp"
#include "input_handler.hpp"

#include "entity_info.hpp"

#include "entity.hpp"
#include "tile_entity.hpp"
#include "world.hpp"
#include "user_interface.hpp"

#define TOKENIZE(string, token, delimiter, index) \
    index = (string).find_first_of(delimiter); \
    (token) = line.substr(0, delimiter_index); \
    line.erase(0, delimiter_index + 1);

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

/** Holds information needed for selecting units for global access*/
extern Selector * selector;

/** Used to read map terrain information from 24 bit bitmap files */
int* readBMP(char* filename);

void gen_vao(sf::VertexArray &vao, float xpos, float ypos, float width, float height, sf::Texture * texture);

/** Generates the vertex array using the specified texture */
sf::VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize, sf::Texture texture);

/** Rotate the coordinates (x,y) by the angle (in radians) and set the value to vec. */
void rotate(sf::Vector2f &vec, float x, float y, double angle);

/** Clamp vec such that x <= vec.x <= x + width and y <= vec.y <= y + height */
void clamp_vec(sf::Vector2f &vec, float x, float y, float width, float height);

/** Generates a textureless vertex array*/
sf::VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize);

/** Rotates a point in reference to (0,0) */
sf::Vector2f rotatePoint(float x, float y, double angle);

/** Rotates a rectangle about the pivot point by the specified angle */
sf::Vector2f * rotateRectangle(sf::Vector2f pivot, sf::VertexArray * rect, double angle);

/** Determines if point is contained within a rectangle, regardless of rotation on the rectangle */
bool intersectPointRect(sf::Vector2f point, sf::VertexArray *quad);

/** Determines if two rectangles intersect, regardless of rotation on the rectangles */
bool intersectRectRect(sf::VertexArray *quadOne, sf::VertexArray *quadTwo);

#endif //RTMOBAS_GAME_HELPER_HPP
