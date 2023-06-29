#include "../window.hpp"
#include "../../../warper/warper.hpp"
#include "../../../fonts/fonts.hpp"

void ui::window::g_draw( ) {
	warp::bindings::g_create_text(
		sdk::vec2_t( 50, 50 ), sdk::col_t( ), fonts::impl::g_font_t::tahoma, "text", false
	);
}