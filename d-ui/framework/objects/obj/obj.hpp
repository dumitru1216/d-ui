#pragma once
#include "../../../includes.hpp"
#include "../../theme/theme.hpp"

namespace ui {
	enum g_object_type {
		g_object_panel,
		g_object_window,
		g_object_tab,
		g_object_group,
		g_object_checkbox,
		g_object_slider,
		g_object_button,
		g_object_textbox,
		g_object_dropdown,
		g_object_colorpicker,
		g_object_keybind,
		g_object_label
	};

	/* deactivating input for objects of lower order */
	static bool g_input = true;
	class obj {
	public:
		/* parent pointer */
		obj* g_parent = nullptr;

		/* area */
		sdk::rect_t g_area = sdk::rect_t( );

		/* object type */
		g_object_type g_type;
		std::vector< std::shared_ptr< obj > > g_objects;

		/* other down */
		double g_time = 0.0;
		double g_start_hover_time = 0.0;
		double g_start_click_time = 0.0;
		double g_fade_timer = 0.0;
		double g_fading_animation_timer = 0.0;
		double g_end_hover_time = 0.0;

		/* find parent window */
		template < typename type >
		type& g_find_parent( g_object_type type_to_find ) {
			auto parent_iter = this;
			try {
				while ( parent_iter->g_type != type_to_find )
					parent_iter = parent_iter->g_parent;
			} 
			catch ( std::exception& ) { }
			return *static_cast< type* >( parent_iter );
		}

		/* animate */
		void g_animate( const sdk::rect_t& g_area );

		/* hovering */
		bool g_hovering( ) {
			return false;
		}

		/* clicking */
		bool g_clicking( ) {
			return false;
		}

		/* calculate element height */
		int g_calculate_height( ) {
			switch ( g_type ) {
				case g_object_slider:
				  return theme::g_init.get( )->g_map.spacing + theme::g_init.get( )->g_map.spacing / 2;
				case g_object_textbox:
				  return theme::g_init.get( )->g_map.spacing * 2 + theme::g_init.get( )->g_map.spacing / 2;
				case g_object_dropdown:
				case g_object_colorpicker:
				case g_object_keybind:
				case g_object_label:
				case g_object_button:
				case g_object_checkbox:
				  return g_area.h;
			}

			return g_area.h;
		}

		/* void & virtual */
		virtual void g_draw( ) = 0;
		void g_draw_ex_parent( );
	};
}