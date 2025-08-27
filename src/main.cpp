#include <iostream>
#include "tensor.hpp"

int main() {
    // Test 1: Create a 1D tensor with zeros
    Tensor t1 = Tensor::zeros({5});
    std::cout << "t1 shape: ";
    for (const auto dim : t1.getShape()) std::cout << dim << " ";
    std::cout << "\nt1 elements: ";
    for (size_t i = 0; i < t1.getSize(); ++i) {
        std::cout << static_cast<double&>(t1[i]) << " ";
    }
    std::cout << "\n\n";

    // Test 2: Create a 2D tensor full of a specific value
    Tensor t2 = Tensor::full({3, 4}, 7.5);
    std::cout << "t2 shape: ";
    for (const auto dim : t2.getShape()) std::cout << dim << " ";
    std::cout << "\nt2 elements:\n";
    for (size_t i = 0; i < t2.getShape()[0]; ++i) {
        for (size_t j = 0; j < t2.getShape()[1]; ++j) {
            std::cout << static_cast<double&>(t2[i][j]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // Test 3: Create an identity matrix
    Tensor t3 = Tensor::eye(4);
    std::cout << "t3 (identity matrix) elements:\n";
    for (size_t i = 0; i < t3.getShape()[0]; ++i) {
        for (size_t j = 0; j < t3.getShape()[1]; ++j) {
            std::cout << static_cast<double&>(t3[i][j]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // Test 4: 3D tensor access
    Tensor t4 = Tensor::full({2, 3, 2}, 1.0);
    t4[1][2][1] = 99.0; // assign to a specific element
    std::cout << "t4[1][2][1] = " << static_cast<double&>(t4[1][2][1]) << "\n\n";

    // Test 5: Modify values through TensorSlice
    t2[0][0] = 42.0;
    std::cout << "After modification, t2[0][0] = " << static_cast<double&>(t2[0][0]) << "\n";

    return 0;
}
