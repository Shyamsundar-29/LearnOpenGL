#pragma once // Prevents duplicate inclusion errors
#include <iostream>
#include <cmath> 

struct  Vector2 {

	float X = 0;
	float Y = 0;

	Vector2() = default;

	constexpr Vector2(float x, float y) : X(x), Y(y){}

	static constexpr Vector2 Zero() { return { 0.0f, 0.0f }; }
	static constexpr Vector2 XDirection() { return { 1.0f, 0.0f}; }
	static constexpr Vector2 YDirection() { return { 0.0f, 1.0f}; }

	// ==========================================================
	// NOTE: Distance Between Two Points
	//
	//             Y
	//             ^
	//
	//         B(x2,y2)
	//            *
	//           /|
	//          / |
	//         /  | dy
	//        /   |
	//       /    |
	//      *-----*
	// A(x1,y1) dx
	//
	//             +---------------> X
	//
	// dx = x2 - x1
	// dy = y2 - y1
	//
	// Distance = sqrt(dx² + dy²)
	//
	// Derived from the Pythagorean Theorem.
	// ==========================================================
	constexpr float Distance(Vector2 otherPoint) {
		float dx = X - otherPoint.X;
		float dy = Y - otherPoint.Y;
		return std::sqrtf(dx * dx + dy * dy);
	}

	// ==========================================================
	// NOTE: Dot Product
	//
	// Formula:
	//
	// Dot(A, B) = Ax*Bx + Ay*By (+ Az*Bz)
	//
	//                 Y
	//                 ^
	//                 |
	//             B  /
	//               / θ
	//              /
	//             /
	// ------------O----------------------> X
	//             \
	//              \
	//               \
	//                \ A
	//
	// The dot product measures how much one vector points
	// in the direction of another.
	//
	// Dot(A,B) = |A| |B| cos(θ)
	//
	// Result:
	//
	//   > 0   Same general direction if retrun +1 same direction
	//   = 0   Perpendicular (90°)	  if retun 0 perpendicular direction
	//   < 0   Opposite directions	  if return -1 opposite direction
	// ==========================================================
	constexpr float Dot(Vector2 otherPoint) const
	{
		return (X * otherPoint.X) + (Y * otherPoint.Y);
	}

	//check is perpendicular
	constexpr bool IsProjectionZero(float dotProductResult) const
	{
		if (dotProductResult == 0.0f)
		{
			return true;
		}
		return false;
	}

	// ==========================================================
	// NOTE: Vector Normalization
	//
	// Original Vector
	//
	//           Y
	//           ^
	//           |
	//           |      V(x,y)
	//           |     /
	//           |    /
	//           |   /
	//           |  /
	// -----------O----------------------> X
	//
	// Length:
	//
	// |V| = sqrt(x² + y²)
	//
	// Normalize:
	//
	// Nx = x / |V|
	// Ny = y / |V|
	//
	// Result:
	//
	//           Y
	//           ^
	//           |
	//           |   Unit Vector
	//           |      /
	//           |     /
	//           |    /
	// -----------O----------------------> X
	//
	// The direction stays the same,
	// but the new vector has length = 1.
	// ==========================================================
	constexpr  Vector2 normalization() {

		float length = std::sqrtf(X * X + Y * Y);
		float normalized_x = X / length;
		float normalized_y = Y / length;
		return Vector2(normalized_x, normalized_y);
	}


	// 1. Vector Addition (Matches Chapter 2, Equation 2.5)
	Vector2 operator + (const Vector2& other) const {
		return Vector2(X + other.X, Y + other.Y);
	}

	// 2. What else is required? Vector Subtraction!
	Vector2 operator - (const Vector2& other) const {
		return Vector2(X - other.X, Y - other.Y);
	}

	// 2. What else? Multiplying by a plain number (scalar scaling)
	Vector2 operator *(float scalar) const {
		return Vector2(X * scalar, Y * scalar);
	}

};