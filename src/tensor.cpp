#include "tensor.hpp"

Tensor::tensorShape Tensor::getShape() const {
    return m_shape;
}

std::size_t Tensor::getNdims() const {
    return m_ndims;
}

std::size_t Tensor::getSize() const {
    return m_data.size();
}

Tensor::Tensor(const tensorShape& shape) : m_shape(shape), m_ndims(shape.size()) {
    std::size_t total_size = 1;
    for(auto dim : shape) {
        total_size *= dim;
    }
    m_data.resize(total_size, 0.0); // fills with zeros
}

Tensor::Tensor(std::initializer_list<std::size_t> shape) : Tensor(tensorShape(shape)) {} // delegates to the first constructor

Tensor Tensor::zeros(tensorShape shape) {
    return Tensor(shape);
}

Tensor Tensor::full(tensorShape shape, double value) {
    Tensor t(shape);
    std::fill(t.m_data.begin(), t.m_data.end(), value);
    return t;
}

Tensor Tensor::eye(std::size_t rows, std::size_t cols = 0) {
  if(cols == 0) cols = rows;
  Tensor t({rows, cols});

  std::size_t min_dim = std::min(rows, cols);
    for(std::size_t i = 0; i < min_dim; i++) {
        std::size_t flat_index = i * cols + i;
        t.m_data[flat_index] = 1.0;
    }
    return t;
}