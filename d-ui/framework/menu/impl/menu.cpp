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
}

void menu::impl::g_init( ) {
	panel->g_render( );
}

long __stdcall menu::impl::g_handle_window( HWND hwnd, std::uint32_t msg, std::uintptr_t wparam, std::uint32_t lparam ) {
	if ( !window->g_window_handle( hwnd, msg, wparam, lparam ) )
		return true;

	if ( window->g_handle_keyboard )
		return true;

	switch ( msg ) {
		/* when clicking */
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
		/* when scrolling */
		case WM_MOUSEWHEEL:
		return true;
	}

	return false;
}