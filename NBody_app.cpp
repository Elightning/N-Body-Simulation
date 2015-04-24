/*********************************************/
/* Name: Eamon Lightning                     */
/* Program: N-Body Simulation                */
/* Date: March 2, 2015                       */
/* File: NBody_app.cpp                       */
/*********************************************/

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <new>
#include <cstdlib>
#include "NBody.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  const double gravity = 6.67 * 1e-11;
  double radius = 0;
  double force = 0;
  double netXForce = 0;
  double netYForce = 0;
  double dX = 0;
  double dY = 0;

  int cycle_count = 0;

  double T = 157788000.0;
  double dT = 25000.0;

  int num_bodies;
  cin >> num_bodies;

  double radius_universe;
  cin >> radius_universe;

  sf::Vector2f window_size(500, 500);

  vector<Body*> bodies(num_bodies);

  for(int i = 0; i < num_bodies; i++) {
    bodies[i] = new Body(radius_universe, window_size); 
    cin >> *bodies[i];
  }

  for(int i = 0; i < num_bodies; i++) {
    bodies[i]->loadImage();
    bodies[i]->setTexture();
  } 

  sf::Texture texture_background;
  sf::Sprite sprite_background;

  texture_background.loadFromFile("Images/starfield.jpg");
  sprite_background.setTexture(texture_background);

  sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Solar System");

  sf::Music music;
  if(music.openFromFile("Audio/2001.ogg")) music.play();
  
  int framesPerSec = 1 / (dT * 1e-6);
  window.setFramerateLimit(framesPerSec);

  int totalcycles = (T * 1e-6) * framesPerSec;

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    if(cycle_count < totalcycles) {
      for(int i = 0; i < num_bodies; i++) {
        for(int j = 0; j < num_bodies; j++) {
          if(i != j) {
            dX = Distance(bodies[i]->_xPos, bodies[j]->_xPos);
            dY = Distance(bodies[i]->_yPos, bodies[j]->_yPos);
            radius = calcRadius(dX, dY);
            force = calcForce(bodies[i]->_mass, bodies[j]->_mass, gravity, radius);
            netXForce += calcForceXY(dX, radius, force);
            netYForce += calcForceXY(dY, radius, force);
          }
        }
        bodies[i]->_xForce = netXForce;
        bodies[i]->_yForce = netYForce;
        netXForce = 0;
        netYForce = 0;
      }  
 
      for(int i = 0; i < num_bodies; i++) {
        bodies[i]->step(dT);
        bodies[i]->universeToWindow();
      }

      window.clear();
      window.draw(sprite_background); 
      for(int i = 0; i < num_bodies; i++) window.draw(*bodies[i]);
      window.display();

      cycle_count++;
    }
  }
  
  return 0;
}