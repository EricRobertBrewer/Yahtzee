/*
Die.cpp
Eric Brewer
8/24/11
Die class implementation - 
*/

#include "Die.hpp"

Die &Die :: operator = ( Die &other ){

  _sides = other._sides;
  _value = other._value;
  return *this;
}

bool Die :: operator == ( const Die &other ){

  return _sides == other._sides && _value == other._value;
}

bool Die :: operator == ( unsigned int other ){

  return _value == other;
}
