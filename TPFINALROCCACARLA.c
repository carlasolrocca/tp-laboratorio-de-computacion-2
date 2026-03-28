/*
Carla Rocca, trabajo final. Laboratorio de computacion II - 2022.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

#include"menu_grales.h"
#include"listar_modif.h"



int main(){
    struct corredor competidor={0,0,0,"",0,0,"",0,1};
    FILE *archCsv;       //Defino puntero del excel.
    FILE *archBin;       //Defino puntero al archivo binario.


    listar(archCsv, archBin, competidor);     //Llamado a funcion Listar.
    menu1(archBin, competidor);               //Llamado al menu principal de opciones.


    getchar();
    return 0;
}
