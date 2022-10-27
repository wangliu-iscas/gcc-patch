// { dg-options "-std=gnu++23" }
// { dg-do run { target c++23 } }

#include <ranges>
#include <algorithm>
#include <utility>
#include <testsuite_hooks.h>
#include <testsuite_iterators.h>

namespace ranges = std::ranges;
namespace views = std::views;

constexpr bool
test01()
{
  int x[] = {1, 2, 3};
  int y[] = {4, 5, 6};
  int z[] = {7, 8};
  int w[] = {9};

  auto v0 = views::cartesian_product();
  VERIFY( ranges::end(v0) - ranges::begin(v0) == 0 );
  VERIFY( ranges::size(v0) == 0 );
  VERIFY( ranges::empty(v0) );

  auto v1 = views::cartesian_product(x);
  VERIFY( ranges::end(v1) - ranges::begin(v1) == 3 );
  VERIFY( ranges::size(v1) == 3 );
  VERIFY( ranges::equal(v1 | views::keys, x) );
  VERIFY( std::get<0>(v1[0]) == 1 );
  VERIFY( std::get<0>(v1[1]) == 2 );
  VERIFY( std::get<0>(v1[2]) == 3 );
  VERIFY( ranges::equal(v1 | views::reverse | views::keys, x | views::reverse));

  auto v2 = views::cartesian_product(x, y);
  VERIFY( ranges::size(v2) == 9 );
  VERIFY( ranges::end(v2) - ranges::begin(v2) == 9 );
  VERIFY( ranges::equal(v2 | views::keys,   (int[]){1, 1, 1, 2, 2, 2, 3, 3, 3}));
  VERIFY( ranges::equal(v2 | views::values, (int[]){4, 5, 6, 4, 5, 6, 4, 5, 6}));
  VERIFY( ranges::equal(v2 | views::reverse | views::keys,   (int[]){3, 3, 3, 2, 2, 2, 1, 1, 1}) );
  VERIFY( ranges::equal(v2 | views::reverse | views::values, (int[]){6, 5, 4, 6, 5, 4, 6, 5, 4}) );

  auto v3 = views::cartesian_product(x, y, z);
  VERIFY( ranges::size(v3) == 18 );
  VERIFY( ranges::equal(v3, (std::tuple<int,int,int>[]){{1,4,7}, {1,4,8}, {1,5,7}, {1,5,8},
							{1,6,7}, {1,6,8}, {2,4,7}, {2,4,8},
							{2,5,7}, {2,5,8}, {2,6,7}, {2,6,8},
							{3,4,7}, {3,4,8}, {3,5,7}, {3,5,8},
							{3,6,7}, {3,6,8}}) );

  auto v4 = views::cartesian_product(x, y, z, w);
  VERIFY( ranges::size(v4) == 18 );
  VERIFY( ranges::equal(v4 | views::elements<3>, views::repeat(9, 18)) );

  auto i4 = v4.begin(), j4 = i4 + 1;
  VERIFY( j4 > i4 );
  VERIFY( i4[0] == std::tuple(1, 4, 7, 9) );
  VERIFY( i4 + 18 == v4.end() );
  i4 += 5;
  VERIFY( i4 != v4.begin() );
  VERIFY( i4 - 5 == v4.begin() );
  VERIFY( *i4 == std::tuple(1, 6, 8, 9) );
  VERIFY( i4 - 5 != i4 );
  i4 -= 3;
  VERIFY( *i4 == std::tuple(1, 5, 7, 9) );
  VERIFY( j4 + 1 == i4 );
  ranges::iter_swap(i4, j4);
  VERIFY( *j4 == std::tuple(1, 5, 7, 9) );
  VERIFY( *i4 == std::tuple(1, 4, 8, 9) );

  return true;
}

void
test02()
{
  int x[] = {1, 2};
  __gnu_test::test_input_range<int> rx(x);
  auto v = views::cartesian_product(rx, x);
  auto i = v.begin();
  std::default_sentinel_t s = v.end();
  VERIFY( i != s );
  VERIFY( std::get<0>(*i) == 1 && std::get<1>(*i) == 1 );
  ++i;
  VERIFY( i != s );
  VERIFY( std::get<0>(*i) == 1 && std::get<1>(*i) == 2 );
  ++i;
  VERIFY( i != s );
  VERIFY( std::get<0>(*i) == 2 && std::get<1>(*i) == 1 );
  ++i;
  VERIFY( i != s );
  VERIFY( std::get<0>(*i) == 2 && std::get<1>(*i) == 2 );
  ++i;
  VERIFY( i == s );
}

void
test03()
{
  int x[] = {1, 2};
  __gnu_test::test_input_range<int> rx(x);
  auto v = views::cartesian_product(views::counted(rx.begin(), 2), x);
  VERIFY( v.size() == 4 );
  VERIFY( std::as_const(v).size() == 4 );
  auto i = v.begin();
  std::default_sentinel_t s = v.end();
  VERIFY( i - s == -4 );
  VERIFY( s - i == 4 );
  ++i;
  VERIFY( i - s == -3 );
  VERIFY( s - i == 3 );
  ++i;
  VERIFY( i - s == -2 );
  VERIFY( s - i == 2 );
  ++i;
  VERIFY( i - s == -1 );
  VERIFY( s - i == 1 );
  ++i;
  VERIFY( i - s == 0 );
  VERIFY( s - i == 0 );
}

void
test04()
{
  // Exhaustively verify correctness of our iterator addition implementation
  // (which runs in constant time) for this 18-element cartesian_product_view.
  int x[] = {1, 2, 3};
  int y[] = {4, 5, 6};
  int z[] = {7, 8};
  int w[] = {9};
  auto v = views::cartesian_product(x, y, z, w);

  for (int i = 0; i <= ranges::ssize(v); i++)
    for (int j = 0; i + j <= ranges::ssize(v); j++)
      {
	auto b1 = v.begin();
	for (int k = 0; k < i + j; k++)
	  ++b1;
	VERIFY( b1 - v.begin() == i + j );
	auto b2 = (v.begin() + i) + j;
	auto b3 = v.begin() + (i + j);
	VERIFY( b1 == b2 && b2 == b3 );

	auto e1 = v.end();
	for (int k = 0; k < i + j; k++)
	  --e1;
	VERIFY( v.end() - e1 == i + j );
	auto e2 = (v.end() - i) - j;
	auto e3 = v.end() - (i + j);
	VERIFY( e1 == e2 && e2 == e3 );
      }
}

int
main()
{
  static_assert(test01());
  test02();
  test03();
  test04();
}
