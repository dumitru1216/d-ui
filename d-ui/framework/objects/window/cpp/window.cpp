#include "../window.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"
#include "../../../input/input.hpp"
#include "../../../theme/theme.hpp"
#include "../../tab/tab.hpp"

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

	/* animate */
	g_animate( g_area );
}

void ui::window::g_draw( ) {
	/* we have not finished input frame */
	handling::input_sdk::g_finished_input_frame = false;

	/* handle input */
	think( );

	/* backround */
	warp::bindings::g_create_filled_rect(
		g_area, theme::g_init.get( )->g_map.g_backround, 3
	);

	/* outline simple */
	warp::bindings::g_create_rect(
		sdk::rect_t( g_area.x - 1, g_area.y - 1, g_area.w + 2, g_area.h + 2 ), sdk::col_t( 0, 0, 0 ), 3
	);

	/* outline anim */
	auto g_highlight = theme::g_init.get( )->g_map.g_anim_speed;
	int g_outline_anim{ 200 };

	/* run it */
	g_outline_anim = g_fade_timer > g_highlight ? 200 : int( g_fade_timer * ( 1.0 / g_highlight ) * g_outline_anim );

	/* clamp */
	if ( g_outline_anim > 200 )
		g_outline_anim = 200;

	if ( g_outline_anim > 0 ) {
		warp::bindings::g_create_rect(
			sdk::rect_t( g_area.x - 1, g_area.y - 1, g_area.w + 2, g_area.h + 2 ), theme::g_init.get( )->g_map.g_accent.g_modify_alpha( g_outline_anim ), 3
		);
	}

	/* top bar */
	warp::bindings::g_create_filled_rect(
		sdk::rect_t( g_area.x, g_area.y, g_area.w, 45 ), theme::g_init.get( )->g_map.g_top_bar, 3
	);

	/* top bar line */
	int g_bar_anim{ 1200 };

	/* run it */
	g_bar_anim = g_fade_timer > g_highlight ? 1200 : int( g_fade_timer * ( 1.0 / g_highlight ) * g_bar_anim );

	/* clamp */
	if ( g_bar_anim > g_area.w )
		g_bar_anim = g_area.w;

	if ( g_bar_anim > 0 ) {
		warp::bindings::g_create_filled_rect(
			sdk::rect_t( g_area.x + ( g_area.w / 2 ) - ( g_bar_anim / 2 ), g_area.y + 45, g_bar_anim, 1 ), theme::g_init.get( )->g_map.g_accent.g_modify_alpha( 120 ), 3
		);
	}

	/* tab system */
	std::vector< std::pair< std::shared_ptr< tab >, int > > g_tab_list;
	auto g_total_tabs_w = 0;

	std::for_each( g_objects.begin( ), g_objects.end( ), [ & ]( std::shared_ptr< obj > g_object ) {
		if ( g_object->g_type == g_object_tab ) {
			auto g_tab = std::static_pointer_cast< tab >( g_object );
		}
	} );

	handling::input_sdk::g_click_switch = false;
	g_scroll_delta = 0.0;
}