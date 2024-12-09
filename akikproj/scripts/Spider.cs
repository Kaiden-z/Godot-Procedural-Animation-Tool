using Godot;
using System;

public partial class Spider : Node3D
{
	[Export] public float direction = 1f;
    [Export] public float speed = 2f;       // Speed of the movement
    [Export] public float distance = 5f;   // Maximum distance from the starting point

    private Vector3 startPosition;
    private float time;

    public override void _Ready()
    {
        // Store the starting position of the node
        startPosition = Position;
    }

    public override void _Process(double delta)
    {
        // Increment time to control movement
        time += (float)delta;

        // Calculate the new X position using a sine wave
        float x = startPosition.X + Mathf.Sin(time * speed) * direction * distance;

        // Set the node's position, maintaining Y and Z
        Position = new Vector3(x, startPosition.Y, startPosition.Z);
    }
}
