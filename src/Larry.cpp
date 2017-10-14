#include "Larry.h"
#include "util.h"
Larry::Larry()
{
    _numPartition=20;
    _body=sf::VertexArray(sf::Quads,4*(_numPartition-1));
}

void Larry::init()
{
    Fish::addKnot(Knot(20.0f,20.0f));
    Fish::addKnot(Knot(20.0f,30.0f));
    Fish::addKnot(Knot(20.0f,50.0f));
    Fish::addKnot(Knot(20.0f,30.0f));
    Fish::addKnot(Knot(20.0f,10.0f));
    Fish::addKnot(Knot(20.0f,10.0f));
    Fish::addKnot(Knot(20.0f,10.0f));

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
    if(_knots.size()<2) return;
    if(_numPartition<2) return;
    if((_numPartition-1)*4!=_body.getVertexCount())
    {
        _body.clear();
        _body.resize((_numPartition-1)*4);
    }
    std::vector<sf::Vector2f> vertices(_numPartition*2);
    Bezier(_knots,vertices);
    //drawBody
    for(size_t i=0;i<_numPartition-1;i++)
    {
        _body[4*i].position=vertices[2*i];
        _body[4*i+1].position=vertices[2*i+1];
        _body[4*i+2].position=vertices[2*(i+1)+1];
        _body[4*i+3].position=vertices[2*(i+1)];
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
    //draw eyes
    _tail.setPosition(_knots[_knots.size()-1].getPosition());
    _tail.setRotation(_knots[_knots.size()-1].getRotation());

}

void Larry::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    states.transform*=getTransform();
    target.draw(_body,states);
    target.draw(_mouth,states);
    target.draw(_eye_left,states);
    target.draw(_eye_right,states);
    target.draw(_fin_big_left,states);
    target.draw(_fin_big_right,states);
    target.draw(_fin_tiny_left,states);
    target.draw(_fin_tiny_right,states);
    target.draw(_tail,states);
}
