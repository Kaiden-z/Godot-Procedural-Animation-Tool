#pragma once

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class AKIK_joint : public Node3D {
    GDCLASS(AKIK_joint, Node3D)

    private:
        NodePath next_path;
        NodePath prev_path;

    protected:
	static void _bind_methods();

    public:
        AKIK_joint* next;
        AKIK_joint* prev;

        NodePath get_next_path();
        void set_next_path(NodePath next);
        NodePath get_prev_path();
        void set_prev_path(NodePath prev);
};