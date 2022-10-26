#include "string.hxx"

namespace fx {
String::String(const char *str, size_t len): length(len) {
    this->str = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        this->str[i] = str[i];
    }

    this->str[len] = '\0';
}

String::String(char *str): length(strLen(str)) {
    this->str = new char[this->length + 1];
    for (size_t i = 0; i < this->length; i++) {
        this->str[i] = str[i];
    }
    this->str[this->length] = '\0';
}

String::String(const char *str): length(strLen(str)) {
    this->str = new char[length + 1];
    for (size_t i = 0; i < length; i++) {
        this->str[i] = str[i];
    }
    this->str[length] = '\0';
}

String::~String() {
    delete str;
}

String::operator const char *() const {
    return str;
}

String String::operator + (const fx::String &other) const {
    const size_t len = this->length + other.length + 1;
    char *result = new char[len];

    for (size_t i = 0; i < this->length; i++) {
        result[i] = this->str[i];
    }

    for (size_t i = 0; i < other.length; i++) {
        result[this->length + i] = other.str[i];
    }

    result[len - 1] = '\0';
    return String(result);
}

size_t String::strLen(const char *string) {
    size_t len = 0;
    while (string[len] != '\0') {
        len++;
    }

    return len;
}
}
