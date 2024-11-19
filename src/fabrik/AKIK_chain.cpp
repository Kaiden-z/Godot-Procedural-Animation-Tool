#include "fabrik/AKIK_chain.h"

void AKIK_chain::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_start_path"), &AKIK_chain::get_start_path);
    ClassDB::bind_method(D_METHOD("set_start_path", "p_start_path"), &AKIK_chain::set_start_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "start_path"), "set_start_path",
                 "get_start_path");

    ClassDB::bind_method(D_METHOD("get_end_path"), &AKIK_chain::get_end_path);
    ClassDB::bind_method(D_METHOD("set_end_path", "p_end_path"), &AKIK_chain::set_end_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "end_path"), "set_end_path",
                 "get_end_path");

    ClassDB::bind_method(D_METHOD("get_expected_end_path"), &AKIK_chain::get_expected_end_path);
    ClassDB::bind_method(D_METHOD("set_expected_end_path", "p_expected_end_path"), &AKIK_chain::set_expected_end_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "expected_end_path"), "set_expected_end_path",
                 "get_expected_end_path");
}

void AKIK_chain::_ready() {
    this->start = (this->start_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(this->start_path);
    this->end = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(this->end_path);
    this->expected_end_node = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(this->expected_end_path);
}

void AKIK_chain::_process(double p_delta) {
    // float total_distance = 0.0f;
    // AKIK_joint* curr = start;
    // while (curr->next != nullptr) {
    //     total_distance += curr->get_position().distance_to(curr->next->get_position());
    //     curr = curr->next;
    // }

    // if (total_distance <= start->get_position().distance_to(end->get_position())) {  // outside of range
    //     curr = start->next;
    // } else { // within range

    // }
}

NodePath AKIK_chain::get_start_path() {
    return start_path;
}
void AKIK_chain::set_start_path(NodePath start) {
    this->start_path = start;
    this->start = (this->start_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(start);
}

NodePath AKIK_chain::get_end_path() {
    return end_path;
}
void AKIK_chain::set_end_path(NodePath end) {
    this->end_path = end;
    this->end = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(end);
}

NodePath AKIK_chain::get_expected_end_path() {
    return expected_end_path;
}
void AKIK_chain::set_expected_end_path(NodePath end_path) {
    expected_end_path = end_path;
    this->expected_end_node = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(end_path);
}