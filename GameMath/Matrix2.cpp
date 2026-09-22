#pragma once // Prevents duplicate inclusion errors
#include <iostream>
#include <cmath> 
#include <Vector>

struct Matrix2 {

	float m00, m01;
	float m10, m11;

	Matrix2() = default;

	// Constructor to easily set all 4 numbers at once
	Matrix2(float n00, float n01, float n10, float n11) {
		m00 = n00; m01 = n01;
		m10 = n10; m11 = n11;
	}

    // ==========================================================
    // NOTE: Determinant (2×2)
    //
    //        | a  b |
    //    M = |      |        +----+      +------.
    //        | c  d |  --->  |    | ---> |     /
    //                        |    |      |    /
    // det(M) = ad - bc       +----+      +---/
    //
    // Determines:
    //
    // • Area scaling
    // • Orientation
    //
    // det > 0  Normal
    // det < 0  Mirrored
    // det = 0  Flattened (No Inverse)
    // ==========================================================
    float determinant() const {
        return (m00 * m11) - (m01 * m10);
    }

    Matrix2 Identity() const {
        return Matrix2(1, 0, 0, 1);
    }


    // ==========================================================
    // NOTE: Inverse (2×2)
    //
    //        | a  b |
    //    M = |      |
    //        | c  d |
    //
    //          1
    // M⁻¹ = --------| d  -b |
    //       det(M)  | -c  a |
    //
    // +----+  --M-->  +----/.  --M⁻¹-->  +----+
    // |    |          |   / |            |    |
    // |    |          |  /  |            |    |
    // +----+          +-/---+            +----+
    //
    // M⁻¹ reverses the transformation.
    //
    // Requires:
    //
    // det(M) ≠ 0
    // ==========================================================
    Matrix2 inverse() const {
        float det = determinant();

        // Safety check: If determinant is 0, we can't divide by 0! 
        // This means the matrix is squished flat and has no inverse.
        if (std::abs(det) < 1e-6f) {
            std::cout << "Warning: Matrix is singular (flat) and cannot be inverted!\n";
            return Identity();  // Return identity matrix as a fallback
        }

        float invDet = 1.0f / det;

        // Swap main diagonal, negate off-diagonal, and multiply by 1/det
        return Matrix2(
            m11 * invDet, -m01 * invDet,
            -m10 * invDet, m00 * invDet
        );
    }

    // ==========================================================
    // NOTE: Scale (Scalar Multiplication)
    //
    // s * | a  b | = | s*a  s*b |
    //     | c  d |   | s*c  s*d |
    // ==========================================================
    Matrix2 scale(float scalar) const {
        return Matrix2(
            m00 * scalar, m01 * scalar,
            m10 * scalar, m11 * scalar
        );
    }

    // ==========================================================
    // NOTE: Eigenvalues (2×2)
    //
    // Solves det(A - λI) = 0 using the quadratic formula:
    // λ² - tr(A)λ + det(A) = 0
    // Where trace tr(A) = a + d
    // ==========================================================
    std::vector<float> eigenvalues() const {
        std::vector<float> result;

        float trace = m00 + m11;
        float det = determinant();

        // Discriminant of the quadratic characteristic equation
        float discriminant = (trace * trace) - (4.0f * det);

        // If discriminant is negative, eigenvalues are complex (e.g. rotation)
        if (discriminant < 0) {
            std::cout << "Warning: Complex eigenvalues detected (not supported by float real numbers).\n";
            return result;
        }

        float sqrtDisc = std::sqrt(discriminant);
        result.push_back((trace + sqrtDisc) / 2.0f); // λ1
        result.push_back((trace - sqrtDisc) / 2.0f); // λ2

        return result;
    }

    // ==========================================================
    // NOTE: Eigenvectors (2×2)
    //
    // For each λ, solves (A - λI)v = 0
    //
    // | a-λ   b  | |x| = |0|
    // |  c   d-λ | |y| = |0|
    //
    // If c != 0, eigenvector is roughly: [-b, a-λ] or [λ-d, c]
    // ==========================================================
    std::vector<std::pair<float, float>> eigenvectors() const {
        std::vector<std::pair<float, float>> vectors;
        std::vector<float> lambdas = eigenvalues();

        for (float lambda : lambdas) {
            float a_minus_lambda = m00 - lambda;
            float b = m01;
            float c = m10;
            float d_minus_lambda = m11 - lambda;

            float vx = 0.0f, vy = 0.0f;

            // Choose the most numerically stable row to solve the locked-in direction
            if (std::abs(c) > 1e-6f) {
                vx = -d_minus_lambda;
                vy = c;
            }
            else if (std::abs(b) > 1e-6f) {
                vx = b;
                vy = -a_minus_lambda;
            }
            else {
                // Diagonal matrix case: directions are along the pure x and y axes
                if (std::abs(a_minus_lambda) < 1e-6f) { vx = 1.0f; vy = 0.0f; }
                else { vx = 0.0f; vy = 1.0f; }
            }

            // Normalize the vector direction so it has a length of 1
            float len = std::sqrt(vx * vx + vy * vy);
            if (len > 1e-6f) {
                vx /= len;
                vy /= len;
            }

            vectors.push_back({ vx, vy });
        }

        return vectors;
    }
};
