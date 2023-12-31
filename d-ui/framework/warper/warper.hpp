#pragma once
#include "../../includes.hpp"
#include "../../entry/entry.hpp"

/* pre-define drawlist */
#define g_warp_drawlist ImGui::GetBackgroundDrawList()

/* externals */
extern bool g_input_clip_area;
extern sdk::rect_t g_input_clip_rect;

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

		/* text size */
		ImVec2 g_text_size( const char* g_text, int g_id );

		/* get mouse pos */
		void g_mouse_position( sdk::pos_t& position );

		/* rendering warper */
		void g_filled_rect( sdk::vec2_t g_pos, sdk::vec2_t g_size, sdk::col_t g_color, int g_rounding );
		void g_rect( sdk::vec2_t g_pos, sdk::vec2_t g_size, sdk::col_t g_color, int g_rounding );
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

		static std::add_pointer_t<void( sdk::rect_t, std::function<void( )> )> g_clip = 
			[ ]( sdk::rect_t g_area, std::function<void( )> g_function ) {
			g_warp_drawlist->PushClipRect( ImVec2( g_area.x - 0.5f, g_area.y - 0.5f ), 
										   ImVec2( g_area.x + g_area.w - 0.5f, g_area.y + g_area.h - 0.5f ), true );

			g_input_clip_area = true;
			g_input_clip_rect = g_area;

			/* run the motherfucker */
			g_function( );

			g_input_clip_area = false;
			g_warp_drawlist->PopClipRect( );
		};

		static std::add_pointer_t<void( sdk::rect_t, sdk::col_t, int )> g_create_filled_rect = [ ]( sdk::rect_t g_rect,
																												 sdk::col_t g_color, int g_rounding ) {
			warp::g_init.get( )->g_filled_rect( sdk::vec2_t(g_rect.x, g_rect.y), sdk::vec2_t(g_rect.w, g_rect.h), g_color, g_rounding );
		};

		static std::add_pointer_t<void( sdk::rect_t, sdk::col_t, int )> g_create_rect = [ ]( sdk::rect_t g_rect,
																									sdk::col_t g_color, int g_rounding ) {
			warp::g_init.get( )->g_rect( sdk::vec2_t( g_rect.x, g_rect.y ), sdk::vec2_t( g_rect.w, g_rect.h ), g_color, g_rounding );
		};

		static std::add_pointer_t<void( sdk::pos_t& )> g_mouse_pos = [ ]( sdk::pos_t& g_pos ) {
			warp::g_init.get( )->g_mouse_position( g_pos );
		};

		static std::add_pointer_t<void( sdk::g_str&, sdk::rect_t&, int )> g_text_bounding = [ ]( sdk::g_str& g_title, sdk::rect_t& g_bounds, int font ) {
			ImVec2 size = warp::g_init.get( )->g_text_size( g_title.c_str( ), font );

			g_bounds.w = size.x;
			g_bounds.h = size.y;
		};
	}
}