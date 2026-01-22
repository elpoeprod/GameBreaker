#include "../include/gamebreaker.hpp"


// To not get GB confused, room's instance ids are starting with object_id_adder value.
// GB can get confused because it can delete every object instance, and not only one object instance.
int object_id_adder=1000000;

namespace GameBreaker {
	void room::add(GBSize size) {
		this->size=size;
		this->background_color={0xaa, 0xaa, 0xaa, 0xff};
		for (int i = 0; i < GB_MAX_CAMERAS; i++) {
			this->background_image[i]=GB_TYPE_NONE;
			this->view[i]={0,0,640,480,0};
			this->port[i]={0,0,640,480};
		}
		this->id = _gbsys_->__add(this);
		this->room_speed=60;
	}
	void room::remove() {
		delete this;
	}
	void room::current() {
		_gbsys_->current_room(this);
		return;
	}

	object *instance::get(int id) {
		if(id==GB_INSTANCE_ANY) {debug_message("instance::get() doesn't accept GB_INSTANCE_ANY."); return nullptr;}
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		if(id>object_id_adder) 
			return myobj[id-object_id_adder-1];
		else
			return myobj[id];
	}

	std::vector<object *> *room::__get_room_objects() {
		return &this->robjects;
	}

	void room::__set_room_objects(std::vector<object *>obj) {
		this->robjects=obj;
		return;
	}
	
	luint instance::count(int id) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		if(id==GB_INSTANCE_ANY) return myobj.size();
		else {
			int myn=0;
			for (luint i = 0; i < myobj.size(); i++) {
				if(i==(luint)id-object_id_adder-1) myn++;
			}
			return myn;
		}
		return 0;
	}

	luint instance::create(object *obj, GBPoint pos) {
		obj->x=pos.x;
		obj->y=pos.y;
		_gbsys_->current_room()->__add(obj);
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		return myobj.size()+object_id_adder;
	}

	void instance::destroy(int id) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		if(id==GB_INSTANCE_ANY) 
			myobj.erase(myobj.begin(),myobj.end());
		else {
			if(id>object_id_adder) {
				for(luint i=0;i<myobj.size();i++) {
					if(i==(luint)id-object_id_adder-1) myobj.erase(myobj.begin()+i);
				}
			} else {
				for(luint i=0;i<myobj.size();i++) {
					if(myobj[i]->id==id) myobj.erase(myobj.begin()+i);
				}
			}
		}
		_gbsys_->current_room()->__set_room_objects(myobj);
		return;
	}

	int instance::nearest(GBPoint pos, int obj_id) {
		if(obj_id>object_id_adder) return -1;
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		GB_NumberBag mybag={};
		for(luint i=0;i<myobj.size();i++) {
			if(myobj[i]->id==obj_id||obj_id==GB_INSTANCE_ANY) {
				mybag.push_back(math::pdistance(pos,{myobj[i]->x,myobj[i]->y}));
			}
		}
		return math::min(mybag);
	}

	int instance::furthest(GBPoint pos, int obj_id) {
		if(obj_id>object_id_adder) return -1;
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		GB_NumberBag mybag={};
		for(luint i=0;i<myobj.size();i++) {
			if(myobj[i]->id==obj_id||obj_id==GB_INSTANCE_ANY) {
				mybag.push_back(math::pdistance(pos,{myobj[i]->x,myobj[i]->y}));
			}
		}
		return math::max(mybag);
	}

	void instance::pos_destroy(GBPoint pos) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		for(luint i=0;i<myobj.size();i++) {
			if(myobj[i]->x==pos.x&&myobj[i]->y==pos.y) myobj.erase(myobj.begin()+i);
		}
		_gbsys_->current_room()->__set_room_objects(myobj);
		return;
	}

	int instance::exists(int id) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects();
		if(id==GB_INSTANCE_ANY) return myobj.size()>0;
		if(id>object_id_adder) {
			for(luint i=0;i<myobj.size();i++) {
				if(i==(luint)id-object_id_adder-1) return 1;
			}
		} else {
			for(luint i=0;i<myobj.size();i++) {
				if(myobj[i]->id==id) return 1;
			}
		}

		return 0;
	}
}
