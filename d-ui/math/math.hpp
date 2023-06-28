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
}