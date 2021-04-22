
#include "map.h"
#include "position.h"
#include "labyrinth.h"


size_t position::hash( ) const 
{
    return abs(this->x * (1023) + this->y);
}

bool operator == ( position p1, position p2 )
{
    return (p1.x == p2.x && p1.y == p2.y);
}

position operator + ( position p1, position p2 )
{ 
   return position( p1.x + p2.x, p1.y + p2.y );
}

///////////////////////////////////////


std::pair< unsigned int*, bool >
map::insert_norehash( position p, unsigned int i )
{
    std::pair< unsigned int *, bool > ret_type;
    size_t term = abs((int) p.hash())  % buckets.size();
    for (auto k : buckets[term]){
        if (p.x == k.first.x && p.y == k.first.y) {
            ret_type.first = &k.second;
            ret_type.second = false;
            return ret_type;
        }
    }
    buckets[term].push_back(std::make_pair( p, i ));
    for (auto k : buckets[term]){
        if (p.x == k.first.x && p.y == k.first.y) {
            map_size++;
            ret_type.first = &k.second;
            ret_type.second = true;
            return ret_type;
        }
    }
}

std::ostream& map::print( std::ostream& out ) const
{ }



const unsigned int* map::lookup( position p ) const
{ }


unsigned int* map::lookup( position p )
{ }


bool map::erase( position p )
{ }


void map::clear( )
{ }


void map::rehash( size_t newbucketsize )
{ }


std::pair< unsigned int* , bool >
map::insert_rehash( position p, unsigned int i )
{ }


map::map( std::initializer_list< std::pair< position, unsigned int >> init )
   : map( )
{ }


