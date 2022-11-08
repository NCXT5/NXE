#include "string.h"

namespace nxe::util {
String::String(const char *str) {
    m_len = 0;
    while (str[m_len] != '\0')
        m_len++;
    m_data = new char[m_len + 1];
    for (size_t i = 0; i < m_len; i++)
        m_data[i] = str[i];
    m_data[m_len] = '\0';
}

String::String(const nxe::util::String &str) {
    m_len = str.m_len;
    m_data = new char[m_len + 1];
    for (size_t i = 0; i < m_len; i++)
        m_data[i] = str.m_data[i];
    m_data[m_len] = '\0';
}

String::String(const char c) {
    m_len = 1;
    m_data = new char[2];
    m_data[0] = c;
    m_data[1] = '\0';
}

String::String() {
    m_len = 0;
    m_data = new char[1];
    m_data[0] = '\0';
}

String::~String() {
//    delete[] m_data;
}

size_t String::len() const {
    return m_len;
}

size_t String::bytes() const {
    return m_len + 1;
}

String String::subStr(size_t start, size_t len) const {
    if (start + len > m_len)
        len = m_len - start;
    char *str = new char[len + 1];
    for (size_t i = 0; i < len; i++)
        str[i] = m_data[start + i];
    str[len] = '\0';
    String s(str);
    delete[] str;
    return s;
}

size_t String::find(const nxe::util::String &str) const {
    for (size_t i = 0; i < m_len; i++) {
        if (m_data[i] == str.m_data[0]) {
            bool found = true;
            for (size_t j = 1; j < str.m_len; j++) {
                if (m_data[i + j] != str.m_data[j]) {
                    found = false;
                    break;
                }
            }
            if (found)
                return i;
        }
    }
    return -1;
}

Array<String> String::split(const String &delim) const {
    Array<String> arr;
    if (delim.len() == 0)
        for (size_t i = 0; i < m_len; i++)
            arr.sAdd(m_data[i]);
    else {
        String copy = *this;
        while (copy.len() > 0) {
            size_t pos = copy.find(delim);
            if (pos == -1) {
                arr.sAdd(copy);
                break;
            }
            arr.sAdd(copy.subStr(0, pos));
            copy = copy.subStr(pos + delim.len(), copy.len() - pos - delim.len());
        }
    }
    return arr;
}

String::operator const char *() const {
    return m_data;
}

String::operator char *() {
    return m_data;
}
}
