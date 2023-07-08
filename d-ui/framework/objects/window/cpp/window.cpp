#include "../window.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"
#include "../../../input/input.hpp"
#include "../../../theme/theme.hpp"
#include "../../../panel/panel.hpp"

void ui::window::think( ) {
	/*
		if g_pressing_move_key is false and the left mouse button is pressed (GetAsyncKeyState(VK_LBUTTON) returns a non-zero value) 
			and the mouse is hovering over a specific area (handled by handling::g_init.get()->g_hovering with a specified rectangle), then:

		set g_pressing_move_key to true.
		retrieve the current mouse position and store it in g_mouse_mpos as a sdk::pos_t object.
		calculate the click offset as the difference between g_mouse_mpos and the coordinates of g_area.
	*/
	if ( !g_pressing_move_key && GetAsyncKeyState( VK_LBUTTON ) && 
		 handling::g_init.get()->g_hovering( sdk::rect_t( g_area.x, g_area.y, g_area.w, 40 ) ) ) {
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

	if ( g_area.y < 0 )
		g_area.y = 0;

	if ( g_area.x + g_area.w > g_screen_rect.w )
		g_area.x = g_screen_rect.w - g_area.w;

	if ( g_area.y + g_area.h > g_screen_rect.h )
		g_area.y = g_screen_rect.h - g_area.h;

	/* animate */
	g_animate( g_area );
}

void ui::window::g_draw( ) {
	/* we have not finished input frame */
	handling::input_sdk::g_finished_input_frame = false;
	gg_render_overlay = false;

	/* parent panel */
	auto& g_parent_panel = g_find_parent< panel >( g_object_panel );

	/* handle input */
	think( );

	/* update cursor pos */
	g_cursor_pos = sdk::pos_t(
		g_area.x + theme::g_init.get()->g_map.spacing, g_area.y + theme::g_init.get( )->g_map.spacing
	);

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

	warp::bindings::g_create_filled_rect(
		sdk::rect_t( g_area.x, g_area.y + 45, g_area.w, 1 ), sdk::col_t( 0, 0, 0 ).g_modify_alpha( 255 ), 3
	);

	if ( g_bar_anim > 0 ) {
		warp::bindings::g_create_filled_rect(
			sdk::rect_t( g_area.x + ( g_area.w / 2 ) - ( g_bar_anim / 2 ), g_area.y + 45, g_bar_anim, 1 ), theme::g_init.get( )->g_map.g_accent.g_modify_alpha( 120 ), 3
		);
	}

	/* tab system */
	std::vector< std::pair< std::shared_ptr< tab >, int > > g_tab_list;
	auto g_total_tabs_w = 0;

	std::for_each( g_objects.begin( ), g_objects.end( ), [ & ]( std::shared_ptr<obj> g_object ) {
		if ( g_object->g_type == g_object_tab ) {
			auto g_tab = std::static_pointer_cast< tab >( g_object );

			sdk::rect_t g_bounds{};
			warp::bindings::g_text_bounding( g_tab->g_title, g_bounds, fonts::impl::g_font_t::roboto ); /* calculate the bounding box of the tab's title text */
			g_total_tabs_w += g_bounds.w + 4 + /* spacing */ + 10; /* increment the total width of tabs by the tab's title width plus 4 */

			g_tab_list.push_back( std::pair<std::shared_ptr<tab>, int>( g_tab, g_bounds.w + 10 ) ); /* add the tab and its title width to the tab list */
		}
	} );

	auto g_last_tab_pos = sdk::vec2_t( g_area.x + ( g_area.w / 2 ) - ( g_total_tabs_w / 2 ) + 6, g_area.y + 15 );
	std::for_each( g_tab_list.begin( ), g_tab_list.end( ), [ & ]( std::pair< std::shared_ptr< tab >, int > object ) {
		if ( handling::g_init.get()->g_clicking( sdk::rect_t( g_last_tab_pos.x, g_last_tab_pos.y, object.second, 16 ) ) ) {
			/* update click timer */
			object.first->g_time = g_parent_panel.g_time;

			/* deselect all */
			std::for_each( g_tab_list.begin( ), g_tab_list.end( ), [ & ]( std::pair< std::shared_ptr< tab >, int > child ) {
				/* re-run animation */
				if ( child.first->g_selected )
					child.first->g_time = g_parent_panel.g_time;

				child.first->g_selected = false;
			} );

			/* select clicked tab */
			object.first->g_selected = true;
		}

		/* animation */
		auto g_time_since_click = std::clamp( g_parent_panel.g_time - object.first->g_time, 0.0, theme::g_init.get( )->g_map.g_anim_speed );
		auto g_bar_width = object.second - object.second * ( g_time_since_click * ( 1.0 / theme::g_init.get( )->g_map.g_anim_speed ) );
		auto g_text_height = 0;
		auto g_alpha = 255 - int( g_time_since_click * ( 1.0 / theme::g_init.get( )->g_map.g_anim_speed ) * 80.0 );

		if ( object.first->g_selected ) {
			g_alpha = 175 + int( g_time_since_click * ( 1.0 / theme::g_init.get( )->g_map.g_anim_speed ) * 80.0 );
			g_bar_width = object.second * ( g_time_since_click * ( 1.0 / theme::g_init.get( )->g_map.g_anim_speed ) );
			g_text_height = 2 * ( g_time_since_click * ( 1.0 / theme::g_init.get( )->g_map.g_anim_speed ) );
		}

		/* render names */
		warp::bindings::g_create_text(
			sdk::vec2_t( g_last_tab_pos.x, g_area.y + 15 ), object.first->g_selected ? sdk::col_t( ).g_modify_alpha( 200 ) : sdk::col_t( ).g_modify_alpha( 100 ),
			fonts::impl::g_font_t::roboto, object.first->g_title.c_str( ), false
		);

		if ( object.first->g_selected ) {
			warp::bindings::g_create_filled_rect(
				sdk::rect_t( g_last_tab_pos.x + ( object.second / 2 ) - ( g_bar_width / 2 ) - 3, g_area.y + 43, g_bar_width, 2 ), theme::g_init.get( )->g_map.g_accent, 2
			);
		}

		g_last_tab_pos.x += object.second + 4;
	} );

	/* draw window objects */
	warp::bindings::g_clip( g_area, [ & ]( ) {
		std::for_each( g_objects.begin( ), g_objects.end( ), [ ]( std::shared_ptr< obj >& child ) {
			child->g_draw( );
		} );
	} );

	/* overlay */
	if ( gg_render_overlay ) {
		g_overlay_func( );
	}

	handling::input_sdk::g_click_switch = false;
	g_scroll_delta = 0.0;
}