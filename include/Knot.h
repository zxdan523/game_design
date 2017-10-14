#ifndef KNOT_H
#define KNOT_H
#include <SFML/Graphics.hpp>
#include <ostream>
#include <vector>

class Knot:public sf::Transformable
{
    public:
        Knot();
        Knot(float width,float height,
             const sf::Vector2f& pos=sf::Vector2f(0.0f,0.0f));
        Knot(const Knot& k);

        Knot& operator=(const Knot& k);

        void setRect(float width,float height);
        void setWidth(float width);
        void setHeight(float height);
        float getWidth() const;
        float getHeight() const;

        /*****************************************/
        /*    (-w,-h/2)v3     width    v0(0,-h/2)*/
        /*             ----------------          */
        /*             |              |          */
        /*      height |              |(0,0)     */
        /*             |              |          */
        /*             ----------------          */
        /*     (-w,h/2)v2              v1(0,h/2) */
        /*****************************************/
        void updateVertices();
        sf::Vector2f getVertex(int i) const;
        friend std::ostream& operator<<(std::ostream& s,const Knot& k)
        {
            sf::Vector2f v1=k.getVertex(0),
                         v2=k.getVertex(1),
                         v3=k.getVertex(2),
                         v4=k.getVertex(3);
            s<<"width: "<<k.getWidth()<<", height: "<<k.getHeight()<<std::endl;
            s<<"v1:("<<v1.x<<","<<v1.y<<")"<<std::endl;
            s<<"v2:("<<v2.x<<","<<v2.y<<")"<<std::endl;
            s<<"v3:("<<v3.x<<","<<v3.y<<")"<<std::endl;
            s<<"v4:("<<v4.x<<","<<v4.y<<")"<<std::endl;
            return s;
        }
    private:
        float _width,_height;
        std::vector<sf::Vector2f> _vertices;
};
#endif
