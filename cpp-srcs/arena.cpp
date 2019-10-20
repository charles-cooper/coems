// copyright 2019 Charles Cooper - MIT license

/* An arena allocator. It uses a non-shrinking vector as its pool,
 * and a vector (LIFO stack) as its free list.
 *
 * To allocate an object, do the following:
 * If there are no free locations, add an empty item to the pool and
 * return its location (size of m_items before adding it).
 * If there is a free location, pop its address off the free list
 * and return that.
 * To free an object, push its address onto the free list.
 * Note that pointers are not guaranteed to be stable across invocations
 * of `allocate`. To have a stable way of referencing an object use
 * `get` on its address.
 *
 * Performance: Since the pool and the free list are both represented
 * as vectors, an allocate is an increment (and possibly an array copy)
 * if the free list is empty, or a decrement and dereference (to the
 * tail of the pool), if the free list is not empty. A deallocate is a
 * decrement and a write to memory.
 */

#include <vector>

template <class T>
class arena {

  std::vector<T>      m_items; // allocated items
  std::vector<size_t> m_free;  // freed items

  arena() { // empty constructor
  }

  // reserve a certain number of items in the underlying vector
  void reserve(size_t reserve_size) {
    m_items.reserve(reserve_size);
  }

  T *get(size_t idx) {
    return &m_items[idx];
  }

  size_t alloc(void) {

    if (m_free.empty()) {
      size_t ret = m_items.size();
      m_items.push_back(T());
      return ret;

    } else {
      size_t ret = m_free.back();
      m_free.pop_back();
      return ret;
    }
  }

  void free(size_t idx) {
    m_free.push_back(idx);
  }
};
