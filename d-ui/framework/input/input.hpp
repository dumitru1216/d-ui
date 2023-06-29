#pragma once
#include "../../includes.hpp"

namespace handling {
	class impl {
	public:
		bool g_hovering( const sdk::rect_t& area, bool from_start = false, 
					   bool override = false, bool overlay = false );

		bool g_clicking( const sdk::rect_t& area, bool from_start = false,
					   bool override = false, bool overlay = false );
	};
	inline const auto g_init = std::make_unique< impl>( );

	namespace input_sdk {
		extern bool g_finished_input_frame;
		extern bool g_click_switch;
		extern bool g_old_click_switch;
		extern sdk::pos_t g_click_start;
	}
}