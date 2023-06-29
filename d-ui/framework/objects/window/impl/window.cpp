#include "../window.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"
#include "../../../input/input.hpp"

void ui::window::think( ) {
	/*
		if g_pressing_move_key is false and the left mouse button is pressed (GetAsyncKeyState(VK_LBUTTON) returns a non-zero value) 
			and the mouse is hovering over a specific area (handled by handling::g_init.get()->g_hovering with a specified rectangle), then:

		set g_pressing_move_key to true.
		retrieve the current mouse position and store it in g_mouse_mpos as a sdk::pos_t object.
		calculate the click offset as the difference between g_mouse_mpos and the coordinates of g_area.
	*/
	if ( !g_pressing_move_key && GetAsyncKeyState( VK_LBUTTON ) && 
		 handling::g_init.get()->g_hovering( sdk::rect_t( g_area.x, g_area.y - 26, g_area.w, 26 ) ) ) {
		g_pressing_move_key = true;

		sdk::pos_t g_mouse_mpos{};

		warp::bindings::g_mouse_pos( g_mouse_mpos );
		g_click_offset = sdk::pos_t( g_mouse_mpos.x - g_area.x, g_mouse_mpos.y - g_area.y );
	}
	/*
		else if g_pressing_move_key is true and the left mouse button is still pressed (GetAsyncKeyState(VK_LBUTTON) 
			returns a non-zero value), then:
		retrieve the current mouse position and store it in g_mouse_mpos as a sdk::pos_t object.
		update the coordinates of g_area by subtracting the click offset (stored in g_click_offset) from the mouse 
			position (g_mouse_mpos).
	*/
	else if ( g_pressing_move_key && GetAsyncKeyState( VK_LBUTTON ) ) {
		sdk::pos_t g_mouse_mpos{};
		warp::bindings::g_mouse_pos( g_mouse_mpos );

		g_area.x = g_mouse_mpos.x - g_click_offset.x;
		g_area.y = g_mouse_mpos.y - g_click_offset.y;
	}
	/*
		we do not want to move it anymore
	*/
	else {
		g_pressing_move_key = false;
	}

	/* clamp on the screen */
	sdk::rect_t g_screen_rect{ 
		sdk::rect_t( 0, 0, 1920, 1080 )
	};

	if ( g_area.x < 0 )
		g_area.x = 0;

	if ( g_area.y - 26 < 0 )
		g_area.y = 26;

	if ( g_area.x + g_area.w > g_screen_rect.w )
		g_area.x = g_screen_rect.w - g_area.w;

	if ( g_area.y + g_area.h - 26 > g_screen_rect.h )
		g_area.y = g_screen_rect.h - g_area.h + 26;
}

void ui::window::g_draw( ) {
	/* we have not finished input frame */
	handling::input_sdk::g_finished_input_frame = false;

	/* handle input */
	think( );

	warp::bindings::g_create_text(
		sdk::vec2_t( g_area.x, g_area.y ), sdk::col_t( ), fonts::impl::g_font_t::tahoma, "text", false
	);
}