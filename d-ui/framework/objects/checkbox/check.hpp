#pragma once
#include "../../../includes.hpp"
#include "../obj/obj.hpp"

namespace ui {
	class checkbox : public obj {
	public:
		sdk::g_str g_label;
		double g_checked_time = 0.0;
		bool g_checked = false;

		/* constructor */
		checkbox( const sdk::g_str& label ) {
			this->g_label = label;
			g_type = g_object_checkbox;
		}
		~checkbox( ) { }

		/* init + drawing */
		void think( );
		void g_draw( ) override;
	};
}