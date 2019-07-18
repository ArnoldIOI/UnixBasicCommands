//
//  mutiCounter2.c
//  UnixInAction
//
//  Created by Arnold on 2019/7/18.
//  Copyright © 2019 Arnold. All rights reserved.
//
//  Calculate the total number of characters in two files in parallel.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * counter(void *a);
struct arg_set{
    char* f;
    int words;
};

int main(int ac, char* av[])
{
    struct arg_set args1, args2;
    if(ac != 3)
    {
        printf("usage: %s file1 file2\n", av[0]);
        exit(1);
    }
    pthread_t t1, t2;
    args1.f = av[1];
    args1.words = 0;
    pthread_create(&t1, NULL, counter, (void*) &args1);
    args2.f = av[2];
    args2.words = 0;
    pthread_create(&t2, NULL, counter, (void*) &args2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Total Words: %d\n", args1.words + args2.words);
}

void *counter(void* a)
{
    struct arg_set  * args = a;
    FILE* fp;
    
    if((fp = fopen(args->f, "r")) != NULL)
    {
        while(getc(fp) != EOF)
            args->words++;
        fclose(fp);
    }
    else
        perror(args->f);
    return NULL;
}
