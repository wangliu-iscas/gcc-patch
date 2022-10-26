/* Test constants which can be built by li/lis + oris/xoris */
void  __attribute__ ((__noinline__, __noclone__)) foo (long long *arg)
{
  *arg++ = 0x98765432ULL;
  *arg++ = 0xffffffff7cdeab55ULL;
  *arg++ = 0xffffffff65430000ULL;
}


