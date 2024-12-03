#include "custom-position-interpolation/follower.h"

void AKIK_follower::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_target_path"), &AKIK_follower::get_target_path);
    ClassDB::bind_method(D_METHOD("set_target_path", "p_target_path"), &AKIK_follower::set_target_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "target_path"), "set_target_path",
                 "get_target_path");
    ClassDB::bind_method(D_METHOD("get_frequency"), &AKIK_follower::get_frequency);
    ClassDB::bind_method(D_METHOD("set_frequency", "p_frequency"), &AKIK_follower::set_frequency);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency_coefficient"), "set_frequency",
                 "get_frequency");
    ClassDB::bind_method(D_METHOD("get_damping"), &AKIK_follower::get_damping);
    ClassDB::bind_method(D_METHOD("set_damping", "p_damping"), &AKIK_follower::set_damping);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "damping_coefficient"), "set_damping",
                 "get_damping");
    ClassDB::bind_method(D_METHOD("get_initial"), &AKIK_follower::get_initial);
    ClassDB::bind_method(D_METHOD("set_initial", "p_initial"), &AKIK_follower::set_initial);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_coefficient"), "set_initial",
                 "get_initial");
}

void AKIK_follower::_ready() {
    this->target = (this->target_path == NodePath("")) ? nullptr : this->get_node<Node3D>(this->target_path);
    compute_constants();
}

void AKIK_follower::_process(double p_delta) {
    if (target == nullptr) {
        return;
    }
    Vector3 x = target->get_global_position();
    Vector3 xd = (x - xp) / p_delta;
    xp = x;
    y = y + p_delta * yd;
    yd = yd + p_delta * (x + k3*xd - y - k1*yd) / k2;
    set_global_position(y);
}

void AKIK_follower::compute_constants() {
    k1 = z / (Math_PI * f);
    k2 = 1 / ((2 * Math_PI * f) * (2 * Math_PI * f));
    k3 = r * z / (2 * Math_PI * f);

    xp = (this->target == nullptr) ? get_global_position() : this->target->get_global_position();
    y = xp;
    yd = Vector3(0, 0, 0);
}

float AKIK_follower::get_frequency() {
    return f;
}
void AKIK_follower::set_frequency(float frequency) {
    f = frequency;
    compute_constants();
}
float AKIK_follower::get_damping() {
    return z;
}
void AKIK_follower::set_damping(float damping) {
    z = damping;
    compute_constants();
}
float AKIK_follower::get_initial() {
    return r;
}
void AKIK_follower::set_initial(float initial) {
    r = initial;
    compute_constants();
}
NodePath AKIK_follower::get_target_path() {
    return target_path;
}
void AKIK_follower::set_target_path(NodePath path) {
    target_path = path;
}