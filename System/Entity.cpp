/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson
 */

#include "Entity.hpp"

#include <cmath>
#include <algorithm>
#include "State.hpp"

namespace tank {

int Entity::numEnts_ = 0;

Entity::Entity(Vectorf const& pos)
    :
      pos_(pos),
      hitbox_({0}),
      type_(""),
      solid_(false),
      visible_(true),
      layer_(0),
      texture_(nullptr),
      state_ (nullptr),
      actorID_(numEnts_++)
{}

Entity::~Entity() {}

//Default draw function
void Entity::draw(IRender* const render)
{
    if(texture_)
    {
        render->draw(texture_, pos_);
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

void Entity::setTexture(Texture const* const texture)
{
    texture_ = texture;
}

void Entity::setState(State* const state)
{
    state_ = state;
}

}
