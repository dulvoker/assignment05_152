
#include <iostream>
#include <sstream>
#include <random>
#include <fstream>

#include "map.h"
#include "timetable.h"
#include "timer.h"

#include "position.h"
#include "labyrinth.h" 

void test(){
    map test;
    auto res = test. insert( { 0,0 }, 0 );
    std::cout << res << "\n";
    res = test. insert( {0,0}, 1 );
    std::cout << res << "\n";

    *test. insert_rehash( { 0, 0 }, 1 ). first = 100;


    timetable tab( std::string( "set" ));


    for( size_t s = 1000; s < 8 * 1000 * 1000; s = 2 * s )
    {
        map somemap1;

        timer tt;
        size_t nr = 0;
        for( int x = 0; x != s / 10000; ++ x )
        {
            for( int y = -5000; y < 5000; ++ y )
            {
                auto p = somemap1. insert_rehash( { x,y }, std::abs( x + 2 * y ));
                if( p. second )
                    ++ nr;
                p = somemap1. insert_rehash( {x,y}, 20 );
                if( p. second )
                    std::cout << "cannot be\n";
            }
        }


        somemap1. printstatistics( std::cout );


        auto somemap2 = somemap1;

        if( nr != somemap1. size( )){
//            std::cout << nr << " " << somemap1.size()<< std::endl;
            throw std::runtime_error( "counting went wrong 1" );
        }

        // We go through someset2, in order to make someset1 empty.

        for( size_t i = 0; i != somemap2. getnrbuckets( ); ++ i )
        {
            for( const auto& s : somemap2. getbucket(i))
            {
                nr -= somemap1. erase( s. first );
            }
        }

        if( nr != 0 || somemap1. size( ) != 0 )
        {
            std::cout << "nr = " << nr << "\n";
            std::cout << "somemap1. size( ) = " << somemap1. size( ) << "\n";
            throw std::runtime_error( "counting went wrong 2" );
        }

        tab. insert( s, tt. time( ));
    }


    std::cout << tab << "\n";
    std::cout << "totaltime " << tab. totaltime( ) << "\n";


#if 1
    // Encore, solving labyrinths:

    labyrinth lab;
    std::ifstream in( "test.lab" );
    lab. read( in );
    std::cout << lab << "\n";
    auto path = lab. shortestpath( { 0, 0 }, { 10, 0 } );

    std::cout << path << "\n";
    lab. writepath( path, '*' );
    std::cout << lab << "\n";
#endif
}



int main( int argc, char * argv [ ] )
{
    test();
    return 0;

}


