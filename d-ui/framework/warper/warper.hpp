#pragma once
#include "../../includes.hpp"

/* pre-define drawlist */
#define g_warp_drawlist ImGui::GetBackgroundDrawList()

namespace warp {
	/* bindings */
	namespace bindings {
		/* credits goes to oxygen for helping me larn how to add pointers */
		static std::add_pointer_t<void( ImFontAtlas* )> g_create_default_font = [ ]( ImFontAtlas* g_font_atlas ) {
			g_font_atlas->AddFontDefault( );
		};

		static std::add_pointer_t<void( ImFontAtlas*, const char*, float, const ImFontConfig*,
										const ImWchar* )> g_create_font = [ ]( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size,
																			   const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges ) {
			warp::g_init.get( )->g_create_font_from_ttf( g_font_atlas, g_filename, g_size, g_font_cfg, g_glyph_ranges );
		};
	}

	/* main class - initialization..etc*/
	class impl {
	public:
		ImFont* g_create_font_from_ttf( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size, 
										const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges );
	};
	inline const auto g_init = std::make_unique< impl >( );
}