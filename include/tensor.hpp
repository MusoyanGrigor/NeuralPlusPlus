#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <iosfwd>
#include <vector>
#include "tensor_slice.hpp"

class Tensor
{
public:
    using tensorShape = std::vector<std::size_t>;

    // Getters
    [[nodiscard]] tensorShape getShape() const;
    [[nodiscard]] std::size_t getNdims() const;
    [[nodiscard]] std::size_t getSize() const;
    [[nodiscard]] const std::vector<double>& getData() const;

    // factory methods
    static Tensor zeros(const tensorShape& shape);
    static Tensor full(const tensorShape& shape, double value);
    static Tensor eye(std::size_t rows, std::size_t cols = 0);

    // Element access
    TensorSlice operator[](std::size_t index);
    TensorSlice operator[](std::size_t index) const;
private:
    explicit Tensor(const tensorShape& shape);
    Tensor(std::initializer_list<std::size_t> shape);

    tensorShape m_shape;
    std::size_t m_ndims;
    std::vector<double> m_data;
};

#endif // TENSOR_HPP