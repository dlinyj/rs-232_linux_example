/* draw.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>     /* memset() */

#define N_ROWS  15      /* Image height */
#define N_COLS  40      /* Image width */
#define FG_CHAR 'O'     /* Foreground character */
#define IMG_FN  "image" /* Image filename */

#define N_MIN(A,B) ((A)<(B)?(A):(B))
#define N_MAX(A,B) ((A)>(B)?(A):(B))

static char buffer[N_COLS];

void init_draw (int fd)
{       
        ssize_t bytes_written = 0;
        memset (buffer, ' ', N_COLS);
        buffer [N_COLS] = '\n';
        while (bytes_written < (N_ROWS * (N_COLS+1)))
                bytes_written += write (fd, buffer, N_COLS+1);
}

void draw_point (int fd, int x, int y)
{
        char ch = FG_CHAR;
        lseek (fd, y * (N_COLS+1) + x, SEEK_SET);
        write (fd, &ch, 1);
}

void draw_hline (int fd, int y, int x1, int x2)
{       
        size_t bytes_write = abs (x2-x1) + 1;
        memset (buffer, FG_CHAR, bytes_write);
        lseek (fd, y * (N_COLS+1) + N_MIN (x1, x2), SEEK_SET);
        write (fd, buffer, bytes_write);
}

void draw_vline (int fd, int x, int y1, int y2)
{
        int i = N_MIN(y1, y2);
        while (i <= N_MAX(y2, y1)) draw_point (fd, x, i++);
}

int main (void)
{
        int a, b, c, i = 0;
        char ch;
        int fd = open (IMG_FN, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
                fprintf (stderr, "Cannot open file\n");
                exit (1);
        }

        init_draw (fd);
        char * icode[] = { "v 1 1 11", "v 11 7 11", "v 14 5 11", 
        "v 18 6 11", "v 21 5 10", "v 25 5 10", "v 29 5 6", "v 33 5 6", 
        "v 29 10 11", "v 33 10 11", "h 11 1 8", "h 5 16 17", 
        "h 11 22 24", "p 11 5 0", "p 15 6 0", "p 26 11 0", "p 30 7 0", 
        "p 32 7 0", "p 31 8 0", "p 30 9 0", "p 32 9 0", NULL }; 

        while (icode[i] != NULL) {
        sscanf (icode[i], "%c %d %d %d", &ch, &a, &b, &c);
                switch (ch) {
                        case 'v': draw_vline (fd, a, b, c); break;
                        case 'h': draw_hline (fd, a, b, c); break;
                        case 'p': draw_point (fd, a, b); break;
                        default: abort();       
                }
                i++;
        }
        close (fd);
        exit (0);
}

