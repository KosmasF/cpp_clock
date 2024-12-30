#include "Object.hpp"

Object::Object(Vector2D position, float rotation)
{
    this->position = position;
    this->rotation = rotation;
}

Object::Object(Object &other)
{
    memcpy((void*)this, (void*)&other, sizeof(Object));
}

Object::~Object()
{
}