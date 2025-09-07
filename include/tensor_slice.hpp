#ifndef TENSOR_SLICE_HPP
#define TENSOR_SLICE_HPP

#include <vector>

class Tensor;

class TensorSlice {
public:
  TensorSlice(std::vector<double>& data, const std::vector<std::size_t>& shape, std::size_t offset);

  // access sub-slice elements
  TensorSlice operator[](std::size_t index);
  explicit operator double&() const;
  TensorSlice& operator=(double value);
  TensorSlice& operator=(Tensor t);

private:
  std::vector<double>& m_data; // reference to original tensor data
  std::vector<std::size_t> m_shape;
  std::size_t m_offset; // start index in m_data
};

#endif // TENSOR_SLICE_HPP