#include "tensor.hpp"

int main() {
    Tensor t = Tensor::zeros({3, 3, 3});
    Tensor eye = Tensor::eye(3);

    t[0] = eye;
    return 0;
}