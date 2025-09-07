#include "tensor.hpp"

int main() {
    Tensor t = Tensor::zeros({3, 3, 3});
    const Tensor eye = Tensor::eye(3);

    t[0] = eye;
    t[1] = Tensor::eye(3);

}