#pragma once
namespace GameMath {

	constexpr float Pi = 3.14159265f;

	constexpr float sqrtf(float x) {
		if (x < 0.0f) return -1.0f;
		if (x == 0.0f || x == 1.0f) return x;
		float curr = x;
		float prev = 0.0f;
		while (curr != prev) {
			prev = curr;
			curr = 0.5f * (curr + x / curr);
		}
		return curr;
	}
}
