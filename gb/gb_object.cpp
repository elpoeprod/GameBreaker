#include "../include/gamebreaker.hpp"

namespace GameBreaker {

    std::vector<GBObject*> gb_objects;
    
    /**
    * returns new object
    * \sa spr - sprite, can be passed as nullptr
    * \sa mask - mask of the object, if passed as nullptr, the mask will be the same as the sprite
    * \sa x, y - coordinates of the object
    **/
    GBObject* object::add(GBSprite* spr, GBSprite* mask, double x, double y)
    {
        GBObject* obj=new GBObject;
            obj->x=x;
            obj->y=y;
            obj->xprevious=x;
            obj->yprevious=y;
            obj->direction=0;
            obj->gravity=0;
            obj->gravity_direction=270;
            obj->friction=0;
            obj->spd=0;
            obj->hspd=0;
            obj->vspd=0;
            obj->spr=spr;
            obj->depth=0;
            obj->mask=mask!=nullptr?mask:spr;
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
}