#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Vector2f.hpp"
#include "Sphere.hpp"
#include "Spring.hpp"
#include <iostream>


int main()
{

    const int width = 1200;
    const int height = 700;
    const float DT = 0.0001;
    const int numberOfBalls = 4;
    const int numberOfSprings = 4;
    float radius = 30;
    float weight = 30;
    float stiffness = 600;

    Vector2f radiusVector = {radius, radius};

    Sphere ball_1 = {{640, 550}, {100, 300}, {0, 0}, sf::Color::Green, radius, weight};
    Sphere ball_2 = {{960, 350}, {-200, -700}, {0, 0}, sf::Color::Green, radius, weight};
    Sphere ball_3 = {{660, 30}, {-200, -700}, {0, 0}, sf::Color::Green, radius, weight};
    Sphere ball_4= {{60, 350}, {-200, -700}, {0, 0}, sf::Color::Green, radius, weight};

    Sphere balls[numberOfBalls] = {ball_1, ball_2, ball_3, ball_4};
    Spring springs[numberOfSprings];

    sf::RenderWindow window(sf::VideoMode(width, height), "Program is working!");

    for (int i = 0; i < numberOfBalls; i++)
    {
        for (int j = 0; j < numberOfSprings; j++)
        {
            Vector2f tmpLengthStart = balls[i].local + radiusVector;
            Vector2f tmpLengthEnd = balls[i].local + radiusVector;

            sf::Color tmpColor = sf::Color::Red;

            Spring tmpSpring = {tmpLengthStart, tmpLengthEnd, tmpLengthStart, tmpLengthEnd, tmpColor};

            springs[j] = tmpSpring;
        }        
    }
    
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
        switch (evnt.type)
         {
         case sf::Event::Closed:
          window.close();
            break;
         case sf::Event::KeyPressed:
             if (evnt.key.code == sf::Keyboard::Space)
                   window.close();
            break;
        }
        }

        window.clear(); 

        for (int j = 0; j < numberOfBalls; j++)
        {
            Spring spring;
            spring.drawSpring(springs[j], &window);
        }
        

        for (int i = 0; i < numberOfBalls; i++)
        {
            Sphere sphere;
            sphere.drawSphere(balls[i], &window);    
        }

        for (int i = 0; i < numberOfBalls; i++)
        {
            Sphere sphere; 
            sphere.resolveWallCollition(&balls[i], width, height);
            sphere.moveSphere(&balls[i], DT);
        }

        for (int i = 0; i < numberOfBalls; i++)
        {
            for (int j = 0; j < numberOfBalls; j++)
               {
                springs[i].lengthStart = balls[i].local + radiusVector;
                springs[i].lengthEnd = balls[j].local + radiusVector;

                Vector2f deltaStart = springs[j].lengthStart - springs[i].length0Start;
                Vector2f deltaEnd = springs[j].lengthEnd - springs[i].length0End;

                balls[i].acceleration = deltaStart  * springs[i].stiffness / balls[i].weight;
                balls[j].acceleration = deltaEnd *  springs[j].stiffness / balls[j].weight;
               }
        }
        window.display();
    }
    return 0;
}
