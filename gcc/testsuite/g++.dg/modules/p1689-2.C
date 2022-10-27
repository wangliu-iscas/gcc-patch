// { dg-additional-options -E }
// { dg-additional-options -MT }
// { dg-additional-options p1689-2.json }
// { dg-additional-options -MD }
// { dg-additional-options -fmodules-ts }
// { dg-additional-options -fdep-format=p1689r5 }
// { dg-additional-options -fdep-output=p1689-2.o }
// { dg-additional-options -fdep-file=p1689-2.json }

// Export a module partition that uses modules.

export module foo:part1;

#include <iostream>

// { dg-final { run-check-p1689-valid p1689-2.json p1689-2.exp.json } }
