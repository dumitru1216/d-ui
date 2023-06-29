#include "../input.hpp"

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