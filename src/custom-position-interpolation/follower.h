#pragma once

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class AKIK_follower : public Node3D {
    GDCLASS(AKIK_follower, Node3D)

    private:
        Vector3 xp;
        Vector3 y;
        Vector3 yd;
        float k1, k2, k3;
        //frequency, damping, initial
        float f = 1, z = 1, r = 0;

        Node3D* target;
        NodePath target_path;


        void compute_constants();

    protected:
	static void _bind_methods();

    public:
        void _ready() override;
        void _process(double p_delta) override;

        float get_frequency();
        void set_frequency(float frequency);
        float get_damping();
        void set_damping(float damping);
        float get_initial();
        void set_initial(float initial);

        NodePath get_target_path();
        void set_target_path(NodePath path);
};
