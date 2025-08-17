#include "../include/gamebreaker.hpp"

double modwrap(double val, double minv, double maxv) {
    ///modwrap(val,min,max)
    //val: value to wrap
    //min: minimum value
    //max: maximum value
    //returns: wrapped value
    //Repeats the value inside the window defined by min and max - max exclusive.
    
    double f=val-minv;
    double w=maxv-minv;
    return f-floor(f/w)*w+minv;
}

namespace GameBreaker {
    /**
    * convert degrees to radians or opposite
    * \sa deg - degree/radian
    **/
    double math::degtorad(double deg)
    {
        return deg * M_PI / 180;
    }
    /**
    * returns a length with given direction for x
    * \sa len - length
    * \sa dir - direction
    **/
    double math::lendir_x(double len, int dir)
    {
        return cos(degtorad(dir)) * len;
    }
    /**
    * returns a length with given direction for y
    * \sa len - length
    * \sa dir - direction
    **/
    double math::lendir_y(double len, int dir)
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
    double math::clamp(double val, double minval, double maxval)
    {
        return val < minval ? minval : val > maxval ? maxval
                                                    : val;
    } // uhhhh

    /**
    * returns true if point is in rectangle
    * \sa px, py - point coordinates
    * \sa rx*, ry* - x/y of rectangle
    **/
    double math::point_in_rect(double px, double py, double rx1, double ry1, double rx2, double ry2)
    {
        return px > rx1 && py > ry1 && px <= rx2 && py <= ry2;
    }

    int math::round(double x) {
        return (int)std::round(x);
    }
    int math::floor(double x) {
        return (int)std::floor(x);
    }
    int math::ceil(double x) {
        return (int)std::ceil(x);
    }
	
    double math::dsin(double x) {
    	return std::sin(degtorad(x));
    }
	
    double math::dcos(double x) {
    	return std::cos(degtorad(x));
    }

    double math::pdirection(double x1,double y1,double x2,double y2) {
        return modwrap(atan2(-(y2-y1),x2-x1)*180/M_PI,0,360);
    }
    double math::pdistance(double x1, double y1, double x2, double y2) {
        return hypot(x2-x1,y2-y1);
    }

    double math::abs(double num) {
    	return std::abs(num);
    }

    int math::sign(double num) {
    	return (int(num)!=0) ? num/math::abs(num) : 0;
    } 

    double math::random(double num) {
    	return rand()%(int)num+(rand()%10000)/10000;
    }
	int math::irandom(int num) {
		return rand()%num;
	}
	double math::random_range(double min, double max) {
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
    	var myrandnum=std::rand();
    	math::random_set_seed(myrandnum);
    	return;
    }

    void *math::choose(GB_ChooseBag bag) {
    	return bag[std::rand()%bag.size()];
    }

    double math::power(double x, int n) {
    	double myxnum=x;
    	for(int i=0;i<n;i++) {
    		myxnum*=x;
    	}
    	return myxnum;
    }
    double math::sqr(double x) {
    	return x*x;
    }
    double math::sqrt(double x) {
    	return std::sqrt(x);
    }
    double math::min(GB_NumberBag bag) {
    	real mynum=bag[0];
    	for(long unsigned int i=1;i<bag.size();i++) {
    		mynum=std::min(mynum,bag[i]);
    	}
    	return mynum;
    }
    double math::max(GB_NumberBag bag) {
    	real mynum=bag[0];
    	for(long unsigned int i=1;i<bag.size();i++) {
    		mynum=std::max(mynum,bag[1]);
    	}
    	return mynum;
    }
    double math::mean(GB_NumberBag bag) {
    	real mynum=0;
    	for(long unsigned int i=0;i<bag.size();i++) {
    		mynum+=bag[i];
    	}
    	return mynum/bag.size();
    }

	double math::median(GB_NumberBag bag) {
		return bag[std::round(bag.size()/2)];
	}
    
	
}
