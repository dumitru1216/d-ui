#include "../menu.hpp"
#include "../../dui_includes.hpp"

std::shared_ptr< ui::panel > panel;
std::shared_ptr< ui::window > window;

void menu::impl::g_run( ) {
	panel = std::make_shared< ui::panel >( ); {
		window = std::make_shared< ui::window >( sdk::rect_t( 200, 200, 550, 430 ), "d-ui framework" ); {

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