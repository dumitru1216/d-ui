#include "../warper.hpp"

/* this should work fine */
ImFont* warp::impl::g_create_font_from_ttf( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size,
								const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges ) {
	return g_font_atlas->AddFontFromFileTTF( g_filename, g_size, g_font_cfg, g_glyph_ranges );
}

void warp::impl::g_freetype_warp( ImFontAtlas* g_font_atlas, int g_flags ) {
	ImGuiFreeType::BuildFontAtlas( g_font_atlas, g_flags );
}