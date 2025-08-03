#include "../include/gamebreaker.hpp"

namespace GameBreaker {
    std::vector<GBRoom *>gb_rooms;
    
    GBRoom *room::add(int width, int height) {
    var rm=new GBRoom;
        rm->width=width;
        rm->height=height;
        rm->speed=60;
        rm->background_visible=1;
        rm->background_color=color::gray;
        rm->background_image=nullptr;  
        rm->view_current=0;
        int i=0; 
        repeat(7) {
            rm->view_enabled[i]=0;
            rm->view[i]={0,0,width,height,0};
            i++;
        }
        gb_rooms.push_back(rm);
        rm->id=gb_rooms.size()-1;
        return rm;
    }

    int room::add_instance(GBRoom *room, GBObject *obj, double x, double y,void (*event_create)()=nullptr) {
    	struct rmobj myobj={
    						.obj_id=obj->id,
    						.instance_id=(int)room->objects.size()+100000,
                            .object=obj,
    						.x=x,
    						.y=y,
    						.event_create=event_create
    						};
        room->objects.push_back(myobj);
        obj->inst_id=room->objects[room->objects.size()-1].instance_id;
        return obj->inst_id;
    }

    void room::remove_instance(GBRoom *room, int instance_id) {
        var i=0; repeat(room->objects.size()) {
            if(instance_id==room->objects[i].instance_id)
                room->objects.erase(room->objects.cbegin()+i);
            i++;
        }
    }
    void room::current(GBRoom *room) {
        room_current=room;
        for(int i=0;i<GB_MAX_ROOM_CAMERAS;i++) {
            view_xview[i]=room_current->view[i].x;
            view_yview[i]=room_current->view[i].y;
            view_wview[i]=room_current->view[i].w;
            view_hview[i]=room_current->view[i].h;
            view_angle[i]=room_current->view[i].angle;
        }
    }

    GBObject *room::find_object(int inst_id) {
        
        for(long unsigned int i=0;i<room_current->objects.size();i++) {
            auto myinst=room_current->objects[i];
            if(myinst.instance_id==inst_id) return myinst.object;
        }
        return nullptr;
    }

    void room::camera_setup(GBRoom *room,int camera_id, int enabled, GB_CamSetup view, GB_CamSetup port,int target_inst_id, GB_CamTarget target) {
        room->view_enabled[camera_id]=enabled;
        room->view[camera_id]=view;
        
        room->port[camera_id]=port;
        
        room->target_id=target_inst_id;
        room->target_setup=target;
    }
};
