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
#include <mem.h>

#include "entity.hpp"
#include "tile_entity.hpp"
#include "world.hpp"
#include "settings.hpp"
#include "resource_manager.hpp"
#include "interface_panels.hpp"

#define TOKENIZE(string, token, delimiter, index) \
    index = (string).find_first_of(delimiter); \
    (token) = line.substr(0, delimiter_index); \
    line.erase(0, delimiter_index + 1);

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

int* readBMP(char* filename);

VertexArray generateVertices(float, float, float, float, Texture texture);

#endif //RTMOBAS_GAME_HELPER_HPP
