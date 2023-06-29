#pragma once
#include "../../includes.hpp"

namespace theme {
	class impl {
	public:
		struct g_mapper {
			int spacing = 15;
		};
		g_mapper g_map;
	};
	inline const auto g_init = std::make_unique<impl>( );
}