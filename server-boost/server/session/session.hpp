#pragma once
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class c_session : public boost::enable_shared_from_this<c_session> {
public:
	c_session( boost::asio::io_context& io ) : socket_( io ), context_( io ) {}

	typedef boost::shared_ptr<c_session> session;

	static session create( boost::asio::io_context& io ) {
		return session( new c_session( io ) );
	}

	tcp::socket& get_socket( ) {
		return socket_;
	}

	void session_start( ) {

		printf( "connection ip: %s\n", socket_.lowest_layer( ).remote_endpoint( ).address( ).to_string( ).c_str( ) );
		printf( "session is starting...\n" );
	}

private:
	tcp::socket socket_;
	boost::asio::io_context& context_;
};