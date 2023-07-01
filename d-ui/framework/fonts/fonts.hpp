#pragma once
#include "../../includes.hpp"

namespace fonts {
	class impl {
	public:
		void g_initialize_fonts( );

		/* fonts */
		enum g_font_t {
			default_font = 0,
			tahoma = 1,
			roboto = 2
		};

		/* safety */
		struct g_mapper {
			bool g_system_initialized = false;
		};
		g_mapper g_map;
	};
	inline const auto g_init = std::make_unique<impl>( );
}