#pragma once
#include "../includes.hpp"

namespace sdk {
	using g_str = std::string;

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

		col_t g_modify_alpha( int a ) {
			return col_t( r, g, b, a );
		}

		col_t g_darker( int amount ) {
			int red = r;
			int green = g;
			int blue = b;

			// reduce the RGB values by the given amount
			red = std::fmax( 0, red - amount );
			green = std::fmax( 0, green - amount );
			blue = std::fmax( 0, blue - amount );

			return col_t( red, green, blue, a );
		}

		int r, g, b, a;
	};

	class divide_t {
	public:
		std::vector< int > g_columns_per_row;
	};
}