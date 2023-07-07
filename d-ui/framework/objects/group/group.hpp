#pragma once
#include "../../../includes.hpp"
#include "../obj/obj.hpp"

namespace ui {
	class group : public obj {
	private:
		double g_scroll_offset = 0.0;
		int g_max_height = 0;
	public:
		std::vector< std::shared_ptr< obj > > g_objects;
		std::string g_title;

		/* constructor */
		group( const std::string& g_title ) {
			this->g_area = g_area;
			this->g_title = g_title;
			g_type = g_object_group;
		}
		~group( ) { }

		void g_handle_obj( const std::shared_ptr< obj >& g_new_obj ) {
			g_new_obj->g_parent = this;
			g_objects.push_back( g_new_obj );
		}

		void g_think( );

		/* override draw */
		void g_draw( ) override;
	};
}