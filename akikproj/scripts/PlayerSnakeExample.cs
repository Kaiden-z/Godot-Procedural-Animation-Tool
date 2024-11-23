using Godot;
using System;

public partial class PlayerSnakeExample : CharacterBody3D
{
	[Export] public float MoveSpeed = 5f; // Movement speed
	[Export] public float JumpVelocity = 8f; // Jump strength

	private Vector3 _velocity = Vector3.Zero;

	public override void _PhysicsProcess(double delta)
	{
		// Reset velocity on the XZ plane
		_velocity.X = 0;
		_velocity.Z = 0;

		// Handle movement input
		Vector2 input = Input.GetVector("left", "right", "up", "down");
		if (input != Vector2.Zero)
		{
			_velocity.X = input.X * MoveSpeed;
			_velocity.Z = input.Y * MoveSpeed;
		}

		MoveAndCollide(_velocity * (float)delta);
	}
}
