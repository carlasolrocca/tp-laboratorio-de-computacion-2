//DECLARACION DE STRUCTS
struct fechaIng{
int     dia;
char    mes[10];
int     anio;
};

struct corredor{
int     orden;
int     id;
struct  fechaIng fecha;
int     edad;
char    pais[30];
float  tiempo;
int     act;
};

//CREAR BINARIO: crea archivo competidores.dat brindando mensaje tanto para la creación exitosa como para un error.
void crear(){
    FILE *competidores;
    competidores = fopen("competidores.dat", "wb"); //Crea archivo con modo escritura.

   if(competidores!=NULL){                          //Si no hubo errores, muestra mensaje por pantalla y cierra el archivo.
        fclose(competidores);
   }else{
        perror("Error al crear el archivo binario.\n");     //Muestra mensaje de error y corta el programa.
        exit(1);
   }
}

//LISTAR: recibe lineas del .csv, las divide en tokens que llenarán los campos del struct de competidor y que luego se mostrarán por pantalla.
void listar(FILE *archCsv, FILE *archBin, struct corredor competidor){
    archCsv=fopen("corredores_v1.csv", "rt");    //Abro archivo excel en modo lectura.
    archBin=fopen("competidores.dat", "wb");    //Abro archivo binario en modo escritura.
    printf("Estos son todos los datos de la lista de competidores de la que se dispone:\n\n");
    if(archCsv!=NULL){                        //Si no hubo errores en la apertura del excel, procede con la lectura.
        char linea[100];
        char *token;
        crear();                            //Llamo a la funcion que crea un archivo binario.
        fgets(linea, sizeof(linea),archCsv);                     //Trae una linea del archivo excel.
        printf("Orden | Corredor | Dia-Mes-Anio | Edad  | Pais  | Tiempo\n");
        printf("----------------------------------------------------------\n");
        while(!feof(archCsv)){                                //Mientras no haya llegado al final del archivo, lee datos.
            token=strtok(linea, ";");
            competidor.orden = atoi(token);                  //Convierte la cadena a tipo int.
            competidor.id= atoi(strtok(NULL, ";"));
            competidor.fecha.dia= atoi(strtok(NULL, ";"));
            strcpy(competidor.fecha.mes,strtok(NULL, ";"));
            competidor.fecha.anio= atoi(strtok(NULL, ";"));
            competidor.edad= atoi(strtok(NULL, ";"));
            strcpy(competidor.pais, strtok(NULL, ";"));
            competidor.tiempo= atof(strtok(NULL, ";"));     //Convierte la cadena a tipo float.

            printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);

            if(archBin!=NULL){
                fwrite(&competidor, sizeof(competidor), 1, archBin);          //Cargo los datos del excel en el binario.
            }else{
                printf("Error en la carga de competidores en el archivo binario.");
            exit(1);
            }
            fgets(linea, sizeof(linea),archCsv);
        }
        printf("----------------------------------------------------------\n");
    }else{
        perror("Error al abrir el archivo.");
        exit(1);
    }
    fclose(archCsv);
    fclose(archBin);
    printf("\nPresione una tecla para continuar: ");
    getchar();
}

//Funcion menu principal. Aborda las tres opciones que estan disponibles para trabajar estos datos: visualizarlos, modificarlos o eliminarlos.
void menu1(FILE *archBin, struct corredor competidor){           //Defino menu principal para ABM
    system("cls");
    int opcion;
    printf("----**Menu principal**----\n");
    printf("1. Visualizacion de registros\n2. Ingreso o modificacion de registros\n0. Salir del programa\n");
    printf("Ingresa una opcion: ");
    scanf("%d", &opcion);

    while(opcion<0 || opcion>2){                        //Validacion de opcion ingresada.
        printf("Ingresaste una opcion incorrecta! Por favor elegi una opcion valida: ");
        scanf("%d", &opcion);
    }
    switch(opcion){
        case 1:                                     //ERRORES SOLO CON UNO+ EN ORDEN Y NRO CORREDOR
            listar_dat(archBin, competidor);
            break;
        case 2:
            modificaciones(archBin, competidor);    //ESTOY CON ESTOOOOOOOOOOOOOOOOOOO
            break;
        default:
            exit(1);
            break;
    }
}
