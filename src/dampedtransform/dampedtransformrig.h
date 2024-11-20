#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>


namespace godot {

class DampedTransformRig : public Node3D {
	GDCLASS(DampedTransformRig, Node3D)

private:
	float segment_spacing;
	Ref<PackedScene> default_segment;
	TypedArray<PackedScene> segments;
	Node3D* rig_head;
	Node3D* rig_tail;

protected:
	static void _bind_methods();

public:
	DampedTransformRig();
	~DampedTransformRig();
 
	void _ready() override;
	void _process(double delta) override;

	Node3D* initialize_segment(int index);
	void refresh_rig();

	void set_segment_spacing(float p_segment_spacing);
	float get_segment_spacing() const;
	void set_default_segment(Ref<PackedScene> p_default_segment);
	Ref<PackedScene> get_default_segment() const;
	void set_segments(TypedArray<PackedScene> p_segment);
	TypedArray<PackedScene> get_segments() const;
};

}