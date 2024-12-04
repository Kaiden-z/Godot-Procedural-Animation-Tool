#include "dampedtransform/AKIK_Procedural_Rig.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void AKIK_Procedural_Rig::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("get_segment_spacing"), &AKIK_Procedural_Rig::get_segment_spacing);
    ClassDB::bind_method(D_METHOD("set_segment_spacing", "p_segment_spacing"), &AKIK_Procedural_Rig::set_segment_spacing);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "segment_spacing"), "set_segment_spacing", "get_segment_spacing");

	ClassDB::bind_method(D_METHOD("get_angle_constraint"), &AKIK_Procedural_Rig::get_angle_constraint);
    ClassDB::bind_method(D_METHOD("set_angle_constraint", "p_angle_constraint"), &AKIK_Procedural_Rig::set_angle_constraint);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle_constraint_(degrees)"), "set_angle_constraint", "get_angle_constraint");

    ClassDB::bind_method(D_METHOD("get_default_segment"), &AKIK_Procedural_Rig::get_default_segment);
    ClassDB::bind_method(D_METHOD("set_default_segment", "p_default_segment"), &AKIK_Procedural_Rig::set_default_segment);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "default_segment"), "set_default_segment", "get_default_segment");

	ClassDB::bind_method(D_METHOD("get_segments"), &AKIK_Procedural_Rig::get_segments);
    ClassDB::bind_method(D_METHOD("set_segments", "p_segment_arr"), &AKIK_Procedural_Rig::set_segments);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "segments"), "set_segments", "get_segments");

	ClassDB::bind_method(D_METHOD("get_damping_enabled"), &AKIK_Procedural_Rig::get_damping_enabled);
    ClassDB::bind_method(D_METHOD("set_damping_enabled", "p_damping_enabled"), &AKIK_Procedural_Rig::set_damping_enabled);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "damping enabled"), "set_damping_enabled", "get_damping_enabled");

	ClassDB::bind_method(D_METHOD("get_damping_speed"), &AKIK_Procedural_Rig::get_damping_speed);
    ClassDB::bind_method(D_METHOD("set_damping_speed", "p_damping_speed"), &AKIK_Procedural_Rig::set_damping_speed);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "damping speed"), "set_damping_speed", "get_damping_speed");
}

AKIK_Procedural_Rig::AKIK_Procedural_Rig() 
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Constructing rig..."); 
	segment_spacing = 1.0f;
	angle_constraint = 90.f;
	default_segment = Ref<PackedScene>();
	segments = TypedArray<PackedScene>();
	damping_enabled = false;
	damping_speed = 20.f;

	chain = Vector<Node3D*>();
}

AKIK_Procedural_Rig::~AKIK_Procedural_Rig()
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Deconstructing rig...");
	for (Node3D* node : chain) {
		node->queue_free();
	}
}

void AKIK_Procedural_Rig::_ready()
{
	UtilityFunctions::print("Calling ready...");
	refresh_rig();
}


void AKIK_Procedural_Rig::_process(double delta) 
{

	float max_angle = Math::deg_to_rad(angle_constraint);

    for (int i = 0; i < chain.size() - 1; ++i) {
		Node3D* node = chain[i];
        Node3D* next_node = chain[i + 1];

        Vector3 diff = next_node->get_global_position() - node->get_global_position();
        Vector3 constrained_offset = diff.normalized() * segment_spacing;

        Vector3 current_dir = diff.normalized();
        Vector3 prev_dir = (i > 0) ? (node->get_global_position() - chain[i - 1]->get_global_position()).normalized() : Vector3(0, 0, -1);

		// Apply damping
		Vector3 damped_dir = current_dir;
        if (i > 0) {
			if (damping_enabled) {
				Vector3 ideal_dir = (prev_dir + current_dir).normalized();
            	damped_dir = current_dir.lerp(ideal_dir, delta * damping_speed);
			}

            float angle = damped_dir.angle_to(prev_dir);
            if (angle > max_angle) {
                Vector3 axis = prev_dir.cross(damped_dir).normalized();
                Transform3D rotation_transform = get_transform().rotated(axis, max_angle);
                damped_dir = rotation_transform.basis.xform(prev_dir).normalized();
            }
        }

		// Move next node to stay within constrained distance
		constrained_offset = damped_dir * segment_spacing;
        next_node->set_global_position(node->get_global_position() + constrained_offset);
        node->look_at(next_node->get_global_position(), Vector3(0, 1, 0));		
	}
}

