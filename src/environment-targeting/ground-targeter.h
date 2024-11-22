#pragma once

#include <godot_cpp/classes/ray_cast3d.hpp>

using namespace godot;

class AKIK_ground_targeter : public RayCast3D {
    GDCLASS(AKIK_ground_targeter, RayCast3D)

    private:
        float length;
        Node3D* target;
        NodePath target_path;
    protected:
        static void _bind_methods();
    public:
        void _ready() override;
        void _process(double p_delta) override;

        float get_length();
        void set_length(float len);

        NodePath get_target_path();
        void set_target_path(NodePath path);
};