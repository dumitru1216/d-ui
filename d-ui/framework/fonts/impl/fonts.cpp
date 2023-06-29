#include "../fonts.hpp"
#include "../../warper/warper.hpp"

/* converted fonts */
#include "../ctx/tahoma.h"

void fonts::impl::g_initialize_fonts( ) {
	/* safety */
	if ( !g_map.g_system_initialized ) {
		/* init font_atlas */
		ImGuiIO& io = ImGui::GetIO( );
		ImFontConfig cfg;

		/* create default font */
		warp::bindings::g_create_default_font( io.Fonts );
		warp::bindings::g_create_font_memory( io.Fonts, tahoma_ttf,
											  tahoma_ttf_len, 13, &cfg, io.Fonts->GetGlyphRangesCyrillic( ) );

		/* warp freetype */
		warp::bindings::g_initialize_freetype( io.Fonts, ImGuiFreeTypeBuilderFlags_Bitmap );

		/* we initialized it */
		g_map.g_system_initialized = true;
	}
}