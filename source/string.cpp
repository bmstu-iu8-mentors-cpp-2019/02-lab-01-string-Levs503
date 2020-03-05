// Copyright 2018 Lev <semkov01@mail.ru>
//
// Created by Лев on 26.02.2020.
//
#include "string.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

String::~String() { delete[] array; }

String::String() : String((size_t)0) {}

String::String(const size_t size) {
  array = new char[size];
  length = size;
}

String::String(const String& rhs) : String(rhs.length) {
  std::copy(rhs.array, rhs.array + length, array);
}

String::String(const char* data) : String(strlen(data)) {
  std::copy(data, data + length, array);
}

String& String::operator=(const String& rhs) {
  if (this != &rhs) {
    delete[] array;
    length = rhs.length;
    array = new char[length];
    std::copy(rhs.array, rhs.array + length, array);
  }
  return *this;
}

String& String::operator+=(const String& rhs) {
  char* save = array;
  array = new char[length + rhs.length];
  std::copy(save, save + length, array);
  std::copy(rhs.array, rhs.array + rhs.length, array + length);
  length += rhs.length;
  delete[] save;
  return *this;
}

String& String::operator*=(unsigned int m) {
  char* save = array;
  length *= m;
  array = new char[length];
  for (size_t i = 0; i < length; i++) {
    array[i] = save[i % (length / m)];
  }
  delete[] save;
  return *this;
}

bool String::operator==(const String& rhs) const {
  if (length == rhs.length) {
    for (size_t i = 0; i < length; i++) {
      std::copy(rhs.array, rhs.array + length, array);
    }
    return true;
  }
  return false;
}

size_t String::Find(const String& substr) const {
  size_t finalsize = substr.length;
  size_t size = 0;
  size_t position = 0;
  for (size_t i = 0; i < length; i++) {
    if (array[i] == substr.array[size]) {
      if (size == 0) {
        position = i;
        if (i > length - substr.length) break;
      }
      size++;
      if (size == finalsize) return position;
    } else {
      i = position;
      position = i + 1;
      size = 0;
    }
  }
  return -1;
}

bool String::operator<(const String& rhs) const {
  if (length < rhs.length) return true;
  if (length > rhs.length) return false;
  for (size_t i = 0; i < length; i++) {
    if (array[i] < rhs.array[i]) return true;
    if (array[i] > rhs.array[i]) return false;
  }
  return false;
}

void String::Replace(char oldSymbol, char newSymbol) {
  for (size_t i = 0; i < length; i++) {
    if (array[i] == oldSymbol) array[i] = newSymbol;
  }
}

size_t String::Size() const { return length; }

bool String::Empty() const { return length == 0; }

char String::operator[](size_t index) const { return array[index]; }

char& String::operator[](size_t index) { return array[index]; }

void String::RTrim(char symbol) {
  size_t lengthsave = length;
  for (size_t i = length - 1; i; i--) {
    if (array[i] == symbol) {
      --lengthsave;
    } else {
      break;
    }
  }
  char* save = new char[lengthsave];
  std::copy(array, &array[lengthsave], save);
  delete[] array;
  length = lengthsave;
  array = new char[length];
  std::copy(save, save + lengthsave, array);
  delete[] save;
}

void String::LTrim(char symbol) {
  size_t lengthremove = 0;
  for (size_t i = 0; i < length; i++) {
    if (array[i] == symbol) {
      ++lengthremove;
    } else {
      break;
    }
  }
  char* save = new char[length];
  std::copy(array, array + length, save);
  delete[] array;
  length = length - lengthremove;
  array = new char[length];
  std::copy(save + lengthremove, save + (length + lengthremove), array);
  delete[] save;
}

void String::swap(String& oth) {
  char* savechar = oth.array;
  size_t savesize = oth.length;
  oth.array = array;
  array = savechar;
  oth.length = length;
  length = savesize;
}

std::ostream& operator<<(std::ostream& out, const String& opa) {
  for (size_t i = 0; i < opa.length; i++) {
    out << opa.array[i];
  }
  return out;
}

String operator+(const String& a, const String& b) {
  String c(a.length + b.length);
  std::copy(a.array, a.array + a.length, c.array);
  std::copy(b.array, b.array + b.length, c.array + a.length);
  return c;
}

String operator*(const String& a, unsigned int b) {
  String c(a.length * b);
  for (unsigned int i = 0; i < b; i++) {
    std::copy(a.array, a.array + a.length, c.array + a.length * i);
  }
  return c;
}

bool operator!=(const String& a, const String& b) { return !(a == b); }

bool operator>(const String& a, const String& b) { return !(a < b || a == b); }
