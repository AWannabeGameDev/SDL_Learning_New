#include "userdata.h"

UserData* getUserData(cle::Collider* coll) {

    return (UserData*)coll->userData;

}
