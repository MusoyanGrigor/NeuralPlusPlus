#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>

class Tensor
{
public:
    using tensorShape = std::vector<std::size_t>;

    [[nodiscard]] tensorShape getShape() const;
    [[nodiscard]] std::size_t getNdims() const;
    [[nodiscard]] std::size_t getSize() const;

    static Tensor zeros(tensorShape shape);
    static Tensor full(tensorShape shape, double value);
    static Tensor eye(std::size_t rows, std::size_t cols);

    Tensor& operator[](std::size_t index);
    const Tensor& operator[](std::size_t index) const;

private:
    explicit Tensor(const tensorShape& shape);
    Tensor(std::initializer_list<std::size_t> shape);

    tensorShape m_shape;
    std::size_t m_ndims;
    std::vector<double> m_data;
};

#endif // TENSOR_HPP
