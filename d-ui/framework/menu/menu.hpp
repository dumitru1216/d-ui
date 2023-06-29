#pragma once
#include "../dui_includes.hpp"

namespace menu {
	class impl {
	public:
		void g_run( );
		void g_init( );
	};
	inline const auto g_init = std::make_unique< impl >( );
}