#include <cstdio>
#include "server/server.hpp"

int main()
{
    printf("hello from %s!\n", "server_boost");

    boost::asio::io_context io;

    c_server server( io, 9999 );

    std::vector<std::thread> threads;
    for( unsigned int i = 0; i < std::thread::hardware_concurrency( ); ++i ) {
        printf( "thread: %u\n", i );
        threads.emplace_back( [&io]( ) {io.run( ); } );
    }

    for( auto& t : threads ) {
        t.join( );
    }

    return 0;
}