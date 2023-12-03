#ifndef CLE_AABB_H
#define CLE_AABB_H

namespace cle {

	struct AABB {

		float x, y;
		float w, h;

	};
	
	// Use this function to determine if two AABBs are overlapping or not.
	bool isOverlapping(const AABB& first, const AABB& second);

}

#endif