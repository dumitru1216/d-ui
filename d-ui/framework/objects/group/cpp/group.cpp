#include "../group.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"
#include "../../../input/input.hpp"

void ui::group::g_think( ) {
	auto& g_parent_window = g_find_parent< window >( g_object_window );

	/* we are going to handle the animation later */

	/* calculate how much room we have for new objects */
	g_max_height = 26 + theme::g_init.get( )->g_map.spacing * 2;

	/* calculate and add the height of each child object to g_max_height */
	std::for_each( g_objects.begin( ), g_objects.end( ), [ & ]( std::shared_ptr<obj>& child ) {
		g_max_height += child->g_calculate_height( );
	} );

	if ( g_area.h > g_max_height )
		g_max_height = g_area.h; /* if g_area.h is greater than g_max_height, update g_max_height to g_area.h */

	/* manage scrolling */
	if ( handling::g_init.get()->g_hovering( sdk::rect_t( g_parent_window.g_cursor_pos.x, g_parent_window.g_cursor_pos.y,
		                   g_area.w, g_area.h ) ) && g_parent_window.g_scroll_delta != 0.0 ) {
		g_scroll_offset += g_parent_window.g_scroll_delta * 10.0;
		g_scroll_offset = std::clamp< double >( g_scroll_offset, 0, static_cast< double >( g_max_height - g_area.h ) );
	}
}

void ui::group::g_draw( ) {
	/* initialize handling */
	g_think( );
}