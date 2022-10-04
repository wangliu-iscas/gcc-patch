// PR c++/99377
// { dg-additional-options -fmodules-ts }
// { dg-do link }
import pr99377;
template<class> void g() { f(); }
int main() { g<int>(); }
