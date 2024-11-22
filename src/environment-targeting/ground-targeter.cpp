#include "environment-targeting/ground-targeter.h"

#include <godot_cpp/variant/utility_functions.hpp>

void AKIK_ground_targeter::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_length"), &AKIK_ground_targeter::get_length);
    ClassDB::bind_method(D_METHOD("set_length", "p_length"), &AKIK_ground_targeter::set_length);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "length"), "set_length",
                 "get_length");

    ClassDB::bind_method(D_METHOD("get_target_path"), &AKIK_ground_targeter::get_target_path);
    ClassDB::bind_method(D_METHOD("set_target_path", "p_target_path"), &AKIK_ground_targeter::set_target_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "target_path"), "set_target_path",
                 "get_target_path");
}

void AKIK_ground_targeter::_ready() {
    this->target = (this->target_path == NodePath("")) ? nullptr : this->get_node<Node3D>(this->target_path);
}

void AKIK_ground_targeter::_process(double p_delta) {
    if (target == nullptr) {
        return;
    }

    force_raycast_update();
    if (is_colliding()) {
        UtilityFunctions::print(get_collision_point());
        target->set_global_position(get_collision_point());
    }
}

float AKIK_ground_targeter::get_length() {
    return length;
}
void AKIK_ground_targeter::set_length(float len) {
    this->length = len;
}

NodePath AKIK_ground_targeter::get_target_path() {
    return target_path;
}
void AKIK_ground_targeter::set_target_path(NodePath path) {
    target_path = path;
}