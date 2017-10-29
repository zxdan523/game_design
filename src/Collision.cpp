/* 
 * File:   collision.cpp
 * Author: Nick
 * 
 * Created on 30 January 2009, 11:02
 */
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Collision.h"
 
Collision::Collision() {
}
 
Collision::~Collision() {
}
 
//sf::IntRect Collision::GetAABB(const sf::Sprite& Object) {
// 
//  //Get the top left corner of the sprite regardless of the sprite's center
//  //This is in Global Coordinates so we can put the rectangle back into the right place
//  sf::Vector2f pos = Object.TransformToGlobal(sf::Vector2f(0, 0));
// 
//  //Store the size so we can calculate the other corners
//  sf::Vector2f size = Object.GetSize();
// 
//  float Angle = Object.GetRotation();
// 
//  //Bail out early if the sprite isn't rotated
//  if (Angle == 0.0f) {
//    return sf::IntRect(static_cast<int> (pos.x),
//		       static_cast<int> (pos.y),
//		       static_cast<int> (pos.x + size.x),
//		       static_cast<int> (pos.y + size.y));
//  }
// 
//  //Calculate the other points as vectors from (0,0)
//  //Imagine sf::Vector2f A(0,0); but its not necessary
//  //as rotation is around this point.
//  sf::Vector2f B(size.x, 0);
//  sf::Vector2f C(size.x, size.y);
//  sf::Vector2f D(0, size.y);
// 
//  //Rotate the points to match the sprite rotation
//  B = RotatePoint(B, Angle);
//  C = RotatePoint(C, Angle);
//  D = RotatePoint(D, Angle);
// 
//  //Round off to int and set the four corners of our Rect
//  int Left = static_cast<int> (MinValue(0.0f, B.x, C.x, D.x));
//  int Top = static_cast<int> (MinValue(0.0f, B.y, C.y, D.y));
//  int Right = static_cast<int> (MaxValue(0.0f, B.x, C.x, D.x));
//  int Bottom = static_cast<int> (MaxValue(0.0f, B.y, C.y, D.y));
// 
//  //Create a Rect from out points and move it back to the correct position on the screen
//  sf::IntRect AABB = sf::IntRect(Left, Top, Right, Bottom);
//  AABB.Offset(static_cast<int> (pos.x), static_cast<int> (pos.y));
//  return AABB;
//}
// 
//float Collision::MinValue(float a, float b, float c, float d) {
//  float min = a;
// 
//  min = (b < min ? b : min);
//  min = (c < min ? c : min);
//  min = (d < min ? d : min);
// 
//  return min;
//}
// 
//float Collision::MaxValue(float a, float b, float c, float d) {
//  float max = a;
// 
//  max = (b > max ? b : max);
//  max = (c > max ? c : max);
//  max = (d > max ? d : max);
// 
//  return max;
//}
// 
//sf::Vector2f Collision::RotatePoint(const sf::Vector2f& Point, float Angle) {
//  Angle = Angle * RADIANS_PER_DEGREE;
//  sf::Vector2f RotatedPoint;
//  RotatedPoint.x = Point.x * cos(Angle) + Point.y * sin(Angle);
//  RotatedPoint.y = -Point.x * sin(Angle) + Point.y * cos(Angle);
//  return RotatedPoint;
//}
// 
//bool Collision::PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
//  //Get AABBs of the two sprites
//  sf::IntRect Object1AABB = GetAABB(Object1);
//  sf::IntRect Object2AABB = GetAABB(Object2);
// 
//  sf::IntRect Intersection;
// 
//  if (Object1AABB.Intersects(Object2AABB, &Intersection)) {
// 
//    //We've got an intersection we need to process the pixels
//    //In that Rect.
// 
//    //Bail out now if AlphaLimit = 0
//    if (AlphaLimit == 0) return true;
// 
//    //There are a few hacks here, sometimes the TransformToLocal returns negative points
//    //Or Points outside the image.  We need to check for these as they print to the error console
//    //which is slow, and then return black which registers as a hit.
// 
//    sf::IntRect O1SubRect = Object1.GetSubRect();
//    sf::IntRect O2SubRect = Object2.GetSubRect();
// 
//    sf::Vector2i O1SubRectSize(O1SubRect.GetWidth(), O1SubRect.GetHeight());
//    sf::Vector2i O2SubRectSize(O2SubRect.GetWidth(), O2SubRect.GetHeight());
// 
//    sf::Vector2f o1v;
//    sf::Vector2f o2v;
//    //Loop through our pixels
//    for (int i = Intersection.Left; i < Intersection.Right; i++) {
//      for (int j = Intersection.Top; j < Intersection.Bottom; j++) {
// 
//	o1v = Object1.TransformToLocal(sf::Vector2f(i, j)); //Creating Objects each loop :(
//	o2v = Object2.TransformToLocal(sf::Vector2f(i, j));
// 
//	//Hack to make sure pixels fall withint the Sprite's Image
//	if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
//                        o1v.x < O1SubRectSize.x && o1v.y < O1SubRectSize.y &&
//	    o2v.x < O2SubRectSize.x && o2v.y < O2SubRectSize.y) {
// 
//	  //If both sprites have opaque pixels at the same point we've got a hit
//	  if ((Object1.GetPixel(static_cast<int> (o1v.x), static_cast<int> (o1v.y)).a > AlphaLimit) &&
//	      (Object2.GetPixel(static_cast<int> (o2v.x), static_cast<int> (o2v.y)).a > AlphaLimit)) {
//	    return true;
//	  }
//	}
//      }
//    }
//    return false;
//  }
//  return false;
//}

