// PR c++/106393
// { dg-do compile { target c++11 } }
// { dg-options "-Wdangling-reference" }

const int& f(const int& i) { return i; }
const int& h(int);
int g;
const int& globref(const int&) { return g; }
struct X {
  int* i;
  operator const int&() const { return *i; }
};
X x{&g};

const int& r1 = f(10); // { dg-warning "dangling reference" }
// r2 = _ZGR2r2_ = (int) *f ((const int &) &TARGET_EXPR <D.2429, 10>) + 1; (const int &) &_ZGR2r2_
const int& r2 = f(10) + 1;
// Don't warn here, we have
//   r3 = f (X::operator const int& (&x))
const int& r3 = f(x);
// Don't warn here, because we've seen the definition of globref
// and could figure out that it may not return one of its parms.
// Questionable -- it can also hide bugs --, but it helps here.
const int& r4 = globref(1);
const int& r5 = (42, f(10)); // { dg-warning "dangling reference" }
const int& r6 = (f(10), 42);
const int& r7 = (f(10)); // { dg-warning "dangling reference" }
const int& r8 = g ? f(10) : f(9); // { dg-warning "dangling reference" }
const int& r9 = (42, g ? f(10) : f(9)); // { dg-warning "dangling reference" }
const int& r10 = (g ? f(10) : f(9), 42);
// Binds to a reference temporary for r11.
const int& r11 = g ? f(10) : 9;
// Invalid, but we don't warn here yet.
// r12 = f (f ((const int &) &TARGET_EXPR <D.2459, 1>))
const int& r12 = f(f(1));
const int& r13 = h(f(1));
// Other forms of initializers.
const int& r14(f(10)); // { dg-warning "dangling reference" }
const int& r15(f(10)); // { dg-warning "dangling reference" }
// Returns a ref, but doesn't have a parameter of reference type.
const int& r16 = h(10);

// OK: the reference is bound to the 10 so still valid at the point
// where it's copied into i1.
int i1 = f(10);

int
test1 ()
{
  const int &lr = f(10); // { dg-warning "dangling reference" }
  int i2 = f(10);
  return lr;
}

struct B { };
struct D : B { };
struct C {
  D d;
};

C c;
D d;

using U = D[3];

const B& frotz(const D&);
const B& b1 = frotz(C{}.d); // { dg-warning "dangling reference" }
const B& b2 = frotz(D{}); // { dg-warning "dangling reference" }
const B& b3 = frotz(c.d);
const B& b4 = frotz(d);
const B& b5 = frotz(U{}[0]); // { dg-warning "dangling reference" }

struct E {
  E(int);
};
const E& operator*(const E&);
const E& b6 = *E(1);

struct S {
  const int &r; // { dg-warning "dangling reference" }
  S() : r(f(10)) { } // { dg-message "destroyed" }
};

// From cppreference.
template<class T>
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

int n = 1;
const int& r20 = max(n - 1, n + 1); // { dg-warning "dangling reference" }

// Don't warn about member functions.
struct Y {
  operator int&&();
  const int& foo(const int&);
};

// x1 = Y::operator int&& (&TARGET_EXPR <D.2410, {}>)
int&& x1 = Y();
int&& x2 = Y{};
const int& t1 = Y().foo(10);
