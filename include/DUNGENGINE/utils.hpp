#ifndef DUNGENGINE_UTILS
#define DUNGENGINE_UTILS
class Vect2
{
private:
    /* data */
public:
    int x, y;
    Vect2(int x, int y);
    ~Vect2();
    Vect2 operator+(Vect2 & o);
    Vect2 operator-(Vect2 & o);
    Vect2 operator*(Vect2 & o);
    Vect2 operator/(Vect2 & o);
    Vect2 operator+(int o);
    Vect2 operator-(int o);
    Vect2 operator*(int o);
    Vect2 operator/(int o);
    Vect2 operator*(float o);
    Vect2 operator/(float o);
};
#endif