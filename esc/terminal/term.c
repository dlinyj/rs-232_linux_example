#include <stdio.h>
#include "term.h"

/*ANSI/VT100 Terminal using example */


#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
/* 
Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
*/
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) 	printf(ESC "[%dm",color)



int main (void) {
	home();
	clrscr();
	printf("Home + clrscr\n");
	gotoxy(20,7);
	printf("gotoxy(20,7)");
	
	gotoxy(1,10);
	printf("gotoxy(1,10)  \n\n");
	
	set_display_atrib(BRIGHT);
	printf("Formatting text:\n");
	resetcolor();
	
	set_display_atrib(BRIGHT);
	printf("Bold\n");
	resetcolor();
	
	set_display_atrib(DIM);
	printf("Dim\n");
	resetcolor();

	set_display_atrib(BLINK);
	printf("Blink\n");
	resetcolor();

	set_display_atrib(REVERSE);
	printf("Reverse\n");
	printf("\n");
	

	set_display_atrib(BRIGHT);
	printf("Text color example:\n");
	resetcolor();

	
	set_display_atrib(F_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(F_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(F_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(F_CYAN);
	printf("Cyan\n");
	resetcolor();

	set_display_atrib(BRIGHT);
	printf("\nBottom color example:\n");
	resetcolor();	
	
	set_display_atrib(B_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(B_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(B_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(B_CYAN);
	printf("Cyan\n");
	printf("\n");
	resetcolor();
	return 0;
}

/*
 man console_codes
 
ESC- but not CSI-sequences

       ESC c     RIS      Reset.
       ESC D     IND      Linefeed.
       ESC E     NEL      Newline.
       ESC H     HTS      Set tab stop at current column.
       ESC M     RI       Reverse linefeed.
       ESC Z     DECID    DEC private identification. The kernel returns the
                          string  ESC [ ? 6 c, claiming that it is a VT102.
       ESC 7     DECSC    Save   current    state    (cursor    coordinates,
                          attributes, character sets pointed at by G0, G1).
       ESC 8     DECRC    Restore state most recently saved by ESC 7.
       ESC [     CSI      Control sequence introducer
       ESC %              Start sequence selecting character set
       ESC % @               Select default (ISO 646 / ISO 8859-1)
       ESC % G               Select UTF-8
       ESC % 8               Select UTF-8 (obsolete)
       ESC # 8   DECALN   DEC screen alignment test - fill screen with E's.
       ESC (              Start sequence defining G0 character set
       ESC ( B               Select default (ISO 8859-1 mapping)
       ESC ( 0               Select VT100 graphics mapping
       ESC ( U               Select null mapping - straight to character ROM
       ESC ( K               Select user mapping - the map that is loaded by
                             the utility mapscrn(8).
       ESC )              Start sequence defining G1
                          (followed by one of B, 0, U, K, as above).
       ESC >     DECPNM   Set numeric keypad mode
       ESC =     DECPAM   Set application keypad mode
       ESC ]     OSC      (Should  be:  Operating  system  command)  ESC ] P
                          nrrggbb: set palette, with parameter  given  in  7
                          hexadecimal  digits after the final P :-(.  Here n
                          is the color  (0-15),  and  rrggbb  indicates  the
                          red/green/blue  values  (0-255).   ESC  ] R: reset
                          palette

 The action of a CSI sequence is determined by its final character.

       @   ICH       Insert the indicated # of blank characters.
       A   CUU       Move cursor up the indicated # of rows.
       B   CUD       Move cursor down the indicated # of rows.
       C   CUF       Move cursor right the indicated # of columns.
       D   CUB       Move cursor left the indicated # of columns.
       E   CNL       Move cursor down the indicated # of rows, to column 1.
       F   CPL       Move cursor up the indicated # of rows, to column 1.
       G   CHA       Move cursor to indicated column in current row.
       H   CUP       Move cursor to the indicated row, column (origin at 1,1).
       J   ED        Erase display (default: from cursor to end of display).
                     ESC [ 1 J: erase from start to cursor.
                     ESC [ 2 J: erase whole display.
                     ESC [ 3 J: erase whole display including scroll-back
                                buffer (since Linux 3.0).
       K   EL        Erase line (default: from cursor to end of line).
                     ESC [ 1 K: erase from start of line to cursor.
                     ESC [ 2 K: erase whole line.
       L   IL        Insert the indicated # of blank lines.
       M   DL        Delete the indicated # of lines.
       P   DCH       Delete the indicated # of characters on current line.
       X   ECH       Erase the indicated # of characters on current line.
       a   HPR       Move cursor right the indicated # of columns.
       c   DA        Answer ESC [ ? 6 c: "I am a VT102".
       d   VPA       Move cursor to the indicated row, current column.
       e   VPR       Move cursor down the indicated # of rows.
       f   HVP       Move cursor to the indicated row, column.
       g   TBC       Without parameter: clear tab stop at current position.
                     ESC [ 3 g: delete all tab stops.
       h   SM        Set Mode (see below).
       l   RM        Reset Mode (see below).
       m   SGR       Set attributes (see below).
       n   DSR       Status report (see below).
       q   DECLL     Set keyboard LEDs.
                     ESC [ 0 q: clear all LEDs
                     ESC [ 1 q: set Scroll Lock LED
                     ESC [ 2 q: set Num Lock LED
                     ESC [ 3 q: set Caps Lock LED
       r   DECSTBM   Set scrolling region; parameters are top and bottom row.
       s   ?         Save cursor location.
       u   ?         Restore cursor location.
       `   HPA       Move cursor to indicated column in current row.

 */
