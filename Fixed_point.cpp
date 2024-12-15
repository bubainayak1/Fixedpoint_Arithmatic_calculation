#include <iostream>
#include <cstdint>
using namespace std;

// Corrected macros
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define mul(a, b) ((a) * (b))

// Define the number of fractional bits in fixed-point representation
#define Fixed_point_fractional_bits 16  
// Define the scaling factor for fixed-point conversion (2^16)
#define Fixed_point_scale (1 << Fixed_point_fractional_bits) // 65536

// Convert a floating-point value to a fixed-point representation
// Formula: fixed_value = float_value * Fixed_point_scale
int Float_to_fixed(float a){
    return static_cast<int>(a * Fixed_point_scale);
}

// Convert an integer value to a fixed-point representation
// Formula: fixed_value = int_value * Fixed_point_scale
int int_to_fixed(int a){
    return static_cast<int>(a) * Fixed_point_scale;
}

// Convert a fixed-point value back to a floating-point representation
// Formula: float_value = fixed_value / Fixed_point_scale
float Fixed_to_float(int a){
    return static_cast<float>(a) / Fixed_point_scale;
}

// Add two fixed-point values (no scaling is required for addition)
int add(int a, int b){
    return (a + b);
}

// Subtract two fixed-point values (no scaling is required for subtraction)
int sub(int a, int b){
    return (a - b);
}

// Fixed-point multiplication
// Algorithm:
// 1. Multiply the two fixed-point values: result = A_fixed * B_fixed.
//    This results in a large intermediate value.
// 2. Scale back by right-shifting the result by Fixed_point_fractional_bits (16).
// 3. Use int64_t for intermediate results to prevent overflow.
// Formula: fixed_result = (A_fixed * B_fixed) >> Fixed_point_fractional_bits
int fixed_multi(int a, int b){
    return static_cast<int>((static_cast<int64_t>(a) * b) >> Fixed_point_fractional_bits);
}

// Fixed-point division
// Algorithm:
// 1. Scale up the numerator by left-shifting it by Fixed_point_fractional_bits (16).
// 2. Divide the scaled numerator by the denominator (B_fixed).
// 3. Use int64_t for intermediate results to prevent overflow.
// Formula: fixed_result = (A_fixed << Fixed_point_fractional_bits) / B_fixed
int fixed_Div(int a, int b){
    return static_cast<int>((static_cast<int64_t>(a) << Fixed_point_fractional_bits) / b);
}

int main(){
    // Example floating-point and integer values
    float f = 1.55555;  // Floating-point value
    int a = 4;          // Integer value

    // Floating-point multiplication and division (baseline for comparison)
    float result = a * f;
    cout << "multi_ply_result :" << result << endl;
    float Dresult = a / f;
    cout << "Divide__result :" << Dresult << endl;

    // Convert integer and float to fixed-point representation
    int A = int_to_fixed(a);  // Convert integer to fixed-point
    int F = Float_to_fixed(f); // Convert float to fixed-point

    cout << "A after conversion to fixed-point integer: " << A << endl;
    cout << "F after conversion to fixed-point integer: " << F << endl;
    cout << "F again converted back to float: " << Fixed_to_float(F) << endl;

    // Perform fixed-point multiplication and division
    int multi_result = fixed_multi(A, F);   // Fixed-point multiplication
    int Divided_result = fixed_Div(A, F);  // Fixed-point division

    cout << "Multiply result after fixed point: " << multi_result << endl;
    cout << "Divided result after fixed point: " << Divided_result << endl;

    // Convert fixed-point results back to floating-point
    cout << "Multiply after convert to floating point: " << Fixed_to_float(multi_result) << endl;
    cout << "Divided after convert to floating point: " << Fixed_to_float(Divided_result) << endl;

    // Calculate precision loss for multiplication
    float fixed_mul_float_result = Fixed_to_float(multi_result);
    float mul_precision_loss = result - fixed_mul_float_result;
    cout << "Precision loss in multiplication: " << mul_precision_loss << endl;

    // Calculate precision loss for division
    float fixed_div_float_result = Fixed_to_float(Divided_result);
    float div_precision_loss = Dresult - fixed_div_float_result;
    cout << "Precision loss in division: " << div_precision_loss << endl;

    return 0;
}