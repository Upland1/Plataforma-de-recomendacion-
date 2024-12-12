#ifndef UNORDERED_MAP_HPP
#define UNORDERED_MAP_HPP
#include <iostream>  // For std::cout
#include <list>      // For std::list
#include <stdexcept> // For std::out_of_range
#include <vector>    // For std::vector
/**
 * Class that defines a Map (key-value store) using hash tables.
 */
template <typename Key, typename Value> class UnorderedMap {
public:
  /**
   * Constructs an empty map with a default capacity.
   */
  UnorderedMap(size_t capacity = 16) : table_(capacity), size_(0) {}
  /**
   * Clears the map.
   */
  void clear() {
    for (auto &bucket : table_) {
      bucket.clear();
    }
    size_ = 0;
  }

  bool empty() const { return size_ == 0; }

  size_t size() const { return size_; }

  void insert(const Key &key, const Value &value) {
    size_t index = hash_function_(key) % table_.size();
    auto &bucket = table_[index];
    // Check if the key already exists
    for (auto &pair : bucket) {
      if (pair.first == key) {
        pair.second = value; // Update value if key exists
        return;
      }
    }
    // Insert new key-value pair
    bucket.emplace_back(key, value);
    ++size_;
    if (load_factor() > max_load_factor_) {
      rehash();
    }
  }

  void erase(const Key &key) {
    size_t index = hash_function_(key) % table_.size();
    auto &bucket = table_[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (it->first == key) {
        bucket.erase(it);
        --size_;
        return;
      }
    }
    throw std::out_of_range("Key not found in the map.");
  }

  bool contains(const Key &key) const {
    size_t index = hash_function_(key) % table_.size();
    const auto &bucket = table_[index];
    for (const auto &pair : bucket) {
      if (pair.first == key) {
        return true;
      }
    }
    return false;
  }

  const Value &at(const Key &key) const {
    size_t index = hash_function_(key) % table_.size();
    const auto &bucket = table_[index];
    for (const auto &pair : bucket) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::out_of_range("Key not found in the map.");
  }

  Value &at(const Key &key) {
    size_t index = hash_function_(key) % table_.size();
    auto &bucket = table_[index];
    for (auto &pair : bucket) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    throw std::out_of_range("Key not found in the map.");
  }

  Value &operator[](const Key &key) {
    size_t index = hash_function_(key) % table_.size();
    auto &bucket = table_[index];
    for (auto &pair : bucket) {
      if (pair.first == key) {
        return pair.second;
      }
    }
    // If key doesn't exist, insert it with a default value
    bucket.emplace_back(key, Value());
    ++size_;
    if (load_factor() > max_load_factor_) {
      rehash();
    }
    return bucket.back().second;
  }

  std::vector<std::pair<Key, Value>> elements() const {
    std::vector<std::pair<Key, Value>> result;
    result.reserve(size_);
    for (const auto &bucket : table_) {
      for (const auto &pair : bucket) {
        result.push_back(pair);
      }
    }
    return result;
  }
  /**
   * Prints the map.
   */
  void print() const {
    auto elem = elements();
    for (const auto &[key, value] : elem)
      std::cout << key << ": " << value << std::endl;
  }

private:
  /**
   * Returns the load factor of the hash table.
   */
  float load_factor() const {
    return static_cast<float>(size_) / table_.size();
  }
  /**
   * Rehashes the table to a larger size to maintain good performance.
   */
  void rehash() {
    size_t new_capacity = table_.size() * 2;
    std::vector<std::list<std::pair<Key, Value>>> new_table(new_capacity);
    for (const auto &bucket : table_) {
      for (const auto &pair : bucket) {
        size_t new_index = hash_function_(pair.first) % new_capacity;
        new_table[new_index].emplace_back(pair);
      }
    }
    table_ = std::move(new_table);
  }

private:
  std::vector<std::list<std::pair<Key, Value>>> table_; /**< Hash table with
  separate chaining. */
  size_t size_;                                         /**< Number of key-
                                          value pairs in the map. */
  float max_load_factor_ = 0.75f;                       /**< Maximum load
                        factor before rehashing. */
  std::hash<Key> hash_function_;                        /**< Hash function for
                         keys. */
};
#endif