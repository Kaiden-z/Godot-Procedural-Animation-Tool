using Godot;
using System;

public partial class Caterpillar : Node3D
{
	[Export] public float speed = 2f;
    [Export] public float amplitude = 5f;
    private Vector3 startPosition;

    public override void _Ready()
    {
        // Store the initial position of the node
        startPosition = Position;
    }

    public override void _Process(double delta)
    {
        // Calculate the new X and Z positions for the squiggly movement
        float x = Mathf.Sin(Time.GetTicksMsec() / 1000.0f * speed) * amplitude + startPosition.X;
        float z = Mathf.Cos(Time.GetTicksMsec() / 1000.0f * speed) * amplitude + startPosition.Z;

        // Set the node's position, maintaining the initial Y position
		Position = new Vector3(x, startPosition.Y, z);
    }
}
