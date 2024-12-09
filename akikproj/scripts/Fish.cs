using Godot;
using System;

public partial class Fish : Node3D
{
    // Variables for movement speed and amplitude
    public float speed = 2f;
    public float amplitude = 5f;
    public float frequency = 1f;

    private Vector3 startPosition;

    public override void _Ready()
    {
        // Store the initial position of the node
        startPosition = Position;
    }

    public override void _Process(double delta)
    {
        // Calculate the new X and Z positions for the squiggly movement
        float x = startPosition.X + Mathf.Sin(Time.GetTicksMsec() / 1000.0f * speed) * amplitude;
        float z = startPosition.Z + Mathf.Cos(Time.GetTicksMsec() / 1000.0f * frequency) * amplitude;

        // Set the node's position, maintaining the initial Y position
        GlobalTransform = new Transform3D(GlobalTransform.Basis, new Vector3(x, startPosition.Y, z));
    }
}
