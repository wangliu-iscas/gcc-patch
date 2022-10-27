// { dg-additional-options -E }
// { dg-additional-options -MT }
// { dg-additional-options p1689-3.json }
// { dg-additional-options -MD }
// { dg-additional-options -fmodules-ts }
// { dg-additional-options -fdep-format=p1689r5 }
// { dg-additional-options -fdep-output=p1689-3.o }
// { dg-additional-options -fdep-file=p1689-3.json }

// Provide a module partition.

module foo:part2;

// { dg-final { run-check-p1689-valid p1689-3.json p1689-3.exp.json } }
