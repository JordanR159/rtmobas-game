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

#include "entity.hpp"
#include "tile_entity.hpp"
#include "world.hpp"
#include "interface_panels.hpp"

#define TOKENIZE(string, token, delimiter, index) \
    index = (string).find_first_of(delimiter); \
    (token) = line.substr(0, delimiter_index); \
    line.erase(0, delimiter_index + 1);

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

int* readBMP(char* filename);

VertexArray generateVertices(float, float, float, float, Texture texture);

Vector2f rotatePoint(int x, int y, double angle);

Vector2f * rotateRectangle(int point_x, int point_y, int left, int top, int right, int bottom, double angle);

#endif //RTMOBAS_GAME_HELPER_HPP
