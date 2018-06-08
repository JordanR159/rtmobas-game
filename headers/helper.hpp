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

using namespace sf;
using namespace std;

#include "resource_manager.hpp"

using namespace resources;

#include "entity.hpp"
#include "tile_entity.hpp"
#include "world.hpp"
#include "interface_panels.hpp"

#include "settings.hpp"

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

/** Generates the vertex array using the specified texture */
VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize, Texture texture);

/** Generates a textureless vertex array*/
VertexArray generateVertices(float xposition, float yposition, float xsize, float ysize);

/** Rotates a point in reference to (0,0) */
Vector2f rotatePoint(float x, float y, double angle);

/** Rotates a rectangle about the pivot point by the specified angle */
Vector2f * rotateRectangle(Vector2f pivot, VertexArray * rect, double angle);

/** Determines if point is contained within a rectangle, regardless of rotation on the rectangle */
bool intersectPointRect(Vector2f point, VertexArray *quad);

/** Determines if two rectangles intersect, regardless of rotation on the rectangles */
bool intersectRectRect(VertexArray *quadOne, VertexArray *quadTwo);

#endif //RTMOBAS_GAME_HELPER_HPP
