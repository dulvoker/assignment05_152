
#ifndef POSITION_INCLUDED
#define POSITION_INCLUDED  1

#include <iostream>

struct position
{
   int x;
   int y; 

   position( ) 
      : x(0), y(0)
   { }

   position( int x, int y )  
      : x(x), y(y)
   { }  

   size_t hash( ) const;

};

bool operator == ( position p1, position p2 );

position operator + ( position p1, position p2 );

inline std::ostream& operator << ( std::ostream& out, position p ) 
{
   return out << "( " << p.x << ", " << p.y << " )";
}


#endif

