#pragma once
#include "../dui_includes.hpp"

namespace menu {
	class impl {
	public:
		void g_run( );
		void g_init( );
		long __stdcall g_handle_window( HWND hwnd, std::uint32_t msg, std::uintptr_t wparam, std::uint32_t lparam );
	};
	inline const auto g_init = std::make_unique< impl >( );
}