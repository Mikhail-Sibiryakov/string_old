#include <iostream>
#include <cstring>
using std::cout, std::cin;

class String {
 private:
  char* array_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

  String(int count) : array_(new char[count + 1]), size_(count), capacity_(count) {
    array_[size_] = '\0';
  }

  void swap(String& str) {
    std::swap(array_, str.array_);
    std::swap(size_, str.size_);
    std::swap(capacity_, str.capacity_);
  }

  void change_capacity(size_t new_capacity) {
    capacity_ = max(1, new_capacity);
    char* new_arrays = new char[capacity_ + 1];
    memcpy(new_arrays, array_, size_ + 1);
    delete[] array_;
    array_ = new_arrays;
  }

  static size_t max(size_t a, size_t b) {
    if (a > b) {
      return a;
    }
    return b;
  }

 public:
  friend std::istream& operator>>(std::istream& in, String& str);

  String(const char* str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
      ++size_;
      ++capacity_;
    }
    array_ = new char[capacity_ + 1];
    memcpy(array_, str, size_ + 1);
  }

  String() : String(0) {};

  String(size_t n, char ch) : array_(new char[n + 1]), size_(n), capacity_(n) {
    memset(array_, ch, n);
    array_[n] = '\0';
  }

  String(const String& str) : array_(new char[str.size_ + 1]), size_(str.size_), capacity_(str.size_) {
    memcpy(array_, str.array_, size_ + 1);
  }

  String& operator=(String str) {
    swap(str);
    return *this;
  }

  char& operator[](size_t index) {
    return array_[index];
  }

  const char& operator[](size_t index) const {
    return array_[index];
  }

  size_t length() const {
    return size_;
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

  void push_back(char ch) {
    if (size_ == capacity_) {
      change_capacity(capacity_ * 2);
    }
    array_[size_] = ch;
    ++size_;
    array_[size_] = '\0';
  }

  void pop_back() {
    --size_;
    array_[size_] = '\0';
  }

  const char& front() const {
    return array_[0];
  }

  char& front() {
    return array_[0];
  }

  const char& back() const {
    return array_[size_ - 1];
  }

  char& back(){
    return array_[size_ - 1];
  }

  String& operator+=(const String& other) {
    if (size_ + other.size_ > capacity_) {
      change_capacity(size_ + other.size_);
    }
    memcpy(array_ + size_, other.array_, other.size_);
    size_ += other.size_;
    array_[size_] = '\0';
    return *this;
  }

  String& operator+=(const char& ch) {
    push_back(ch);
    return *this;
  }

  size_t find(const String& substr) const {
    for (size_t left = 0; left < size_ - substr.size_; ++left) {
      bool ans = true;
      for (size_t i = left; i < left + substr.size_; ++i) {
        if (array_[i] != substr.array_[i - left]) {
          ans = false;
          break;
        }
      }
      if (ans) {
        return left;
      }
    }
    return length();
  }

  size_t rfind(const String& substr) const {
    for (size_t right = size_ - 1; right >= substr.size_ - 1; --right) {
      bool ans = true;
      for (size_t i = right; i >= right - (substr.size_ - 1); --i) {
        if (array_[i] != substr.array_[i - right + substr.size_ - 1]) {
          ans = false;
          break;
        }
      }
      if (ans) {
        return right - substr.size_ + 1;
      }
    }
    return length();
  }

  String substr(size_t start, int count) const {
    String result(count);
    memcpy(result.array_, array_ + start, count);
    return result;
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
    array_[size_] = '\0';
  }

  void shrink_to_fit() {
    change_capacity(size_);
  }

  char* data(){
    return array_;
  }

  const char* data() const {
    return array_;
  }

  ~String() {
    delete[] array_;
  }
};

bool operator<(const String& a, const String& b) {
  for (size_t i = 0; i < a.size() && i < b.size(); ++i) {
    if (a[i] != b[i]) {
      return a[i] < b[i];
    }
  }
  return a.size() < b.size();
}

bool operator>(const String& a, const String& b) {
  return b < a;
}

bool operator<=(const String& a, const String& b) {
  return !(a > b);
}

bool operator>=(const String& a, const String& b) {
  return !(a < b);
}

bool operator==(const String& a, const String& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& a, const String& b) {
  return !(a == b);
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  out << str.data();
  return out;
}

std::istream& operator>>(std::istream& in, String& str) {
  str.clear();
  char tmp;
  in.get(tmp);
  while (!std::isspace(tmp)) {
    str.push_back(tmp);
    in.get(tmp);
  }
  return in;
}

String operator+(const String& a, const String& b) {
  String result = a;
  result += b;
  return result;
}

String operator+(const String& a, const char& ch) {
  String result = a;
  result += ch;
  return result;
}

String operator+(const char& ch, const String& a) {
  String result("");
  result += ch;
  result += a;
  return result;
}

