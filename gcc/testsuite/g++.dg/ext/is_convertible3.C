// PR c++/106784
// { dg-do compile { target c++11 } }
// Make sure we don't reject this at runtime by trying to instantiate
// char_traits<CharT>::eq(CharT, CharT) while evaluating __is_convertible.

template<bool B>
struct bool_constant { static constexpr bool value = B; };
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template<typename T> struct is_void : false_type { };
template<> struct is_void<void> : true_type { };

template<typename T> T&& declval();

template<bool> struct enable_if { };
template<> struct enable_if<true> { using type = void; };
template<bool B> using enable_if_t = typename enable_if<B>::type;

template<typename _From, typename _To>
  struct is_convertible
  : public bool_constant<__is_convertible(_From, _To)>
  { };

template<class CharT>
struct char_traits
{
  static unsigned long length(const char* s) { eq(*s, *s); return 0; }

  static void eq(CharT l, CharT r) noexcept { l.f(r); }
};

template<class CharT>
struct basic_string_view
{
  using traits_type = char_traits<CharT>;

  constexpr basic_string_view() = default;
  constexpr basic_string_view(const basic_string_view&) = default;

  constexpr
  basic_string_view(const CharT* __str) noexcept
  : _M_len{traits_type::length(__str)}
  { }

  unsigned long _M_len = 0;
};

template<class CharT>
struct basic_string
{
  template<class T>
    enable_if_t<is_convertible<const T&, basic_string_view<CharT>>::value
                && !is_convertible<const T&, const char*>::value>
    replace(int, T) { }

  void replace(unsigned long, const char*) { }

  void replace(const char* s) { replace(1, s); }
};

int main()
{
  basic_string<char> s;
  s.replace("");
}
