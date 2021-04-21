
#ifndef LABYRINTH_INCLUDED
#define LABYRINTH_INCLUDED   1

#include "position.h"
#include <string>
#include <vector>

struct labyrinth
{
   std::vector< std::string > tab;

   labyrinth( ) = default;

   labyrinth( const std::vector< std::string > & tab )
      : tab( tab )
   { }

   labyrinth( std::vector< std::string > && tab )
      : tab( std::move( tab ))  
   { }

   bool canstandhere( position p ) const; 
      // True if you can stand on this position. 
      // p.x is the row, p.y is the column.
      // This is the case if position is in the labyrinth, and
      // contains a space.  
      // This method is completely robust. It accepts
      // negative positions and positions that out of range.
      // It just returns falls in such cases. 

   void read( std::istream& in );   

   std::vector< position > 
   shortestpath( position from, position to ) const;
      // We return empty vector, if no path was found.

   void print( std::ostream& out ) const; 

   void writepath( const std::vector< position > & path, char c );
      // write the path using c. 

};

inline std::ostream& operator << ( std::ostream& out, const labyrinth& lab )
{
   lab. print( out );
   return out;
}

std::ostream& 
operator << ( std::ostream& out, const std::vector< position > & path );

#endif


