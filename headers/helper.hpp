//
// Created by jorda on 5/30/2018.
//

#ifndef RTMOBAS_GAME_HELPER_HPP
#define RTMOBAS_GAME_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include <gtc/matrix_transform.hpp>

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <cmath>


#include <rpmalloc.h>
#include <mem.h>

#include "entity.hpp"
#include "world.hpp"
#include "settings.hpp"

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

extern const int SCROLL_UP;
extern const int SCROLL_DOWN;
extern const int SCROLL_LEFT;
extern const int SCROLL_RIGHT;

int* readBMP(char* filename);

VertexArray generateVertices(int xposition, int yposition, int xsize, int ysize, Texture texture);

bool isOnScreen(Entity entity, int startx, int starty, int endx, int endy);

#endif //RTMOBAS_GAME_HELPER_HPP
