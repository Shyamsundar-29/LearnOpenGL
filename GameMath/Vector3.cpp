#pragma once // Prevents duplicate inclusion errors
#include <iostream>
#include <cmath> 

struct  Vector3 {

	float X = 0;
	float Y = 0;
	float Z = 0;

	Vector3() = default;

	constexpr Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    static constexpr Vector3 Zero() { return { 0.0f, 0.0f, 0.0f }; }
	static constexpr Vector3 XDirection() { return { 1.0f, 0.0f, 0.0f }; }
	static constexpr Vector3 YDirection() { return { 0.0f, 1.0f, 0.0f }; }
	static constexpr Vector3 ZDirection() { return { 0.0f, 0.0f, 1.0f }; }
	
	// ==========================================================
	// NOTE: Distance Between Two Points (3D)
	//
	// Given:
	//
	//     A(x1, y1, z1)
	//     B(x2, y2, z2)
	//
	//                  Z
	//                  ^
	//                  |
	//                  |        * B(x2,y2,z2)
	//                  |       /
	//                  |      /
	//                  |     /
	//                  |    /
	//                  |   /
	//                  |  /
	//                  | /
	//                  |/
	//      * A---------+-----------------------> X
	//                 /
	//                /
	//               /
	//              Y
	//
	// dx = x2 - x1
	// dy = y2 - y1
	// dz = z2 - z1
	//
	// Distance = sqrt(dx² + dy² + dz²)
	//
	// This is the 3D extension of the Pythagorean Theorem.
	// ==========================================================
	constexpr float Distance(Vector3 otherPoint) {
		float dx = X - otherPoint.X;
	    float dy = Y - otherPoint.Y;
		float dz = Z - otherPoint.Z;
		
		return std::sqrtf(dx * dx + dy * dy + dz * dz);
	}	

	// ==========================================================
	// NOTE: Dot Product (3D)
	//
	// Formula:
	//
	// Dot(A, B) = Ax*Bx + Ay*By + Az*Bz
	//
	//                  Z
	//                  ^
	//                  |
	//                  |      B
	//                  |     /
	//                  |    / θ
	//                  |   /
	//                  |  /
	//                  | /
	// -----------------O-------------------------> X
	//                /
	//               /
	//              /
	//             Y
	//
	// A and B start from the same origin.
	//
	// The angle θ is the angle BETWEEN the vectors.
	//
	// Dot(A,B) = |A| |B| cos(θ)
	//
	// Result:
	//
	//   > 0   Same direction       if retrun +1 same direction
	//   = 0   Perpendicular		if retun 0 perpendicular direction
	//   < 0   Opposite direction   if return -1 opposite direction
	// ==========================================================	
	constexpr float Dot(Vector3 otherPoint) const
	{
		return (X * otherPoint.X) + (Y * otherPoint.Y) + (Z * otherPoint.Z);
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
	// NOTE: Normalize a Vector (3D)
	//
	// Original Vector
	//
	//                  Z
	//                  ^
	//                  |
	//                  |      V(x,y,z)
	//                  |     /
	//                  |    /
	//                  |   /
	//                  |  /
	//                  | /
	//                  O-----------------------> X
	//                 /
	//                /
	//               /
	//              Y
	//
	// Step 1:
	// Compute the vector length.
	//
	// Length = sqrt(x² + y² + z²)
	//
	// Step 2:
	// Divide every component by the length.
	//
	// Nx = x / Length
	// Ny = y / Length
	// Nz = z / Length
	//
	// Result:
	//
	// • Same direction
	// • Length = 1 (Unit Vector)
	//
	// Normalized = V / |V|
	// ==========================================================
	constexpr  Vector3 normalization() {

		float length  = std::sqrtf(X * X + Y * Y + Z * Z);
		float normalized_x = X / length;
		float normalized_y = Y / length;
		float normalized_z = Z / length;
		return Vector3(normalized_x , normalized_y , normalized_z);
	}

	// ==========================================================
	// NOTE: Cross Product
	//
	//            | i   j   k |
	// A × B =    |Ax  Ay  Az|
	//            |Bx  By  Bz|
	//
	// Expands to:
	//
	// X = AyBz - AzBy
	// Y = AzBx - AxBz
	// Z = AxBy - AyBx
	//
	//
	//
	//                 Z
	//                 ^
	//                 |
	//                 |     A × B
	//                 |      ^
	//                 |      |
	//                 |      |
	//                 O---------------> X
	//                /
	//               /
	//              /
	//             Y
	//
	//
	// A and B lie in the XY plane.
	//
	//              Y
	//              ^
	//              |
	//              |     A
	//              |    /
	//              |   /
	//              |  /
	//              | /
	// -------------O------------------> X
	//               \
	//                \
	//                 \ B
	//
	// The resulting vector points
	// perpendicular to BOTH vectors.
	//
	// Magnitude:
	//
	// |A × B| = |A||B|sin(θ)
	//
	// Special Cases:
	//
	// θ = 0°      -> Zero Vector
	// θ = 180°    -> Zero Vector
	// θ = 90°     -> Maximum Magnitude
	// ==========================================================
	constexpr  Vector3 Cross(Vector3 Point1 , Vector3 Point2) {

		return Vector3(
			Point1.Y * Point2.Z - Point1.Z * Point2.Y, // X component
			Point1.Z * Point2.X - Point1.X * Point2.Z, // Y component
			Point1.X * Point2.Y - Point1.Y * Point2.X  // Z component
		);
	}


	// 1. Vector Addition (Matches Chapter 2, Equation 2.5)
	Vector3 operator + (const Vector3& other) const {
		return Vector3(X + other.X, Y + other.Y, Z + other.Z);
	}

	// 2. What else is required? Vector Subtraction!
	Vector3 operator - (const Vector3& other) const {
		return Vector3(X - other.X, Y - other.Y, Z - other.Z);
	}

	// 3. What else? Multiplying by a plain number (scalar scaling)
	Vector3 operator*(float scalar) const {
		return Vector3(X * scalar, Y * scalar, Z * scalar);
	}

};