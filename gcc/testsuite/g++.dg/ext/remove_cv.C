// { dg-do compile { target c++11 } }

#define SA(X) static_assert((X),#X)

SA(__is_same(__remove_cv(void), void));
SA(__is_same(__remove_cv(int*), int*));

SA(__is_same(__remove_cv(int&), int&));
SA(__is_same(__remove_cv(const int&), const int&));
SA(__is_same(__remove_cv(volatile int&), volatile int&));
SA(__is_same(__remove_cv(const volatile int&), const volatile int&));

SA(__is_same(__remove_cv(int&&), int&&));
SA(__is_same(__remove_cv(const int&&), const int&&));
SA(__is_same(__remove_cv(volatile int&&), volatile int&&));
SA(__is_same(__remove_cv(const volatile int&&), const volatile int&&));

SA(__is_same(__remove_cv(int[3]), int[3]));
SA(__is_same(__remove_cv(const int[3]), int[3]));
SA(__is_same(__remove_cv(volatile int[3]), int[3]));
SA(__is_same(__remove_cv(const volatile int[3]), int[3]));

SA(__is_same(__remove_cv(int(int)), int(int)));
SA(__is_same(__remove_cv(int(*const)(int)), int(*)(int)));
SA(__is_same(__remove_cv(int(*volatile)(int)), int(*)(int)));
SA(__is_same(__remove_cv(int(*const volatile)(int)), int(*)(int)));
