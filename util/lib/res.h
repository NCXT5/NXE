#pragma once

#ifdef __linux__
    #include <exception>
#endif

namespace nxe::util {
/// This is a shorthand class used for returning a function
/// result as a value.
/// @tparam VType The type of the value.
template <typename VType> class Ok {
public:
    /// The value of the result.
    const VType m_value;

    /// Initialize the result with a value.
    /// @param value The value to store.
    explicit Ok(const VType &value) : m_value(value) {}
};

/// This is a shorthand class used for returning a function
/// result as an error.
/// @tparam EType The type of the error.
template <typename EType> class Err {
public:
    /// The error of the result.
    const EType m_error;

    /// Initialize the result with an error.
    /// @param error The error to store.
    explicit Err(const EType &error) : m_error(error) {}
};

/// This is a result class. It is used for returning and accessing error/value
/// data from a function.
/// @tparam VType The type of the value.
/// @tparam EType The type of the error.
template <typename VType, typename EType> class Result {
    const union {
        /// The value data. This is on a successful result.
        VType m_value;

        /// The error data. This is on a failed result.
        EType m_error;
    };

public:
    /// Whether or not the result is a success.
    const bool m_isOk;

    /// Initialize the result with a value. This is for a successful result.
    /// @param value The value to store.
    /// NOLINTNEXTLINE(google-explicit-constructor) TODO: Remove need for google style
    Result(const Ok<VType> &value) : m_value(value.m_value), m_isOk(true) {}

    /// Initialize the result with an error. This is for a failed result.
    /// @param error The error to store.
    /// NOLINTNEXTLINE(google-explicit-constructor) TODO: Remove need for google style
    Result(const Err<EType> &error) : m_error(error.m_error), m_isOk(false) {}

    /// Try to reveal the successful value of the result. If the result is not
    /// successful, this will throw an error.
    /// @return The value of the result.
    VType rev() const {
        if (m_isOk)
            return m_value;
        else {
#ifdef __linux__
            throw std::runtime_error("Result is not an error.");
#else
            // perform an operation that is illegal to cause the program to crash
            // and still be searchable in the debugger.

            // Confused? This is a hack done in assembly to prevent linter warnings.
            __asm__("int $3");
#endif
        }
    }

    /// Try to reveal error of the result. If the result is successful, this will
    /// throw an error.
    /// @return The error of the result.
    EType revErr() const {
        if (!m_isOk)
            return m_error;
        else {
#ifdef __linux__
            throw std::runtime_error("Result is not an error.");
#else
            // perform an operation that is illegal to cause the program to crash
            // and still be searchable in the debugger.

            // Confused? This is a hack done in assembly to prevent linter warnings.
            __asm__("int $3");
#endif
        }
    }
};
}
