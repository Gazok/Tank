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
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#ifndef TANK_GRAPHIC_HPP
#define TANK_GRAPHIC_HPP

#include "../Utility/Vector.hpp"
#include "../Utility/Rect.hpp"

namespace tank {

class Graphic
{
public:
    Graphic()
        : pos_({})
        , rot_(0.f)
        , relativeToParent_(true) {}
    virtual ~Graphic() {}

    virtual void setPos(Vectorf pos)
    {
        pos_ = pos;
    }
    virtual Vectorf getPos() const
    {
        return pos_;
    }

    virtual void setRotation(float angle)
    {
        rot_ = angle;
    }
    virtual float getRotation() const
    {
        return rot_;
    }

    void drawRelativeToParent(bool relative)
    {
        relativeToParent_ = relative;
    }
    bool isRelativeToParent() const
    {
        return relativeToParent_;
    }

    virtual void setSize(Vectorf) = 0;
    virtual Vectorf getSize() const = 0;

    virtual void setOrigin(Vectorf) = 0;
    virtual Vectorf getOrigin() const = 0;

    virtual void setClip(Rect) = 0;
    virtual Rect getClip() const = 0;

    virtual Vector<unsigned int> getTextureSize() const = 0;

    virtual void draw(Vectorf parentPos, float parentRot, Vectorf camera = {0,0}) = 0;
private:
    Vectorf pos_;
    float rot_;
    bool relativeToParent_;
};

}

#endif /* TANK_GRAPHIC_HPP */
