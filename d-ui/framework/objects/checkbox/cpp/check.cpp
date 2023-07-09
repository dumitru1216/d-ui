#include "../check.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"
#include "../../../input/input.hpp"
#include "../../../panel/panel.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"

void ui::checkbox::g_think( ) {
	auto& g_parent_window = g_find_parent< window >( g_object_window );

	/* cursor pos */
	auto& g_cursor_pos = g_parent_window.g_cursor_pos;

	/* we are going to handle the animation later */
	g_animate( sdk::rect_t( g_parent_window.g_cursor_pos.x, g_parent_window.g_cursor_pos.y, g_area.w, g_area.h ) );

	/* handling */
	if ( handling::g_init.get( )->g_clicking( sdk::rect_t( g_cursor_pos.x, g_cursor_pos.y, g_area.w, g_area.h ) ) && GetAsyncKeyState( VK_LBUTTON ) ) {
		auto as_checkbox = static_cast< checkbox* >( this );
		as_checkbox->g_checked = !as_checkbox->g_checked;
		as_checkbox->g_checked_time = g_parent_window.g_time;
	}
}

void ui::checkbox::g_draw( ) {
	/* initialize handling */
	g_think( );

	/* parent */
	auto& g_parent_panel = g_find_parent< panel >( g_object_panel );
	auto& g_parent_window = g_find_parent< window >( g_object_window );

	/* cursor pos */
	auto& g_cursor_pos = g_parent_window.g_cursor_pos;

	/* drawing */
	warp::bindings::g_create_filled_rect(
		sdk::rect_t( g_cursor_pos.x, g_cursor_pos.y, g_area.w, g_area.h ),
		g_checked ? sdk::col_t( 255, 57, 57 ) : sdk::col_t( 57, 57, 57 ), 3
	);
}