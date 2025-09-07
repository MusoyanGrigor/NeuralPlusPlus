#include "tensor_slice.hpp"
#include "tensor.hpp"
#include <stdexcept>

TensorSlice::TensorSlice(std::vector<double>& data, const std::size_t offset, const std::vector<std::size_t>& shape,
    const std::vector<std::size_t>& originalShape) : m_data(data), m_offset(offset), m_shape(shape), m_originalShape(originalShape){}

TensorSlice TensorSlice::operator[](const std::size_t index) {
    if(m_shape.empty()) { throw std::out_of_range("index out of range"); }
    if(index >= m_shape[0]) { throw std::out_of_range("index exceeds dimension size"); }

    if(m_shape.size() == 1) {
        return {m_data, m_offset + index, {}, m_shape};
    }
      std::size_t stride = 1; // number of elements in each sub-slice along this dimension.
      for(std::size_t i = 1; i < m_shape.size(); ++i) {
            stride *= m_shape[i];
      }
      return {m_data, m_offset + index * stride,
          std::vector<std::size_t>(m_shape.begin() + 1, m_shape.end()), m_shape};

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

TensorSlice& TensorSlice::operator=(const Tensor& t) {
    if(this->m_shape != t.getShape()) {
        throw std::logic_error("Shape mismatch");
    }

    const std::size_t& ndim = t.getNdims();
    // compute row-major strides for full tensor
    std::vector<size_t> strides(ndim);
    strides[ndim - 1] = 1;
    for (long long i = static_cast<long long>(ndim) - 2; i >= 0; --i) {
        strides[i] = strides[i + 1] * m_originalShape[i + 1];
    }
    // multi-index counter
    std::vector<size_t> idx(ndim, 0);
    std::size_t i = 0;
    while (true) {
        // compute flat index in parent buffer
        size_t flat_idx = m_offset;
        for (size_t d = 0; d < ndim; ++d) {
            flat_idx += idx[d] * strides[d];
        }
        m_data[flat_idx] = t.getData()[i++];
        // increment multi-index
        long long dim = static_cast<long long>(ndim) - 1;
        while (dim >= 0) {
            idx[dim]++;
            if (idx[dim] < m_shape[dim]) break;
            idx[dim--] = 0;
        }
        if (dim < 0) break; // finished all elements
    }
    return *this;
}
