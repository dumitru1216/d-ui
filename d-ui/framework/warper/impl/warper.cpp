#include "../warper.hpp"

/* this should work fine */
ImFont* warp::impl::g_create_font_from_ttf( ImFontAtlas* g_font_atlas, const char* g_filename, float g_size,
								const ImFontConfig* g_font_cfg, const ImWchar* g_glyph_ranges ) {
	return g_font_atlas->AddFontFromFileTTF( g_filename, g_size, g_font_cfg, g_glyph_ranges );
}

ImFont* warp::impl::g_create_font_from_memory( ImFontAtlas* g_font_atlas, void* g_ttf_data, int g_ttf_size, float g_size_pixels, 
											   const ImFontConfig* g_font_cfg_template, const ImWchar* g_glyph_ranges ) {
	/* i guess that will work fine, im not sure abt the pointer */
	return g_font_atlas->AddFontFromMemoryTTF( g_ttf_data, g_ttf_size, g_size_pixels, g_font_cfg_template, g_glyph_ranges );
}

void warp::impl::g_freetype_warp( ImFontAtlas* g_font_atlas, int g_flags ) {
	ImGuiFreeType::BuildFontAtlas( g_font_atlas, g_flags );
}

void warp::impl::g_create_text( sdk::vec2_t pos, sdk::col_t color, int g_id, const char* g_text,
					bool g_shadow  ) {
	/* font -> */
	ImGuiIO& io = ImGui::GetIO( );
	ImGui::PushFont( io.Fonts->Fonts[ g_id ] );

	/* drop shadow */
	if ( g_shadow ) {
		g_warp_drawlist->AddText( ImVec2( pos.x + 1.f, pos.y + 1.f ), sdk::col_t( 5, 5, 5 ).g_convert( ), g_text );
	}

	/* create text */
	g_warp_drawlist->AddText( ImVec2( pos.x, pos.y ), color.g_convert( ), g_text );

	/* font <- */
	ImGui::PopFont( );
}