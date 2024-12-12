#ifndef ARREGLODINAMICO_HPP
#define ARREGLODINAMICO_HPP

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class ArregloDinamico {
public:
    ArregloDinamico() : size_(0), capacity_(1), data_(new T[capacity_]) {}
    // Constructor que inicializa el arreglo del tamaño n sin inicializar sus elementos
    ArregloDinamico(unsigned int size) : size_(size) {
        while (capacity_ < size_) {
            capacity_ *= 2;
        }
        data_ = new T[capacity_];
    };
    

    // Constructor que inicializa el arreglo de tamaño n inicializando sus elementos a un valor constante
    ArregloDinamico(unsigned int size, const T& value) : size_(size) {
        while (capacity_ < size_) {
            capacity_ *= 2;
        }
        data_ = new T[capacity_];
        for (int i = 0; i < size; ++i) {
            data_[i] = value;
        }
    };

    // Constructor que copia el contenido de otro arreglo.
    ArregloDinamico(const ArregloDinamico& array) {
        this->size_ = array.size();
        while (capacity_ < this->size_) {
            capacity_ *= 2;
        }
        this->data_ = new T[this->capacity_];
        for (unsigned int i = 0; i < size_; i++) {
            this->data_[i] = array[i];
        }
    };

    T& operator[](const unsigned int i) { return data_[i]; };

    const T& operator[](const unsigned int i) const { return data_[i]; };

    unsigned int size() const { return size_; }

    unsigned int capacity() const { return capacity_; }

    T& front() { return data_[0]; }

    const T& front() const { return data_[0]; }

    T& back() { return data_[size_ - 1]; }

    const T& back() const { return data_[size_ - 1]; }

    T& at(unsigned int index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at(unsigned int index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    bool empty() const { return size_ == 0; }

    void fill(const T& value) {
        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    int find(const T& value) {
        for (int i = 0; i < size_; ++i) {
            if (data_[i] == value) {
                return i;
            }
        }
        return -1;
    }

    void clear() {
        if (data_ != nullptr) {
            delete[] data_;
        }

        data_ = nullptr;
        size_ = 0;
        capacity_ = 1;
        data_ = new T[capacity_];
    }

    void resize(unsigned int n, const T& value) {
        if (n == (capacity_ / 2)) {
            capacity_ = 1;
        }
        if (n > capacity_) {
            while (capacity_ < n) {
                capacity_ *= 2;
            }
            T* newData = new T[capacity_];
            unsigned int copySize = (n < size_) ? n : size_;
            for (unsigned int i = 0; i < copySize; ++i) {
                newData[i] = data_[i];
            }

            if (data_ != nullptr) {
                delete[] data_;
            }
            data_ = newData;
        }

        if (size_ < n) {
            for (unsigned int i = size_; i < n; ++i) {
                data_[i] = value;
            }
        }

        size_ = n;
    }

    void resize(unsigned int n) {
        if (n == (capacity_ / 2)) {
            capacity_ = 1;
        }
        if (n > capacity_) {
            while (capacity_ < n) {
                capacity_ *= 2;
            }
            T* newData = new T[capacity_];
            unsigned int copySize = (n < size_) ? n : size_;
            for (unsigned int i = 0; i < copySize; ++i) {
                newData[i] = data_[i];
            }

            if (data_ != nullptr) {
                delete[] data_;
            }
            data_ = newData;
        }
        size_ = n;
    }

    void insert(unsigned int index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }

        resize(size_ + 1);

        for (unsigned int i = size_ - 1; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
    }

    void erase(unsigned int n) {
        if (n > size_) {
            throw std::out_of_range("Index out of range");
        }

        for (unsigned int i = n; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        resize(size_ - 1);
    }

    void push_back(const T& value) {
        resize(size_ + 1);
        data_[size_ - 1] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            resize(size_ - 1);
        }
    }

    void push_front(const T& value) { insert(0, value); }

    void pop_front() { erase(0); }

    void print() {
        std::cout << "[ ";
        for (unsigned int i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }

private:
    unsigned int size_{0};
    unsigned int capacity_{1};
    T* data_{nullptr};
};

#endif