#include <stdio.h>
#include "Clases.h"
#include "linuxLibGame.h"
#include <iostream>
#include "cliente.h"
#include <thread>

using namespace std;

char numero_jugador[32];
conexion cliente;
Menu M;
Jugador A(7,15);
Jugador B(77,15);
Pelota P(42,14,1,1);
char tecla;
int contador=0, abre_juego;



void manda()
{
    while(golesA<3 && golesB<3)
    {
        if(kbhit())  //Detecta si se apreta una tecla y posteriormente se guarda en tecla con getch
        {
            A.Borrar();
            B.Borrar();
            tecla=getch();

            if(strcmp(numero_jugador,"1")==0)
            {
                //   tecla2=getch(); Esta tecla se usara en el futuro para recibir los datos del jugador 2
                if(tecla == 'w' && A.get_y()>6  )   //Controlo los movimientos del jugador A con w y s para arriba y abajo respectivamente
                {
                    send(cliente.sockfd,"w",32,0);

                    A.set_y(-1);
                }
                else if(tecla=='s' && A.get_y()<23 )
                {
                    send(cliente.sockfd,"s",32,0);


                    A.set_y(1);
                }

            }
            if(strcmp(numero_jugador,"2")==0)
            {


                if(tecla== 'o' && B.get_y()>6 )  //Controlo los movimientos del jugador B con O y L para arriba y abajo respectivament e
                {

                    send(cliente.sockfd,"o",32,0);

                    B.set_y(-1);
                }
                else if(tecla=='l' && B.get_y()<23)
                {

                    send(cliente.sockfd,"l",32,0);

                    B.set_y(1);
                }

            }
            A.Pintar();
            B.Pintar();

        }

        P.Mover(A,B);

        /*if(strcmp(numero_jugador,"1")==0 && contador==0){
           pausa(50000);
           contador++;
           }*/
        pausa(50000);
    }

 

}



void lee()
{
    char recibe[32];
    while(golesA<3 && golesB<3)
    {

        if(recv(cliente.sockfd, recibe, LENGTH, 0)>0)  //Detecta si se apreta una tecla y posteriormente se guarda en tecla con getch
        {
            A.Borrar();
            B.Borrar();

            tecla=recibe[0];


            //   tecla2=getch(); Esta tecla se usara en el futuro para recibir los datos del jugador 2
            if(tecla == 'w' && A.get_y()>6 )   //Controlo los movimientos del jugador A con w y s para arriba y abajo respectivamente
            {
                A.set_y(-1);
            }
            else if(tecla=='s' && A.get_y()<23 )
            {
                A.set_y(1);
            }



            if(tecla== 'o' && B.get_y()>6 )  //Controlo los movimientos del jugador B con O y L para arriba y abajo respectivament e
            {
                B.set_y(-1);
            }
            else if(tecla=='l' && B.get_y()<23)
            {
                B.set_y(1);
            }

            A.Pintar();
            B.Pintar();


        }

        P.Mover(A,B);
        P.restaxy();
        pintar_marco();


        pausa(50000);
    }

}



int main()
{
    system("clear");


    cliente.conecta();
    recv(cliente.sockfd,numero_jugador,32,0);

    OcultaCursor();
    pintar_marco();


    //Creamos el menu

    M.ImprimePortada(abre_juego);
    char start[32];
    

    while(true)
    {
   
        recv(cliente.sockfd,start,32,0);
        if(strcmp(start,"comienza")==0)
        {
            break;
        }
        pausa(50);
    }

    limpiar();


    //Creamos la barra del jugador A

    A.Pintar();

    //Creamos la Barra del jugador B

    B.Pintar();

    //Creamos la pelota

    //IMPORTANTE: Esta variable guardara la tecla presionada para mover al jugador
    //char tecla2; //Tecla que mueve al jugador B

    std::thread envia(manda);
    std::thread recibe(lee);

    envia.join();
    recibe.join();




  gotoxy(0,28);
    printf("Juego finalizado.");

    //pausa();
    //pausa(50);
}

