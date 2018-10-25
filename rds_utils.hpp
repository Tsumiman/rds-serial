#ifndef __RDS_UTILS_HPP__
#define __RDS_UTILS_HPP__
#include <chrono>

struct algorithm_run {
  std::string graphname;
  bool valid = false;
  bool complete = false;
  bool reverse = false;
  bool complement = false;
  bool correct = false;

  unsigned int time_limit;

  std::chrono::duration<double> time;
  unsigned int value;
  unsigned int last_i;

  std::vector<uint> certificate;
};

struct vertex_set {
  std::vector<uint> vertices;
  uint weight = 0;

  inline void add_vertex(const uint& v, const uint& w) {
    vertices.push_back(v);
    weight += w;
  }

  inline void pop_vertex(const uint& w) {
    vertices.pop_back();
    weight -= w;
  }

  inline size_t size() const {
    return vertices.size();
  }

  inline bool empty() const {
    return vertices.empty();
  }

  inline void clear() {
    vertices.resize(0);
    weight = 0;
  }

  inline void reserve(const size_t& size) {
    vertices.reserve(size);
  }

  operator std::vector<uint>&() { return vertices; }

  inline const uint& operator[](const size_t& idx) const { return vertices[idx]; }
  inline uint& operator[](const size_t& idx) { return vertices[idx]; }
};

#endif
