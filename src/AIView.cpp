#include "AIView.h"
#include "util.h"
#include "Constants.h"
#include <iostream>
AIView::AIView(const std::shared_ptr<Larry>& larry_ptr,
                    const std::shared_ptr<std::vector<std::shared_ptr<Minions>>>& minions_ptr,
                    const std::shared_ptr<Shark>& shark_ptr1,
                    const std::shared_ptr<Shark>& shark_ptr2,
                    const std::shared_ptr<Eel>& eel_ptr,
                    const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr,
                    const std::shared_ptr<PowerUpSystem>& powerup_ptr)
 {
     _larry_ptr=larry_ptr;
     _minions_ptr=minions_ptr;
     _shark_ptr1=shark_ptr1;
     _shark_ptr2=shark_ptr2;
     _eel_ptr=eel_ptr;
     _swordfish_ptr=swordfish_ptr;
     _powerup_ptr=powerup_ptr;
     _enableShark1=false;
     _enableShark2=false;
     _enableEel=false;
     _enableSwordfish=false;
 }

void AIView::resetSwordfishPtr(const std::shared_ptr<std::vector<std::shared_ptr<Swordfish>>>& swordfish_ptr)
 {
     _swordfish_ptr=swordfish_ptr;
 }

void AIView::enableShark1()
 {
     _enableShark1=true;
 }

 void AIView::disableShark1()
 {
     _enableShark1=false;
 }

 void AIView::enableShark2()
 {
     _enableShark2=true;
 }

 void AIView::disableShark2()
 {
     _enableShark2=false;
 }

 void AIView::enableEel()
 {
     _enableEel=true;
 }

 void AIView::disableEel()
 {
     _enableEel=false;
 }

 void AIView::enableSwordfish()
 {
     _enableSwordfish=true;
 }

 void AIView::disableSwordfish()
 {
     _enableSwordfish=false;
 }

void AIView::update(float deltaTime)
{
    if(_enableShark1)
    {
        updateShark(_shark_ptr1,deltaTime);
    }
    if(_enableShark2)
    {
        updateShark(_shark_ptr2,deltaTime);
    }
    updateMinions(deltaTime);
}

