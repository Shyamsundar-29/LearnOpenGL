#pragma once
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

};