#pragma once
#include "../../../includes.hpp"
#include "../obj/obj.hpp"
#include "../group/group.hpp"
#include <array>

/* disable warning */
#pragma warning ( disable : 4018 )

namespace ui {
	class tab : public obj {
	private:
		sdk::divide_t divider;
	public:
		std::vector< std::shared_ptr< obj > > g_objects;
		bool g_selected = false;
		sdk::g_str g_title;

		tab( const sdk::g_str& g_title ) {
			this->g_title = g_title;
			g_type = g_object_tab;
		}
		~tab( ) { }

		void g_add_columns( int columns ) {
			divider.g_columns_per_row.push_back( columns );
		}

		void g_handle_obj( const std::shared_ptr< obj >& g_new_obj ) {
			g_new_obj->g_parent = this;
			g_objects.push_back( g_new_obj );
		}

		/* function handle group - to do */
		void g_handle_group( const std::shared_ptr< group >& new_group ) {
			g_handle_obj( new_group );
		}

		/* override draw */
		void g_draw( ) override;
	};
}