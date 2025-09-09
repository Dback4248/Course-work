#include "FanfString.h"
#include <cstddef>

FanfString::FanfString() : data_() {}
FanfString::FanfString(const char* cstr) : data_(cstr ? cstr : "") {}
FanfString::FanfString(const std::string& s) : data_(s) {}

FanfString::FanfString(const FanfString& other) : data_(other.data_) {}
FanfString::FanfString(FanfString&& other) noexcept : data_(std::move(other.data_)) {}

FanfString& FanfString::operator=(const FanfString& other) {
    if (this != &other) data_ = other.data_;
    return *this;
}
FanfString& FanfString::operator=(FanfString&& other) noexcept {
    if (this != &other) data_ = std::move(other.data_);
    return *this;
}

FanfString::~FanfString() = default;

std::size_t FanfString::size() const { return data_.size(); }
bool FanfString::empty() const { return data_.empty(); }
const char* FanfString::c_str() const { return data_.c_str(); }
std::string FanfString::std() const { return data_; }

FanfString& FanfString::append(const FanfString& rhs) { data_ += rhs.data_; return *this; }
FanfString& FanfString::append(const char* rhs) { data_ += (rhs ? rhs : ""); return *this; }
FanfString& FanfString::push_back(char ch) { data_.push_back(ch); return *this; }

bool FanfString::operator==(const FanfString& rhs) const { return data_ == rhs.data_; }
bool FanfString::operator!=(const FanfString& rhs) const { return data_ != rhs.data_; }

FanfString operator+(const FanfString& a, const FanfString& b) {
    FanfString out(a.data_);
    out.data_ += b.data_;
    return out;
}

std::ostream& operator<<(std::ostream& os, const FanfString& s) {
    os << s.data_;
    return os;
}