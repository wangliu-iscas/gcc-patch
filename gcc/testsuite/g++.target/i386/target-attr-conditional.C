/* { dg-do compile } */
/* { dg-options "-Wno-psabi -m32 -march=i386 -std=c++20" } */

#pragma GCC push_options
#pragma GCC target("sse")

typedef int __m64 __attribute__ ((__vector_size__ (8), __may_alias__));
typedef short __v4hi __attribute__ ((__vector_size__ (8)));

extern __inline int __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_extract_pi16 (__m64 const __A, int const __N)
{
  return (unsigned short) __builtin_ia32_vec_ext_v4hi ((__v4hi)__A, __N);
}

#pragma GCC pop_options

consteval const char*
target_string (bool enable_sse)
{
  return enable_sse ? "sse" : "";
}

// Via consteval function
template<bool enable_sse>
[[gnu::target (target_string (enable_sse))]]
int
extract1 (__m64 const src)
{
  if constexpr (enable_sse)
    return _mm_extract_pi16 (src, 0);
  else
    return reinterpret_cast<__v4hi>(src)[1];
}

// Via ternary operator
template<bool enable_sse>
[[gnu::target (enable_sse ? "sse" : "")]]
int
extract2 (__m64 const src)
{
  if constexpr (enable_sse)
    return _mm_extract_pi16 (src, 2);
  else
    return reinterpret_cast<__v4hi>(src)[3];
}

int
test (__m64 const src)
{
  return extract1<true>(src) + extract1<false>(src)
       + extract2<true>(src) + extract2<false>(src);
}
