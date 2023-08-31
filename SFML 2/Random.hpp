//
//  Math.hpp
//  SFML 2
//
//  Created by Ali Muhamedzhan on 13.06.2023.
//

#pragma once

#ifndef Random_hpp
#define Random_hpp

#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

extern mt19937 mt;

void initRand();

float Rand();

float Rand(float min, float max);

Vector2f RandV2f(Vector2f min, Vector2f max);

Color RandColor();

#endif /* Random_hpp */
