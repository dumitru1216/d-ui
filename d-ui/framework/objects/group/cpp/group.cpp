#include "../group.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"
#include "../../../input/input.hpp"
#include "../../../panel/panel.hpp"
#include "../../../warper/warper.hpp"

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

	/* parent */
	auto& g_parent_panel = g_find_parent< panel >( g_object_panel );
	auto& g_parent_window = g_find_parent< window >( g_object_window );

	/* cursor pos */
	auto& cursor_pos = g_parent_window.g_cursor_pos;
	const auto og_cursor_pos = cursor_pos;

	/* move all objects inside group */
	cursor_pos.x += theme::g_init.get( )->g_map.spacing;
	cursor_pos.y += theme::g_init.get( )->g_map.spacing * 2;

	/* draw group objects */
	warp::bindings::g_clip( sdk::rect_t( og_cursor_pos.x, og_cursor_pos.y + 26 + 1, g_area.w, g_area.h - 26 - 1 ), [ & ]( ) {
		cursor_pos.y -= g_scroll_offset;

		std::for_each(g_objects.begin( ),g_objects.end( ),[ & ]( std::shared_ptr< obj >& child ) {
			child->g_area = sdk::rect_t( 0, 0, g_area.w - theme::g_init.get( )->g_map.spacing * 2, theme::g_init.get( )->g_map.spacing );
			child->g_draw_ex_parent( );
		}
		);
	} );

	/* too many items; we need to be able to scroll down on this groupbox */
	if ( g_max_height - g_area.h > 0 ) {
		/* draw smth here */
	}
}