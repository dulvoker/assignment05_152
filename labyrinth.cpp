
#include "labyrinth.h"
#include "map.h"
#include <algorithm>

bool labyrinth::canstandhere( position p ) const
{
   if( p.x < 0 || p.x >= tab. size( ))
      return false;
   if( p.y < 0 || p.y > tab[p.x]. size( ))  
      return false;
   return tab[p.x][p.y] == ' '; 
}


void labyrinth::read( std::istream& in )
{
   tab. clear( );
   tab. push_back( std::string( ));

   while( in. good( ))
   {
      char c = in. get( );
      if( in. good( ))
      {
         if( c == '\n' )
            tab. push_back( std::string( ));
         else
            tab. back( ). push_back(c);
      }
   }

   // Erase empty lines from beginning:

   auto p = tab. begin( );
   while( p != tab. end( ) && p -> empty( ))
      ++ p;
   tab. erase( tab. begin( ), p );

   // Erase empty lines from end:

   while( !tab. empty( ) && tab. back( ). empty( ))
      tab. pop_back( ); 
}

std::vector< position > 
labyrinth::shortestpath( position from, position to ) const 
{
   if( !canstandhere( from ) || !canstandhere( to )) 
      return { };

   std::vector< position > unchecked;
   map reached;

   unchecked. push_back( from );
   reached. insert( from, 0 );

   std::vector< position > neighbours =
      { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }};

   while( unchecked. size( ))
   {
      position current = unchecked. back( );
      unchecked. pop_back( );
      // std::cout << "checking position " << current << " ";
      unsigned int dist = * reached. lookup( current );
      // std::cout << "with distance " << dist << "\n";

      for( const auto& n : neighbours ) 
      {
         position neighbour = current + n; 
         if( canstandhere( neighbour ))
         {
            auto p = reached. insert_rehash( neighbour, dist + 1 );
            if( p.second || *p.first > dist + 1 ) 
            {
               *p.first = dist + 1;
               unchecked. push_back( neighbour );
            }
         }
      }
   }

   std::vector< position > path;

   if( reached. contains( to ))
   {
      path. push_back( to );
      unsigned int dist = * reached. lookup( to );

      while( dist > 0 )
      {
         position next; 
         for( const auto& n : neighbours )
         {
            position neighbour = path. back( ) + n; 
            auto p = reached. lookup( neighbour );
            if( p && *p < dist )
               next = neighbour;  
         }

         path. push_back( next );
         dist = * reached. lookup( next );  
      }
      std::reverse( path. begin( ), path. end( ));
   }
   return path;
}

void labyrinth::print( std::ostream& out ) const
{
   out << "        01234567890123456789\n";
   out << "============================\n";

   for( size_t i = 0; i != tab. size( ); ++ i )
   {
      if( i < 100 ) out << ' ';
      if( i < 10 ) out << ' ';
      out << i << "   : ";
      out << tab[i] << "\n";
   }
}


void 
labyrinth::writepath( const std::vector< position > & path, char c )
{
   for( auto p : path )
   {
      if( !canstandhere(p))
         std::cout << "not a path, cannot stand on " << p << "\n";
      else
         tab[ p.x ][ p.y ] = c;
   }
}

  
std::ostream& 
operator << ( std::ostream& out, const std::vector< position > & path )
{
   out << " [ ";
   for( auto p = path. begin( ); p != path. end( ); ++ p )
   {
      if( p != path. begin( ))
         out << ", ";
      out << *p;
   }
   out << " ]";
   return out;
}


