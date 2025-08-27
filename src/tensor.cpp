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