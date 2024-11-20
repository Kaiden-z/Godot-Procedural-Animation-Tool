#include "dampedtransform/dampedtransformrig.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void DampedTransformRig::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("get_segment_spacing"), &DampedTransformRig::get_segment_spacing);
    ClassDB::bind_method(D_METHOD("set_segment_spacing", "p_segment_spacing"), &DampedTransformRig::set_segment_spacing);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "segment_spacing"), "set_segment_spacing", "get_segment_spacing");

    ClassDB::bind_method(D_METHOD("get_default_segment"), &DampedTransformRig::get_default_segment);
    ClassDB::bind_method(D_METHOD("set_default_segment", "p_default_segment"), &DampedTransformRig::set_default_segment);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "default_segment"), "set_default_segment", "get_default_segment");

	ClassDB::bind_method(D_METHOD("get_segments"), &DampedTransformRig::get_segments);
    ClassDB::bind_method(D_METHOD("set_segments", "p_segment_arr"), &DampedTransformRig::set_segments);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "segments"), "set_segments", "get_segments");
}

DampedTransformRig::DampedTransformRig() 
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Constructing rig..."); 
	segment_spacing = 1.0f;
	default_segment = Ref<PackedScene>();
	segments = TypedArray<Node3D>();
	rig_head = nullptr;
	rig_tail = nullptr;
}

DampedTransformRig::~DampedTransformRig()
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Deconstructing rig...");  
	if (rig_head != nullptr) {
		rig_head->queue_free();
		rig_head = nullptr;
		rig_tail = nullptr;
	} 
}

void DampedTransformRig::_ready()
{
	UtilityFunctions::print("Calling ready...");
}


void DampedTransformRig::_process(double delta) 
{
	
}

Node3D* DampedTransformRig::initialize_segment(int index)
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

void DampedTransformRig::refresh_rig() 
{
	UtilityFunctions::print("[0x", String::num_int64(reinterpret_cast<uintptr_t>(this), 16), "] Refreshing rig...");

	if (rig_head != nullptr) {
		rig_head->queue_free();
		rig_head = nullptr;
		rig_tail = nullptr;
	}

	if (!segments.is_empty()) {
		rig_head = initialize_segment(0); 
		add_child(rig_head);

		rig_tail = rig_head;

		for (int i = 1; i < segments.size(); ++i) { 
			Node3D* segment = initialize_segment(i);
			rig_tail->add_child(segment);
			segment->set_position(Vector3(0, 0, segment_spacing * -1));
			rig_tail = segment;
		}
	}
}





void DampedTransformRig::set_segment_spacing(float p_segment_spacing)
{
	segment_spacing = p_segment_spacing;
	refresh_rig(); 
}

float DampedTransformRig::get_segment_spacing() const
{
    return segment_spacing;
}
void DampedTransformRig::set_default_segment(Ref<PackedScene> p_default_segment)
{
	default_segment = p_default_segment;
	refresh_rig(); 
}

Ref<PackedScene> DampedTransformRig::get_default_segment() const
{
    return default_segment; 
}

void DampedTransformRig::set_segments(TypedArray<PackedScene> p_segment_arr) 
{	
	// Iterate through the input array and replace null PackedScenes with the default segment
    for (int i = 0; i < p_segment_arr.size(); ++i) {
        if (Object::cast_to<PackedScene>(p_segment_arr[i]) == nullptr) {
            p_segment_arr[i] = *default_segment; // Replace with default segment if null
        }
    }

    // Assign the updated array to the segments member
    segments = p_segment_arr; 

	refresh_rig(); 
}

TypedArray<PackedScene> DampedTransformRig::get_segments() const
{
    return segments;
}
