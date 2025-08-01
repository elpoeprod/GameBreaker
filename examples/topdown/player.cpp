#include "player.hpp"

float xspeed=0,
    yspeed=0,
    maxspeed=3;

float facspeed=0.5;

void scrPlayerKeyboard() {
    if(keyboard::holding('W')) {
        if(yspeed>-maxspeed) yspeed-=facspeed;
    }
    if(keyboard::holding('S')) {
        if(yspeed<maxspeed) yspeed+=facspeed;
    }
    if(keyboard::holding('A')) {
        if(xspeed>-maxspeed) xspeed-=facspeed;
    }
    if(keyboard::holding('D')) {
        if(xspeed<maxspeed) xspeed+=facspeed;
    }

    if(!keyboard::holding('W') and !keyboard::holding('S')) {
        if(yspeed>0) yspeed-=facspeed; 
        else {
            if(yspeed<0) yspeed+=facspeed; else yspeed=0;
        }
    }

    if(!keyboard::holding('A') and !keyboard::holding('D')) {
        if(xspeed>0) xspeed-=facspeed; 
        else {
            if(xspeed<0) xspeed+=facspeed; else xspeed=0;
        }
    }

    objPlayer->x+=xspeed;
    objPlayer->y+=yspeed;
    //objPlayer->image_index+=(xspeed+yspeed)*0.015;
    if(objPlayer->x>room::width+64) objPlayer->x=room::width+64;
    if(objPlayer->x<-64) objPlayer->x=-64;
    if(objPlayer->y>room::height+64) objPlayer->y=room::height+64;
    if(objPlayer->y<-64) objPlayer->y=-64;
}

void scrPlayer_eventCreate() {
    objPlayer->image_speed=0;
    objPlayer->image_index=0;
    objEffector->spr=sprCursor;
	objEffector->image_speed=0.4;
}

int aimfar=0;
float factor=1;
double pdir=0;
float mousex=0,mousey=0;

void scrAim(int instance) {
	var target=room::find_object(instance);
    factor=1;
    aimfar=0;
    
    if(keyboard::holding(SDLK_LSHIFT)) {
    	factor=1.8;
    	aimfar=1;
    }
    
    float width=display::get_width();
    float height=display::get_height();
    mousex=target->x+((display::mouse_x-width*0.5)*(view_wview[0]/width))*factor;
    mousey=target->y+((display::mouse_y-height*0.5)*(view_hview[0]/height))*factor;
	if(aimfar) {
		var spdist=math::pdistance(view_xview[0]+view_wview[0]/2,view_yview[0]+view_hview[0]/2,mousex,mousey)*0.1;
		var spdir=math::pdirection(view_xview[0]+view_wview[0]/2,view_yview[0]+view_hview[0]/2,mousex,mousey);
		view_xview[0]+=math::lendir_x(spdist,spdir);
		view_yview[0]+=math::lendir_y(spdist,spdir);
	} else {
	    pdir=math::pdirection(target->x,target->y,mousex,mousey);
	    var spdist=math::pdistance(view_xview[0]+view_wview[0]/2.f,view_yview[0]+view_hview[0]/2.f,target->x+math::lendir_x(24,pdir),target->y+math::lendir_y(24,pdir))*0.1;
	    var spdir=math::pdirection(view_xview[0]+view_wview[0]/2.f,view_yview[0]+view_hview[0]/2.f,target->x+math::lendir_x(24,pdir),target->y+math::lendir_y(24,pdir));
		view_xview[0]+=math::lendir_x(spdist,spdir);
		view_yview[0]+=math::lendir_y(spdist,spdir);
	}
}	

void scrPlayer_eventStep() {
    scrPlayerKeyboard();
    scrAim(objPlayer->inst_id);
}

double myframe=0;

void scrPlayer_eventDraw() {
    draw::color_rgb(255,255,255);
    draw::rect(objPlayer->x-8,objPlayer->y-8,16,16,0);
    //draw::text_rt(view_xview[0]+100, view_yview[0]+100, "x "+stringify(view_xview[0]));
    //draw::text_rt(view_xview[0]+100,view_yview[0]+120, "y "+stringify(view_yview[0]));
    //draw::text_rt(view_xview[0]+100,view_yview[0]+140, "fps "+stringify(GameBreaker::fps_current));
    if(myframe<sprCursor->frames) myframe+=0.4; else myframe=0;
    draw::sprite_ext(sprCursor,myframe,mousex,mousey,1,1,0,col::white);
}