void AIView::updateMinions(float deltaTime)
{
    if(_minions_ptr==nullptr) return;
    PowerUp::TYPE powerUpType=_powerup_ptr->getTypeInUse();
    std::shared_ptr<sf::RectangleShape> tool=_powerup_ptr->getToolInUse();
    sf::Vector2f diff,dist,pos;
    //the effect of use different powerup tools
    switch(powerUpType)
    {
        //don't update fish
        case PowerUp::TIME_MACHINE:
            break;
        case PowerUp::DECOY:
            for(size_t i=0;i<_minions_ptr->size();i++)
            {
                if((*_minions_ptr)[i]->getState()!=Minions::NORMAL&&
                   (*_minions_ptr)[i]->getState()!=Minions::ATTACK)
                {
                    continue;
                }
                if((*_minions_ptr)[i]->getState()==Minions::ATTACK) (*_minions_ptr)[i]->recovered();
                diff=tool->getPosition()-(*_minions_ptr)[i]->getKnot(0).getPosition();
                dist=((*_minions_ptr)[i]->getHeadDistance()+(*_minions_ptr)[i]->getSpeed()*deltaTime)*normalize(diff);
                if(mag(diff)>mag(dist))
                {
                    pos=(*_minions_ptr)[i]->getKnot(0).getPosition()+dist;
                    goToPosition((*_minions_ptr)[i],pos);
                }
            }
            break;
        case PowerUp::OCTOPUS:
            for(size_t i=0;i<_minions_ptr->size();i++)
            {
                if((*_minions_ptr)[i]->getState()!=Minions::NORMAL&&
                   (*_minions_ptr)[i]->getState()!=Minions::ATTACK)
                {
                    continue;
                }
                diff=(*_minions_ptr)[i]->getKnot(0).getPosition()-tool->getPosition();
                if(mag(diff)<(*_minions_ptr)[i]->getKnot(0).getWidth()/2+tool->getSize().x/2)
                {
                    (*_minions_ptr)[i]->setAttackTarget(findNearestTarget((*_minions_ptr)[i]));
                }
                goToTarget((*_minions_ptr)[i],deltaTime);
            }
            break;
        case PowerUp::NONE:
            for(size_t i=0;i<_minions_ptr->size();i++)
            {
                (*_minions_ptr)[i]->setAttackTarget(_larry_ptr);
                if((*_minions_ptr)[i]->getState()==Minions::WEAK)
                {
                    escapeFromTarget((*_minions_ptr)[i],deltaTime);
                }
                else if((*_minions_ptr)[i]->getState()==Minions::NORMAL||
                        (*_minions_ptr)[i]->getState()==Minions::ATTACK)
                {
                    goToTarget((*_minions_ptr)[i],deltaTime);
                }
            }
            break;
    }
    if(_enableEel&&_eel_ptr!=nullptr)
    {
        sf::Vector2f eelCenter=_eel_ptr->getCenter();
        for(size_t i=0;i<_minions_ptr->size();i++)
        {
            if(_eel_ptr->getState()==Eel::RELEASE&&(*_minions_ptr)[i]->getState()!=Minions::SHOCKED)
            {
                Knot knot=(*_minions_ptr)[i]->getKnot(0);
                if(mag(eelCenter-knot.getPosition())<_eel_ptr->getAttackRadius()+knot.getWidth()/2)
                {
                    (*_minions_ptr)[i]->shocked();
                }
            }
            else if(_eel_ptr->getState()==Eel::RELEASED&&(*_minions_ptr)[i]->getState()==Minions::SHOCKED)
            {
                (*_minions_ptr)[i]->weaken();
            }
        }
    }
    else if(_enableSwordfish&&_swordfish_ptr!=nullptr)
    {
        for(size_t i=0;i<_swordfish_ptr->size();i++)
        {
            if((*_swordfish_ptr)[i]->getState()!=Swordfish::SHOOT)
            {
                continue;
            }
            sf::Vector2f center=(*_swordfish_ptr)[i]->getCenter();
            float radius=(*_swordfish_ptr)[i]->getAttackRadius();
            for(size_t j=0;j<_minions_ptr->size();j++)
            {
                if((*_minions_ptr)[j]->getState()!=Minions::SHOT)
                {
                    Knot knot=(*_minions_ptr)[j]->getKnot(0);
                    if(mag(center-knot.getPosition())<radius+knot.getWidth()/2)
                    {
                        (*_minions_ptr)[j]->shot();
                    }
                }
            }
        }
    }
    clearDeadMinions();
}

