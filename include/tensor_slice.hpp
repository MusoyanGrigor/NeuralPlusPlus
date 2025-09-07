#ifndef TENSOR_SLICE_HPP
#define TENSOR_SLICE_HPP

#include <vector>
class Tensor; // forward declare

class TensorSlice {
public:
  TensorSlice(std::vector<double>& data, std::size_t offset,
              const std::vector<std::size_t>& shape,
              const std::vector<std::size_t>& originalShape);

  // access sub-slice elements
  TensorSlice operator[](std::size_t index);
  explicit operator double&() const;

  // assignment operators
  TensorSlice& operator=(double value);
  TensorSlice& operator=(const Tensor& t);
  TensorSlice& operator=(Tensor&& t);

private:
  std::vector<double>& m_data; // reference to original tensor data
    std::size_t m_offset; // start index in m_data
    std::vector<std::size_t> m_shape;
    std::vector<std::size_t> m_originalShape;
};

#endif // TENSOR_SLICE_HPP
