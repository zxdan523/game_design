#include "Larry.h"
#include "util.h"
#include <algorithm>
#include <cassert>
const float Larry::KNOT_DIST=20;
Larry::Larry()
{
    _numPartition=20;
    _body=sf::VertexArray(sf::Quads,4*(_numPartition-1));
    _back_fin=sf::VertexArray(sf::Quads,2*(_numPartition-1));
}

void Larry::init()
{
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*3.0f/2.0f));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*5.0f/2.0f));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*3.0f/2.0f));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*1.0f/2.0f));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*1.0f/2.0f));
    Fish::addKnot(Knot(KNOT_DIST,KNOT_DIST*1.0f/2.0f));

    assert(_texture!=nullptr);
    assert(_textureAreas!=nullptr);
    assert(_knots.size()>=3);
    _mouth=sf::RectangleShape(sf::Vector2f(_knots[0].getHeight(),_knots[0].getHeight()));
    _mouth.setOrigin(sf::Vector2f(0.0f,_mouth.getSize().y/2.0f));
    _mouth.setTexture(_texture.get());
    _mouth.setTextureRect((*_textureAreas)["Larry_mouth"]);
    
    _eye_left=sf::RectangleShape(_mouth.getSize());
    _eye_left.setOrigin(0.5f*_eye_left.getSize());
    _eye_left.setTexture(_texture.get());
    _eye_left.setTextureRect((*_textureAreas)["Larry_eye"]);
    _eye_right=sf::RectangleShape(_mouth.getSize());
    _eye_right.setOrigin(0.5f*_eye_right.getSize());
    _eye_right.setTexture(_texture.get());
    _eye_right.setTextureRect((*_textureAreas)["Larry_eye"]);
    
    _fin_big_left=sf::RectangleShape(1.5f*_mouth.getSize());
    _fin_big_left.setOrigin(_fin_big_left.getSize());
    _fin_big_left.setTexture(_texture.get());
    _fin_big_left.setTextureRect((*_textureAreas)["Larry_fin_big_left"]);
    _fin_big_right=sf::RectangleShape(1.5f*_mouth.getSize());
    _fin_big_right.setOrigin(sf::Vector2f(_fin_big_right.getSize().x,0.0f));
    _fin_big_right.setTexture(_texture.get());
    _fin_big_right.setTextureRect((*_textureAreas)["Larry_fin_big_right"]);

    _fin_tiny_left=sf::RectangleShape(_mouth.getSize());
    _fin_tiny_left.setOrigin(_fin_tiny_left.getSize());
    _fin_tiny_left.setTexture(_texture.get());
    _fin_tiny_left.setTextureRect((*_textureAreas)["Larry_fin_tiny_left"]);
    _fin_tiny_right=sf::RectangleShape(_mouth.getSize());
    _fin_tiny_right.setOrigin(sf::Vector2f(_fin_tiny_right.getSize().x,0.0f));
    _fin_tiny_right.setTexture(_texture.get());
    _fin_tiny_right.setTextureRect((*_textureAreas)["Larry_fin_tiny_right"]);

    float tail_size=_knots[_knots.size()-1].getHeight()*256.0f/43.0f;
    _tail=sf::RectangleShape(sf::Vector2f(tail_size/2.0f,tail_size));
    _tail.setOrigin(sf::Vector2f(tail_size/2.0f,tail_size/2.0f));
    _tail.setTexture(_texture.get());
    _tail.setTextureRect((*_textureAreas)["Larry_tail"]);
    updateShape();
}

void Larry::setNumPartition(int numPartition)
{
    _numPartition=numPartition;
}

