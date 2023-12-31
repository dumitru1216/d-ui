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

void warp::impl::g_filled_rect( sdk::vec2_t g_pos, sdk::vec2_t g_size, sdk::col_t g_color, int g_rounding ) {
	g_warp_drawlist->AddRectFilled( ImVec2( g_pos.x, g_pos.y ), ImVec2( g_pos.x + g_size.x, g_pos.y + g_size.y ), g_color.g_convert( ), g_rounding );
}

void warp::impl::g_rect( sdk::vec2_t g_pos, sdk::vec2_t g_size, sdk::col_t g_color, int g_rounding ) {
	g_warp_drawlist->AddRect( ImVec2( g_pos.x, g_pos.y ), ImVec2( g_pos.x + g_size.x, g_pos.y + g_size.y ), g_color.g_convert( ), g_rounding );
}

void warp::impl::g_mouse_position( sdk::pos_t& position ) {
	ImVec2 g_mouse_pos = ImGui::GetMousePos( );
	position = sdk::pos_t(
		static_cast< int >( g_mouse_pos.x ), static_cast< int >( g_mouse_pos.y )
	);
}

ImVec2 warp::impl::g_text_size( const char* text, int g_id ) {
	ImGuiIO& io = ImGui::GetIO( );
	ImGui::PushFont( io.Fonts->Fonts[ g_id ] );
	return ImGui::GetFont( )->CalcTextSizeA( ImGui::GetFontSize( ), FLT_MAX, -1.0f, text );
	ImGui::PopFont( );
}