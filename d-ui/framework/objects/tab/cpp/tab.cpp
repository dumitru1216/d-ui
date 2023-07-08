#include "../tab.hpp"
#include "../../window/window.hpp"
#include "../../../theme/theme.hpp"

void ui::tab::g_draw( ) {
	if ( !g_selected ) return;

	/* reset draw cursor pos */
	auto& g_parent = g_find_parent< window >( g_object_window );
	auto& g_cursor_pos = g_parent.g_cursor_pos;
	auto& g_window_dimensions = g_parent.g_area;

	/* backup cursor information */
	auto backup_pos = g_cursor_pos;

	/* row system */
	const auto g_rows = divider.g_columns_per_row.size( );
	if ( !g_rows ) {
		/* draw tab objects */
		std::for_each(g_objects.begin( ),g_objects.end( ),[ ]( std::shared_ptr< obj >& child ) {
			child->g_draw( );
		} );

		return;
	}

	/* calculate column width with information */
	auto space_per_column = ( g_window_dimensions.w / g_rows ) - 10;
	auto calculated_column_width = 0;

	if ( g_rows > 1 )
		calculated_column_width = space_per_column - theme::g_init.get( )->g_map.spacing - 
		                             double( theme::g_init.get( )->g_map.spacing ) / double( g_rows );
	else
		calculated_column_width = space_per_column - theme::g_init.get( )->g_map.spacing * 2.0;

	/* draw all the groups in all the rows and columns, automatically calculate the width and height of each groupbox */
	for ( auto row = 0; row < g_rows; row++ ) {
		auto selected_group = 0;

		auto previous_group_count = 0;
		auto next_group_count = 0;
		auto item_count_inside_row = 0;

		auto row_counter = 0;

		/* find amount of columns behind the last row */
		for ( auto& column_counter : divider.g_columns_per_row ) {
			if ( row_counter < row ) {
				previous_group_count += column_counter;
			}

			if ( row_counter <= row ) {
				next_group_count = previous_group_count + column_counter;
				item_count_inside_row = column_counter;
			}

			row_counter++;
		}

		/* calculate column height with previous information */
		auto space_per_column_h = ( g_window_dimensions.h / item_count_inside_row );
		auto calculated_column_height = 0;

		if ( item_count_inside_row > 1 )
			calculated_column_height = ( space_per_column_h - theme::g_init.get( )->g_map.spacing -
										 double( theme::g_init.get( )->g_map.spacing ) / double( item_count_inside_row ) ) - 20;
		else
			calculated_column_height = ( space_per_column_h - theme::g_init.get( )->g_map.spacing * 2.0 ) - 40;

		/* draw groups that are in the corresponding columns */
		std::for_each( g_objects.begin( ), g_objects.end( ), [ & ]( std::shared_ptr< obj >& child ) {
			if ( child->g_type == g_object_group ) {
				if ( selected_group >= previous_group_count && selected_group < next_group_count ) {
					/* set group dimension parameters accordingly */
					child->g_area.w = calculated_column_width;
					child->g_area.h = calculated_column_height;

					auto backup_pos_child = g_cursor_pos;

					child->g_draw_ex_parent( );

					g_cursor_pos.x = backup_pos_child.x;
					g_cursor_pos.y = backup_pos_child.y;

					/* move down to next group */
					g_cursor_pos.y += calculated_column_height + theme::g_init.get( )->g_map.spacing;
				}

				selected_group++;
			}
		} );

		/* reset cursor y value */
		g_cursor_pos.y = backup_pos.y;

		/* move to the next row */
		g_cursor_pos.x += calculated_column_width + theme::g_init.get( )->g_map.spacing;
	}

	/* restore to original location */
	g_cursor_pos = backup_pos;
}