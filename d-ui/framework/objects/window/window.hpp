#pragma once
#include "../../../includes.hpp"
#include "../obj/obj.hpp"

namespace ui {
	class window : public obj {
		std::string g_title;
	public:
		sdk::pos_t g_cursor_pos;

		window( const sdk::rect_t& g_area, std::string g_title ) {
			this->g_area = g_area;
			this->g_title = g_title;

			/* object type */
			g_type = g_object_window;
		};
		~window( ) { }

		/* override func */
		void g_draw( ) override;
	};
}