#include "my_collision_listener.h"
#include "userdata.h"

void MyCollisionListener::beginTouch(cle::Collider* first, cle::Collider* second, cle::Vector2D normal) {

	if(getUserData(first)) {

		if(getUserData(first)->text == "player") {

			f_playerBeginTouch(first, second, normal);

		}

	} else if(getUserData(second)) {

		if(getUserData(second)->text == "player") {

			normal.x *= -1;
			normal.y *= -1;
			f_playerBeginTouch(second, first, normal);

		}

	}

}

void MyCollisionListener::beginOverlap(cle::Collider* first, cle::Collider* second) {

	cle::resolveCollision(first, second);

}

void MyCollisionListener::endTouch(cle::Collider* first, cle::Collider* second, cle::Vector2D normal) {

	if(getUserData(first)) {

		if(getUserData(first)->text == "player") {

			f_playerEndTouch(first, second, normal);

		}

	} else if(getUserData(second)) {

		if(getUserData(second)->text == "player") {

			normal.x *= -1;
			normal.y *= -1;
			f_playerEndTouch(second, first, normal);

		}

	}

}

void MyCollisionListener::endOverlap(cle::Collider* first, cle::Collider* second) {



}

void MyCollisionListener::f_playerBeginTouch(cle::Collider* playerCol, cle::Collider* other, cle::Vector2D normal) {

	Player* player = (Player*)getUserData(playerCol)->ptr;

	if(normal.y > 0) {

		player->m_grounded = true;
		player->m_groundCount++;

	}

}

void MyCollisionListener::f_playerEndTouch(cle::Collider* playerCol, cle::Collider* other, cle::Vector2D normal) {

	Player* player = (Player*)getUserData(playerCol)->ptr;

	if((normal.y > 0) && --player->m_groundCount == 0) player->m_grounded = false;

}