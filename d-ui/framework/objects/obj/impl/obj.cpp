#include "../obj.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"

void ui::obj::g_draw_ex_parent( ) {
	g_draw( );

	/* create a new line */
	auto& g_parent = g_find_parent< window >( g_object_window );
	g_parent.g_cursor_pos.y += theme::g_init.get( )->g_map.spacing;
}