#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>

class Tensor
{
public:
    using tensorShape = std::vector<std::size_t>;

    tensorShape getShape() const;
    std::size_t getNdims() const;
    std::size_t getSize() const;

    static Tensor zeros(tensorShape shape);
    static Tensor eye(std::size_t N);
    static Tensor full(tensorShape shape, double value);

    Tensor& operator[](std::size_t index);
    const Tensor& operator[](std::size_t index) const;

private:
    explicit Tensor(const tensorShape& shape);
    explicit Tensor(std::initializer_list<std::size_t> shape);

    tensorShape m_shape;
    std::size_t m_ndims;
    std::vector<double> m_data;
};

#endif // TENSOR_HPP