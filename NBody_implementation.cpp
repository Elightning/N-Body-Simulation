/*********************************************/
/* Name: Eamon Lightning                     */
/* Program: N-Body Simulation                */
/* Date: March 2, 2015                       */
/* File: NBody_implementation.cpp            */
/*********************************************/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "NBody.hpp"

using namespace std;

Body::Body(double radius, const sf::Vector2f& window_size) : _radius_universe(radius), _window_size(window_size) {}

Body::~Body() {}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  target.draw(_sprite);
}

void Body::step(double dT) {

  // Calculates x/y acceleration
  double xAccel = _xForce / _mass;
  double yAccel = _yForce / _mass;

  calcVel(xAccel, yAccel, dT); 

  calcPos(dT);
}

void Body::calcVel(double xAccel, double yAccel, double dT) {

  _xVel += (xAccel * dT);
  _yVel += (yAccel * dT);
}

void Body::calcPos(double dT) {

  _xPos += (_xVel * dT);
  _yPos += (_yVel * dT);
}

void Body::universeToWindow() {

  // Sets origin to center of window, and calculates the offset of the sprite by converting its x,y values from meters to pixels.
  double xModified = ((_xPos/_radius_universe) * (_window_size.x / 2)) + _window_size.x / 2;   
  double yModified = (-(_yPos/_radius_universe) * (_window_size.y / 2)) + _window_size.y / 2;

  sf::FloatRect sprite_dimensions = _sprite.getGlobalBounds();     // Gets dimensions of the sprite
  xModified -= (sprite_dimensions.width / 2);   // The right operand accounts for the positioning of the sprite relative to its upper left hand corner. After it's applied, its now positioned relative to its center. 
  yModified -= (sprite_dimensions.height / 2); 
  
  _sprite.setPosition(xModified, yModified); 
}

void Body::loadImage() {

  if(!(_texture.loadFromFile("Images/" + _image))) cerr << "Failed to load " << _image << " ." << endl;
}

void Body::setTexture() {

  _sprite.setTexture(_texture);
}

istream& operator>>(istream& in, Body& B) {

  in >> B._xPos >> B._yPos >> B._xVel >> B._yVel >> B._mass >> B._image;

  return in;
}

double Distance(double Pos1, double Pos2) {

  return Pos2 - Pos1;
}

double calcRadius(double dX, double dY) {

  return sqrt(pow(dX, 2) + pow(dY, 2));
}

double calcForce(double m1, double m2, double G, double r) {

  return (G * m1 * m2) / pow(r, 2);
}

double calcForceXY(double delta, double r, double F) {

  return F * (delta / r);
}



