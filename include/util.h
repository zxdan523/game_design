#ifndef UTIL_H
#define UTIL_H
#include <cmath>
#include <random>
#include <vector>
#include "Knot.h"
#include <SFML/Graphics.hpp>
static std::random_device rd;
static std::mt19937 rnd;
static float dot(const sf::Vector2f& v1,const sf::Vector2f& v2)
{
    return v1.x*v2.x+v1.y*v2.y;
}
static float cross(const sf::Vector2f& v1,const sf::Vector2f& v2)
{
    return v1.x*v2.y-v1.y*v2.x;
}
static float mag(const sf::Vector2f& v)
{
    return sqrtf(v.x*v.x+v.y*v.y);
}
static sf::Vector2f normalize(const sf::Vector2f& v)
{
    return v/mag(v); 
}

static float angle(const sf::Vector2f& v)
{
    return atan2(v.y,v.x)*180.0f/M_PI;
}

static float randomFloat(float lower=0.0f,float upper=1.0f)
{
    std::uniform_real_distribution<float> dist(lower,upper);
    return dist(rnd);
}

static unsigned int randomInt(unsigned int up)
{
    std::uniform_int_distribution<unsigned int> dist(0,up);
    return dist(rnd);
}

static sf::Vector2f randomDirection(float r=randomFloat(),float range=2.0f*M_PI,sf::Vector2f center=sf::Vector2f(1.0f,0.0f))
{
    float angle=range*(r-0.5f);
    sf::Transform rotate(cos(angle),-sin(angle),0.0f,sin(angle),cos(angle),0.0f,0.0f,0.0f,1.0f);
    return rotate*center;
}

static void Bezier(const std::vector<Knot>& knots,std::vector<sf::Vector2f>& vertices)
{
    float total=vertices.size()/2.0f;
    std::vector<sf::Vector2f> parms_up(knots.size());
    std::vector<sf::Vector2f> parms_down(knots.size());
    float n_choose_k=1;
    parms_up[0]=n_choose_k*knots[0].getVertex(0);
    parms_down[0]=n_choose_k*knots[0].getVertex(1);
    for(size_t i=1;i<knots.size();i++)
    {
        n_choose_k*=(float)(knots.size()-i)/(float)i;
        parms_up[i]=n_choose_k*knots[i].getVertex(0);
        parms_down[i]=n_choose_k*knots[i].getVertex(1);
    }

    for(size_t i=0;i<total;i++)
    {
        float t=(float)i/(total-1);
        float accum=pow(1.0f-t,knots.size()-1);
        vertices[2*i]=sf::Vector2f(0.0f,0.0f);
        vertices[2*i+1]=sf::Vector2f(0.0f,0.0f);
        for(size_t j=0;j<knots.size();j++)
        {
            vertices[2*i]+=parms_up[j]*accum;
            vertices[2*i+1]+=parms_down[j]*accum;
            accum*=(t/(1.0f-t));
        }
    }
}
#endif
