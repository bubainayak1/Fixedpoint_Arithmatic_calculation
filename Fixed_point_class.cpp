#include <iostream>
#include <cstdint>
#include <limits>

using namespace std;

// Define the number of fractional bits in fixed-point representation
#define FIXED_POINT_FRACTIONAL_BITS 16  // You can modify this value for different precision
#define FIXED_POINT_SCALE (1 << FIXED_POINT_FRACTIONAL_BITS) // 2^16

// Define fixed-width types based on your target platform (e.g., 32-bit or 16-bit)
typedef int32_t fixed_t;  // Choose a fixed-width integer for fixed-point operations

class FixedPointMath {
public:
    // Convert a floating-point value to a fixed-point representation
    static fixed_t Float_to_fixed(float a) {
        return static_cast<fixed_t>(a * FIXED_POINT_SCALE);
    }

    // Convert an integer value to a fixed-point representation
    static fixed_t int_to_fixed(int a) {
        return static_cast<fixed_t>(a) * FIXED_POINT_SCALE;
    }

    // Convert a fixed-point value back to a floating-point representation
    static float Fixed_to_float(fixed_t a) {
        return static_cast<float>(a) / FIXED_POINT_SCALE;
    }

    // Add two fixed-point values (no scaling needed)
    static fixed_t add(fixed_t a, fixed_t b) {
        return a + b;
    }

    // Subtract two fixed-point values (no scaling needed)
    static fixed_t sub(fixed_t a, fixed_t b) {
        return a - b;
    }

    // Fixed-point multiplication (scaled by the number of fractional bits)
    static fixed_t fixed_multi(fixed_t a, fixed_t b) {
        // Perform multiplication and shift to avoid overflow
        int64_t result = static_cast<int64_t>(a) * b;
        return static_cast<fixed_t>(result >> FIXED_POINT_FRACTIONAL_BITS);
    }

    // Fixed-point division (scaled by the number of fractional bits)
    static fixed_t fixed_div(fixed_t a, fixed_t b) {
        // Perform division and shift to avoid fractional loss
        if (b == 0) {
            cerr << "Division by zero!" << endl;
            return std::numeric_limits<fixed_t>::max(); // Return the max value to indicate error
        }
        return static_cast<fixed_t>((static_cast<int64_t>(a) << FIXED_POINT_FRACTIONAL_BITS) / b);
    }

    // Check for overflow/underflow conditions (assuming 32-bit fixed-point)
    static bool check_overflow(fixed_t a) {
        return a > std::numeric_limits<fixed_t>::max() || a < std::numeric_limits<fixed_t>::min();
    }
};

int main() {
    // Example floating-point and integer values
    float f = -1.55555;  // Floating-point value
    int a = 4;           // Integer value

    // Convert integer and float to fixed-point representation
    fixed_t A = FixedPointMath::int_to_fixed(a);
    fixed_t F = FixedPointMath::Float_to_fixed(f);

    cout << "A after conversion to fixed-point integer: " << A << endl;
    cout << "F after conversion to fixed-point integer: " << F << endl;

    // Perform fixed-point arithmetic
    fixed_t multi_result = FixedPointMath::fixed_multi(A, F);   // Fixed-point multiplication
    fixed_t div_result = FixedPointMath::fixed_div(A, F);       // Fixed-point division

    // Check for overflow/underflow conditions
    if (FixedPointMath::check_overflow(multi_result)) {
        cout << "Overflow in multiplication!" << endl;
    } else {
        cout << "Multiplication result (fixed-point): " << multi_result << endl;
        cout << "Multiplication result (float): " << FixedPointMath::Fixed_to_float(multi_result) << endl;
    }

    if (FixedPointMath::check_overflow(div_result)) {
        cout << "Overflow in division!" << endl;
    } else {
        cout << "Division result (fixed-point): " << div_result << endl;
        cout << "Division result (float): " << FixedPointMath::Fixed_to_float(div_result) << endl;
    }

    return 0;
}
