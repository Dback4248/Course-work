#pragma once

#ifndef FANF_STRING_H
#define FANF_STRING_H

#include <string>
#include <iostream>

class FanfString {
public:
    FanfString();
    explicit FanfString(const char* cstr);
    explicit FanfString(const std::string& s);

    // Rule of 5
    FanfString(const FanfString& other);
    FanfString(FanfString&& other) noexcept;
    FanfString& operator=(const FanfString& other);
    FanfString& operator=(FanfString&& other) noexcept;
    ~FanfString();

    // Basic ops
    std::size_t size() const;
    bool empty() const;
    const char* c_str() const;
    std::string std() const;

    FanfString& append(const FanfString& rhs);
    FanfString& append(const char* rhs);
    FanfString& push_back(char ch);

    // Comparisons
    bool operator==(const FanfString& rhs) const;
    bool operator!=(const FanfString& rhs) const;

    // Concatenation
    friend FanfString operator+(const FanfString& a, const FanfString& b);

    // Streaming
    friend std::ostream& operator<<(std::ostream& os, const FanfString& s);

private:
    std::string data_;
};

#endif // FANF_STRING_H
