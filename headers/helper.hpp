//
// Created by jorda on 5/30/2018.
//

#ifndef RTMOBAS_GAME_HELPER_HPP
#define RTMOBAS_GAME_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <fstream>
#include <iostream>
#include <list>
#include <map>

#include <rpmalloc.h>
#include <mem.h>

#include "entity.hpp"
#include "world.hpp"

int* readBMP(char* filename);

VertexArray generateVertices(int xposition, int yposition, int xsize, int ysize, Texture texture);

bool isOnScreen(Entity entity, int startx, int starty, int endx, int endy);

#endif //RTMOBAS_GAME_HELPER_HPP
