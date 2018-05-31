//
// Created by jorda on 5/30/2018.
//

#ifndef RTMOBAS_GAME_HELPER_HPP
#define RTMOBAS_GAME_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <iostream>
#include <map>

#include <rpmalloc.h>
#include <mem.h>

#include <world.hpp>
#include <settings.hpp>
#include <entity.hpp>

extern const char * INPUT_SETTINGS_LOCATION;
extern const char * SETTINGS_LOCATION;

extern const int SCROLL_UP;
extern const int SCROLL_DOWN;
extern const int SCROLL_LEFT;
extern const int SCROLL_RIGHT;

int* readBMP(char* filename);

#endif //RTMOBAS_GAME_HELPER_HPP
