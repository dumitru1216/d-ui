#include "../group.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"
#include "../../../input/input.hpp"
#include "../../../panel/panel.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"

void ui::group::g_think( ) {
	auto& g_parent_window = g_find_parent< window >( g_object_window );

	/* we are going to handle the animation later */
	g_animate( sdk::rect_t( g_parent_window.g_cursor_pos.x, g_parent_window.g_cursor_pos.y, g_area.w, g_area.h ) );

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
	auto& g_cursor_pos = g_parent_window.g_cursor_pos;
	const auto og_cursor_pos = g_cursor_pos;

	/* move all objects inside group */
	g_cursor_pos.x += theme::g_init.get( )->g_map.spacing;
	g_cursor_pos.y += theme::g_init.get( )->g_map.spacing * 2;

	/* drawing */
	warp::bindings::g_create_filled_rect(
		sdk::rect_t( g_cursor_pos.x - 10, g_cursor_pos.y + 5, g_area.w, g_area.h ), 
		sdk::col_t( 22, 18, 43 ), 3
	);

	/* im too lazy to make something fancy atm so im just going to do a simple style / max 15 topbar */
	warp::bindings::g_create_filled_rect(
		sdk::rect_t( g_cursor_pos.x - 10, g_cursor_pos.y + 28, g_area.w, 1 ),
		sdk::col_t( 0, 0, 0 ), 0
	);

	/* animation */
	auto g_highlight = theme::g_init.get( )->g_map.g_anim_speed + 
		/* increase animation time without creating another double */ 0.15;
	int g_bar_anim{ 1200 };
	int g_outline_anim{ 200 };

	/* initialization */
	g_bar_anim = g_fade_timer > g_highlight ? 1200 : int( g_fade_timer * ( 1.0 / g_highlight ) * g_bar_anim );
	g_outline_anim = g_fade_timer > g_highlight ? 200 : int( g_fade_timer * ( 1.0 / g_highlight ) * g_outline_anim );

	/* clamping */
	if ( g_outline_anim > 200 )
		g_outline_anim = 200;

	if ( g_bar_anim > g_area.w )
		g_bar_anim = g_area.w;

	if ( g_bar_anim > 0 ) {
		warp::bindings::g_create_filled_rect(
			sdk::rect_t( ( g_cursor_pos.x - 10 ) + ( g_area.w / 2 ) - ( g_bar_anim / 2 ),
			g_cursor_pos.y + 28, g_bar_anim, 1 ), theme::g_init.get( )->g_map.g_accent.g_modify_alpha( 120 ), 3
		);
	}

	if ( g_outline_anim > 0 ) {
		warp::bindings::g_create_rect(
			sdk::rect_t( g_cursor_pos.x - 10 - 1, g_cursor_pos.y + 5 - 1, g_area.w + 1, g_area.h + 1 ),
			theme::g_init.get( )->g_map.g_accent.g_modify_alpha( g_outline_anim ), 3
		);
	}

	warp::bindings::g_create_text(
		sdk::vec2_t( g_cursor_pos.x - 3, g_cursor_pos.y + 8 ), sdk::col_t( ).g_modify_alpha( 200 ), 
		             fonts::impl::g_font_t::roboto, this->g_title.c_str( ), false
	);

	/* clip elements */
	warp::bindings::g_clip( sdk::rect_t( og_cursor_pos.x, og_cursor_pos.y + 26 + 1, g_area.w, g_area.h - 26 - 1 ), [ & ]( ) {
		std::for_each( g_objects.begin( ), g_objects.end( ), [ & ]( std::shared_ptr<obj>& child ) {
			child->g_area = sdk::rect_t( 0, 0, g_area.w - theme::g_init.get( )->g_map.spacing * 2, theme::g_init.get( )->g_map.spacing );
			/* set the child's area to a new rectangle with adjusted width and height */

			child->g_draw_ex_parent( ); /* invoke the g_draw_ex_parent function for the child */
		} );
	} );

	/* too many items; we need to be able to scroll down on this groupbox */
	if ( g_max_height - g_area.h > 0 ) {
		/* draw smth here */
	}
}