#pragma once
#include "../../includes.hpp"

namespace theme {
	class impl {
	public:
		struct g_mapper {
			int spacing = 15;
			double g_anim_speed = 0.25;

			sdk::col_t g_backround = sdk::col_t( 14, 12, 29 );
		};
		g_mapper g_map;
	};
	inline const auto g_init = std::make_unique<impl>( );
}