#include "DUNGENGINE/utils.hpp"

Vect2 Vect2::operator+(Vect2 & o)
{
    return Vect2(this->x + o.x, this->y + o.y);
}

Vect2 Vect2::operator-(Vect2 & o)
{
    return Vect2(this->x - o.x, this->y - o.y);
}

Vect2 Vect2::operator*(Vect2 & o)
{
    return Vect2(this->x * o.x, this->y * o.y);
}

Vect2 Vect2::operator/(Vect2 & o)
{
    return Vect2((int)this->x / o.x, (int)this->y / o.y);
}

Vect2 Vect2::operator+(int o)
{
    return Vect2(this->x + o, this->y + o);
}

Vect2 Vect2::operator-(int o)
{
    return Vect2(this->x - o, this->y - o);
}

Vect2 Vect2::operator*(int o)
{
    return Vect2(this->x * o, this->y * o);
}

Vect2 Vect2::operator*(float o)
{
    return Vect2((int)(this->x * o), (int) (this->y * o));
}

Vect2 Vect2::operator/(int o)
{
    return Vect2((int)this->x / o, (int)this->y / o);
}

Vect2 Vect2::operator/(float o)
{
    return Vect2((int)this->x / o, (int) this->y / o);
}

Vect2::Vect2()
{
    this->x = 0;
    this->y = 0;
}

Vect2::Vect2(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vect2::~Vect2()
{
}
