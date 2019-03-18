#include "matrix.h"
#include <future>
#include <cassert>


Matrix::Matrix(const size_t height, const size_t width)
{
    data_.reserve(height);
    for (size_t i = 0; i < height; i++)
    {
        std::vector<int> temp_vector;
        temp_vector.reserve(width);
        for (size_t j = 0; j < width; j++)
        {
            temp_vector.push_back(0);
        }
        data_.push_back(std::move(temp_vector));
    }
}



size_t Matrix::GetHeight() const
{
    return data_.size();
}



size_t Matrix::GetWidth() const
{
    if (data_.size() > 0)
    {
        return data_[0].size();
    }
    return 0;
}


int Matrix::GetValue(const size_t height_index, const size_t width_index) const
{
    if (height_index >= GetHeight() || width_index >= GetWidth())
    {
        throw std::out_of_range("out of range");
    }

    return data_[height_index][width_index];
}



void Matrix::SetValue(const size_t height_index, const size_t width_index,
                      const int value)
{
    if (height_index >= GetHeight() || width_index >= GetWidth())
    {
        throw std::out_of_range("out of range");
    }

    data_[height_index][width_index] = value;
}



Matrix Matrix::Transpose() const
{
    Matrix transposed(GetWidth(), GetHeight());

    for (size_t y = 0; y < GetHeight(); y++)
    {
        for (size_t x = 0; x < GetWidth(); x++)
        {
            transposed.SetValue(x, y, data_[y][x]);
        }
    }

    return transposed;
}



std::vector<std::vector<int>> MultiplyMatricesPiece(
    const Matrix& lhs, const Matrix& rhs_transposed,
    const size_t begin_row, const size_t end_row)
{
    assert(begin_row <= end_row);
    assert(lhs.GetWidth() == rhs_transposed.GetWidth());

    std::vector<std::vector<int>> res;
    res.reserve(end_row - begin_row);
    //std::cerr << "Thread: " << begin_row << " - " << end_row << " started" << std::endl;

    for (size_t y = begin_row; y < end_row; y++)
    {
        res.push_back({});
        res.back().reserve(rhs_transposed.GetHeight());
        for (size_t x = 0; x < rhs_transposed.GetHeight(); x++)
        {
            int res_single_element = 0;
            for (size_t i = 0; i < lhs.GetWidth(); i++)
            {
                res_single_element += lhs.GetValue(y, i) * rhs_transposed.GetValue(x, i);
            }
            res.back().push_back(res_single_element);
            //res.SetValue(y, x, res_single_element);
        }
    }

    //std::cerr << "Thread: " << begin_row << " - " << end_row << " finished" << std::endl;
    return res;
}



Matrix Matrix::operator*(Matrix& rhs)
{
    if (GetWidth() == 0)
    {
        if (rhs.GetWidth() != 0)
        {
            throw std::logic_error("Incopatible sizes of matrices");
        }
        return Matrix(0, 0);
    }

    if (GetWidth() != rhs.GetHeight())
    {
        throw std::logic_error("Incopatible sizes of matrices");
    }

    /*{
        LOG_DURATION("No cache-friendly");
        Matrix res(GetHeight(), rhs.GetWidth());
        for (size_t y = 0; y < GetHeight(); y++)
        {
            for (size_t x = 0; x < rhs.GetWidth(); x++)
            {
                int res_single_element = 0;
                for (size_t i = 0; i < GetWidth(); i++)
                {
                    res_single_element += data_[y][i] * rhs.GetValue(i, x);
                }
                res.SetValue(y, x, res_single_element);
            }
        }
        return res;
    }*/
    
    /*{
        LOG_DURATION("cache-friendly");
        Matrix res(GetHeight(), rhs.GetWidth());
        const Matrix rhs_transposed = rhs.Transpose();
        for (size_t y = 0; y < GetHeight(); y++)
        {
            for (size_t x = 0; x < rhs.GetWidth(); x++)
            {
                int res_single_element = 0;
                for (size_t i = 0; i < GetWidth(); i++)
                {
                    res_single_element += GetValue(y, i) * rhs_transposed.GetValue(x, i);
                }
                res.SetValue(y, x, res_single_element);
            }
        }
        return res;
    }*/

    {
        LOG_DURATION("parallel");
        const Matrix rhs_transposed = rhs.Transpose();
        const size_t threads_count = 8;
        std::vector<std::future<std::vector<std::vector<int>>>> res_pieces;
        res_pieces.reserve(threads_count);
        std::vector<std::vector<int>> last_piece;

        for (size_t i = 0; i < threads_count; i++)
        {
            const size_t piece_size = GetHeight() / threads_count;
            const size_t begin_row = i * piece_size;
            const size_t end_row = (i + 1 == threads_count) ?
                GetHeight() : (i + 1) * piece_size;

            if (i + 1 != threads_count)
            {
                res_pieces.emplace_back(std::async(
                    std::launch::async, MultiplyMatricesPiece,
                    *this, rhs_transposed, begin_row, end_row
                ));
            }
            else
            {
                last_piece = MultiplyMatricesPiece(
                    *this, rhs_transposed, begin_row, end_row
                );
            }
        }

        Matrix res(GetHeight(), rhs.GetWidth());
        size_t row_index = 0;
        for (size_t i = 0; i < threads_count; i++)
        {
            const auto& res_piece = (i + 1 == threads_count) ?
                last_piece : res_pieces[i].get();
            for (size_t y = 0; y < res_piece.size(); y++)
            {
                for (size_t x = 0; x < res_piece[y].size(); x++)
                {
                    res.SetValue(row_index, x, res_piece[y][x]);
                }
                row_index++;
            }
        }

        return res;
    }
}



std::istream& operator>>(std::istream& input_stream, Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            int temp_int = 0;
            input_stream >> temp_int;
            matrix.SetValue(y, x, temp_int);
        }
    }

    return input_stream;
}



std::ostream& operator<<(std::ostream& output_stream, Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            output_stream << matrix.GetValue(y, x) << " ";
        }
        std::cout << "\n";
    }

    return output_stream;
}


