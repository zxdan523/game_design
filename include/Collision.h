/* 
 * File:   collision.h
 * Author: Nick Koirala
 *
 * Collision Detection and handling class
 * For SFML.
 
(c) 2009 - LittleMonkey Ltd
 
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
 
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
 
1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.
 
2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.
 
3. This notice may not be removed or altered from any
   source distribution.
 
   *
   * Created on 30 January 2009, 11:02
   */
 
#ifndef COLLISION_H
#define COLLISION_H
 
 
#ifndef PI
#define PI (3.14159265358979323846)
#endif
#define RADIANS_PER_DEGREE (PI/180.0)
 
 
   class Collision {
 public:
 
     virtual ~Collision();
 
     /**
      *  Test for a pixel perfect collision detection between
      *  two Sprites, Rotation and Scale is supported in this test
      *
      *  @param Object1 The first sprite
      *  @param Object2 The second sprite
      *  @AlphaLimit How opaque a pixel needs to be before a hit it registered
      */
     static bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 127);
 
     /**
      *  Test for collision using circle collision dection
      *  Radius is averaged from the dimesnions of the sprite so
      *  roughly circular objects will be much more accurate
      */
     static bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
 
     /**
      *  Test for bounding box collision using OBB Box.
      *  To test against AABB use PixelPerfectTest with AlphaLimit = 0
      *
      *  @see Collision::PixelPerfectTest
      */
     static bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
 
     /**
      *  Generate a Axis-Aligned Bounding Box for broad phase of
      *  Pixel Perfect detection.
      *
      *  @returns IntRect to round off Floating point positions.
      */
     static sf::IntRect GetAABB(const sf::Sprite& Object);
 
     /**
      *  Helper function in order to rotate a point by an Angle
      *
      *  Rotation is CounterClockwise in order to match SFML Sprite Rotation
      *
      *  @param Point a Vector2f representing a coordinate
      *  @param Angle angle in degrees
      */
     static sf::Vector2f RotatePoint(const sf::Vector2f& Point, float Angle);
 
     /**
      *  Helper function to get the minimum from a list of values
      */
     static float MinValue(float a, float b, float c, float d);
 
     /**
      *  Helper function to get the maximum from a list of values
      */
     static float MaxValue(float a, float b, float c, float d);
 
 private:
 
     Collision();
 };
 
#endif/* _COLLISION_H */
