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