/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-dse1-details" } */
typedef float real_t;

#define iterations 100000
#define LEN_1D 32000
#define LEN_2D 256
real_t flat_2d_array[LEN_2D*LEN_2D];

real_t x[LEN_1D];

real_t a[LEN_1D],b[LEN_1D],c[LEN_1D],d[LEN_1D],e[LEN_1D],
bb[LEN_2D][LEN_2D],cc[LEN_2D][LEN_2D],tt[LEN_2D][LEN_2D];

int indx[LEN_1D];

real_t* __restrict__ xx;
real_t* yy;
real_t s243(void)
{
  for (int nl = 0; nl < iterations; nl++) {
    for (int i = 0; i < LEN_1D-1; i++) {
        a[i] = b[i] + c[i  ] * d[i];
        b[i] = a[i] + d[i  ] * e[i];
        a[i] = b[i] + a[i+1] * d[i];
    }
  }
}

/* { dg-final { scan-tree-dump "Deleted dead store" "dse1" } } */