Node3D* AKIK_Procedural_Rig::initialize_segment(int index)
{
	PackedScene* segment_scene = Object::cast_to<PackedScene>(segments[index]);

	if (segment_scene == nullptr) {
		UtilityFunctions::print("Segment at index (", index, ") is null, creating a Node3D instance instead...");
		return memnew(Node3D);
	} 

	Node3D* segment = Object::cast_to<Node3D>(segment_scene->instantiate());

	if (segment == nullptr) {
		UtilityFunctions::print("Root type of segment is not of type Node3D, creating a Node3D instance instead...");
		return memnew(Node3D);
	}

	return segment;
}

void AKIK_Procedural_Rig::refresh_rig() 
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Refreshing rig...");

	for (Node3D* node : chain) {
		node->queue_free();
	}

	chain.clear();

	for (int i = 0; i < segments.size(); ++i) { 
		Node3D* node = initialize_segment(i);
		chain.push_back(node); 
		add_child(node);
		if (i > 0) node->set_as_top_level(true);
		node->set_global_position(get_global_position() + Vector3(0, 0, segment_spacing * i * -1));
	}

	if (!segments.is_empty()) {
		Node3D* end_node = memnew(Node3D);
		chain.push_back(end_node);
		add_child(end_node);
		end_node->set_as_top_level(true);
		end_node->set_global_position(get_global_position() + Vector3(0, 0, segment_spacing * segments.size() * -1));
	}

}





void AKIK_Procedural_Rig::set_segment_spacing(float p_segment_spacing)
{
	segment_spacing = godot::Math::clamp<float>(p_segment_spacing, 0.f, std::numeric_limits<float>::max());
	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig(); 
}

float AKIK_Procedural_Rig::get_segment_spacing() const
{
    return segment_spacing;
}

void AKIK_Procedural_Rig::set_angle_constraint(float p_angle_constraint)
{
	angle_constraint = godot::Math::clamp<float>(p_angle_constraint, 0.f, 360.f);
	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig();
}

float AKIK_Procedural_Rig::get_angle_constraint() const
{
    return angle_constraint;
}

void AKIK_Procedural_Rig::set_default_segment(Ref<PackedScene> p_default_segment)
{
	default_segment = p_default_segment;
	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig(); 
}

Ref<PackedScene> AKIK_Procedural_Rig::get_default_segment() const
{
    return default_segment; 
}

void AKIK_Procedural_Rig::set_segments(TypedArray<PackedScene> p_segment_arr) 
{	
	// Iterate through the input array and replace null PackedScenes with the default segment
    for (int i = 0; i < p_segment_arr.size(); ++i) {
        if (p_segment_arr[i].get_type() == Variant::NIL) {
            p_segment_arr[i] = *default_segment;
        }
    }

    // Assign the updated array to the segments member
    segments = p_segment_arr; 

	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig(); 
}

TypedArray<PackedScene> AKIK_Procedural_Rig::get_segments() const
{
    return segments;
}

void AKIK_Procedural_Rig::set_damping_enabled(bool p_damping_enabled)
{
	damping_enabled = p_damping_enabled;
	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig(); 
}

bool AKIK_Procedural_Rig::get_damping_enabled() const
{
    return damping_enabled;
}

void AKIK_Procedural_Rig::set_damping_speed(float p_damping_speed)
{
	damping_speed = godot::Math::clamp<float>(p_damping_speed, 0.f, std::numeric_limits<float>::max());;
	if (Engine::get_singleton()->is_editor_hint() && is_node_ready()) refresh_rig(); 
}

float AKIK_Procedural_Rig::get_damping_speed() const
{
    return damping_speed;
}
