#pragma once
enum MovementDirection { Up, Down, Left, Right };

struct SnakeData {
	int HeadRow;
	int HeadCol;
	int Length;
	MovementDirection Direction;
};