#pragma once
#include "../../includes.hpp"
#include "../objects/window/window.hpp"
#include "../objects/obj/obj.hpp"

namespace ui {
	class panel : public obj {
		std::vector< std::shared_ptr< window > > g_windows;
	public:
		panel( ) {
			g_type = g_object_panel;
		}
		~panel( ) { }

		/* add window */
		void g_add_window( const std::shared_ptr< window >& g_new_window ) {
			g_new_window->g_parent = this;
			g_windows.push_back( g_new_window );
		}

		/* overriders */
		void g_draw( ) override { };
		void g_render( double g_t );
	};
}