void AIView::updateShark(const std::shared_ptr<Shark>& shark,float deltaTime)
{
    PowerUp::TYPE powerUpType=_powerup_ptr->getTypeInUse();
    std::shared_ptr<sf::RectangleShape> tool=_powerup_ptr->getToolInUse();
    sf::Vector2f diff,dist,pos;
    switch(powerUpType)
    {
        case PowerUp::TIME_MACHINE:
            break;
        case PowerUp::DECOY:
            if(shark->getState()==Shark::NORMAL)
            {
                diff=tool->getPosition()-shark->getHeadPosition();
                dist=(shark->getHeadDistance()+shark->getSpeed()*deltaTime)*normalize(diff);
                if(mag(diff)>mag(dist))
                {
                    pos=shark->getHeadPosition()+dist;
                    goToPosition(shark,pos);
                }
            }
            else if(shark->getState()==Shark::CRAZY)
            {
                goToTarget(shark,deltaTime);
            }
            break;
        case PowerUp::OCTOPUS:
            if(shark->getState()==Shark::NORMAL)
            {
                diff=shark->getCenter()-tool->getPosition();
                if(mag(diff)<shark->getRadius()/2+tool->getSize().x/2)
                {
                    shark->setTarget(findNearestTarget(shark));
                }
                goToTarget(shark,deltaTime);
            }
            else if(shark->getState()==Shark::CRAZY)
            {
                goToTarget(shark,deltaTime);
            }
            break;
        case PowerUp::NONE:
            shark->setTarget(_larry_ptr);
            if(shark->getState()==Shark::WEAKEN)
            {
                escapeFromTarget(shark,deltaTime);
            }
            else if(shark->getState()==Shark::NORMAL||shark->getState()==Shark::CRAZY)
            {
                goToTarget(shark,deltaTime);
            }
            break;
    }
    if(_enableEel&&_eel_ptr!=nullptr&&_eel_ptr->getState()==Eel::RELEASE&&shark->getState()!=Shark::SHOCKED&&shark->getType()!=Shark::SHARK_UP1)
    {
        sf::Vector2f eelCenter=_eel_ptr->getCenter();
        if(mag(eelCenter-shark->getCenter())<_eel_ptr->getAttackRadius()+shark->getRadius())
        {
            shark->shocked();
        }
    }
    else if(_enableEel&&_eel_ptr!=nullptr&&_eel_ptr->getState()==Eel::RELEASED&&shark->getState()==Shark::SHOCKED)
    {
        shark->hurt();
    }
    else if(_enableSwordfish&&_swordfish_ptr!=nullptr&&shark->getState()!=Shark::SHOT&&shark->getType()!=Shark::SHARK2)
    {
        for(size_t i=0;i<_swordfish_ptr->size();i++)
        {
            if((*_swordfish_ptr)[i]->getState()!=Swordfish::SHOOT)
            {
                continue;
            }
            sf::Vector2f center=(*_swordfish_ptr)[i]->getCenter();
            float radius=(*_swordfish_ptr)[i]->getAttackRadius();
            if(mag(shark->getCenter()-center)<shark->getRadius()+radius)
            {
                shark->shot();
            }
        }
    }
    clearDeadMinions();
}

void AIView::goToTarget(const std::shared_ptr<Minions>& minions,float deltaTime)
{
    std::shared_ptr<Fish> target=minions->getAttackTarget();
    Knot knot=minions->getKnot(0);
    const std::shared_ptr<std::vector<Knot>> knots=target->getKnots();
    sf::Vector2f diff,dist;
    float touchDist;
    float headDist=minions->getHeadDistance();
    if(target.get()==_shark_ptr1.get())
    {
        diff=_shark_ptr1->getCenter()-knot.getPosition();
        touchDist=knot.getWidth()/2+_shark_ptr1->getRadius();
        
    }
    else if(target.get()==_shark_ptr2.get())
    {
        diff=_shark_ptr2->getCenter()-knot.getPosition();
        touchDist=knot.getWidth()/2+_shark_ptr2->getRadius();
    }
    else
    {
   
        float min_dist=INFITY;
        for(int i=0;i<knots->size();i++)
        {
            sf::Vector2f temp_diff=(*knots)[i].getPosition()-knot.getPosition();
            if(mag(temp_diff)-(*knots)[i].getHeight()/2<min_dist)
            {
                min_dist=mag(temp_diff)-(*knots)[i].getHeight()/2;
                diff=temp_diff;
                touchDist=knot.getWidth()/2+(*knots)[i].getHeight()/2;
            }
        }
    }
    dist=(minions->getSpeed()*deltaTime+headDist)*normalize(diff);
    float mag_diff=mag(diff);
    float mag_dist=mag(dist);

    if(mag_diff<mag_dist)
    {
        target->attacked();
        clearTarget(target);
    }
    else if(mag_diff-mag_dist<touchDist)
    {
        minions->swimTo(knot.getPosition()+normalize(diff)*(mag_dist-touchDist));
        target->attacked();
        clearTarget(target);
    }
    else
    {
        minions->swimTo(knot.getPosition()+dist);
    }
    clearDeadMinions();
}

