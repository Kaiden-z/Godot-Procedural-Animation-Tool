using Godot;
using System;

public partial class Caterpillar : Node3D
{
	[Export] public float speed = 2f;
    private Vector3 startPosition;

    public override void _Ready()
    {
        // Store the initial position of the node
        startPosition = new Vector3(0, 1, 7f);
    }

    public override void _Process(double delta)
    {
        // Calculate the new X and Z positions for the squiggly movement
        float x = Mathf.Sin(Time.GetTicksMsec() / 1000.0f * speed) * 7;
        float z = Mathf.Cos(Time.GetTicksMsec() / 1000.0f * speed) * 7;

        // Set the node's position, maintaining the initial Y position
		GlobalPosition = new Vector3(x, 2, z);
    }
}
