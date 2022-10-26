#pragma once

namespace fx {
/**
 * This string class is a cross platform, multi architecture string class. The class
 * is designed to be very fast, and work on common microcontrollers, processors, and other
 * platforms.
 */
class String {
private:
    /**
     * The raw string pointer.
     */
    char *str;

    /**
     * This is the length of the string.
     */
    size_t length;

public:

    /**
     * @param str Input string as a character array.
     * @param len Length of the input string.
     */
    String(const char* str, size_t len);

    /**
     * @param str Input string as a character array.
     */
    // TODO: Next line, remove google linter components
    // NOLINTNEXTLINE(google-explicit-constructor)
    String(const char* str);

    /**
     * @param str Input string as a character array.
     */
    explicit String(char* str);

    ~String();

    /**
     * This returns the computed string length.
     * @param str The string to compute the length of.
     * @return The computed string length.
     */
    static size_t strLen(const char *string);

    explicit operator const char *() const;
    String operator+(const String& other) const;
};
}
