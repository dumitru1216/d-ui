#include "../menu.hpp"
#include "../../dui_includes.hpp"

std::shared_ptr< ui::panel > panel;
std::shared_ptr< ui::window > window;

void menu::impl::g_run( ) {
	panel = std::make_shared< ui::panel >( ); {
		window = std::make_shared< ui::window >( sdk::rect_t( 200, 200, 200, 200 ), "salut" ); {

		}
		panel->g_add_window( window );
	}

	g_initialized = true;
}

void menu::impl::g_init( ) {
	panel->g_render( );
}

long __stdcall menu::impl::g_handle_window( HWND hwnd, std::uint32_t msg, std::uintptr_t wparam, std::uint32_t lparam ) {
	if ( !g_initialized )
		return false;
	
	return window->g_window_handle( hwnd, msg, wparam, lparam );
}