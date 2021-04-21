/*
 * map.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: benja
 */

#include "map.h"


unsigned int map::at( position p ) const
{
   const auto* i = lookup(p);
   if( !i ) throw std::out_of_range( "map: key not found" );
   return *i;
}

unsigned int& map::at( position p ) 
{
   auto* i = lookup(p);
   if( !i ) throw std::out_of_range( "map: key not found" );
   return *i;
}

unsigned int& map::operator[] ( position p )
{
   return *insert_rehash( p, 0 ). first;
}

std::ostream& map::printstatistics( std::ostream& out ) const
{
   out << "set size =            " << size( ) << "\n";
   out << "load factor =         " << loadfactor( ) << 
          " ( max = " << max_load_factor << " )\n";
   out << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}

std::ostream& operator << ( std::ostream& out,
                            std::pair< unsigned int*, bool > p )
{
   out << "( ";
   if( p. first )
      out << '&' << *( p. first );
   else
      out << "nullptr";
   out << ", ";
   if( p. second )
      out << "true";
   else
      out << "false";
   out << " )";
   return out;
}

