/* sfs2x.cpp */

#include "sfs2x.h"

void SmartFoxServer::add(int value) {
    count += value;
}

void SmartFoxServer::reset() {
    count = 0;
}

int SmartFoxServer::get_total() const {
    return count;
}

void SmartFoxServer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add", "value"), &SmartFoxServer::add);
    ClassDB::bind_method(D_METHOD("reset"), &SmartFoxServer::reset);
    ClassDB::bind_method(D_METHOD("get_total"), &SmartFoxServer::get_total);
}

SmartFoxServer::SmartFoxServer() {
    count = 0;
}
