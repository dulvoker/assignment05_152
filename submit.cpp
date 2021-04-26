
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


std::pair< unsigned int*, bool >
map::insert_norehash( position p, unsigned int i )
{
    std::pair< unsigned int *, bool > ret_type;
    size_t term = abs((int) p.hash())  % buckets.size();
    for (auto &k : buckets[term]) {
        if (p == k.first) {
            ret_type.first = &k.second;
            ret_type.second = false;
            return ret_type;
        }
    }
    buckets[term].push_back(std::make_pair( p, i ));
    for (auto &k : buckets[term]) {
        if (p == k.first) {
            map_size++;
            ret_type.first = &k.second;
            ret_type.second = true;
            return ret_type;
        }
    }
}



std::ostream& map::print( std::ostream& out ) const
{
    int i = 0;
    for (auto k : buckets) {
        out<<"Bucket["<<i<<"] = ";
        for (auto z : k) {
            out<<"( {"<<z.first.x<<","<<z.first.y<<"}, "<<z.second<<" ) ";
        }
        out <<std::endl;
        i++;
    }
    return out;
}

const unsigned int* map::lookup( position p ) const
{
    size_t term = abs((int) p.hash())  % buckets.size();
    for (auto &k : buckets[term]) {
        if (p == k.first) {
            return &k.second;
        }
    }
    return nullptr;

}


unsigned int* map::lookup( position p )
{
    size_t term = abs((int) p.hash())  % buckets.size();
    for (auto &k : buckets[term]) {
        if (p == k.first) {
            unsigned int* x = &k.second;
            return x;
        }
    }
    return nullptr;

}


bool map::erase( position p )
{
    if (lookup(p) != nullptr){
        size_t term = abs((int) p.hash())  % buckets.size();
        for (auto &k : buckets[term]) {
            if (p == k.first) {
                buckets[term].remove(k);
                map_size--;
                return 1;
            }
        }
    }
    return 0;
}


void map::clear( ) {

    for(size_t term = 0; term < buckets.size(); term ++){
        buckets[term].clear();
    }
    map_size = 0;
}

void map::rehash( size_t newbucketsize )
{
    if( newbucketsize < 4 ) newbucketsize = 4;
    std::vector< buckettype > newbuckets( newbucketsize );
    for (auto k : buckets) {
        for (auto z : k) {
            newbuckets[z.first.hash() % newbucketsize].push_back(std::make_pair( z.first, z.second ));
        }
    }
    buckets.clear();
    std::swap(newbuckets, buckets);
}


std::pair< unsigned int* , bool >
map::insert_rehash( position p, unsigned int i )
{ }


map::map( std::initializer_list< std::pair< position, unsigned int >> init )
   : map( )
{ }


