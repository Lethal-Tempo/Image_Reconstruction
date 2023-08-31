//
//  Math.cpp
//  SFML 2
//
//  Created by Ali Muhamedzhan on 13.06.2023.
//

#include "Random.hpp"

mt19937 mt;

void initRand(){
    mt.seed((unsigned)chrono::steady_clock::now().time_since_epoch().count());
}

float Rand(){
    return (float)mt() / mt.max();
}

float Rand(float min, float max){
    return Rand() * (max - min) + min;
}

Vector2f RandV2f(Vector2f min, Vector2f max){
    return Vector2f(Rand(min.x, max.x), Rand(min.y, max.y));
}

Color RandColor(){
    return Color(Rand() * 255, Rand() * 255, Rand() * 255, Rand() * 255);
}
