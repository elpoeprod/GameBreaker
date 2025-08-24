#include "../include/gamebreaker.hpp"

namespace GameBreaker {

    std::vector<GBObject*> gb_objects;
    
    /**
    * returns new object
    * \sa spr - sprite, can be passed as nullptr
    * \sa mask - mask of the object, if passed as nullptr, the mask will be the same as the sprite
    * \sa x, y - coordinates of the object
    **/
    GBObject* object::add(GBSprite* spr, GBSprite* mask)
    {
        GBObject* obj=new GBObject;
            obj->x=0;
            obj->y=0;
            obj->xprevious=0;
            obj->yprevious=0;
            obj->direction=0;
            obj->gravity=0;
            obj->gravity_direction=270;
            obj->friction=0;
            obj->spd=0;
            obj->hspd=0;
            obj->vspd=0;
            obj->spr=spr;
            obj->depth=0;
            obj->image_index=0;
            obj->image_speed=1;
            obj->mask=mask!=nullptr?mask:spr;
			obj->event_create=nullptr;
			obj->event_step=nullptr;
			obj->event_step_end=nullptr;
			obj->event_step_begin=nullptr;
			obj->event_draw=nullptr;
			obj->event_destroy=nullptr;
			for(int i=0;i<GB_MAX_OBJ_ALARMS;i++) {
				obj->alarm[i]=-1;
				obj->event_alarm[i]=nullptr;
			}
			obj->initialized=0;
            
            gb_objects.push_back(obj);
            obj->id=gb_objects.size()-1;
        return obj;
    }

    void object::destroy(GBObject* obj) {
        obj->direction=0;
        obj->gravity_direction=0;
        obj->friction=0;
        obj->gravity=0;
        obj->hspd=0;
        obj->mask=nullptr;
        obj->spd=0;
        obj->vspd=0;
        obj->spr=nullptr;
        obj->x=0;
        obj->y=0;
        delete obj;
    }
    void add_event(GBObject *obj, enum ev ev_type, void(*event)(GBObject *self)) {
        switch(ev_type) {
            case ev::create: 
                obj->event_create=event;
            break;
            case ev::step_begin:
                obj->event_step_begin=event;
            break;
            case ev::step:
                obj->event_step=event;
            break;
            case ev::step_end:
                obj->event_step_end=event;
            break;
            case ev::draw:
                obj->event_draw=event;
            break;
            case ev::destroy:
                obj->event_destroy=event;
            break;
            default: break;
        }
        return;
    }
}
