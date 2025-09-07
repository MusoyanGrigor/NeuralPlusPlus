#include "tensor_slice.hpp"
#include <stdexcept>

TensorSlice::TensorSlice(std::vector<double>& data, const std::vector<std::size_t>& shape, const std::size_t offset)
    : m_data(data), m_shape(shape), m_offset(offset) {}

TensorSlice TensorSlice::operator[](const std::size_t index) {
    if(m_shape.empty()) { throw std::out_of_range("index out of range"); }
    if(index >= m_shape[0]) { throw std::out_of_range("index exceeds dimension size"); }

    if(m_shape.size() == 1) {
        return {m_data, {}, m_offset + index};
    }
      std::size_t stride = 1; // number of elements in each sub-slice along this dimension.
      for(std::size_t i = 1; i < m_shape.size(); ++i) {
            stride *= m_shape[i];
      }
      return {m_data, std::vector<std::size_t>(m_shape.begin() + 1, m_shape.end()), m_offset + index * stride};

}

TensorSlice::operator double&() const {
    if(!m_shape.empty()) {
        throw std::logic_error("Cannot convert non-scalar slice to double");
    }
    return m_data[m_offset];
}

TensorSlice& TensorSlice::operator=(const double value) {
    m_data[m_offset] = value;
    return *this;
}