bool Collision::CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
  //Simplest circle test possible
  //Distance between points <= sum of radius
 
  float Radius1 = (Object1.getGlobalBounds().width + Object1.getGlobalBounds().height) / 4;
  float Radius2 = (Object2.getGlobalBounds().width + Object2.getGlobalBounds().height) / 4;
  float xd = Object1.getPosition().x - Object2.getPosition().x;
  float yd = Object1.getPosition().y - Object2.getPosition().y;
 
  return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}
 
//From Rotated Rectangles Collision Detection, Oren Becker, 2001
 
//bool Collision::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
// 
//  sf::Vector2f A, B, C, BL, TR;
//  sf::Vector2f HalfSize1 = Object1.GetSize();
//  sf::Vector2f HalfSize2 = Object2.GetSize();
// 
//  //For somereason the Vector2d divide by operator
//  //was misbehaving
//  //Doing it manually
//  HalfSize1.x /= 2;
//  HalfSize1.y /= 2;
//  HalfSize2.x /= 2;
//  HalfSize2.y /= 2;
//  //Get the Angle we're working on
//  float Angle = Object1.GetRotation() - Object2.GetRotation();
//  float CosA = cos(Angle * RADIANS_PER_DEGREE);
//  float SinA = sin(Angle * RADIANS_PER_DEGREE);
// 
//  float t, x, a, dx, ext1, ext2;
// 
//  //Normalise the Center of Object2 so its axis aligned an represented in
//  //relation to Object 1
//  C = Object2.GetPosition();
// 
//  C -= Object1.GetPosition();
// 
//  C = RotatePoint(C, Object2.GetRotation());
// 
//  //Get the Corners
//  BL = TR = C;
//  BL -= HalfSize2;
//  TR += HalfSize2;
// 
//  //Calculate the vertices of the rotate Rect
//  A.x = -HalfSize1.y*SinA;
//  B.x = A.x;
//  t = HalfSize1.x*CosA;
//  A.x += t;
//  B.x -= t;
// 
//  A.y = HalfSize1.y*CosA;
//  B.y = A.y;
//  t = HalfSize1.x*SinA;
//  A.y += t;
//  B.y -= t;
// 
//  t = SinA * CosA;
// 
//  // verify that A is vertical min/max, B is horizontal min/max
//  if (t < 0) {
//    t = A.x;
//    A.x = B.x;
//    B.x = t;
//    t = A.y;
//    A.y = B.y;
//    B.y = t;
//  }
// 
//  // verify that B is horizontal minimum (leftest-vertex)
//  if (SinA < 0) {
//    B.x = -B.x;
//    B.y = -B.y;
//  }
// 
//  // if rr2(ma) isn't in the horizontal range of
//  // colliding with rr1(r), collision is impossible
//  if (B.x > TR.x || B.x > -BL.x) return false;
// 
//  // if rr1(r) is axis-aligned, vertical min/max are easy to get
//  if (t == 0) {
//    ext1 = A.y;
//    ext2 = -ext1;
//  }// else, find vertical min/max in the range [BL.x, TR.x]
//  else {
//    x = BL.x - A.x;
//    a = TR.x - A.x;
//    ext1 = A.y;
//    // if the first vertical min/max isn't in (BL.x, TR.x), then
//    // find the vertical min/max on BL.x or on TR.x
//    if (a * x > 0) {
//      dx = A.x;
//      if (x < 0) {
//	dx -= B.x;
//	ext1 -= B.y;
//	x = a;
//      } else {
//	dx += B.x;
//	ext1 += B.y;
//      }
//      ext1 *= x;
//      ext1 /= dx;
//      ext1 += A.y;
//    }
// 
//    x = BL.x + A.x;
//    a = TR.x + A.x;
//    ext2 = -A.y;
//    // if the second vertical min/max isn't in (BL.x, TR.x), then
//    // find the local vertical min/max on BL.x or on TR.x
//    if (a * x > 0) {
//      dx = -A.x;
//      if (x < 0) {
//	dx -= B.x;
//	ext2 -= B.y;
//	x = a;
//      } else {
//	dx += B.x;
//	ext2 += B.y;
//      }
//      ext2 *= x;
//      ext2 /= dx;
//      ext2 -= A.y;
//    }
//  }
// 
//  // check whether rr2(ma) is in the vertical range of colliding with rr1(r)
//  // (for the horizontal range of rr2)
//  return !((ext1 < BL.y && ext2 < BL.y) ||
//	   (ext1 > TR.y && ext2 > TR.y));
// 
//}
