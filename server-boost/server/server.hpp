#pragma once
#include "session/session.hpp"

class c_server {
public:
	c_server( boost::asio::io_context& io, short port ) :
		context_( io ), acceptor_( io, boost::asio::ip::tcp::endpoint( tcp::v4( ), port ) ) {

		start_accept( );
	}

private:
	void start_accept( ) {
		c_session::session new_session = c_session::create( context_ );
		acceptor_.async_accept( new_session->get_socket( ).lowest_layer( ),
			boost::bind( &c_server::on_accept, this, new_session, boost::asio::placeholders::error ) );
	}

	void on_accept( c_session::session s, const boost::system::error_code& err ) {
		if( !err ) {
			s->session_start( );
		}
		else {
			printf( "error: %s\n", err.message( ) );
		}

		start_accept( );
	}

	boost::asio::io_context& context_;
	tcp::acceptor acceptor_;
};