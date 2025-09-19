#ifndef CHAR_TRAITS_FIX_H
#define CHAR_TRAITS_FIX_H

#include <cstring>
#include <string> // For std::char_traits
namespace std {
template <> struct char_traits<unsigned char> {
    using char_type = unsigned char; // NOLINT(*-identifier-naming)
    using int_type = int; // NOLINT(*-identifier-naming)
    using off_type = streamoff; // NOLINT(*-identifier-naming)
    using pos_type = streampos; // NOLINT(*-identifier-naming)
    using state_type = mbstate_t; // NOLINT(*-identifier-naming)
    // using comparison_category = strong_ordering; // NOLINT(*-identifier-naming)
    static constexpr void assign(char_type &l, const char_type &r) noexcept {
        l = r;
    }
    static constexpr bool eq(char_type l, char_type r) noexcept {
        return l == r;
    }
    static constexpr bool lt(char_type l, char_type r) noexcept {
        return l < r;
    }
    static int compare(const char_type *l, const char_type *r, size_t s) noexcept {
        return strncmp((const char *) l, (const char *) r, s);
    }
    static size_t length(const char_type *s) noexcept {
        return strlen((const char *) s);
    }
    static const char_type *find(const char_type *haystack, size_t size, const char_type &needle) noexcept {
        return (const char_type *) memchr(haystack, (int_type) needle, size);
    }
    static char_type *move(char_type *dst, const char_type *src, size_t size) noexcept {
        return (char_type *) memmove(dst, src, size);
    }
    static char_type *copy(char_type *dst, const char_type *src, size_t size) noexcept {
        return (char_type *) memcpy(dst, src, size);
    }
    static constexpr char_type *assign(char_type *dst, size_t size, char_type c) noexcept {
        for (char_type *it = dst, *end = dst + size; it != end; ++it) {
            *it = c;
        }
        return dst;
    }
    static constexpr int_type not_eof(int_type c) noexcept {
        return eq_int_type(c, eof()) ? ~eof() : c;
    }
    static constexpr char_type to_char_type(int_type c) noexcept {
        return char_type(c);
    }
    static constexpr int_type to_int_type(char_type c) noexcept {
        return int_type((unsigned char) c);
    }
    static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept {
        return c1 == c2;
    }
    static constexpr int_type eof() noexcept {
        return int_type(EOF);
    }
}; // char_traits<unsigned char>

template<> struct char_traits<unsigned short>
{
  typedef unsigned short	char_type;
  typedef unsigned long     int_type;
  typedef streampos         pos_type;
  typedef streamoff         off_type;
  typedef mbstate_t         state_type;
  static void 
  assign(char_type& __c1, const char_type& __c2)
  { __c1 = __c2; }
  static bool 
  eq(const char_type& __c1, const char_type& __c2)
  { return __c1 == __c2; }
  static bool 
  lt(const char_type& __c1, const char_type& __c2)
  { return __c1 < __c2; }
  static int 
  compare(const char_type* __s1, const char_type* __s2, size_t __n)
  { 
    for (size_t __i = 0; __i < __n; ++__i)
      if (!eq(__s1[__i], __s2[__i]))
        return lt(__s1[__i], __s2[__i]) ? -1 : 1;
    return 0; 
  }
  static size_t
  length(const char_type* __s)
  { 
    const char_type* __p = __s; 
    while (*__p) ++__p; 
    return static_cast<size_t>(__p - __s);
  }
  static const char_type* 
  find(const char_type* __s, size_t __n, const char_type& __a)
  { 
    for (const char_type* __p = __s; size_t(__p - __s) < __n; ++__p)
      if (*__p == __a) return __p;
    return 0;
  }
  static char_type* 
  move(char_type* __s1, const char_type* __s2, size_t __n)
  { return static_cast<char_type*>(memmove(__s1, __s2, __n * sizeof(char_type))); }
  static char_type* 
  copy(char_type* __s1, const char_type* __s2, size_t __n)
  { return static_cast<char_type*>(memcpy(__s1, __s2, __n * sizeof(char_type))); }
  static char_type* 
  assign(char_type* __s, size_t __n, char_type __a)
  { 
    for (char_type* __p = __s; __p < __s + __n; ++__p) 
      assign(*__p, __a);
    return __s; 
  }
  static char_type 
  to_char_type(const int_type& __c)
  { return char_type(__c); }
  static int_type 
  to_int_type(const char_type& __c) { return int_type(__c); }
  static bool 
  eq_int_type(const int_type& __c1, const int_type& __c2)
  { return __c1 == __c2; }
  static int_type 
  eof() { return int_type(-1); }
  static int_type 
  not_eof(const int_type& __c)
  { return eq_int_type(__c, eof()) ? int_type(0) : __c; }
};
template <> struct char_traits<unsigned int> {
  using char_type = unsigned int;
  using int_type = unsigned long; 
  using off_type = streamoff;
  using pos_type = streampos;
  using state_type = mbstate_t;
  static constexpr void assign(char_type &r, const char_type &a) noexcept {
    r = a;
  }
  static constexpr bool eq(char_type a, char_type b) noexcept { return a == b; }
  static constexpr bool lt(char_type a, char_type b) noexcept { return a < b; }
  static constexpr int compare(const char_type *s1, const char_type *s2, size_t n) {
    for (size_t i = 0; i < n; ++i) {
      if (lt(s1[i], s2[i]))
        return -1;
      if (lt(s2[i], s1[i]))
        return 1;
    }
    return 0;
  }
  static constexpr size_t length(const char_type *s) {
    size_t i = 0;
    while (!eq(s[i], char_type(0)))
      ++i;
    return i;
  }
  static constexpr const char_type *find(const char_type *s, size_t n, const char_type &a) {
    for (size_t i = 0; i < n; ++i) {
      if (eq(s[i], a))
        return s + i;
    }
    return nullptr;
  }
  static char_type *move(char_type *s1, const char_type *s2, size_t n) {
    if (n == 0)
      return s1;
    return static_cast<char_type *>(memmove(s1, s2, n * sizeof(char_type)));
  }
  static char_type *copy(char_type *s1, const char_type *s2, size_t n) {
    if (n == 0)
      return s1;
    return static_cast<char_type *>(memcpy(s1, s2, n * sizeof(char_type)));
  }
  static char_type *assign(char_type *s, size_t n, char_type a) {
    for (size_t i = 0; i < n; ++i)
      assign(s[i], a);
    return s;
  }
  static constexpr int_type not_eof(int_type c) noexcept {
    return eq_int_type(c, eof()) ? ~eof() : c;
  }
  static constexpr char_type to_char_type(int_type c) noexcept {
    return static_cast<char_type>(c);
  }
  static constexpr int_type to_int_type(char_type c) noexcept {
    return static_cast<int_type>(c);
  }
  static constexpr bool eq_int_type(int_type c1, int_type c2) noexcept {
    return c1 == c2;
  }
  static constexpr int_type eof() noexcept {
    return static_cast<int_type>(-1); // Or ULONG_MAX or similar
  }
};
} // namespace std
#endif // CHAR_TRAITS_FIX_H
