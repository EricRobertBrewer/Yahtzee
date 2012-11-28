/*
Die.hpp
Eric Brewer
12-1-10
Die class - 
*/

#ifndef DIE_ROLL_HPP
#define DIE_ROLL_HPP

#include <stdlib.h>
#include <ctime>

class Die{

public:
  Die(): _sides( 6 ), _value( 1 ) { srand( time( NULL ) ); }
  Die( unsigned int num_sides ): _sides( num_sides ), _value( 1 ) { srand( time( NULL ) ); }

  Die &operator = ( Die &other );
  bool operator == ( const Die &other );
  bool operator == ( unsigned int other );

  unsigned int roll() { return _value = rand() % _sides + 1; }
  unsigned int value() { return _value; }

private:
  unsigned int _sides;
  unsigned int _value;
};

#endif
