// Test pthread_cond_clockwait not generating false positives with tsan
// { dg-do run { target { { *-*-linux* *-*-gnu* *-*-uclinux* } && pthread } } }
// { dg-options "-fsanitize=thread -lpthread" }

#include <pthread.h>

// Include this to get the libstdc++ _GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT
// macro that indicates pthread_cond_clockwait is available.
#include <type_traits>

pthread_cond_t cv;
pthread_mutex_t mtx;

void *fn(void *vp) {
    pthread_mutex_lock(&mtx);
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main() {
    pthread_mutex_lock(&mtx);

    pthread_t tid;
    pthread_create(&tid, NULL, fn, NULL);

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    ts.tv_sec += 10;
#ifdef _GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT
    pthread_cond_clockwait(&cv, &mtx, CLOCK_MONOTONIC, &ts);
#endif
    pthread_mutex_unlock(&mtx);

    pthread_join(tid, NULL);
    return 0;
}