void AIView::goToTarget(const std::shared_ptr<Shark>& shark,float deltaTime)
{
    std::shared_ptr<Fish> target=shark->getTarget();
    sf::Vector2f center=shark->getCenter();
    float radius=shark->getRadius();
    const std::shared_ptr<std::vector<Knot>> knots=target->getKnots();
    sf::Vector2f diff,dist;
    float touchDist;
    if(target.get()==_shark_ptr1.get())
    {
        diff=_shark_ptr1->getCenter()-center;
        touchDist=radius+_shark_ptr1->getRadius();
        
    }
    else if(target.get()==_shark_ptr2.get())
    {
        diff=_shark_ptr2->getCenter()-center;
        touchDist=radius+_shark_ptr2->getRadius();
    }
    else
    {
        float min_dist=INFITY;
        for(int i=0;i<knots->size();i++)
        {
            sf::Vector2f temp_diff=(*knots)[i].getPosition()-center;
            if(mag(temp_diff)-(*knots)[i].getHeight()/2<min_dist)
            {
                min_dist=mag(temp_diff)-(*knots)[i].getHeight()/2;
                diff=temp_diff;
                touchDist=radius+(*knots)[i].getHeight()/2;
            }
        }
    }
    
    dist=(shark->getHeadDistance()+shark->getSpeed()*deltaTime)*normalize(diff);
    float mag_diff=mag(diff);
    float mag_dist=mag(dist);
    
    if(mag_diff<mag_dist)
    {
        target->attacked();
        clearTarget(target);
    }
    else if(mag_diff-mag_dist<touchDist)
    {
        shark->swimTo(center+normalize(diff)*(mag_dist-touchDist));
        target->attacked();
        clearTarget(target);
    }
    else
    {
        shark->swimTo(center+dist);
        if(shark->getState()==Shark::CRAZY)
        {
            for(int i=0;i<_minions_ptr->size();i++)
            {
                Knot k=(*_minions_ptr)[i]->getKnot(0);
                if(mag(k.getPosition()-(center+dist))<k.getWidth()/2)
                {
                    (*_minions_ptr)[i]->attacked();
                    clearTarget((*_minions_ptr)[i]);
                }
            }
        }
    }
    clearDeadMinions();
}

void AIView::escapeFromTarget(const std::shared_ptr<Minions>& minions,float deltaTime)
{
    Knot knot_larry=_larry_ptr->getKnot(0);
    Knot knot_minions=minions->getKnot(0);
    sf::Vector2f diff=knot_minions.getPosition()-knot_larry.getPosition();
    sf::Vector2f dist=knot_minions.getPosition()+(minions->getHeadDistance()+minions->getSpeed()*deltaTime)*normalize(diff);
    if(dist.x<0) dist.x=0;
    if(dist.x>WINDOW_WIDTH) dist.x=WINDOW_WIDTH;
    if(dist.y<0) dist.y=0;
    if(dist.y>WINDOW_HEIGHT) dist.y=WINDOW_HEIGHT;

    minions->swimTo(dist);
}

void AIView::escapeFromTarget(const std::shared_ptr<Shark>& shark,float deltaTime)
{
    Knot knot_larry=_larry_ptr->getKnot(0);
    Knot knot_shark=shark->getKnot(0);
    sf::Vector2f diff=knot_shark.getPosition()-knot_larry.getPosition();
    sf::Vector2f dist=knot_shark.getPosition()+shark->getSpeed()*deltaTime*normalize(diff);
    if(dist.x<0) dist.x=0;
    if(dist.x>WINDOW_WIDTH) dist.x=WINDOW_WIDTH;
    if(dist.y<0) dist.y=0;
    if(dist.y>WINDOW_HEIGHT) dist.y=WINDOW_HEIGHT;

    shark->swimTo(dist);
}

void AIView::goToPosition(const std::shared_ptr<Minions>& minions,const sf::Vector2f& pos)
{
    std::shared_ptr<std::vector<Knot>> knots=_larry_ptr->getKnots();
    minions->swimTo(pos);
    for(int i=0;i<knots->size();i++)
    {
        if(mag((*knots)[i].getPosition()-pos)<(*knots)[i].getHeight()/2)
        {
            _larry_ptr->attacked();
        }
    }
}

