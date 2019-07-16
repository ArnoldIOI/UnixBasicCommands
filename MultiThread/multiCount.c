//
//  mutiCounter.c
//  UnixInAction
//
//  Created by Arnold on 2019/7/16.
//  Copyright © 2019 Arnold. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int wordsInToall;

void * counter(void *f);
int main(int ac, char* av[])
{
    if(ac != 3)
    {
        printf("usage: %s file1 file2\n", av[0]);
        exit(1);
    }
    wordsInToall = 0;
    pthread_t t1, t2;
    pthread_create(&t1, NULL, counter, (void*)av[1]);
    pthread_create(&t2, NULL, counter, (void*)av[2]);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Total Words: %d\n", wordsInToall);
}

void *counter(void* f)
{
    char *filename = (char *)f;
    FILE* fp;
    
    if((fp = fopen(filename, "r")) != NULL)
    {
        while(getc(fp) != EOF)
            wordsInToall++;
        fclose(fp);
    }
    else
        perror(filename);
    return NULL;
}
