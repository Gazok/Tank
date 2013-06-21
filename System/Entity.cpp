#include "Entity.hpp"

#include <cmath>
#include <algorithm>
#include "State.hpp"

namespace tank {

int Entity::numEnts_ = 0;

Entity::Entity(Vectorf const& pos)
    : pos_(pos)
    , rot_(0)
    , hitbox_({0})
    , type_("")
    , solid_(false)
    , visible_(true)
    , layer_(0)
    , state_ (nullptr)
    , graphic_(nullptr)
    , actorID_(numEnts_++)
{}

Entity::~Entity() {}

//Default draw function
void Entity::draw()
{
    if(graphic_)
    {
        graphic_->draw(pos_, rot_);
    }
}

std::vector<Entity*> Entity::collide(std::string type)
{
    std::vector<std::unique_ptr<Entity>> const& origList = state_->getEntities();
    std::vector<Entity*> entList;
    std::vector<Entity*> collisions;

    for(auto& unique : origList)
    {
        if(type == unique->getType())
        {
            entList.push_back(unique.get());
        }
    }
    /*if(type != "")
    {
        entList.erase(std::remove_if(entList.begin(), entList.end(),
                                     [type](Entity* ent)
        {
            return ent->getType() != type;
        }), entList.end());
    }*/

    for(auto ent : entList)
    {
        if(ent != this)
        {
            Rect const& A = hitbox_;
            Rect const& B = ent->getHitbox();

            const double leftA   = A.x + pos_.x;
            const double leftB   = B.x + ent->getPos().x;
            const double rightA  = A.x + A.w + pos_.x;
            const double rightB  = B.x + B.w + ent->getPos().x;
            const double topA    = A.y + pos_.y;
            const double topB    = B.y + ent->getPos().y;
            const double bottomA = A.y + A.h + pos_.y;
            const double bottomB = B.y + B.h + ent->getPos().y;

            if(leftA > rightB) continue;
            if(topA > bottomB) continue;
            if(rightA < leftB) continue;
            if(bottomA < topB) continue;

            collisions.push_back(ent);
        }
    }

    return collisions;
}

void Entity::setPos(Vectorf const& pos)
{
    pos_ = pos;
}

void Entity::setHitbox(Rect const& hitbox)
{
    hitbox_ = hitbox;
}

void Entity::setSolid(bool solid)
{
    solid_ = solid;
}

void Entity::setVisible(bool visible)
{
    visible_ = visible;
}

void Entity::setLayer(int layer)
{
    layer_ = layer;
}

void Entity::setState(State* const state)
{
    state_ = state;
}

}
