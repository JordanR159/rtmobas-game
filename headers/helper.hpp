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

int* readBMP(char* filename);

VertexArray generateVertices(float, float, float, float, Texture texture);

/** Rotate the coordinates (x,y) by the angle (in radians) and set the value to vec. */
void rotate(Vector2f &vec, float x, float y, double angle);

/** Clamp vec such that x <= vec.x <= x + width and y <= vec.y <= y + height */
void clamp_vec(Vector2f &vec, float x, float y, float width, float height);

void rotatePoint(Vertex &, float x, float y, double angle);

void rotateRectangle(VertexArray vao, int point_x, int point_y, int left, int top, int right, int bottom, double angle);

#endif //RTMOBAS_GAME_HELPER_HPP
