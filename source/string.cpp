// Copyright 2018 Lev <semkov01@mail.ru>
//
// Created by Лев on 26.02.2020.
//
#include "string.hpp"

#include <algorithm>
#include <iostream>

String::~String() { delete[] array; }

String::String() {
  array = new char[0];
  length = 0;
}

String::String(const size_t size) {
  array = new char[size];
  length = size;
}

String::String(const String& rhs) {
  length = rhs.length;
  array = new char[length];
  std::copy(rhs.array, &rhs.array[length], array);
}

String::String(const char* data) {
  size_t i = 0;
  length = 0;
  while (data[i] != '\0') {
    length++;
    i++;
  }
  array = new char[length];
  std::copy(data, &data[length], array);
}

String& String::operator=(const String& rhs) {
  if (this != &rhs) {
    delete[] array;
    length = rhs.length;
    array = new char[length];
    std::copy(rhs.array, &rhs.array[length], array);
  }
  return *this;
}

String& String::operator+=(const String& rhs) {
  String save(*this);
  delete[] array;
  array = new char[length + rhs.length];
  std::copy(save.array, &save.array[length], array);
  std::copy(rhs.array, &rhs.array[rhs.length], &array[length]);
  length += rhs.length;
  return *this;
}

String& String::operator*=(unsigned int m) {
  char* save = new char[length];
  std::copy(array, &array[length], save);
  size_t lengthsave = length;
  length *= m;
  delete[] array;
  array = new char[length];
  for (size_t i = 0; i < length; i++) {
    array[i] = save[i % lengthsave];
  }
  delete[] save;
  return *this;
}

bool String::operator==(const String& rhs) const {
  if (length == rhs.length) {
    for (size_t i = 0; i < length; i++) {
      std::copy(rhs.array, &rhs.array[length], array);
    }
    return true;
  } else {
    return false;
  }
}

size_t String::Find(const String& substr) const {
  size_t finalsize = substr.length;
  size_t size = 0;
  size_t position = 0;
  for (size_t i = 0; i < length; i++) {
    if (array[i] == substr.array[size]) {
      if (size == 0) position = i;
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

bool String::Empty() const {
  if (length == 0) return true;
  return false;
}

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
  std::copy(save, &save[lengthsave], array);
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
  std::copy(array, &array[length], save);
  delete[] array;
  length = length - lengthremove;
  array = new char[length];
  std::copy(&save[lengthremove], &save[length + lengthremove], array);
  delete[] save;
}

void String::swap(String& oth) {
  String save(oth);
  oth.length = length;
  length = save.length;
  delete[] oth.array;
  oth.array = new char[oth.length];
  std::copy(array, &array[oth.length], oth.array);
  delete[] array;
  array = new char[length];
  std::copy(save.array, &save.array[length], array);
}

std::ostream& operator<<(std::ostream& out, const String& opa) {
  for (size_t i = 0; i < opa.length; i++) {
    out << opa.array[i];
  }
  return out;
}

String operator+(const String& a, const String& b) {
  String c(a);
  c += b;
  return c;
}

String operator*(const String& a, unsigned int b) {
  String c(a);
  c *= b;
  return c;
}

bool operator!=(const String& a, const String& b) {
  if (a == b) return false;
  return true;
}

bool operator>(const String& a, const String& b) {
  if (a != b || a < b) return false;
  return true;
}
