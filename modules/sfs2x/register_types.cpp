/* register_types.cpp */

#include "register_types.h"
#include "class_db.h"
#include "sfs2x.h"

void register_sfs2x_types() {
    ClassDB::register_class<SmartFoxServer>();
}

void unregister_sfs2x_types() {
   //nothing to do here
}
