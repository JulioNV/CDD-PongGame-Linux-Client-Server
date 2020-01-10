#include "linuxLibGame.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void gotoxy(int x,int y){
printf("%c[%d;%df",0x1B,y,x);
}

void OcultaCursor() {
    printf("\e[?25l");
}

void pintar_marco()       // funcion que pinta los limites del escenario
{
     // Lineas horizontals
     for(int i=2; i < 82; i++){
        gotoxy (i, 3); printf ("%c", 205);
        gotoxy(i, 27); printf ("%c", 205);
     }
     //Lineas verticales
     for(int v=4; v < 27; v++){
        gotoxy (2,v);  printf ("%c", 186);
        gotoxy(82,v);  printf ("%c", 186);
     }
     // Esquinas
     gotoxy  (2,3);    printf ("%c", 201);
     gotoxy (2,27);    printf ("%c", 200);
     gotoxy (82,3);    printf ("%c", 187);
     gotoxy(82,27);    printf ("%c", 188);
}

void limpiar(){

 for(int i=0; i <16; i++){
        for(int j=0; j<70; j++){
            gotoxy(j+5,i+5);
            printf(" ");
        }
    }
}

/**------ getch()-------------*/
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/* getch() hecho por mi*/
char getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    char c=ch;
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return c;
}
/**------ getch()-------------*/

/**------ khbit-------------*/
bool kbhit(){
termios term;
tcgetattr(0,&term);
termios term2=term;
term2.c_lflag &=~ICANON;
tcsetattr(0,TCSANOW,&term2);
int byteswaiting;
ioctl(0,FIONREAD,&byteswaiting);
tcsetattr(0,TCSANOW,&term);
return byteswaiting>0;

}
/**------ khbit-------------*/

void pausa(int x){
    usleep(x);

}

/**------------ITOA----------*/
/*const char *my_itoa_buf(char *buf, size_t len, int num)
{
  static char loc_buf[sizeof(int) * CHAR_BITS];
  if (!buf)
  {
    buf = loc_buf;
    len = sizeof(loc_buf);
  }

  if (snprintf(buf, len, "%d", num) == -1)
    return "";

  return buf;
}*/


/**------------ITOA----------*/

