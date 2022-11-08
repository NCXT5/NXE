#pragma once

#include <cstddef>
#include "array.h"

namespace nxe::util {
/// This is a class that can represent strings with objects.
class String {
    /// This is the length of the string.
    size_t m_len;

    /// The actual string data store container.
    char *m_data;

public:
    /// Create a new string from a constant char array.
    /// @param str The string to create.
    String(const char *str);

    /// Create a new string from an already existing string
    /// object.
    /// @param str The string to create from.
    String(const String &str);

    /// Create a new string from a char.
    /// @param c The char to create from.
    String(const char c);

    /// Create a new empty string.
    String();

    ~String();

    /// Get the length of the string.
    /// @return The length of the string.
    size_t len() const;

    /// Get the amount of bytes allocated for the string.
    /// @return The amount of bytes allocated for the string.
    size_t bytes() const;

    /// Get the string part from a staring index to the position of that + the length.
    /// Substr function implementation.
    /// @param start The starting index.
    /// @param len The length of the string.
    /// @return The string part.
    String subStr(size_t start, size_t len) const;

    /// Find a segment in a string and return the index of the first char of that segment.
    /// @param str The string to find.
    /// @return The index of the first char of the segment.
    size_t find(const String &str) const;

    /// Split the string into an array of strings.
    /// @param delim The delimiter to split the string by.
    /// @return The array of strings.
    [[nodiscard]] Array<String> split(const String &delim) const;

    /// Conversion for the string to a c string.
    /// @return The c string.
    operator const char *() const;

    /// Conversion for the string to a c string.
    /// @return The c string.
    operator char *();
};
}
