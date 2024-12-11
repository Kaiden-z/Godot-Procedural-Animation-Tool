using Godot;
using System;

public partial class DragonPlayer : Node3D
{
    // [Export] private float speed = 10f; // Speed of the player while flying
    // [Export] private float acceleration = 5f; // Acceleration towards the target velocity
    // [Export] private float deceleration = 5f; // Deceleration when no input is given

    // private Camera3D _camera;
    // private Vector3 _velocity;

    // public override void _Ready()
    // {
    //     // Get the camera, assuming it is a child of this node
    //     _camera = GetNode<Camera3D>("Camera3D");
    //     if (_camera == null)
    //     {
    //         GD.PrintErr("Camera node not found! Make sure the camera node path is correct.");
    //     }
    // }

    // public override void _PhysicsProcess(double delta)
    // {
    //     Vector3 inputDirection = GetInputDirection();

    //     if (inputDirection != Vector3.Zero)
    //     {
    //         Vector3 targetVelocity = inputDirection * speed;
    //         _velocity = _velocity.Lerp(targetVelocity, acceleration * (float)delta);
    //     }
    //     else
    //     {
    //         _velocity = _velocity.Lerp(Vector3.Zero, deceleration * (float)delta);
    //     }

    //     Translate(_velocity * (float)delta);
    // }

    // private Vector3 GetInputDirection()
    // {
    //     Vector3 direction = Vector3.Zero;

    //     // Get input from player
    //     if (Input.IsActionPressed("up"))
    //         direction += Vector3.Forward;
    //     if (Input.IsActionPressed("left"))
    //         direction -= Vector3.Right;
    //     if (Input.IsActionPressed("right"))
    //         direction += Vector3.Right;

    //     // Convert local direction to global direction based on the camera's orientation
    //     direction = direction.Rotated(Vector3.Up, _camera.GlobalTransform.Basis.GetEuler().Y);

    //     return direction.Normalized();
    // }
}
