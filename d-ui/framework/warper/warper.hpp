#pragma once
#include "../../includes.hpp"

/* pre-define drawlist */
#define g_warp_drawlist ImGui::GetBackgroundDrawList()

namespace warp {
	/* main class - initialization..etc*/
	class impl {
	public:
		ImFont* g_create_font_from_ttf( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size,
										const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges );
		ImFont* g_create_font_from_memory( ImFontAtlas* g_font_atlas, void* g_ttf_data, int g_ttf_size, 
										   float g_size_pixels, const ImFontConfig* g_font_cfg_template, const ImWchar* g_glyph_ranges );

		/* freetype warping */
		void g_freetype_warp( ImFontAtlas* g_font_atlas, int g_flags );
		void g_create_text( sdk::vec2_t pos, sdk::col_t color, int g_id, const char* g_text,
					   bool g_shadow = false );
	};
	inline const auto g_init = std::make_unique< impl >( );

	/* bindings */
	namespace bindings {
		/* credits goes to oxygen for helping me larn how to add pointers */
		static std::add_pointer_t<void( ImFontAtlas* )> g_create_default_font = [ ]( ImFontAtlas* g_font_atlas ) {
			g_font_atlas->AddFontDefault( );
		};

		static std::add_pointer_t<void( ImFontAtlas*, int )> g_initialize_freetype = [ ]( ImFontAtlas* g_font_atlas, int g_flags ) {
			warp::g_init.get( )->g_freetype_warp( g_font_atlas, g_flags );
		};

		static std::add_pointer_t<void( ImFontAtlas*, const char*, float, const ImFontConfig*,
										const ImWchar* )> g_create_font = [ ]( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size,
																			   const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges ) {
			warp::g_init.get( )->g_create_font_from_ttf( g_font_atlas, g_filename, g_size, g_font_cfg, g_glyph_ranges );
		};

		static std::add_pointer_t<void( ImFontAtlas*, void*, int, float, const ImFontConfig*,
										const ImWchar* )> g_create_font_memory = [ ]( ImFontAtlas* g_font_atlas, void* g_ttf_data, int g_ttf_size,
																					  float g_size_pixels, const ImFontConfig* g_font_cfg_template, const ImWchar* g_glyph_ranges ) {
			warp::g_init.get( )->g_create_font_from_memory( g_font_atlas, g_ttf_data, g_ttf_size, g_size_pixels, g_font_cfg_template, g_glyph_ranges );
		};

		static std::add_pointer_t<void( sdk::vec2_t, sdk::col_t, int, const char*, 
										bool)> g_create_text = [ ]( sdk::vec2_t pos, sdk::col_t color, int g_id, 
																	const char* g_text, bool g_shadow ) {
			warp::g_init.get( )->g_create_text( pos, color, g_id, g_text, g_shadow );
		};	
	}
}