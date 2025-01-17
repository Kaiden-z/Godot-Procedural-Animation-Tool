#include "fabrik/AKIK_chain.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>

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

    ClassDB::bind_method(D_METHOD("get_is_following"), &AKIK_chain::get_is_following);
    ClassDB::bind_method(D_METHOD("set_is_following", "p_follow"), &AKIK_chain::set_is_following);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_following"), "set_is_following", "get_is_following");
}

void AKIK_chain::_ready() {
    UtilityFunctions::print("ready");
    this->start = (this->start_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(this->start_path);
    this->end = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(this->end_path);
    this->expected_end_node = (this->expected_end_path == NodePath("")) ? nullptr : this->get_node<Node3D>(this->expected_end_path);
    start_anchor = start->get_position();
}

void AKIK_chain::_process(double p_delta) {
    if (start == nullptr || end == nullptr || expected_end_node == nullptr || start == end) {
        // UtilityFunctions::print("Chain not set.");
        return;
    }
    
    Input* input = Input::get_singleton();

    if (is_following || input->is_action_pressed("fabrik")) { //TODO: this doesn't work cause input map isn't loaded in editor
        fabrik_step();
    }
}

void AKIK_chain::fabrik_step() {
    float total_distance = 0.0f;
    AKIK_joint* curr = start;
    while (curr->next != nullptr) {
        total_distance += curr->get_next_length();
        curr = curr->next;
    }

    if (total_distance <= start->get_position().distance_to(expected_end_node->get_position())) {  // outside of range
        curr = start->next;
        Vector3 oldPos = start->get_position();
        while (curr != nullptr) {
            float distance = curr->get_prev_length();
            Vector3 newCurrPos = (expected_end_node->get_position() - oldPos).normalized() * distance + oldPos;
            oldPos = curr->get_position();
            curr->set_position(newCurrPos);
            curr = curr->next;
        }
    } else { // within range
        float tolerance = 0.01;
        if (end->get_position().distance_to(expected_end_node->get_position()) > tolerance) {
            forward_kinematic();
            backward_kinematic();
        }
    }
}

void AKIK_chain::forward_kinematic() {
    float dist = end->get_prev_length();
    end->set_position(expected_end_node->get_position());
    AKIK_joint* curr = end->prev;

    while (curr != nullptr) {
        Vector3 newPos = (curr->get_position() - curr->next->get_position()).normalized() * dist + curr->next->get_position();

        if (curr->prev != nullptr) {
            dist = curr->get_prev_length();
        }
        curr->set_position(newPos);
        curr = curr->prev;
    }
}

void AKIK_chain::backward_kinematic() {
    float dist = start->get_next_length();
    start->set_position(start_anchor);
    AKIK_joint* curr = start->next;

    while (curr != nullptr) {
        Vector3 newPos = (curr->get_position() - curr->prev->get_position()).normalized() * dist + curr->prev->get_position();

        if (curr->next != nullptr) {
            dist = curr->get_next_length();
        }
        curr->set_position(newPos);
        curr = curr->next;
    }
}

NodePath AKIK_chain::get_start_path() {
    return start_path;
}
void AKIK_chain::set_start_path(NodePath start) {
    this->start_path = start;
    // this->start = (this->start_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(start);
    UtilityFunctions::print("Set start");
}

NodePath AKIK_chain::get_end_path() {
    return end_path;
}
void AKIK_chain::set_end_path(NodePath end) {
    this->end_path = end;
    // this->end = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(end);
}

NodePath AKIK_chain::get_expected_end_path() {
    return expected_end_path;
}
void AKIK_chain::set_expected_end_path(NodePath end_path) {
    expected_end_path = end_path;
    // this->expected_end_node = (this->end_path == NodePath("")) ? nullptr : this->get_node<AKIK_joint>(end_path);
}

bool AKIK_chain::get_is_following() {
    return is_following;
}
void AKIK_chain::set_is_following(bool follow) {
    is_following = follow;
}