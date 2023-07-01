#include "../input.hpp"
#include "../../warper/warper.hpp"

/* initialize this too */
bool g_input_clip_area = false;
sdk::rect_t g_input_clip_rect = sdk::rect_t( );

/* initialize that so we wont get errors */
bool handling::input_sdk::g_finished_input_frame = false;
bool handling::input_sdk::g_click_switch = false;
bool handling::input_sdk::g_old_click_switch = false;
sdk::pos_t handling::input_sdk::g_click_start;

bool g_clip_arrival( sdk::pos_t& g_pos, bool g_overlay = false ) {
	if ( !g_input_clip_area || g_overlay )
		return false;

	return !( g_pos.x >= g_input_clip_rect.x && g_pos.y >= g_input_clip_rect.y && g_pos.x <= 
			  g_input_clip_rect.x + g_input_clip_rect.w && g_pos.y <= g_input_clip_rect.y + g_input_clip_rect.h );
}

bool handling::impl::g_hovering( const sdk::rect_t& area, bool from_start,
				 bool override, bool overlay ) {
	if ( handling::input_sdk::g_finished_input_frame ) {
		return false;
	}

	/* handle mouse position */
	sdk::pos_t g_mouse_pos{};
	warp::bindings::g_mouse_pos( g_mouse_pos );

	if ( from_start ) {
		if ( handling::input_sdk::g_click_start.x && handling::input_sdk::g_click_start.y )
			return handling::input_sdk::g_click_start.x >= area.x && handling::input_sdk::g_click_start.y >= area.y && 
			          handling::input_sdk::g_click_start.x <= area.x + area.w && handling::input_sdk::g_click_start.y <= area.y + 
			              area.h && !g_clip_arrival( handling::input_sdk::g_click_start, overlay );

		return false;
	}

	return g_mouse_pos.x >= area.x && g_mouse_pos.y >= area.y && g_mouse_pos.x <= area.x + area.w && 
		g_mouse_pos.y <= area.y + area.h && !g_clip_arrival( g_mouse_pos, overlay );
}

bool handling::impl::g_clicking( const sdk::rect_t& area, bool from_start,
				 bool override, bool overlay ) {
	if ( handling::input_sdk::g_finished_input_frame ) {
		return false;
	}

	/* handle mouse position */
	sdk::pos_t g_mouse_pos{};
	warp::bindings::g_mouse_pos( g_mouse_pos );

	/* handle it */
	if ( !handling::input_sdk::g_click_switch && GetAsyncKeyState( VK_LBUTTON ) && !g_clip_arrival( g_mouse_pos, overlay ) ) { /* press key */
		handling::input_sdk::g_click_start = g_mouse_pos;

		if ( from_start ) {
			if ( g_hovering( area, true, override, overlay ) ) {
				handling::input_sdk::g_click_switch = true;
				return true;
			}
		} else if ( g_hovering( area, false, override, overlay ) ) {
			handling::input_sdk::g_click_switch = true;
			handling::input_sdk::g_finished_input_frame = true;
			return true;
		}
	} else if ( handling::input_sdk::g_click_switch && !GetAsyncKeyState( VK_LBUTTON ) ) { /* release key */
		handling::input_sdk::g_click_start = sdk::pos_t( 0, 0 );
	}

	return false;
}