#include "fabrik/AKIK_joint.h"

void AKIK_joint::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_next_path"), &AKIK_joint::get_next_path);
    ClassDB::bind_method(D_METHOD("set_next_path", "p_next_path"), &AKIK_joint::set_next_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "next_path"), "set_next_path",
                 "get_next_path");

    ClassDB::bind_method(D_METHOD("get_prev_path"), &AKIK_joint::get_prev_path);
    ClassDB::bind_method(D_METHOD("set_prev_path", "p_prev_path"), &AKIK_joint::set_prev_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "prev_path"), "set_prev_path",
                 "get_prev_path");
}

NodePath AKIK_joint::get_next_path() {
    return next_path;
}

void AKIK_joint::set_next_path(NodePath next) {
    this->next_path = next;
    this->next = (this->next_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(next);
}

NodePath AKIK_joint::get_prev_path() {
    return prev_path;
}

void AKIK_joint::set_prev_path(NodePath prev) {
    this->prev_path = prev;
    this->prev = (this->prev_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(prev);
}