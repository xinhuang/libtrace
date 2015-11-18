#pragma once

#ifndef _MSC_VER
#include <tbb/enumerable_thread_specific.h>
using tbb::enumerable_thread_specific;
#elif  _MSC_VER != 1700
#include <tbb/enumerable_thread_specific.h>
using tbb::enumerable_thread_specific;
#else

#include <thread>
#include <tbb/concurrent_hash_map.h>

// This is a simple re-implementation of tbb::enumerable_thread_specific
// because VC14 crashes when compiling it. Hope it will be fixed in later
// release.
template <typename T> class enumerable_thread_specific {
  struct ThreadIdHasher {
    std::hash<std::thread::id> Hasher;
    size_t hash(const std::thread::id &V) { return Hasher(V); }
    static bool equal(const std::thread::id &L, const std::thread::id &R) {
      return L == R;
    }
  };
  using Container =
      tbb::concurrent_hash_map<std::thread::id, T, ThreadIdHasher>;
  Container Values;

public:
  using value_type = T;
  class const_iterator {
    typename Container::const_iterator Iter;

  public:
    const_iterator(typename Container::const_iterator Iter) : Iter(Iter) {}
    const T &operator*() const { return Iter->second; }
    const_iterator &operator++() {
      ++Iter;
      return *this;
    }
    const const_iterator &operator++(int) {
      const_iterator V = *this;
      Iter++;
      return V;
    }
    friend bool operator==(const const_iterator &Lhs,
                           const const_iterator &Rhs) {
      return Lhs.Iter == Rhs.Iter;
    }
    friend bool operator!=(const const_iterator &Lhs,
                           const const_iterator &Rhs) {
      return !(Lhs == Rhs);
    }
  };

  T &local() {
    typename Container::accessor A;
    Values.insert(A, std::this_thread::get_id());
    return A->second;
  }

  const_iterator begin() const { return const_iterator(std::begin(Values)); }
  const_iterator end() const { return const_iterator(std::end(Values)); }
};
#endif // _MSC_VER
