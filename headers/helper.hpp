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
#include <cmath>


#include <rpmalloc.h>
#include <mem.h>

#include "entity.hpp"
#include "world.hpp"
#include "settings.hpp"
#include "resource_manager.hpp"

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

int* readBMP(char* filename);

VertexArray generateVertices(int xposition, int yposition, int xsize, int ysize);

bool isOnScreen(Entity entity, int startx, int starty, int endx, int endy);

#endif //RTMOBAS_GAME_HELPER_HPP
