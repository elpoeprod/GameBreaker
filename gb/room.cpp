#include "../include/gamebreaker.hpp"

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

	object *room::get_instance(int id) {
		return this->robjects[id];
	}

	std::vector<object *> *room::__get_room_objects() {
		return &this->robjects;
	}

	void room::__set_room_objects(std::vector<object *>obj) {
		this->robjects=obj;
		return;
	}
	
	luint room::instance_count(int id) {
		if(id==GB_INSTANCE_ANY) return this->robjects.size();
		else {
			int myn=0;
			for (luint i = 0; i < this->robjects.size(); i++) {
				if(i==(luint)id) myn++;
			}
			return myn;
		}
		return 0;
	}

	void room::add_instance(object *obj, GBPoint pos) {
		obj->x=pos.x;
		obj->y=pos.y;
		this->robjects.push_back(obj);
	}
}
