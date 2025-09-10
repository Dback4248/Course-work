#include <cstring>
#include "String.h.cpp"
#include "String.h"
#include <cctype>
#include <stdexcept>

String::String() {
    Contents = new char[1];
    Contents[0] = '\0';
}

String::String(const char* str) {
    if (!str) {
        Contents = new char[1];
        Contents[0] = '\0';
    }
    else {
        size_t len = std::strlen(str);
        Contents = new char[len + 1];
        std::memcpy(Contents, str, len + 1);
    }
}

String::String(const char* str, size_t len) {
    Contents = new char[len + 1];
    std::memcpy(Contents, str, len);
    Contents[len] = '\0';
}

String::String(const String& other) {
    size_t len = std::strlen(other.Contents);
    Contents = new char[len + 1];
    std::memcpy(Contents, other.Contents, len + 1);
}

String::~String() {
    delete[] Contents;
}

size_t String::Length() const {
    return std::strlen(Contents);
}

char& String::CharacterAt(size_t Index) {
    if (Index >= Length()) throw std::out_of_range("Index out of range");
    return Contents[Index];
}

const char& String::CharacterAt(size_t Index) const {
    if (Index >= Length()) throw std::out_of_range("Index out of range");
    return Contents[Index];
}

bool String::Equals(const String& Other) const {
    return std::strcmp(Contents, Other.Contents) == 0;
}

String& String::Append(const String& Str) {
    size_t len1 = Length();
    size_t len2 = Str.Length();
    char* newBuf = new char[len1 + len2 + 1];
    std::memcpy(newBuf, Contents, len1);
    std::memcpy(newBuf + len1, Str.Contents, len2 + 1);
    delete[] Contents;
    Contents = newBuf;
    return *this;
}

String& String::Prepend(const String& Str) {
    size_t len1 = Length();
    size_t len2 = Str.Length();
    char* newBuf = new char[len1 + len2 + 1];
    std::memcpy(newBuf, Str.Contents, len2);
    std::memcpy(newBuf + len2, Contents, len1 + 1);
    delete[] Contents;
    Contents = newBuf;
    return *this;
}

const char* String::CStr() const {
    return Contents;
}

String String::ToLower() const {
    size_t len = Length();
    String result(*this);
    for (size_t i = 0; i < len; i++) {
        result.Contents[i] = std::tolower((unsigned char)Contents[i]);
    }
    return result;
}

String String::ToUpper() const {
    size_t len = Length();
    String result(*this);
    for (size_t i = 0; i < len; i++) {
        result.Contents[i] = std::toupper((unsigned char)Contents[i]);
    }
    return result;
}

int String::Find(const String& Str) const {
    return Find(0, Str);
}

int String::Find(size_t StartIndex, const String& Str) const {
    if (StartIndex >= Length()) return -1;
    const char* pos = std::strstr(Contents + StartIndex, Str.Contents);
    if (!pos) return -1;
    return static_cast<int>(pos - Contents);
}

String& String::Replace(const String& Find, const String& Replace) {
    size_t findLen = Find.Length();
    size_t replLen = Replace.Length();

    if (findLen == 0) return *this;

    String result;
    for (size_t i = 0; i < Length();) {
        if (std::strncmp(Contents + i, Find.Contents, findLen) == 0) {
            result.Append(Replace);
            i += findLen;
        }
        else {
            char tmp[2] = { Contents[i], '\0' };
            result.Append(String(tmp));
            i++;
        }
    }
    *this = result;
    return *this;
}

String String::operator+(const String& Other) const {
    String temp(*this);
    temp.Append(Other);
    return temp;
}

String& String::operator+=(const String& Other) {
    return Append(Other);
}

bool String::operator==(const String& Other) const {
    return Equals(Other);
}

bool String::operator!=(const String& Other) const {
    return !Equals(Other);
}

String& String::operator=(const String& Str) {
    if (this != &Str) {
        delete[] Contents;
        size_t len = Str.Length();
        Contents = new char[len + 1];
        std::memcpy(Contents, Str.Contents, len + 1);
    }
    return *this;
}

char& String::operator[](size_t Index) {
    return CharacterAt(Index);
}

const char& String::operator[](size_t Index) const {
    return CharacterAt(Index);
}

std::ostream& operator<<(std::ostream& Stream, const String& Str) {
    Stream << Str.Contents;
    return Stream;
}