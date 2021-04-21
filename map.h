
#ifndef MAP_INCLUDED
#define MAP_INCLUDED    1

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

#include "position.h"

// Maps positions to unsigned int. 

class map 
{
   size_t map_size;           // Total number of elements.

   double max_load_factor;

   using buckettype = std::list< std::pair< position, unsigned int >> ; 
      // The type that a bucket has.

   std::vector< buckettype > buckets;

public:
   // Number of buckets cannot be zero. 
   
   map( size_t num_buckets = 4, double max_load_factor = 3.0 ) 
      : map_size(0),
        max_load_factor( max_load_factor ),
        buckets( std::vector< buckettype > ( num_buckets ))
   {
      if( num_buckets == 0 )
         throw std::runtime_error( "number of buckets cannot be zero" ); 
   }

   // Define the copy constructor, assignment operator, and destructor
   // as defaults, which means that they are just applied on the members.

   map( const map& s ) = default; 
   map& operator = ( const map& m ) = default; 
   ~map() = default; 

   map( std::initializer_list< std::pair< position, unsigned int >> init );

   const unsigned int* lookup( position p ) const;
   unsigned int* lookup( position p ); 
      // Returns a pointer to the value, nullptr if
      // p is not found. 

   bool contains( position p ) const
      { return lookup(p); }

   std::pair< unsigned int* , bool >
   insert_norehash( position p, unsigned int i );
      // The returned pair has the following form: 
      // If the insertion took place 
      // (p had no value before), 
      // then .second = true. 
      // .first points to the inserted value, or the 
      // already existing value. 
      // This method never rehashes.

   std::pair< unsigned int* , bool >
   insert_rehash( position p, unsigned int i ); 
      // The pair has the following form: 
      // If the insertion took place (no value existed), 
      // then .second = true. 
      // .first points to the inserted value, or the 
      // already existing value. 
      // This method calls insert_norehash, and
      // then checks if a rehash is necessary. 

   bool erase( position p );
      // Returns true if s was present. 

   size_t size() const
   {
      return map_size;
   }

   bool isempty() const
   {
      return map_size == 0;
   }

   double loadfactor() const 
   {
      return static_cast<double> ( map_size ) / buckets. size( ); 
         // C-style casts of form (double) map_size are deprecated. 
   }

   double standarddev() const 
   {
      double sum = 0.0;
      double lf = loadfactor();

      for ( const auto& l : buckets ) 
      {
	  double dif = l. size( ) - lf;
          sum += dif*dif;
      }

      return sqrt( sum / buckets. size( ));
   }

   void clear();
     
   void rehash( size_t newbucketsize );
      // Is this a const operation? Somewhat.
 
   std::ostream& print( std::ostream& out ) const; 

   // The functions below are not part of 
   // the usual set interface, but they are useful for 
   // testing. You don't have to implement them. 
  
   std::ostream& printstatistics( std::ostream& out ) const;

   size_t getnrbuckets( ) const  
      { return buckets. size( ); }

   const buckettype& getbucket( size_t i ) const
      { return buckets[i]; }

   unsigned int at( position p ) const;
   unsigned int& at( position p );
      // Throw exception when p is not there.
 
   unsigned int& operator[] ( position p );
      // Quietly add 0 when p is not there.  

   bool insert( position p, unsigned int i ) 
      { return insert_rehash( p, i ). second; } 
      // As defined in the lecture videos. 
};


inline std::ostream& operator << ( std::ostream& out, const map& m ) 
{
   return m. print( out );
}

std::ostream& 
operator << ( std::ostream& out, std::pair< unsigned int*, bool > p );

#endif


