#pragma once
#include "gamebreaker.hpp"
namespace gb=GameBreaker;

#define gb_run 					gb::run
#define gb_init 				gb::init
#define gb_shutdown 			gb::shutdown

#define font_add 				gb::font::add
#define font_style 				gb::font::style
#define font_style_ext 			gb::font::style_ext
#define font_destroy 			gb::font::destroy
#define font_option 			gb::font::option

#define object_add 				gb::object::add
#define object_destroy 			gb::object::destroy

#define io_clear 				gb::io::clear

#define keyboard_pressed	 	gb::keyboard::pressed
#define keyboard_released	 	gb::keyboard::released
#define keyboard_holding		gb::keyboard::holding
#define keyboard_ord			gb::keyboard::ord
#define keyboard_chr			gb::keyboard::ord

#define joystick_count			gb::joy::count
#define joystick_working		gb::joy::working
#define joystick_pressed		gb::joy::pressed
#define joystick_released		gb::joy::released
#define joystick_holding 		gb::joy::holding
#define joy_button				gb::joy::button

#define window_set_size			gb::window::set_size
#define window_set_pos			gb::window::set_pos
#define window_get_x			gb::window::get_x
#define window_get_y			gb::window::get_y
#define window_get_width		gb::window::get_width
#define window_get_height		gb::window::get_height
#define window_set_icon			gb::window::set_icon
#define window_get_size			gb::window::get_size
#define window_get_pos			gb::window::get_pos
#define window_get_renderer		gb::window::get_renderer
#define window_set_title		gb::window::set_title

#define display_get_width		gb::display::get_width
#define display_get_height		gb::display::get_height
#define display_get_size		gb::display::get_size
#define display_mouse_x			gb::display::mouse_x
#define display_mouse_y			gb::display::mouse_y

#define audio_add				gb::audio::add
#define audio_set_pos			gb::audio::set_pos
#define audio_play				gb::audio::play
#define audio_loop				gb::audio::loop
#define audio_pause				gb::audio::pause
#define audio_resume			gb::audio::resume
#define audio_stop				gb::audio::stop
#define audio_set_vol			gb::audio::set_vol
#define audio_get_wave			gb::audio::get_wave
#define audio_get_tags			gb::audio::get_tags
#define audio_get_pos			gb::audio::get_pos
#define audio_get_length		gb::audio::get_len
#define audio_destroy			gb::audio::destroy

#define c_black 				gb::color::black
#define c_white 				gb::color::white
#define c_red 					gb::color::red
#define c_blue 					gb::color::blue
#define c_green 				gb::color::green
#define c_lime 					gb::color::lime
#define c_gray 					gb::color::gray
#define c_ltgray 				gb::color::lt_gray
#define c_dkgray 				gb::color::dk_gray
#define c_fuchsia 				gb::color::fuchsia
#define c_purple 				gb::color::purple
#define c_aqua	 				gb::color::aqua
#define c_pink 					gb::color::pink

#define show_message			gb::show::message
#define show_error				gb::show::error

#define mb_none					gb::mb::none
#define mb_left					gb::mb::left
#define mb_right				gb::mb::right
#define mb_middle				gb::mb::middle
#define mb_any					gb::mb::any

#define vk_shift				gb::vk::shift
#define vk_space				gb::vk::space
#define vk_left					gb::vk::left
#define vk_right				gb::vk::right
#define vk_up					gb::vk::up
#define vk_down					gb::vk::down
#define vk_enter				gb::vk::enter

#define mouse_pressed			gb::mouse::pressed
#define mouse_released			gb::mouse::released
#define mouse_holding			gb::mouse::holding
#define mouse_nothing			gb::mouse::nothing
#define mouse_which				gb::mouse::which
#define mouse_x					gb::mouse::x
#define mouse_y					gb::mouse::y

#define sprite_add				gb::graphics::sprite::add
#define sprite_add_ext			gb::graphics::sprite::add_ext
#define sprite_destroy			gb::graphics::sprite::destroy
#define sprite_get_offset_x		gb::graphics::sprite::get_offset_x
#define sprite_get_offset_y		gb::graphics::sprite::get_offset_y
#define sprite_set_offset		gb::graphics::sprite::set_offset

#define draw_rectangle			gb::graphics::draw::rectangle
#define draw_rectangle_color	gb::graphics::draw::rectangle_color
#define draw_triangle			gb::graphics::draw::triangle
#define draw_circle				gb::graphics::draw::circle
#define draw_line				gb::graphics::draw::line
#define draw_point				gb::graphics::draw::point
#define draw_set_alpha			gb::graphics::draw::alpha
#define draw_set_color			gb::graphics::draw::color
#define draw_set_color_sdl		gb::graphics::draw::color_sdl
#define draw_set_color_rgb		gb::graphics::draw::color_rgb
#define draw_set_color_hsv		gb::graphics::draw::color_hsv
#define draw_get_color			gb::graphics::draw::color_get
#define draw_set_blendmode		gb::graphics::draw::blendmode
#define draw_sprite				gb::graphics::draw::sprite
#define draw_sprite_part		gb::graphics::draw::sprite_part
#define draw_sprite_ext			gb::graphics::draw::sprite_ext
#define draw_sprite_stretched	gb::graphics::draw::sprite_stretched
#define draw_button				gb::graphics::draw::button
#define draw_text				gb::graphics::draw::text
#define draw_text_rt			gb::graphics::draw::text_rt
#define draw_set_font			gb::graphics::draw::set_font
#define draw_text_align			gb::graphics::draw::set_align
