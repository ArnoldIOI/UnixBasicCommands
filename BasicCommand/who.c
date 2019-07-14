//
//  who.c
//  UnixInAction
//
//  Created by Arnold on 2019/7/14.
//  Copyright © 2019 Arnold. All rights reserved.
//

#include <stdio.h>
#include <utmpx.h>
#include <stdlib.h>
#include <time.h>

void show_info(struct utmpx *utbufp);

int main(void)
{
    struct utmpx *current_record;
    
    while((current_record = getutxent()) != NULL)
        if((*current_record).ut_type == 7)
            show_info(current_record);
    return 0;
}

void show_info(struct utmpx *utbufp)
{
    printf("%-8.8s", utbufp->ut_user);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    printf("%10s", ctime(&utbufp->ut_tv.tv_sec));
    printf("\n");
}

