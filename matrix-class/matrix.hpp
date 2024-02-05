#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Matrica {
private:
    int width_;
    int height_;
    T *arr_;
public:
    Matrica(int height, int width) : width_(width), height_(height), arr_(new T[width*height]) {}
    Matrica(std::initializer_list<T> l);
    Matrica(const Matrica& o);
    Matrica(Matrica&& o);
    ~Matrica();
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;
    Matrica operator+(const Matrica<T>& o) const;
    Matrica operator-(const Matrica<T>& o) const;
    Matrica& operator+=(const Matrica<T>& o);
    Matrica& operator-=(const Matrica<T>& o);
    Matrica operator*(const T& element) const;
    Matrica operator/(const T& element) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrica<T>& o);
};

template<typename T>
Matrica<T>::Matrica(std::initializer_list<T> l) {
    if (l.size() < 2) throw std::invalid_argument("Matrica<T>::Matrica(std::intializer_list<T>) error: invalid initializer list, there have to be at least two elements");
    auto it = l.begin();
    height_ = *it;
    ++it;
    width_ = *it;
    ++it;
    if (height_*width_ < l.size() - 2) throw std::domain_error("Matrica<T>::Matrica(std::initializer_list<T>) error: too many elements in initializer list");
    arr_ = new T[height_*width_];
    for (int i = 2; i < l.size(); ++i) {
        arr_[i-2] = *it; ++it;
    }
    for (int i = l.size(); i < width_*height_+2; ++i) {
        arr_[i-2] = T();
    }
}

template<typename T>
Matrica<T>::Matrica(const Matrica<T>& o) {
    width_ = o.width_;
    height_ = o.height_;
    arr_ = new T[width_*height_];
    for (int i = 0; i < width_*height_; ++i) {
        arr_[i] = o.arr_[i];
    }
}

template<typename T>
Matrica<T>::Matrica(Matrica<T>&& o) {
    width_ = o.width_;
    height_ = o.height_;
    arr_ = o.arr_;
    o.arr_ = nullptr;
    o.width_ = o.height_ = 0;
}

template<typename T>
Matrica<T>::~Matrica() {
    delete[] arr_;
    width_ = height_ = 0;
}

template<typename T>
T& Matrica<T>::operator()(int i, int j) {
    if (i < 0 || i >= height_) throw std::invalid_argument("XD");
    if (j < 0 || j >= width_) throw std::invalid_argument("YD");
    return arr_[i*width_ + j];
}

template<typename T>
const T& Matrica<T>::operator()(int i, int j) const {
    if (i < 0 || i >= height_) throw std::invalid_argument("XD");
    if (j < 0 || j >= width_) throw std::invalid_argument("YD");
    return arr_[i*width_ + j];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrica<T>& o) {
    for (int i = 0; i < o.height_; ++i) {
        for (int j = 0; j < o.width_; ++j) {
            os << o(i, j) << "  ";
        }
        os << std::endl;
    }
    return os;
}