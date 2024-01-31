#pragma once

#include <cmath>
class Vec3
{
    private : 
        float _x{};
        float _y{};
        float _z{};
    
    public :
        //Binary Operation.
        Vec3(float x, float y, float z) : _x{x},_y{y},_z{z}
        {}
        Vec3();

        Vec3& operator=(Vec3& other) = default;
        Vec3 operator+(Vec3 other)
        {
           return  {_x+other._x,_y+other._y,_z+other._z};
        }
        Vec3 operator-(Vec3& other) const
        {
           return  {_x-other._x,_y-other._y,_z-other._z};
        }
        Vec3 operator*(float scalar) const
        {
            return {scalar*_x,scalar*_y,scalar*_z};
        }
        Vec3 operator/(float scalar) const 
        {
            return {_x/scalar,_y/scalar,_z/scalar};
        }
        Vec3 operator*(Vec3& other) const
        {
            return {_x*other._x,_y*other._y,_z*other._z};
        }
        

        float length(Vec3& other) const
        {
            return std::sqrt(pow(_x-other._x,2)
                            +   pow(_y-other._y,2)
                            +   pow(_z-other._z,2));
        }
};