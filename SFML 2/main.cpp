//
//  main.cpp
//  SFML 2
//
//  Created by Ali Muhamedzhan on 14.06.2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Random.hpp"
#include "Figure.hpp"
#include <time.h>

using namespace sf;
using namespace std;

const int width = 1280, height = 1024;

string imgPath = "spongebob.jpg";

Image img, nImg, cur;
Texture imgTexture, nImgTexture;
Sprite imgSprite, nImgSprite;

float Llast, L = 100;

bool found = false;
int cnt = 0;

vector<Triangle> triangles;

float triArea(Vector2f v1, Vector2f v2, Vector2f v3){
    return (v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y);
}

bool pointInTri(Vector2f pt, Triangle tri){
    float ta, a1, a2, a3;
    
    ta = triArea(tri.vertices[0], tri.vertices[1], tri.vertices[2]);
    ta = abs(ta);
    a1 = triArea(pt, tri.vertices[1], tri.vertices[2]);
    a1 = abs(a1);
    a2 = triArea(pt, tri.vertices[0], tri.vertices[2]);
    a2 = abs(a2);
    a3 = triArea(pt, tri.vertices[0], tri.vertices[1]);
    a3 = abs(a3);
    
    if(a1 + a2 + a3 - 0.01f > ta)return false;
    return true;
    
}

void computeLoss(){
    Llast = L;
    L = 0;
    for(int i = 0; i < img.getSize().x; i ++){
        for(int j = 0; j < img.getSize().y; j ++) {
            L += abs((float)img.getPixel(i, j).r - (float)nImg.getPixel(i, j).r);
            L += abs((float)img.getPixel(i, j).g - (float)nImg.getPixel(i, j).g);
            L += abs((float)img.getPixel(i, j).b - (float)nImg.getPixel(i, j).b);
        }
    }
    L /= (img.getSize().x * img.getSize().y);
    L /= 3;
    L /= 2.55;
}

void add(Triangle x, Image &image){
    for(int i = max(0.f, x.left.x); i < min((float)image.getSize().x, x.right.x); i ++){
        for(int j = max(0.f, x.left.y); j < min((float)image.getSize().y, x.right.y); j ++){
            if(pointInTri(Vector2f(i, j), x)){
                float r0, g0, b0, a0;
                float r1, g1, b1, a1;
                r0 = x.color.r / 255.f;
                g0 = x.color.g / 255.f;
                b0 = x.color.b / 255.f;
                a0 = x.color.a / 255.f;
                
                Color ic = image.getPixel(i, j);
                r1 = ic.r / 255.f;
                g1 = ic.g / 255.f;
                b1 = ic.b / 255.f;
                a1 = ic.a / 255.f;
                
                float a01 = (1 - a0) * a1 + a0;
                float r01 = ((1 - a0) * a1 * r1 + a0 * r0) / a01;
                float g01 = ((1 - a0) * a1 * g1 + a0 * g0) / a01;
                float b01 = ((1 - a0) * a1 * b1 + a0 * b0) / a01;
                
                ic = Color(r01 * 255, g01 * 255, b01 * 255, a01 * 255);
                
                image.setPixel(i, j, ic);
            }
        }
    }
}

int main()
{
    initRand();
    
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    
    img.loadFromFile("/Users/alimuhamedzhan/Desktop/SFML 2/SFML 2/Lalo.png");
    imgTexture.loadFromImage(img);
    imgSprite.setTexture(imgTexture);
    
    cur.create(img.getSize().x, img.getSize().y, Color(255, 255, 255));
    nImg.create(img.getSize().x, img.getSize().y, Color(255, 255, 255));
    nImgTexture.loadFromImage(nImg);
    
    nImgSprite.setScale(1.5, 1.5);
    imgSprite.setScale(1.5, 1.5);
    //width - imgTexture.getSize().x * imgSprite.getScale().x
    //height - imgTexture.getSize().y * imgSprite.getScale().y
    imgSprite.setPosition(width - imgTexture.getSize().x * imgSprite.getScale().x, 0);
    
    Vector2f size = Vector2f(img.getSize().x, img.getSize().y);
    
    triangles.push_back(Triangle(RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandColor()));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        int last = (int)triangles.size() - 1;
        
        Triangle t = triangles[last];
        
        triangles[last].move(RandV2f(Vector2f(-5, -5), Vector2f(5, 5)), RandV2f(Vector2f(-5, -5), Vector2f(5, 5)), RandV2f(Vector2f(-5, -5), Vector2f(5, 5)));
        triangles[last].calc();
        
        triangles[last].color.r += Rand(Rand() * (-10), Rand() * 10);
        triangles[last].color.g += Rand(Rand() * (-10), Rand() * 10);
        triangles[last].color.b += Rand(Rand() * (-10), Rand() * 10);
        triangles[last].color.a += Rand(Rand() * (-10), Rand() * 10);
        
        nImg = cur;
        add(triangles[last], nImg);
        
        computeLoss();
        
        if(L < Llast) {
            cout << "fitness = " << 100 - L << endl;
            found = 1;
            cnt = 0;
            
            nImgTexture.loadFromImage(nImg);
            nImgSprite.setTexture(nImgTexture);

            window.clear();
            
            window.draw(imgSprite);
            window.draw(nImgSprite);
            
            window.display();
        }
        else{
            if(!found){
                triangles[last] = Triangle(RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandColor());
                cnt = 0;
            }
            else{
                triangles[last] = t;
            }
            L = Llast;
            cnt ++;
        }
        if(cnt > 500){
            if(!found){
                nImg = cur;
                triangles.pop_back();
            }
            else{
                nImg = cur;
                add(t, nImg);
                cur = nImg;
            }
            Triangle nwTri = Triangle(RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandColor());
            while(triArea(nwTri.vertices[0], nwTri.vertices[1], nwTri.vertices[2]) < 6.f)nwTri = Triangle(RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandV2f(Vector2f(0, 0), size), RandColor());
            triangles.push_back(nwTri);
            cout << "new triangle #" << triangles.size() << endl;
            cnt = 0;
            found = 0;
        }
        
        
    }

    return 0;
}
