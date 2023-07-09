#include "../obj.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"
#include "../../../input/input.hpp"
#include "../../checkbox/check.hpp"

void ui::obj::g_animate( const sdk::rect_t& g_area ) {
	auto& g_parent = g_find_parent<obj>( g_object_panel );

	g_fade_timer = g_parent.g_time; /* set g_fade_timer to the parent's time */

	if ( g_start_click_time != 0.0 ) {
		g_fade_timer = std::clamp( theme::g_init.get( )->g_map.g_anim_speed - ( g_parent.g_time - g_start_click_time ) *
								   0.5, theme::g_init.get( )->g_map.g_anim_speed / 2.0, theme::g_init.get( )->g_map.g_anim_speed );

		if ( g_fade_timer <= theme::g_init.get( )->g_map.g_anim_speed / 2.0 ) {
			g_start_click_time = 0.0; /* reset g_start_click_time */
			g_end_hover_time = g_parent.g_time; /* set g_end_hover_time to the parent's time */
			g_fade_timer = theme::g_init.get( )->g_map.g_anim_speed / 2.0;
		}

		g_fading_animation_timer = theme::g_init.get( )->g_map.g_anim_speed / 2.0;
	} else if ( handling::g_init.get( )->g_hovering( g_area ) ) {
		g_time = g_parent.g_time; /* set g_time to the parent's time */

		if ( g_start_hover_time == 0.0 )
			g_start_hover_time = g_parent.g_time; /* set g_start_hover_time to the parent's time */

		g_fade_timer = std::clamp( g_parent.g_time - g_start_hover_time, 0.0, theme::g_init.get( )->g_map.g_anim_speed / 2.0 );
		g_end_hover_time = g_parent.g_time; /* set g_end_hover_time to the parent's time */
		g_fading_animation_timer = theme::g_init.get( )->g_map.g_anim_speed / 2.0;
	} else {
		g_fade_timer = std::clamp( g_fading_animation_timer - ( g_parent.g_time -
								   g_end_hover_time ), 0.0, g_fading_animation_timer );
		g_start_hover_time = 0.0; /* reset g_start_hover_time */
	}
}

void ui::obj::g_draw_ex_parent( ) {
	g_draw( );

	/* create a new line */
	auto& g_parent = g_find_parent< window >( g_object_window );
	g_parent.g_cursor_pos.y += theme::g_init.get( )->g_map.spacing;
}