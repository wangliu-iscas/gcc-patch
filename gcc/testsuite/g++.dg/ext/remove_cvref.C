// { dg-do compile { target c++11 } }

#define SA(X) static_assert((X),#X)

SA(__is_same(__remove_cvref(void), void));
SA(__is_same(__remove_cvref(int*), int*));

SA(__is_same(__remove_cvref(int&), int));
SA(__is_same(__remove_cvref(const int&), int));
SA(__is_same(__remove_cvref(volatile int&), int));
SA(__is_same(__remove_cvref(const volatile int&), int));

SA(__is_same(__remove_cvref(int&&), int));
SA(__is_same(__remove_cvref(const int&&), int));
SA(__is_same(__remove_cvref(volatile int&&), int));
SA(__is_same(__remove_cvref(const volatile int&&), int));

SA(__is_same(__remove_cvref(int[3]), int[3]));
SA(__is_same(__remove_cvref(const int[3]), int[3]));
SA(__is_same(__remove_cvref(volatile int[3]), int[3]));
SA(__is_same(__remove_cvref(const volatile int[3]), int[3]));

SA(__is_same(__remove_cvref(int(int)), int(int)));
SA(__is_same(__remove_cvref(int(*const)(int)), int(*)(int)));
SA(__is_same(__remove_cvref(int(*volatile)(int)), int(*)(int)));
SA(__is_same(__remove_cvref(int(*const volatile)(int)), int(*)(int)));
