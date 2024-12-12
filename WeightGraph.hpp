#ifndef WEIGHTED_GRAPH
#define WEIGHTED_GRAPH

#include "UnorderedMap.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <vector>

template <typename T> class WeightedGraph {
public:
  WeightedGraph() = default;

  bool empty() const { return vertex.empty(); }

  void clear() {
    vertex.clear();
    matrix.clear();
  }

  void add_vertex(const T &v) {
    int x = 0;
    std::vector<double> p;
    vertex.push_back(v);
    matrix.push_back(p);
    unsigned int n = matrix.size() - 1;
    while (x < n) {
      double y = relationship(v, vertex[x]);
      matrix[x].push_back(y);
      matrix[n].push_back(y);
      if (matrix[x][n] != matrix[n][x]) {
        std::cout << n << " matrix size: " << matrix[n].size() << std::endl;
      }
      ++x;
    }
    matrix[n].push_back(0);
    // std::cout << "añadido" << std::endl;
  }

  bool contains_vertex(const T &v) const {
    return std::find(vertex.begin(), vertex.end(), v) != vertex.end();
  }

  void add_edge(const T &v1, const T &v2, const double value) {
    int i1 = get_index(v1);
    int i2 = get_index(v2);
    matrix[i1][i2] = value;
    matrix[i2][i1] = value;
  }

  bool contains_edge(const T &v1, const T &v2) const {
    if (!contains_vertex(v1) || !contains_vertex(v2))
      throw std::out_of_range("One or both vertices not in graph");
    if (v1 == v2)
      throw std::invalid_argument("Cannot check edge to itself");
    int i1 = get_index(v1);
    int i2 = get_index(v2);
    return matrix[i1][i2];
  }

  std::vector<T> neighbors(const T &v) const {
    if (!contains_vertex(v))
      throw std::invalid_argument("Vertex not in graph");
    int index = get_index(v);
    std::vector<T> result;
    for (size_t i = 0; i < matrix[index].size(); ++i) {
      if (matrix[index][i] <= 0.6 && matrix[index][i] > 0) {
        // std::cout << vertex[i].title << ", " << matrix[i][index] <<
        // std::endl;
        result.push_back(vertex[i]);
      }
    }
    return result;
  }

  std::vector<T> getvertex() { return vertex; }

  int get_index_by_title(const std::string &v) {
    int k = vertex.size();
    for (int i = 0; i < k; ++i) {
      if (vertex[i].title == v) {
        return i;
      }
    }
    return -1;
  }

  std::vector<T> vertex;

  std::vector<T> bfs(const T &start) {
    if (!contains_vertex(start))
      throw std::invalid_argument("Start vertex not in graph");

    std::set<T> visited;
    std::queue<T> q;
    std::vector<T> result;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
      T vertex = q.front();
      q.pop();
      result.push_back(vertex);

      for (const T &neighbor : neighbors(vertex)) {
        if (visited.find(neighbor) == visited.end()) {
          visited.insert(neighbor);
          q.push(neighbor);
        }
      }
    }

    return result;
  }

  std::vector<T> dfs(const T &start) {
    if (!contains_vertex(start))
      throw std::invalid_argument("Start vertex not in graph");

    std::set<T> visited;
    std::stack<T> s;
    std::vector<T> result;

    s.push(start);

    while (!s.empty()) {
      T vertex = s.top();
      s.pop();

      if (visited.find(vertex) == visited.end()) {
        visited.insert(vertex);
        result.push_back(vertex);

        for (const T &neighbor : neighbors(vertex)) {
          if (visited.find(neighbor) == visited.end()) {
            s.push(neighbor);
          }
        }
      }
    }

    return result;
  }

  std::vector<T> find_path(const T &start, const T &end,
                           const std::string &method) {
    if (!contains_vertex(start) || !contains_vertex(end)) {
      throw std::invalid_argument("Start or end vertex not in graph");
    }

    if (start == end) {
      return {start};
    }

    std::map<T, T> predecessors;
    std::set<T> visited;
    std::queue<T> q;
    std::stack<T> s;
    std::vector<T> result;

    if (method == "BFS") {
      q.push(start);
      visited.insert(start);

      while (!q.empty()) {
        T current = q.front();
        q.pop();

        for (const T &neighbor : neighbors(current)) {
          if (visited.find(neighbor) == visited.end()) {
            visited.insert(neighbor);
            predecessors[neighbor] = current;
            q.push(neighbor);

            if (neighbor == end) {

              T current_node = end;
              while (current_node != start) {
                result.push_back(current_node);
                current_node = predecessors[current_node];
              }
              result.push_back(start);
              std::reverse(result.begin(), result.end());
              return result;
            }
          }
        }
      }
    } else if (method == "DFS") {
      s.push(start);

      while (!s.empty()) {
        T current = s.top();
        s.pop();

        if (visited.find(current) == visited.end()) {
          visited.insert(current);

          if (current == end) {
            T current_node = end;
            while (current_node != start) {
              result.push_back(current_node);
              current_node = predecessors[current_node];
            }
            result.push_back(start);
            std::reverse(result.begin(), result.end());
            return result;
          }

          for (const T &neighbor : neighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
              if (predecessors.find(neighbor) == predecessors.end()) {
                predecessors[neighbor] = current;
              }
              s.push(neighbor);
            }
          }
        }
      }
    }

    return {};
  }

private:
  double relationship(const T &v1, const T &v2) {
    double relation = 1;

    int year_diff = std::abs(v2.releaseYear - v1.releaseYear);
    if (year_diff > 10) {
      return 999;
    } else {
      relation -= 0.05;
      if (year_diff < 2) {
        relation -= 0.15;
      }
    }

    double rating_diff = std::abs(v2.ratingAvg - v1.ratingAvg);
    if (rating_diff > 1.5) {
      return 999;
    } else {
      relation -= 0.10;
      if (rating_diff < 0.5) {
        relation -= 0.10;
      }
    }

    const int n1 = v1.genres_sep.size();
    const int n2 = v2.genres_sep.size();
    double grade_relation = 0.5 / std::min(n1, n2);

    for (int k = 0; k < n1; ++k) {
      if (v2.genre_Map.contains(v1.genres_sep[k])) {
        relation -= grade_relation;
      }
    }

    return relation;
  }

  std::vector<std::vector<double>> matrix;

  int get_index(const T &v) const {
    auto it = std::find(vertex.begin(), vertex.end(), v);
    if (it == vertex.end())
      throw std::invalid_argument("Vertex not in graph");
    return std::distance(vertex.begin(), it);
  }
};

#endif