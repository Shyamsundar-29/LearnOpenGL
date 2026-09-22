#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

struct Matrix3
{
    // ==========================================================
    // Matrix3 Layout
    //
    //        | m00  m01  m02 |
    //    M = | m10  m11  m12 |
    //        | m20  m21  m22 |
    //
    // First number  = Row
    // Second number = Column
    //
    // Example:
    //
    // m12 = Row 1, Column 2
    //
    // ==========================================================

    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;


    // ==========================================================
    // Default Constructor
    // ==========================================================

    Matrix3() = default;


    // ==========================================================
    // Constructor
    //
    // Allows us to create the complete matrix at once.
    //
    // ==========================================================

    Matrix3(
        float n00, float n01, float n02,
        float n10, float n11, float n12,
        float n20, float n21, float n22)
    {
        m00 = n00; m01 = n01; m02 = n02;
        m10 = n10; m11 = n11; m12 = n12;
        m20 = n20; m21 = n21; m22 = n22;
    }


    // ==========================================================
    // NOTE: Identity Matrix
    //
    //        | 1  0  0 |
    //    I = | 0  1  0 |
    //        | 0  0  1 |
    //
    // The Identity Matrix does nothing to a vector.
    //
    //        I × V = V
    //
    //             Y
    //             ^
    //             |
    //             |       V
    //             |      /
    //             |     /
    //             |    /
    //             O-----------------> X
    //
    // After:
    //
    //        I × V
    //
    // The vector stays exactly the same.
    //
    // ==========================================================

    static Matrix3 Identity()
    {
        return Matrix3(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        );
    }


    // ==========================================================
    // NOTE: Determinant (3×3)
    //
    // Matrix:
    //
    //        | a  b  c |
    //    M = | d  e  f |
    //        | g  h  i |
    //
    // Expand using the first row:
    //
    // det(M)
    //
    // = a(ei - fh)
    // - b(di - fg)
    // + c(dh - eg)
    //
    //
    //             +---------+
    //             |         |
    //             |         |
    //             |         |
    //             +---------+
    //
    //                 M
    //                 |
    //                 | Transform
    //                 V
    //
    //             +-----------+
    //             |          /
    //             |         /
    //             |        /
    //             +-------/
    //
    //
    // The determinant tells us the volume scaling.
    //
    // det > 0  -> Same orientation
    // det < 0  -> Mirrored orientation
    // det = 0  -> Flattened volume
    //
    // If det = 0, the matrix has no inverse.
    //
    // ==========================================================

    float determinant() const
    {
        return
            m00 * (m11 * m22 - m12 * m21)
            - m01 * (m10 * m22 - m12 * m20)
            + m02 * (m10 * m21 - m11 * m20);
    }


    // ==========================================================
    // NOTE: Inverse Matrix (3×3)
    //
    // The inverse reverses the transformation.
    //
    //        V
    //        |
    //        | Apply M
    //        V
    //
    //       M × V
    //
    //        |
    //        | Apply M⁻¹
    //        V
    //
    //        V
    //
    // Therefore:
    //
    //        M⁻¹ × M = I
    //
    //
    // Formula:
    //
    //        1
    // M⁻¹ = --- × adj(M)
    //       det(M)
    //
    //
    // Important:
    //
    // det(M) ≠ 0
    //
    // If det(M) = 0, the transformation has lost
    // information and cannot be reversed.
    //
    // ==========================================================

    Matrix3 inverse() const
    {
        // STEP 1:
        // Calculate determinant.

        float det = determinant();


        // STEP 2:
        // A determinant close to zero means that
        // the matrix is singular or nearly singular.

        if (std::abs(det) < 1e-6f)
        {
            std::cout
                << "Warning: Matrix3 is singular and cannot be inverted.\n";

            return Identity();
        }


        // ======================================================
        // STEP 3: Calculate Cofactors
        //
        // Each cofactor is the determinant of a 2×2 minor
        // multiplied by an alternating sign.
        //
        // Sign pattern:
        //
        //        | +  -  + |
        //        | -  +  - |
        //        | +  -  + |
        //
        // ======================================================

        float c00 = (m11 * m22 - m12 * m21);
        float c01 = -(m10 * m22 - m12 * m20);
        float c02 = (m10 * m21 - m11 * m20);

        float c10 = -(m01 * m22 - m02 * m21);
        float c11 = (m00 * m22 - m02 * m20);
        float c12 = -(m00 * m21 - m01 * m20);

        float c20 = (m01 * m12 - m02 * m11);
        float c21 = -(m00 * m12 - m02 * m10);
        float c22 = (m00 * m11 - m01 * m10);


        // ======================================================
        // STEP 4:
        // Transpose the Cofactor Matrix.
        //
        // Cofactor Matrix:
        //
        //        | c00  c01  c02 |
        //    C = | c10  c11  c12 |
        //        | c20  c21  c22 |
        //
        // Transpose:
        //
        //        | c00  c10  c20 |
        // adj(M)=| c01  c11  c21 |
        //        | c02  c12  c22 |
        //
        // ======================================================

        float invDet = 1.0f / det;

        return Matrix3(
            c00 * invDet, c10 * invDet, c20 * invDet,
            c01 * invDet, c11 * invDet, c21 * invDet,
            c02 * invDet, c12 * invDet, c22 * invDet
        );
    }


    // ==========================================================
    // NOTE: Scalar Multiplication
    //
    // Every element is multiplied by the same scalar.
    //
    //        | a  b  c |          | sa  sb  sc |
    // s × M =| d  e  f |   --->   | sd  se  sf |
    //        | g  h  i |          | sg  sh  si |
    //
    // Example:
    //
    //        | 1  2  3 |
    // 2 × M =| 4  5  6 |
    //        | 7  8  9 |
    //
    //        | 2   4   6 |
    //      = | 8  10  12 |
    //        |14  16  18 |
    //
    // ==========================================================

    Matrix3 scale(float scalar) const
    {
        return Matrix3(
            m00 * scalar, m01 * scalar, m02 * scalar,
            m10 * scalar, m11 * scalar, m12 * scalar,
            m20 * scalar, m21 * scalar, m22 * scalar
        );
    }


    // ==========================================================
    // NOTE: Trace
    //
    // The trace is the sum of the main diagonal.
    //
    //        | a  b  c |
    //    M = | d  e  f |
    //        | g  h  i |
    //
    //              a
    //               \
    //                e
    //                 \
    //                  i
    //
    // trace(M) = a + e + i
    //
    // For Matrix3:
    //
    // trace = m00 + m11 + m22
    //
    // ==========================================================

    float trace() const
    {
        return m00 + m11 + m22;
    }


    // ==========================================================
    // NOTE: Characteristic Polynomial
    //
    // Eigenvalues are NOT calculated using the Matrix2
    // quadratic formula.
    //
    // For a 3×3 matrix:
    //
    //        det(M - λI) = 0
    //
    // produces a CUBIC equation:
    //
    // λ³ - tr(M)λ² + Cλ - det(M) = 0
    //
    // where C is the sum of the principal 2×2 minors:
    //
    // C =
    //   (m00*m11 - m01*m10)
    // + (m00*m22 - m02*m20)
    // + (m11*m22 - m12*m21)
    //
    // This is different from Matrix2.
    //
    // Matrix2 -> Quadratic
    // Matrix3 -> Cubic
    //
    // ==========================================================

    float characteristicCoefficient() const
    {
        return
            (m00 * m11 - m01 * m10)
            + (m00 * m22 - m02 * m20)
            + (m11 * m22 - m12 * m21);
    }
};