extends Node3D

@export var target_node: Node3D

# Called when the node enters the scene tree for the first time.
func _ready():
	if target_node:
		scale_child_mesh_to_target_position()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta):
	scale_child_mesh_to_target_position()

func scale_child_mesh_to_target_position():
	var target_position = target_node.global_transform.origin
	var direction = target_position - get_node("MeshInstance3D").global_transform.origin
	var distance = direction.length()
	look_at(target_node.global_position)
	scale = Vector3(1, 1, distance + -get_node("MeshInstance3D").position.z)
