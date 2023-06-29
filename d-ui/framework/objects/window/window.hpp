#pragma once
#include "../../../includes.hpp"
#include "../obj/obj.hpp"
#include <array>

namespace ui {
	class window : public obj {
	private:
		std::string g_title;
		sdk::pos_t g_click_offset = sdk::pos_t( );
	public:
		sdk::pos_t g_cursor_pos;

		/* booleans */
		bool g_open = false;
		bool g_handle_keyboard = true;
		bool g_pressing_move_key = false;
		bool g_pressing_open_key = false;

		/* key arrays */
		std::array< bool, 5 > g_mouse_down{ false };
		std::array< bool, 512 > g_key_down{ false };
		std::function< void( wchar_t ) > g_keyboard_handler_func;

		/* doubles */
		double g_scroll_delta = 0.0;

		window( const sdk::rect_t& g_area, std::string g_title ) {
			this->g_area = g_area;
			this->g_title = g_title;

			/* object type */
			g_type = g_object_window;
		};
		~window( ) { }

		/* override func */
		void g_draw( ) override;

		/* mouse think */
		void think( );

		/* window handler */
		long __stdcall g_window_handle( HWND hwnd, std::uint32_t msg, 
								std::uintptr_t wparam, std::uint32_t lparam ) {
			/* 
				- thanks to oxygen
			*/

			/*
				if g_open is true:

				switch statement to handle different message types:
				if msg is wm_lbuttondown or wm_lbuttondblclk, button is set to 0.
				if msg is wm_rbuttondown or wm_rbuttondblclk, button is set to 1.
				if msg is wm_mbuttondown or wm_mbuttondblclk, button is set to 2.
				if msg is wm_xbuttondown or wm_xbuttondblclk, button is set to 3 if 
					get_xbutton_wparam(wparam) is xbutton1, otherwise it is set to 4.
				sets the corresponding element in g_mouse_down array to true based on the button value.
				returns true.
				if msg is wm_lbuttonup, wm_rbuttonup, wm_mbuttonup, or wm_xbuttonup:
				sets button based on the message type (0 for wm_lbuttonup, 
					1 for wm_rbuttonup, 2 for wm_mbuttonup, 3 if get_xbutton_wparam(wparam) is xbutton1, otherwise 4).
				sets the corresponding element in g_mouse_down array to false.
				returns true.
				if msg is wm_keydown or wm_syskeydown:
				if wparam is less than 256, sets the corresponding element in g_key_down array to true.
				returns true.
				if msg is wm_keyup or wm_syskeyup:
				if wparam is less than 256, sets the corresponding element in g_key_down array to false.
				returns true.
				if msg is wm_char:
				if wparam is within the valid range, calls g_keyboard_handler_func with the character as an argument.
				returns true.
				if msg is wm_mousewheel:
				increments g_scroll_delta based on the wheel delta value.
				returns true.
			*/
			if ( g_open ) {
				switch ( msg ) {
					case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
					case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
					case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
					case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
					{
						int button = 0;
						if ( msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK ) { button = 0; }
						if ( msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK ) { button = 1; }
						if ( msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK ) { button = 2; }
						if ( msg == WM_XBUTTONDOWN || msg == WM_XBUTTONDBLCLK ) { button = ( GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ) ? 3 : 4; }
						g_mouse_down[ button ] = true;
						return true;
					}

					case WM_LBUTTONUP:
					case WM_RBUTTONUP:
					case WM_MBUTTONUP:
					case WM_XBUTTONUP:
					{
						int button = 0;
						if ( msg == WM_LBUTTONUP ) { button = 0; }
						if ( msg == WM_RBUTTONUP ) { button = 1; }
						if ( msg == WM_MBUTTONUP ) { button = 2; }
						if ( msg == WM_XBUTTONUP ) { button = ( GET_XBUTTON_WPARAM( wparam ) == XBUTTON1 ) ? 3 : 4; }
						g_mouse_down[ button ] = false;
						return true;
					}

					case WM_KEYDOWN:
					case WM_SYSKEYDOWN:
						if ( wparam < 256 )
							g_key_down[ wparam ] = true;
					return true;
					case WM_KEYUP:
					case WM_SYSKEYUP:
						if ( wparam < 256 )
							g_key_down[ wparam ] = false;
					return true;
					case WM_CHAR:
						if ( wparam > 0 && wparam < ( 1 << 16 ) && g_handle_keyboard ) {
							g_keyboard_handler_func( wchar_t( wparam ) );
						}
					return true;
					case WM_MOUSEWHEEL:
					    g_scroll_delta += -( ( double )GET_WHEEL_DELTA_WPARAM( wparam ) / ( double )WHEEL_DELTA );
					return true;
				}
			}

			/* return */
			return false;
		}
	};
}