#include "../include/gamebreaker.hpp"

struct hsv {
	int h, s, v;
};

hsv rgb2hsv(GBColor in);

namespace GameBreaker {
	GBColor c_aqua={0,0xff,0xff,0xff},
			c_black=BLACK,
			c_blue=BLUE,
			c_dkgray=DARKGRAY, 
			c_fuchsia={0xff,0x0,0x7f,0xff}, 
			c_gray=GRAY,
			c_green=GREEN, 
			c_lime=LIME, 
			c_ltgray=LIGHTGRAY, 
			c_maroon=MAROON, 
			c_navy={0x0,0x0,0x99,0xff}, 
			c_olive={0x80,0x80,0x00,0xff}, 
			c_purple=PURPLE,
			c_red=RED, 
			c_silver={0xc4,0xc4,0xc4,0xff}, 
			c_teal={0x00,0x80,0x80,0xff}, 
			c_white=RAYWHITE, 
			c_yellow=YELLOW, 
			c_orange=ORANGE;

	GBColor color::make_hsv(real hue, real saturation, real value) {
		double hh, p, q, t, ff;
		    long i;
		    GBColor out;
		
		    if(saturation <= 0.0) {
		        out.r = value;
		        out.g = value;
		        out.b = value;
		        return out;
		    }
		    hh = hue;
		    if(hh >= 360.0) hh = 0.0;
		    hh /= 60.0;
		    i = (long)hh;
		    ff = hh - i;
		    p = value * (1.0 - saturation);
		    q = value * (1.0 - (saturation * ff));
		    t = value * (1.0 - (saturation * (1.0 - ff)));
		
		    switch(i) {
		    case 0:
		        out.r = value;
		        out.g = t;
		        out.b = p;
		        break;
		    case 1:
		        out.r = q;
		        out.g = value;
		        out.b = p;
		        break;
		    case 2:
		        out.r = p;
		        out.g = value;
		        out.b = t;
		        break;
		
		    case 3:
		        out.r = p;
		        out.g = q;
		        out.b = value;
		        break;
		    case 4:
		        out.r = t;
		        out.g = p;
		        out.b = value;
		        break;
		    case 5:
		    default:
		        out.r = value;
		        out.g = p;
		        out.b = q;
		        break;
		    }
		    return out;     
	}

	real color::get_hue(GBColor col) {
		return rgb2hsv(col).h;
	}
	
	real color::get_saturation(GBColor col) {
			return rgb2hsv(col).s;
	}
	
	real color::get_value(GBColor col) {
			return rgb2hsv(col).v;
	}
	
	GBColor color::mix(GBColor col1, GBColor col2) {
			return {Uint8((col1.r*col2.r)/255),Uint8((col1.g*col2.g)/255),Uint8((col1.b*col2.b)/255),Uint8((col1.a*col2.a)/255)};
		}
	
	GBColor color::merge(GBColor col1, GBColor col2, real amount) {
		return {Uint8(math::lerp(col1.r,col2.r,amount)),Uint8(math::lerp(col1.g,col2.g,amount)),Uint8(math::lerp(col1.b,col2.b,amount)),Uint8(math::lerp(col1.a,col2.a,amount))};
	}

	GBColor color::merge_corrected(GBColor col1, GBColor col2, real amount) {
		return {
			Uint8(math::sqrt(math::lerp(math::sqr(col1.r), math::sqr(col2.r), amount))),
			Uint8(math::sqrt(math::lerp(math::sqr(col1.g), math::sqr(col2.g), amount))),
			Uint8(math::sqrt(math::lerp(math::sqr(col1.b), math::sqr(col2.b), amount))),
			Uint8(math::sqrt(math::lerp(math::sqr(col1.a), math::sqr(col2.a), amount)))
			};
	}

	real color::get_luminance(GBColor col) {
		return (col.r*0.2126+col.g*0.7152+col.b*0.0722);
	}

	GBColor color::make_rgb(long unsigned int col) {
		auto mcol = col;
		return (GBColor){Uint8((mcol>>16)&0xff), Uint8((mcol>>8)&0xff), Uint8(mcol&0xff)};
	}
}



hsv rgb2hsv(GBColor in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}
