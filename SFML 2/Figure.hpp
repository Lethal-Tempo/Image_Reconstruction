//
//  Figure.hpp
//  SFML 2
//
//  Created by Ali Muhamedzhan on 14.06.2023.
//

#ifndef Figure_hpp
#define Figure_hpp

#include <SFML/Graphics.hpp>
//#include <algorithm>

using namespace sf;
using namespace std;

class Triangle {
public:
    Color color;
    
    Vector2f left, right;
    
    Vector2f vertices[3];
    
    Triangle(Vector2f vertex1, Vector2f vertex2, Vector2f vertex3, Color _color);
    
    void setColor(Color _color);
    
    void move(Vector2f v1, Vector2f v2, Vector2f v3);
    
    void calc();
};

#endif /* Figure_hpp */
