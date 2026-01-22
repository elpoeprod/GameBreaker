/*
 * Math functions and calculations
 * 2025 elpoep
*/

#include "../include/gamebreaker.hpp"

namespace GameBreaker {
    /**
    * convert degrees to radians or opposite
    * \sa deg - degree/radian
    **/
    real math::degtorad(real deg)
    {
        return deg * M_PI / 180;
    }
    /**
    * returns a length with given direction for x
    * \sa len - length
    * \sa dir - direction
    **/
    real math::lendir_x(real len, int dir)
    {
        return cos(degtorad(dir)) * len;
    }
    /**
    * returns a length with given direction for y
    * \sa len - length
    * \sa dir - direction
    **/
    real math::lendir_y(real len, int dir)
    {
        return -sin(degtorad(dir)) * len;
    }
    /**
    * clamps a value between two others
    * \sa val - value that should be clamped
    * \sa minval - minimum value
    * \sa maxval - maximum value
    * \sa if val < minval return minval, else if val>maxval return maxval, else return val
    **/
    real math::clamp(real val, real minval, real maxval)
    {
        return val < minval ? minval : val > maxval ? maxval
                                                    : val;
    } // uhhhh

    /**
    * returns true if point is in rectangle
    * \sa px, py - point coordinates
    * \sa rx*, ry* - x/y of rectangle
    **/
    real math::point_in_rect(real px, real py, real rx1, real ry1, real rx2, real ry2)
    {
        return px > rx1 && py > ry1 && px <= rx2 && py <= ry2;
    }

    int math::round(real x) {
        return (int)std::round(x);
    }
    int math::floor(real x) {
        return (int)std::floor(x);
    }
    int math::ceil(real x) {
        return (int)std::ceil(x);
    }
	
    real math::dsin(real x) {
    	return std::sin(degtorad(x));
    }
	
    real math::dcos(real x) {
    	return std::cos(degtorad(x));
    }

    real math::pdirection(GBPoint v1, GBPoint v2) {
        return math::modwrap(atan2(-(v2.y-v1.y),v2.x-v1.x)*180/M_PI,0,360);
    }
    real math::pdistance(GBPoint v1, GBPoint v2) {
        return hypot(v2.x-v1.x,v2.y-v1.y);
    }
    
    real math::pdistance_3d(GBPoint3D v1, GBPoint3D v2) {
        return sqrt(sqr(v2.x-v1.x)+sqr(v2.y-v1.y)+sqr(v2.z-v1.z));
    }

    real math::abs(real num) {
    	return std::abs(num);
    }

    int math::sign(real num) {
    	return (int(num)!=0) ? num/math::abs(num) : 0;
    } 

    real math::random(real num) {
    	return rand()%(int)num+(rand()%10000)/10000;
    }
	int math::irandom(int num) {
		return rand()%num;
	}
	real math::random_range(real min, real max) {
		return (((min<0) ? -(rand()%int(math::abs(min))) : rand()%int(min))||((max<0) ? -(rand()%int(math::abs(max))) : rand()%int(max)))+(rand()%10000)/10000;
	}

    int math::irandom_range(int min, int max) {
    	return (((min<0) ? -(rand()%int(math::abs(min))) : rand()%min)||((max<0) ? -(rand()%int(math::abs(max))) : rand()%max));
    }

    void math::random_set_seed(int seed) {
    	std::srand(seed);
    	__gb_rand_seed=seed;
    	return;
    }
    int math::random_get_seed() {
    	return __gb_rand_seed;
    }
    void math::randomize() {
    	auto myrandnum=std::rand();
    	math::random_set_seed(myrandnum);
    	return;
    }

    void *math::choose(GB_ChooseBag bag) {
    	return bag[std::rand()%bag.size()];
    }

    real math::power(real x, int n) {
    	real myxnum=x;
    	for(int i=0;i<abs(n);i++) {
    		myxnum*=x;
    	}
    	return n>0?myxnum:1/myxnum;
    }
    real math::sqr(real x) {
    	return x*x;
    }
    real math::sqrt(real x) {
    	return std::sqrt(x);
    }
    real math::min(GB_NumberBag bag) {
    	real mynum=bag[0];
    	for(luint i=1;i<bag.size();i++) {
    		mynum=std::min(mynum,bag[i]);
    	}
    	return mynum;
    }
    real math::max(GB_NumberBag bag) {
    	real mynum=bag[0];
    	for(luint i=1;i<bag.size();i++) {
    		mynum=std::max(mynum,bag[1]);
    	}
    	return mynum;
    }
    real math::mean(GB_NumberBag bag) {
    	real mynum=0;
    	for(luint i=0;i<bag.size();i++) {
    		mynum+=bag[i];
    	}
    	return mynum/bag.size();
    }

	real math::median(GB_NumberBag bag) {
		return bag[std::round(bag.size()/2)];
	}
    
	real math::frac(real x) {
		return x-std::floor(x);
	}

	int math::irandom_fresh(int oldval, int minval, int maxval) {
		return math::modwrap(oldval+1+math::irandom(maxval-minval-1),minval,maxval+1);
	}

	real math::lerp(real a, real b, real amount) {
		return a*(1-amount)+b*amount;
	}

	real math::modwrap(real val, real minval, real maxval) {
		real f=val-minval;
	    real w=maxval-minval;
	    return f-floor(f/w)*w+minval;
	}

	real math::gauss(real range) {
		var __i=0.f;
		repeat (12) __i+=math::random(1);
		return ((__i-6)/6+0.5)*range;
	}

	real math::gauss_range(real min, real max) {
		var __i=0.f;
		repeat (12) __i+=math::random(1);
		return ((__i-6)/6+0.5)*(max-min)+min;
	}

	real math::floor_to(real x, real to) {
		return std::floor(x/to)*to;
	}

	real math::ceil_to(real x, real to) {
		return std::ceil(x/to)*to;
	}

	real math::round_to(real x, real to) {
		return std::round(x/to)*to;
	}
	
	real math::exp(real x) {
		return math::power(2.718282,(int)x);
	}

	real math::log(real x) {
		return std::log(x);
	}

	real math::logn(real n, real x) {
		if(x!=0)
			return math::log(n)/math::log(x);
		return 0;
	}

	real math::log10(real x) {
		return std::log10(x);
	}
	
	real math::log2(real x) {
		return std::log2(x);
	}

	real math::ln(real x) {
		return log1p(x-1.l);
	}

	real math::sin(real x) {
		return std::sin(x);
	}

	real math::cos(real x) {
		return std::cos(x);
	}
	
	real math::tan(real x) {
		return math::sin(x)/math::cos(x);
	}
	
	real math::cotan(real x) {
		return 1/math::tan(x);
	}
	
	real math::tg(real x) {
		return math::tan(x);
	}

	real math::ctg(real x) {
		return math::cotan(x);
	}

	real math::arcsin(real x) {
		return std::asin(x);
	}

	real math::arccos(real x) {
		return std::acos(x);
	}

	real math::arctan(real x) {
		return std::atan(x);
	}

	real math::arctan2(real y, real x) {
		return math::arctan(y/x);
	}


	real math::dot_product(GBPoint v1, GBPoint v2) {
		return v1.x*v2.x+v1.y*v2.y;
	}

	real math::dot_product_3d(GBPoint3D v1, GBPoint3D v2) {
		return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
	}

	
}
