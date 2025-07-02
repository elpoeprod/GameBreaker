#include "../include/gamebreaker.hpp"

namespace GameBreaker {
    std::vector<GBRoom *>gb_rooms;
    
    GBRoom *room::add(int width, int height) {
    var rm=new GBRoom;
        rm->width=width;
        rm->height=height;
        rm->objects={};
        rm->view_current=0;
        int i=0; repeat(8) {
            rm->view_enabled[i]=0;
            rm->view[i]={0,0,width,height};
            i++;
        }
        gb_rooms.push_back(rm);
        rm->id=gb_rooms.size()-1;
        return rm;
    }

    int room::add_instance(GBRoom *room, GBObject *obj, int x, int y) {
        room->objects.push_back({obj->id,(int)room->objects.size()+100000});
        return room->objects[room->objects.size()-1].instance_id;
    }

    void room::remove_instance(GBRoom *room, int instance_id) {
        var i=0; repeat(room->objects.size()) {
            if(room->objects[i].instance_id==room->objects[room->objects.size()-1].instance_id)
                room->objects.erase(room->objects.cbegin()+i);
            i++;
        }
    }
    void room::current(GBRoom *room) {
        _gb_curroom=room;
    }
};
