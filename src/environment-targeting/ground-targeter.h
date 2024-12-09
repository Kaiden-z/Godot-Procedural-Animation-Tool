#pragma once

#include <godot_cpp/classes/ray_cast3d.hpp>

using namespace godot;

class AKIK_ground_targeter : public RayCast3D {
    GDCLASS(AKIK_ground_targeter, RayCast3D)

    private:
        float length;
        Node3D* target;
        NodePath target_path;
        float jump_margin = 0.0f;

        bool is_jump_margin_traveled();
    protected:
        static void _bind_methods();
    public:
        void _ready() override;
        void _process(double p_delta) override;

        float get_length();
        void set_length(float len);
        float get_jump_margin();
        void set_jump_margin(float jump_margin);

        NodePath get_target_path();
        void set_target_path(NodePath path);

        Node3D* get_target();
        void set_target(Node3D* target);
};