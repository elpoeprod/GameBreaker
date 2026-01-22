#include "../include/gamebreaker.hpp"

namespace GameBreaker {

	void object::default_init() {
		debug_message("initializing object...");
		this->x=0;
		this->y=0;
		this->xprevious=0;
		this->yprevious=0;
		this->gravity=0;
		this->gravity_direction=0;
		this->friction=0;
		this->speed=0;
		this->hspeed=0;
		this->vspeed=0;
		this->depth=0;
		this->solid=0;

		//Events
		this->event_create=nullptr;
		this->event_destroy=nullptr;
		this->event_step_begin=nullptr;
		this->event_step=nullptr;
		this->event_step_end=nullptr;
		this->event_draw=nullptr;
		debug_message("End of initializing");
		return;
	}
	void object::default_adder() {
		this->id=_gbsys_->__add(this);
		debug_message("Initialized "+std::to_string(this->id)+". continuing...");
		_gbsys_->__sys_sort_objects();
	}
	
	void object::add(sprite *spr, sprite *mask) {
		this->default_init();
		this->default_adder();
		this->sprite_index=spr->id;
		this->mask_index=mask->id;
		return;
	}
	
	void object::add(sprite *spr) {
		this->default_init();
		this->sprite_index=spr->id;
		this->mask_index=spr->id;
		return;
	}
	
	void object::add() {
		this->default_init();
		this->sprite_index=GB_TYPE_NONE;
		this->mask_index=GB_TYPE_NONE;
		return;
	}
	
	void object::remove() {
		this->default_init();
		this->sprite_index=GB_TYPE_NONE;
		this->mask_index=GB_TYPE_NONE;
		debug_message("Removed object with id "+std::to_string(this->id));
		delete this;
	}

	// Collisions (place::*, move::* etc)
	int place::free(GBPoint pos) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects(); //can be slow as fuck
		for(luint ob=0;ob<myobj.size();ob++) {
			if(myobj[ob]->x==pos.x&&myobj[ob]->y==pos.y) {
				if(myobj[ob]->solid) return 0;
			} 
		}
		return 1;
	}

	int place::empty(GBPoint pos) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects(); //can be slow as fuck
		for(luint ob=0;ob<myobj.size();ob++) {
			if(myobj[ob]->x==pos.x&&myobj[ob]->y==pos.y)
				return 0;
		}
		return 1;
	}

	int place::meeting(GBPoint pos, object *obj) {
		auto myobj=*_gbsys_->current_room()->__get_room_objects(); //can be slow as fuck
		for(luint ob=0;ob<myobj.size();ob++) {
			if(myobj[ob]->x==pos.x&&myobj[ob]->y==pos.y&&myobj[ob]->id==obj->id) {
				if(myobj[ob]->solid) return 0;
			} 
		}
		return 1;
	}
};
