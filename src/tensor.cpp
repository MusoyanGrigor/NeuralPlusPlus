#include "tensor.hpp"
#include <stdexcept>
#include <algorithm>

Tensor::tensorShape Tensor::getShape() const {
    return m_shape;
}

std::size_t Tensor::getNdims() const {
    return m_ndims;
}

std::size_t Tensor::getSize() const {
    return m_data.size();
}

const std::vector<double> &Tensor::getData() const {
    return m_data;
}

Tensor::Tensor(const tensorShape &shape) : m_shape(shape), m_ndims(shape.size()) {
    std::size_t total_size = 1;
    for (const auto dim: shape) {
        total_size *= dim;
    }
    m_data.resize(total_size, 0.0); // fills with zeros
}

Tensor::Tensor(const std::initializer_list<std::size_t> shape)
    : Tensor(tensorShape(shape)) {
} // delegates to the first constructor

Tensor Tensor::zeros(const tensorShape &shape) {
    return Tensor(shape);
}

Tensor Tensor::full(const tensorShape &shape, const double value) {
    Tensor t(shape);
    std::ranges::fill(t.m_data, value);
    return t;
}

Tensor Tensor::eye(const std::size_t rows, std::size_t cols) {
    if (cols == 0) cols = rows;
    Tensor t({rows, cols});

    for (std::size_t i = 0; i < std::min(rows, cols); i++) {
        t.m_data[i * cols + i] = 1.0;
    }
    return t;
}

TensorSlice Tensor::operator[](std::size_t index) {
    if (index >= m_shape[0]) {
        throw std::out_of_range("index exceeds dimension size");
    }

    if (m_ndims == 1) {
        return {m_data, index, {}, m_shape};
    }
    std::size_t stride = 1;
    for (std::size_t i = 1; i < m_ndims; i++) {
        stride *= m_shape[i];
    }
    return {
        m_data, index * stride,
        std::vector<std::size_t>(m_shape.begin() + 1, m_shape.end()),
        m_shape
    };
}

TensorSlice Tensor::operator[](std::size_t index) const {
    if (index >= m_shape[0]) {
        throw std::out_of_range("index exceeds dimension size");
    }

    if (m_ndims == 1) {
        return {const_cast<std::vector<double> &>(m_data), index, {}, m_shape};
    }
    std::size_t stride = 1;
    for (std::size_t i = 1; i < m_ndims; i++) {
        stride *= m_shape[i];
    }
    return {
        const_cast<std::vector<double> &>(m_data), index * stride,
        std::vector<std::size_t>(m_shape.begin() + 1, m_shape.end()),
        m_shape
    };
}