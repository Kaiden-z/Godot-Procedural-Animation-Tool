#pragma once

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class AKIK_joint : public Node3D {
    GDCLASS(AKIK_joint, Node3D)

    private:
        NodePath next_path;
        NodePath prev_path;
        float next_length;

    protected:
	static void _bind_methods();

    public:
        void _ready() override;
        
        AKIK_joint* next;
        AKIK_joint* prev;


        NodePath get_next_path();
        void set_next_path(NodePath next);
        NodePath get_prev_path();
        void set_prev_path(NodePath prev);
        float get_next_length();
        float get_prev_length();
};