int Larry::getNumPartition() const
{
    return _numPartition;
}
void Larry::updateShape()
{
    if(_knots.size()<3) return;
    if(_numPartition<3) return;
    if((_numPartition-1)*4!=_body.getVertexCount())
    {
        _body.clear();
        _body.resize((_numPartition-1)*4);
    }
    if((_numPartition-1)*2!=_back_fin.getVertexCount())
    {
        _back_fin.clear();
        _back_fin.resize((_numPartition-1)*2);
    }
    std::vector<sf::Vector2f> vertices(_numPartition*2);
    Bezier(_knots,vertices);
    //drawBody
    int fin_begin=_numPartition*1.0f/_knots.size();
    int fin_end=fin_begin+(_numPartition-1)/2;
    float bias=_knots[1].getHeight()/2.25f;
    for(size_t i=0;i<_numPartition-1;i++)
    {
        _body[4*i].position=vertices[2*i];
        _body[4*i+1].position=vertices[2*i+1];
        _body[4*i+2].position=vertices[2*(i+1)+1];
        _body[4*i+3].position=vertices[2*(i+1)];
        if(i>=fin_begin&&i<fin_end)
        {
            size_t j=i-fin_begin;
            sf::Vector2f center=(vertices[2*i]+vertices[2*i+1])/2.0f;
            sf::Vector2f dir_up=normalize(vertices[2*i]-center);
            sf::Vector2f dir_down=normalize(vertices[2*i+1]-center);
            float fin_radius=std::max(mag(vertices[2*i]-center)-bias,0.0f);
            _back_fin[4*j].position=center+dir_up*fin_radius;
            _back_fin[4*j+1].position=center+dir_down*fin_radius;
            
            center=(vertices[2*(i+1)]+vertices[2*(i+1)+1])/2.0f;
            dir_up=normalize(vertices[2*(i+1)]-center);
            dir_down=normalize(vertices[2*(i+1)+1]-center);
            fin_radius=std::max(mag(vertices[2*(i+1)]-center)-bias,0.0f);
            _back_fin[4*j+2].position=center+dir_down*fin_radius;
            _back_fin[4*j+3].position=center+dir_up*fin_radius;
            
        
            _back_fin[4*j].color=sf::Color::Black;
            _back_fin[4*j+1].color=sf::Color::Black;
            _back_fin[4*j+2].color=sf::Color::Black;
            _back_fin[4*j+3].color=sf::Color::Black;
        }
    }
    //draw mouth
    _mouth.setPosition(_knots[0].getPosition());
    _mouth.setRotation(_knots[0].getRotation());
    //draw eyes
    _eye_left.setPosition(_knots[0].getVertex(0));
    _eye_left.setRotation(_knots[0].getRotation());
    _eye_right.setPosition(_knots[0].getVertex(1));
    _eye_right.setRotation(_knots[0].getRotation());
    //draw big fins
    _fin_big_left.setPosition(vertices[2*_numPartition*(1.0f/(_knots.size()-1))]);
    _fin_big_left.setRotation(_knots[1].getRotation());
    _fin_big_right.setPosition(vertices[2*_numPartition*(1.0f/(_knots.size()-1))+1]);
    _fin_big_right.setRotation(_knots[1].getRotation());
    //draw tiny fins
    _fin_tiny_left.setPosition(vertices[2*_numPartition*(4.0f/(_knots.size()-1))]);
    _fin_tiny_left.setRotation(_knots[4].getRotation());
    _fin_tiny_right.setPosition(vertices[2*_numPartition*(4.0f/(_knots.size()-1))+1]);
    _fin_tiny_right.setRotation(_knots[4].getRotation());
    //draw tail
    _tail.setPosition(_knots[_knots.size()-1].getPosition());
    _tail.setRotation(_knots[_knots.size()-1].getRotation());

}

void Larry::update(float deltaTime)
{
    updateShape();
}
void Larry::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.transform*=getTransform();
    
    target.draw(_tail,states);
    target.draw(_body,states);
    target.draw(_mouth,states);
    target.draw(_eye_left,states);
    target.draw(_eye_right,states);
    target.draw(_fin_big_left,states);
    target.draw(_fin_big_right,states);
    target.draw(_fin_tiny_left,states);
    target.draw(_fin_tiny_right,states);
<<<<<<< HEAD
    target.draw(_back_fin,states);
=======
    target.draw(_tail,states);

    /*for(int i=0;i<_knots.size();i++)
    {
        sf::CircleShape circle(5.0f);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(_knots[i].getPosition());
        target.draw(circle,states);
    }*/
>>>>>>> 6bb2a560a27ac7382cffaf5bfe5f8d91e789b628
}
