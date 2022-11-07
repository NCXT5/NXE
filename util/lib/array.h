#pragma once

#include "res.h"

namespace nxe::util {
/// This is an error code list which contains errors that can be
/// thrown by the array class.
enum class ArrayError {
    /// The index of the accessor was out of bounds.
    IndexOutOfBounds,
};

/// C++ array list class that can store any list of data that meets the
/// compiler's requirements. This class is based off raw C style
/// arrays. This array class makes use of dynamic memory allocation.
/// @tparam ArrEl The type of data to store in the array.
template <typename ArrEl> class Array {
    /// The array storage pointer.
    ArrEl *m_arr;

    /// The current bytes allocated for the array.
    size_t m_bytes;

    /// The current number of elements in the array.
    size_t m_len;

public:
    /// Initialize the array with a given size and starting
    /// data store.
    /// @param data The original data store to use.
    /// @param size The size of the data store.
    explicit Array(const ArrEl *data, const size_t size) {
        m_bytes = size * sizeof(ArrEl);
        m_len = size;
        m_arr = new ArrEl[size];
        for (size_t i = 0; i < size; i++)
            m_arr[i] = data[i];
    }

    /// Initialize the array with a given size and default
    /// initialized items.
    /// @param size The size of the data store.
    explicit Array(const size_t size) {
        m_bytes = size * sizeof(ArrEl);
        m_len = size;
        m_arr = new ArrEl[size];
        for (size_t i = 0; i < size; i++)
            m_arr[i] = ArrEl();
    }

    /// Construct a new array from an already existing array object.
    /// @param arr The array to build from.
    Array(const Array<ArrEl> &arr) {
        m_bytes = arr.m_bytes;
        m_len = arr.m_len;
        m_arr = new ArrEl[m_len];
        for (size_t i = 0; i < m_len; i++)
            m_arr[i] = arr.m_arr[i];
    }

    /// Initialize the array with absolutely no data inside of it.
    /// The size of the array will also be 0 until elements are added.
    Array() {
        m_bytes = 0;
        m_len = 0;
        m_arr = nullptr;
    }

    ~Array() {
        delete[] m_arr;
    }

    /// Retrieve the amount of bytes allocated by the array.
    /// @return The amount of bytes allocated by the array.
    [[nodiscard]] size_t bytes() const {
        return m_bytes;
    }

    /// Retrieve the amount of elements in the array.
    /// @return The amount of elements in the array.
    [[nodiscard]] size_t len() const {
        return m_len;
    }

    /// Add an element into the array. Adding an element will increment the size
    /// of the array by +1. The element will be added to the end of the array.
    /// @param el The element to add to the array.
    /// @return The index of the element that was added to the array's suffix.
    size_t sAdd(const ArrEl &el) {
        m_bytes += sizeof(ArrEl);
        m_len++;
        auto *newArr = new ArrEl[m_len];
        for (size_t i = 0; i < m_len - 1; i++)
            newArr[i] = m_arr[i];
        newArr[m_len - 1] = el;
        delete[] m_arr;
        m_arr = newArr;
        return m_len - 1;
    }

    /// Add an element into the array. Adding an element will increment the size
    /// of the array by +1. The element will be added to the start of the array.
    /// @param el The element to add to the array's prefix.
    /// @return The index of the element that was added to the array's prefix.
    size_t pAdd(const ArrEl &el) {
        m_bytes += sizeof(ArrEl);
        m_len++;
        auto *newArr = new ArrEl[m_len];
        newArr[0] = el;
        for (size_t i = 1; i < m_len; i++)
            newArr[i] = m_arr[i - 1];
        delete[] m_arr;
        m_arr = newArr;
        return 0;
    }

    /// Remove an element at a specific index of the array.
    /// @param index The index of the element to remove.
    /// @return Whether the element was found and removed. False will
    /// be returned if the element is not found.
    bool kill(const size_t index) {
        if (index >= m_len)
            return false;
        m_bytes -= sizeof(ArrEl);
        m_len--;
        auto *newArr = new ArrEl[m_len];
        for (size_t i = 0; i < index; i++)
            newArr[i] = m_arr[i];
        for (size_t i = index; i < m_len; i++)
            newArr[i] = m_arr[i + 1];
        delete[] m_arr;
        m_arr = newArr;
        return true;
    }

    /// Remove an element from the end of the array.
    /// @return Whether the element was found and removed. False will
    /// be returned if the element is not found.
    bool sKill() {
        if (m_len == 0)
            return false;
        m_bytes -= sizeof(ArrEl);
        m_len--;
        auto *newArr = new ArrEl[m_len];
        for (size_t i = 0; i < m_len; i++)
            newArr[i] = m_arr[i];
        delete[] m_arr;
        m_arr = newArr;
        return true;
    }

    /// Remove an element from the start of the array.
    /// @return Whether the element was found and removed. False will
    /// be returned if the element is not found.
    bool pKill() {
        if (m_len == 0)
            return false;
        m_bytes -= sizeof(ArrEl);
        m_len--;
        auto *newArr = new ArrEl[m_len];
        for (size_t i = 0; i < m_len; i++)
            newArr[i] = m_arr[i + 1];
        delete[] m_arr;
        m_arr = newArr;
        return true;
    }

    /// Try to access a specific element in the array.
    /// @param index The index of the element to access.
    /// @return A result carrier containing an error or result.
    [[nodiscard]] Result<ArrEl, ArrayError> access(const size_t index) const {
        if (index >= m_len)
            return Err(ArrayError::IndexOutOfBounds);
        return Ok(m_arr[index]);
    }

    /// Get the beginning pointer to the array.
    /// @return The beginning pointer to the array.
    [[nodiscard]] ArrEl *begin() const {
        return m_arr;
    }

    /// Get the end pointer to the array.
    /// @return The end pointer to the array.
    [[nodiscard]] ArrEl *end() const {
        return m_arr + m_len;
    }
};
}
