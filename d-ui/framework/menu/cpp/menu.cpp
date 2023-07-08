#include "../menu.hpp"
#include "../../dui_includes.hpp"

std::shared_ptr< ui::panel > panel;
std::shared_ptr< ui::window > window;

void menu::impl::g_run( ) {
	panel = std::make_shared< ui::panel >( ); {
		window = std::make_shared< ui::window >( sdk::rect_t( 200, 200, 550, 430 ), "d-ui framework" ); {
			auto ragebot = std::make_shared< ui::tab >( "aim" );
			{
				auto main_grp = std::make_shared< ui::group >( "main" );
				{
					ragebot->g_handle_group( main_grp );
				}; ragebot->g_add_columns( 1 );

				auto main_grp2 = std::make_shared< ui::group >( "accuracy" );
				{
					ragebot->g_handle_group( main_grp2 );
				}; 
				auto main_grp3 = std::make_shared< ui::group >( "other" );
				{
					ragebot->g_handle_group( main_grp3 );
				}; ragebot->g_add_columns( 2 ); /* max 2 columns */

			} window->g_add_tab( ragebot );

			auto antiaim = std::make_shared< ui::tab >( "anti-aim" );
			{

			} window->g_add_tab( antiaim );

			auto world = std::make_shared< ui::tab >( "world" );
			{

			} window->g_add_tab( world );

			auto player = std::make_shared< ui::tab >( "player" );
			{

			} window->g_add_tab( player );

			auto misc = std::make_shared< ui::tab >( "misc" );
			{

			} window->g_add_tab( misc );
		}
		panel->g_add_window( window );
	}

	g_initialized = true;
}

void menu::impl::g_init( ) {
	panel->g_render( static_cast< double > ( std::chrono::duration_cast< std::chrono::milliseconds > 
					 ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) ) / 1000.0 );
}

long __stdcall menu::impl::g_handle_window( HWND hwnd, std::uint32_t msg, std::uintptr_t wparam, std::uint32_t lparam ) {
	if ( !g_initialized )
		return false;
	
	return window->g_window_handle( hwnd, msg, wparam, lparam );
}