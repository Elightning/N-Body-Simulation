/*********************************************/
/* Name: Eamon Lightning                     */
/* Program: N-Body Simulation                */
/* Date: March 2, 2015                       */
/* File: NBody.hpp                           */
/*********************************************/

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Body : public sf::Drawable {
  public: 
    Body(double radius, const sf::Vector2f& window_size);
    ~Body();
    friend istream& operator>>(istream& in, Body& B);
    void loadImage();
    void setTexture();
    void universeToWindow();
    void step(double dT);

    double _xPos;
    double _yPos;
    double _xVel;
    double _yVel;
    double _xForce;
    double _yForce;
    double _mass;

    const double _radius_universe;    
    const sf::Vector2f _window_size;

    string _image;
    sf::Texture _texture;
    sf::Sprite _sprite;

  private:
    void calcVel(double xAccel, double yAccel, double dT);
    void calcPos(double dT);
    void virtual draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

double Distance(double Pos1, double Pos2);
double calcRadius(double dX, double dY);
double calcForce(double m1, double m2, double G, double r);
double calcForceXY(double delta, double r, double F);