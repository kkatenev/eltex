#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "lib.c"

int main()
{
    srand(time(NULL));
    pthread_t buyer[3];
    pthread_t loader;
    store_start(store);
    buyer_buy(buyer);
    loader_load(loader);
    threads_join(buyer, loader);
    return 0;
}