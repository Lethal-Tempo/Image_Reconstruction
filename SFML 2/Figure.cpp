//
//  Figure.cpp
//  SFML 2
//
//  Created by Ali Muhamedzhan on 14.06.2023.
//

#include "Figure.hpp"

Triangle::Triangle(Vector2f vertex1, Vector2f vertex2, Vector2f vertex3, Color _color){
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;
    
    color = _color;
    
    calc();
}

void Triangle::setColor(Color _color){
    color = _color;
}

void Triangle::move(Vector2f v1, Vector2f v2, Vector2f v3){
    vertices[0] += v1;
    vertices[1] += v2;
    vertices[2] += v3;
}

void Triangle::calc(){
    left = Vector2f(min(vertices[0].x, min(vertices[1].x, vertices[2].x)), min(vertices[0].y, min(vertices[1].y, vertices[2].y)));
    right = Vector2f(max(vertices[0].x, max(vertices[1].x, vertices[2].x)), max(vertices[0].y, max(vertices[1].y, vertices[2].y)));
}
