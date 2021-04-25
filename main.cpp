
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

        if( nr != somemap1. size( ))
            throw std::runtime_error( "counting went wrong 1" );

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

    map test;
    auto res = test. insert_norehash( { 0,0 }, 1 );
    res = test. insert_norehash( {0,0}, 0 );
    test. insert_norehash( {0,1}, 2 );
    test. insert_norehash( {0,3}, 3 );
    test. insert_norehash( {0,2}, 4 );
    test. insert_norehash( {0,4}, 5 );
    test. insert_norehash( {0,5}, 6 );
    test. insert_norehash( {0,6}, 7 );

    *test.insert_norehash({0,1}, 4).first = 12123123;

    std::cout << test ;
//    map test2;
//    position q(4,5);
//    position w(8,10);
//    position e(3,2);
//    position d(5,1);
//    position r(1,5);
//    test2.insert_norehash(q, 12);
//    test2.insert_norehash(w, 13);
//    test2.insert_norehash(e, 14);
//    test2.insert_norehash(r, 15);
////    std::cout<<test2.insert_norehash(d, 16) ;
////    *test2.insert_norehash(d,16).first = 23;
//    std::cout<<test2;
    return 0;

}


