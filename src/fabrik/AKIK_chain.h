#pragma once

#include "fabrik/AKIK_joint.h"

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class AKIK_chain : public Node3D {
    GDCLASS(AKIK_chain, Node3D)

    private:
        AKIK_joint* start;
        NodePath start_path;
        AKIK_joint* end;
        NodePath end_path;
        AKIK_joint* curr = nullptr;

        NodePath expected_end_path;
        Node3D* expected_end_node;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _process(double p_delta) override;

        NodePath get_start_path();
        void set_start_path(NodePath start);
        NodePath get_end_path();
        void set_end_path(NodePath end);

        NodePath get_expected_end_path();
        void set_expected_end_path(NodePath end_path);
};