void AIView::goToPosition(const std::shared_ptr<Shark>& shark,const sf::Vector2f& pos)
{
    std::shared_ptr<std::vector<Knot>> knots=_larry_ptr->getKnots();
    shark->swimTo(pos);
    for(int i=0;i<knots->size();i++)
    {
        if(mag((*knots)[i].getPosition()-pos)<(*knots)[i].getHeight()/2)
        {
            _larry_ptr->attacked();
        }
    }
}

void AIView::clearDeadMinions()
{
    if(_minions_ptr==nullptr) return;
    for(int i=0;i<_minions_ptr->size();i++)
    {
        if((*_minions_ptr)[i]->getState()==Minions::DIE)
        {
            _minions_ptr->erase(_minions_ptr->begin()+i);
        }
    }
}

void AIView::clearTarget(const std::shared_ptr<Fish>& target)
{
    if(target.get()==_larry_ptr.get())
    {
        return;
    }
    else if(target.get()==_shark_ptr1.get())
    {
        if(_shark_ptr1->getState()!=Shark::DIE) return;
    }
    else if(target.get()==_shark_ptr2.get())
    {
        if(_shark_ptr2->getState()!=Shark::DIE) return;
    }
    else
    {
        Minions* minions=(Minions*)target.get();
        if(minions->getState()!=Minions::DIE) return;
    }
    if(_enableShark1&&_shark_ptr1->getTarget().get()==target.get())
    {
        _shark_ptr1->setTarget(_larry_ptr);
    }
    if(_enableShark2&&_shark_ptr2->getTarget().get()==target.get())
    {
        _shark_ptr2->setTarget(_larry_ptr);
    }
    for(size_t i=0;i<_minions_ptr->size();i++)
    {
        if((*_minions_ptr)[i]->getAttackTarget().get()==target.get())
        {
            (*_minions_ptr)[i]->setAttackTarget(_larry_ptr);
        }
    }
}

std::shared_ptr<Fish> AIView::findNearestTarget(const std::shared_ptr<Fish>& fish)
{
    float min_dist=INFITY;
    std::shared_ptr<Fish> target;
    sf::Vector2f center;
    if(fish.get()==_larry_ptr.get())
    {
        return nullptr;
    }
    else if(_enableShark1&&fish.get()==_shark_ptr1.get())
    {
        center=_shark_ptr1->getCenter();
    }
    else if(_enableShark2&&fish.get()==_shark_ptr2.get())
    {
        center=_shark_ptr2->getCenter();
    }
    else
    {
        for(size_t i=0;i<_minions_ptr->size();i++)
        {
            if((*_minions_ptr)[i]->getAttackTarget().get()==target.get())
            {
                center=(*_minions_ptr)[i]->getKnot(0).getPosition();
            }
        }
    }

    //test larry
    sf::Vector2f diff;
    if(fish.get()!=_larry_ptr.get())
    {
        diff=_larry_ptr->getKnot(0).getPosition()-center;
        if(mag(diff)<min_dist)
        {
            min_dist=mag(diff);
            target=_larry_ptr;
        }
    }
    //test shark1
    if(_enableShark1&&fish.get()!=_shark_ptr1.get())
    {
        diff=_shark_ptr1->getCenter()-center;
        if(mag(diff)<min_dist)
        {
            min_dist=mag(diff);
            target=_shark_ptr1;
        }
    }
    //test shark2
    if(_enableShark2&&fish.get()!=_shark_ptr2.get())
    {
        diff=_shark_ptr2->getCenter()-center;
        if(mag(diff)<min_dist)
        {
            min_dist=mag(diff);
            target=_shark_ptr2;
        }
    }
    //test minions
    for(size_t i=0;i<_minions_ptr->size();i++)
    {
        if((*_minions_ptr)[i].get()!=fish.get())
        {
            diff=(*_minions_ptr)[i]->getKnot(0).getPosition()-center;
            if(mag(diff)<min_dist)
            {
                min_dist=mag(diff);
                target=(*_minions_ptr)[i];
            }
        }
    }
    return target;
}
