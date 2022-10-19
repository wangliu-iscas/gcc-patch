/* Make sure that post-ipa-free-lang-data diagnostics expand macros as
   expected.  */

/* { dg-do compile } */
/* { dg-require-effective-target lto } */
/* { dg-options "-flto -O2 -Wnonnull-compare" } */

#define X(p) p == 0 /* { dg-warning {-Wnonnull-compare} } */
int f (void *) __attribute__((nonnull));
int f (void *p)
{
  return X (p); /* { dg-note {in expansion of macro 'X'} } */
}

#define X2(p) p == 0 /* { dg-warning {-Wnonnull-compare} } */
#define Y2(p) X2(p) /* { dg-note {in expansion of macro 'X2'} } */

#define MAKE_F2 \
  int f2 (void *) __attribute__((nonnull)); \
  int f2 (void *p) \
  { \
    return Y2 (p); /* { dg-note {in expansion of macro 'Y2'} } */ \
  }

MAKE_F2 /* { dg-note {in expansion of macro 'MAKE_F2'} } */
