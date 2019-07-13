//
//  more.c
//  UnixInAction
//
//  Created by Arnold on 2019/7/13.
//  Copyright © 2019 Arnold. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
# define PAGELEN 24
# define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);

int main(int ac, const char * av[]) {
    FILE * fp;
    if(ac == 1)
        do_more(stdin);
    else
        while(--ac)
        if((fp = fopen(* ++av, "r")) != NULL)
        {
            do_more(fp);
            fclose(fp);
        }
        else
            exit(1);
    return 0;
}

void do_more(FILE * fp){
    char line[LINELEN];
    int num_of_lines = 0;
    int see_more(FILE *), reply;
    FILE * fptty = fopen("/dev/tty", "r");
    while(fgets(line, LINELEN, fp)){
        if(num_of_lines == PAGELEN){
            reply = see_more(fptty);
            if( reply == 0)
                break;
            num_of_lines -= reply;
        }
        if(fputs(line, stdout) == EOF)
            exit(1);
        num_of_lines++;
    }
}

int see_more(FILE *cmd){
    int c;
    struct termios save, current;
    tcgetattr(0, &save);
    current = save;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;
    current.c_cc[VMIN] = 1;
    current.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &current);
    printf("\033[7m more?\033[m");
    while((c=getchar()) != EOF){
        tcsetattr(0, TCSANOW, &save);
        if(c == 'q')
            return 0;
        if(c == ' ')
            return PAGELEN;
        if(c == '\n')
            return 1;
    }
    return 0;
}
