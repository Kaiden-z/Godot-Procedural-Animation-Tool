using Godot;
using System;

public partial class Dragon : Node3D
{
    [Export] private float amplitude = 2.0f; // Height of the wave
    [Export] private float frequency = 1.0f; // Speed of the wave

    private Vector3 initialPosition;

    public override void _Ready()
    {
        // Store the initial position of the node
        initialPosition = Position;
    }

    public override void _Process(double delta)
    {
        // Calculate the new Y position using a sine wave
        float waveY = amplitude * 0.01f * Mathf.Sin(Time.GetTicksMsec() / 1000.0f * Mathf.Pi * 2 * frequency);

        // Update the node's position
        Vector3 newPosition = GlobalPosition;
        newPosition.Y += waveY;
        GlobalTransform = new Transform3D(GlobalTransform.Basis, newPosition);
    }
}
