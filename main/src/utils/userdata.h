#ifndef USERDATA_H
#define USERDATA_H

#include <string>
#include <cle_collider.h>

struct UserData {

	std::string text;
	void* ptr;

};

UserData* getUserData(cle::Collider* coll);

#endif