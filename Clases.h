#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED
#include "linuxLibGame.h"
int golesA=0, golesB=0; //Declaro las variables globales para indicar los goles recibidos por cada jugador

class Jugador
{
private:
    int x,y,GolesRecibidos=0; //Coordenadas que tendra el jugador;
public:
    Jugador(int _x, int _y); //Constructor
    void Pintar(); //Esta funcion pintara una barra que representara al jugador. Utilizara 6 posiciones de caracteres
    void Borrar();
    void set_y(int _x);
    int get_x();
    int get_y();
};


Jugador::Jugador(int _x, int _y)
{
    x = _x;
    y = _y;
}

int Jugador::get_x()  //Obtiene la coordenada X actual del jugador
{
    return x;
}

int Jugador::get_y()  //Obtiene la coordenada Y actual del jugador
{
    return y;
}

void Jugador::set_y(int _y)  //Cambia el valor de la coordenada del jugador
{
    y+=_y;
}
void Jugador::Pintar()
{
    gotoxy(x, y-2);
    printf("%c",219);
    gotoxy(x, y-1);
    printf("%c",219); //219 en el codigo ASCII es una barrita que representara al jugador
    gotoxy(x, y);
    printf("%c",219);
    gotoxy(x, y+1);
    printf("%c",219);
    gotoxy(x, y+2);
    printf("%c",219);
    gotoxy(x, y+3);
    printf("%c",219);

}

void Jugador::Borrar()
{
    gotoxy(x, y-2);
    printf(" ");
    gotoxy(x, y-1);
    printf(" ");
    gotoxy(x, y);
    printf(" ");
    gotoxy(x, y+1);
    printf(" ");
    gotoxy(x, y+2);
    printf(" ");
    gotoxy(x, y+3);
    printf(" ");
}

class Pelota
{
public:
    int x,y;
    int dx,dy;
public:
    Pelota(int _x, int _y, int _dx, int _dy);
    void Pintar();
    void Borrar();
    void Mover(Jugador A, Jugador B);
    void Gol(int _x, int _y);
    void ImprimeMarcador(int a, int b);
    int get_dx();
    int get_dy();
    void restaxy();
};
int Pelota::get_dx()
{
    return dx;
}

int Pelota::get_dy()
{
    return dy;
}

void Pelota::restaxy()
{
    Borrar();
    if(dx>0 && dy>0)
    {
        x=x-1;
        y=y-1;
    }
    if(dx<0 && dy<0)
    {
        x=x+1;
        y=y+1;
    }
    if(dx>0 && dy<0)
    {
        x=x-1;
        y=y+1;
    }
    if(dx<0 && dy>0)
    {
        x=x+1;
        y=y-1;
    }
    Pintar();

}

Pelota::Pelota(int _x, int _y, int _dx, int _dy)
{
    x=_x;
    y=_y;
    dx=_dx;

    dy=_dy;
}
void Pelota::Pintar()
{
    gotoxy(x,y);
    printf("%c",254);
}

void Pelota::Borrar()
{
    gotoxy(x,y);
    printf(" ");
}


void Pelota::ImprimeMarcador(int a, int b)
{
    gotoxy(0,0);
    printf("Jugador 1:  %d",b);
    printf("\t\t\t");
    printf("Jugador 2:  %d",a);
    printf("\n");

}

void Pelota::Mover(Jugador A, Jugador B)
{
    Borrar();
    x+= dx;
    y+= dy;
    Pintar();

    if(x+dx == 3)  //En caso de colisionar con el borde izquierdo
    {
        Borrar();
        Gol(38,14); //Significa que hubo un gol, por lo que vuelve al principio
        golesB++;
        dx=-dx; //Cambiar el sentido de la pelota hacia el que hizo el punto
    }
    if(x+dx==81)  //En caso de colisionar con el borde izquierdo
    {
        Borrar();
        Gol(38,14); //Significa que hubo un gol, por lo que vuelve al principio
        golesA++;
        dx=-dx; //Cambiar el sentido de la pelota hacia el que hizo el punto
    }
    ImprimeMarcador(golesB, golesA);
    if(y+dy == 3 || y+dy==27) //En caso de colisionar con los bordes en el eje x
        dy=-dy; //cambiar el sentido de la pelota

    if(x+dx == A.get_x() && y>=A.get_y()-2 && y<=A.get_y()+3)
        dx=-dx;
    if(x+dx == B.get_x() && y>=B.get_y()-2 && y<=B.get_y()+3)
        dx=-dx;
}


void Pelota::Gol(int _x, int _y)
{
    x=_x;
    y=_y;
}

class Menu
{
public:
    void ImprimePortada(int &a);
};
void Menu::ImprimePortada(int &a)
{
    char portada[18][71] =
    {
        "                                                                      ",
        "   aaaass                                                             ",
        "   aa  aas                             PROYECTO FINAL DE SEMESTRE     ",
        "   aaaass  aaa   aa   aa aaaas         Integrantes:                   ",
        "   aa    ss   ss aas  aa aa                       -Marcelo Araya      ",
        "   aa    ss   ss aa a aa aa  aa                   -Francisco Ibacache ",
        "   aa      aaa   aa  aas aaaasa                   -Julio Nain        ",
        "                                                                      ",
        "                                                                      ",
        "     aaaas  aaaas     aaaas                                           ",
        "   aa       aa   ss   aa   ss                                         ",
        "   aa       aa    ss  aa    ss         Esperando Conexion...          ",
        "   aa       aa    ss  aa    ss                                        ",
        "   aa       aa    ss  aa    ss                                        ",
        "     aaass  aaaas     aaaas                                           ",
        "                                                                      ",

    };
    for(int i=0; i <16; i++)
    {
        for(int j=0; j<70; j++)
        {
            gotoxy(j+5,i+5);
            printf("%c", portada[i][j]);
        }
    }

//Acá hay que invocar el socket en algun momento de la vidita :(


}

#endif // CLASES_H_INCLUDED
