#pragma once
#include "../includes.hpp"

namespace sdk {
	struct vec2_t {
		/* default builders */
		vec2_t( ) : x( 0 ), y( 0 ) { }
		vec2_t( float x, float y ) : x( x ), y( y ) { }
		~vec2_t( ) { }

		/* parameters */
		float x;
		float y;
	};

	struct rect_t {
		rect_t( ) : x( 0 ), y( 0 ), w( 0 ), h( 0 ) { }
		rect_t( int x, int y, int w, int h ) : x( x ), y( y ), w( w ), h( h ) { }
		~rect_t( ) { }

		int x, y, w, h;
	};

	struct pos_t {
		pos_t( ) : x( 0 ), y( 0 ) { }
		pos_t( int x, int y ) : x( x ), y( y ) { }
		~pos_t( ) { }

		int x, y;
	};

	struct col_t {
		col_t( ) : r( 255 ), g( 255 ), b( 255 ), a( 255 ) { } /* default white */
		col_t( int r, int g, int b, int a = 255 ) : r( r ), g( g ), b( b ), a( a ) { }
		~col_t( ) { }

		std::uint32_t g_convert( ) {
			std::uint32_t out = 0;

			out = static_cast< std::uint32_t >( this->r ) << 0;
			out |= static_cast< std::uint32_t >( this->g ) << 8;
			out |= static_cast< std::uint32_t >( this->b ) << 16;
			out |= static_cast< std::uint32_t >( this->a ) << 24;

			return out;
		}

		int r, g, b, a;
	};
}