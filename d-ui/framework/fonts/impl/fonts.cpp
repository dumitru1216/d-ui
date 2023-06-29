#include "../fonts.hpp"

void fonts::impl::g_initialize_fonts( ) {
	/* safety */
	if ( !g_map.g_system_initialized ) {
		/* init font_atlas */
		ImGuiIO& io = ImGui::GetIO( );
		ImFontConfig cfg;

		/* create default font */
		warp::bindings::g_create_default_font( io.Fonts );

		/* warp freetype */
		warp::bindings::g_initialize_freetype( io.Fonts, ImGuiFreeTypeBuilderFlags_Bitmap );

		/* we initialized it */
		g_map.g_system_initialized = true;
	}
}