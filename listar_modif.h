
//Funcion para diversos listados de los datos que se disponen. Usa un switch para derivar cada accion a una funcion auxiliar especifica.
void listar_dat(FILE *archBin, struct corredor competidor){
    archBin=fopen("competidores.dat", "rb");
    int opcion;
    printf("\n----*Menu visualizacion*----\n");
    printf("1. Mostrar todos los registros\n2. Mostrar solo competidores activos\n3. Buscar competidor por pais\n4. Buscar competidor segun rango de tiempo\n5. Buscar competidor por nro de orden\n6. Buscar competidor por ID\n0. Salir del programa\n");
    printf("Ingresa una opcion: ");
    scanf("%d", &opcion);

    while(opcion<0 || opcion>6){
        printf("Ingresaste una opcion incorrecta! Por favor elegi una opcion valida: ");
        scanf("%d", &opcion);
    }
        switch(opcion){
        case 1:
            listado(archBin, competidor, opcion);       //LISTADO DE TODOS LOS COMPETIDORES
            break;
        case 2:
            listado(archBin, competidor, opcion);       //LISTADO SOLO DE LOS ACTIVOS
            break;
        case 3:
            lista_pais(archBin, competidor);            //LISTADO SEGUN EL PAIS
            break;
        case 4:
            rango_tiempo(archBin, competidor);          //LISTADO POR RANGO DE TIEMPO
            break;
        case 5:
            nro_orden(archBin, competidor);             //LISTADO POR NUMERO DE ORDEN
            break;
        case 6:
            nro_corredor(archBin, competidor);          //LISTADO POR NRO DE COMPETIDOR
            break;
        default:
            exit(1);
            break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////VISUALIZACION REGISTROS
//Responde a la busqueda de todos los competidores y segun campo activo.
void listado(FILE *archBin, struct corredor competidor, int opcion){
    archBin=fopen("competidores.dat", "rb");

    if(opcion==1){
        printf("\nEstos son todos los competidores: \n");
        printf("Orden | Corredor | Dia-Mes-Anio | Edad  | Pais  | Tiempo\n");
    }else{
        printf("\nEstos son solo los competidores activos: \n");
        printf("Orden | Corredor | Dia-Mes-Anio | Edad  | Pais  | Tiempo\n");
    }

    fread(&competidor, sizeof(competidor), 1, archBin);

    if(archBin!=NULL){              //Mientras el archivo no devuelva error ni haya llegado a su final, imprime todos los registros de competidores.
        while(!feof(archBin)){
            if(opcion==1){
                printf("----------------------------------------------------------\n");
                printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
            }
            if(opcion==2){
                printf("----------------------------------------------------------\n");
                if(competidor.act==1){
                    printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
                }
            }
            fread(&competidor, sizeof(competidor), 1, archBin);
        }
    }
    fclose(archBin);
    printf("Pulse enter para continuar: ");
    getchar();
}
//Responde a la busqueda por pais.
void lista_pais(FILE *archBin, struct corredor competidor){
    archBin=fopen("competidores.dat", "rb");
    char pais[15];                  //Pais que se ingresa por teclado
    char paisFinal[4];             //Pais recortado para comparar cadenas con el archivo binario.
    int i, bandera=0;

    printf("Ingresa el pais segun el cual queres buscar: ");
    scanf("%s", pais);
    fflush(stdin);

    if(strcmp(pais, "0")!=0){        //Comparo el pais ingresado usando la funcion que se que devuelve 0 cuando son iguales.
        for(i=0;i<3;i++){
            paisFinal[i]=toupper(pais[i]);
        }
        paisFinal[3]= '\0';         //Corto la cadena de pais en 3 caracteres.
        fread(&competidor, sizeof(competidor), 1, archBin);
        while(!feof(archBin)){
            if(competidor.pais==paisFinal){
                bandera = 1;                //Encontro una coincidencia.
            }
            fread(&competidor, sizeof(competidor), 1, archBin);
        }
        if(bandera==1){
            printf("\n-----Competidores pertenecientes al pais %s-----\n", paisFinal);
            printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
        }else{
            printf("No existen corredores dentro de ese pais.\nIngrese otro: ");
            scanf("%s", &pais);
            fflush(stdin);
        }
    }
    fclose(archBin);
}

//Listado por rango de tiempo definiendo un minimo y un maximo, mostrando a aquellos competidores dentro de ese rango.
void rango_tiempo(FILE *archBin, struct corredor competidor){
    float minimo, maximo;
    int i, bandera=0;

    printf("Ingresa un rango de tiempo minimo seguido de un max. Ejemplo: 230.0-300.0: ");
    scanf("%f-%f", &minimo, &maximo);
    fflush(stdin);

    if(minimo!=0){                                          //Chequeo que el minimo no sea 0.
        fread(&competidor, sizeof(competidor), 1, archBin);
        while(!feof(archBin)){
            if(competidor.tiempo>=minimo && competidor.tiempo<=maximo){
                bandera= 1;
            }
            fread(&competidor, sizeof(competidor), 1, archBin);
        }
        if(bandera==1){
            printf("\n-----Competidores dentro de ese rango-----\n");
            printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
        }else{
            printf("No existen corredores dentro de ese rango.\nIngrese otro: ");
            scanf("%f-%f", &minimo, &maximo);
            fflush(stdin);
        }
    }
    fclose(archBin);
}

//Listado segun el numero de orden del corredor.
void nro_orden(FILE *archBin, struct corredor competidor){
    int orden, bandera=0;
    archBin=fopen("competidores.dat", "r+b");

    printf("Ingresa el numero de orden de tu competidor: ");
    scanf("%d", &orden);
    fflush(stdin);

    while(orden<0){                 //Validacion de numero de orden positivo.
        printf("Por favor, ingresa un numero de orden mayor a cero.\n");
        scanf("%d", &orden);
        fflush(stdin);
    }

    while(bandera==0 && orden!=0){      //Mientras no lo haya encontrado. ME TRAE EL SIGUIENETEEEEE
        fseek(archBin,0,SEEK_SET);
        fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_CUR);
        fread(&competidor, sizeof(competidor), 1, archBin);
        if(competidor.orden==orden){
            bandera=1;
            orden= competidor.orden;
        }else{
            printf("No hay un jugador asociado a ese nro de orden.\n");
        }
        fread(&competidor, sizeof(competidor), 1, archBin);
    }
        if(bandera==1){
            printf("-----Competidor correspondiente a este numero de orden %d-----\n", orden);
            printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
        }
    fclose(archBin);
}

//Listado segun el numero de orden del corredor, recibe el archivo y el struct de competidores. Lee, busca coincidencias y emite. Misma logica que con el listado por orden.
void nro_corredor(FILE *archBin, struct corredor competidor){
    int nro, bandera=0;
    archBin=fopen("competidores.dat", "r+b");

    if(archBin!=NULL){
        printf("Ingresa el numero de corredor: ");
        scanf("%d", &nro);
        fflush(stdin);

        while(nro<0){                 //Validacion de numero de corredor positivo.
            printf("Por favor, ingresa un numero de corredor mayor a cero.\n");
            scanf("%d", &nro);
            fflush(stdin);
        }

        while(bandera==0 && nro!=0){
            fseek(archBin, 0, SEEK_SET);
            fread(&competidor, sizeof(competidor), 1, archBin);
            if(competidor.id==nro){
                bandera=1;
            }
            fread(&competidor, sizeof(competidor), 1, archBin);
        }
        if(bandera==1){
            printf("-----Competidor correspondiente a este numero de corredor %d-----\n", nro);
            printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
        }
    }
    fclose(archBin);
}
//////////////////////////////////////////////////////////////FIN DE 1ERA OPCION DEL MENU PPAL PARA VISUALIZAR REGISTROS.




///////////////////////////////////////////////////////////////2DA OPCION PARA MODIFICAR
void modificaciones(FILE *archBin, struct corredor competidor){
    archBin=fopen("competidores.dat", "rb");
    int opcion;
    printf("\n----**Menu modificaciones**----\n");
    printf("1. Registrar un nuevo competidor\n2. Modificar edad o tiempo de un competidor\n3. Dar de baja a un competidor\n4. Remover del listado a un competidor\n0. Salir del programa\n");
    printf("Ingresa una opcion: ");
    scanf("%d", &opcion);

    while(opcion<0 || opcion>4){
        printf("Ingresaste una opcion incorrecta! Por favor elegi una opcion valida: ");
        scanf("%d", &opcion);
    }
        switch(opcion){
        case 1:
            registroCompetidor(archBin, competidor);              //FUNCION PARA CARGAR A UN COMPETIDOR
            break;
        case 2:
            modificar(archBin, competidor);                     //FUNCION DE MODIFICACION DE EDAD Y TIEMPO
            break;
        case 3:
            darBaja(archBin, competidor);                                //FUNCION PARA DAR DE BAJA CON CAMPO ACT
            break;
        case 4:
            break;                        //FUNCION PARA REMOVER DEFINITIVAMENTE UN REGISTRO DE UN COMPETIDOR
        default:
            exit(1);
            break;
    }
}


//Funcion que se encarga de registrar un nuevo competidor teniendo en cuenta el nro de orden a la hora d eubicarlo y diversas validaciones
void registroCompetidor(FILE *archBin, struct corredor competidor){
    archBin=fopen("competidores.dat", "r+b");
    int orden, i, nReg;
    printf("Ingresa el numero de orden del nuevo competidor: ");
    scanf("%d", &orden);
    fflush(stdin);

    while(orden<0 || orden>40){             //Pido que sea positivo pero tambien le doy un tope.
        printf("Ingresa un numero de orden valido Pueden ir desde 1 hasta 40:  ");
        scanf("%d", &orden);
        fflush(stdin);
    }

    if(archBin!=NULL){
        fseek(archBin,-1*sizeof(struct corredor),SEEK_END);         //Me ubico al final para saber el max valor de orden
        fread(&competidor, sizeof(struct corredor), 1, archBin);
        nReg= competidor.orden;                                     //Me lo guardo y lo comparo con lo ingresado.
        if(nReg>=orden){
            fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_SET);      //Me paro en la posicion en la que deberia registrar a ese nuevo competidor para ver si ese id no esta ya en uso.
            fread(&competidor, sizeof(struct corredor), 1, archBin);
            printf("No puedes registrar un competidor con ese id porque ya esta en uso.\n");
        }else{
            fseek(archBin,(orden-1)*sizeof(struct corredor), SEEK_SET);     //Si no lo esta, procedo con el alta.
            altaComp(archBin, orden, competidor);                       //Llamo a la funcion que registra un nuevo competidor y le paso el nro de orden
            orden=0;
        }
    }
}

///////////////////////
//Funcion para agregar un competidor.
void altaComp(FILE *archBin, int orden, struct corredor competidor){
    archBin=fopen("competidores.dat", "r+b");
    printf("\nDatos a ingresar para el competidor con nro orden %d: ", orden);

    int id, id_valid=1, edad, i;
    char *token;
    char fecha[15], pais[10];
    float tiempo;


    competidor.orden=orden;

    printf("\nIngresa el id de tu competidor: ");
    scanf("%d", &id);
    fflush(stdin);

    while(id<1 || id>40000){
        printf("\nIngresa un id valido para tu competidor. Este debe ser mayor que 1 pero menor que 40.000: ");
        scanf("%d", &id);
        fflush(stdin);
    }

    while(id_valid==1){
        id_valid = 0;
        fseek(archBin, 0, SEEK_SET);
        fread(&competidor, sizeof(struct corredor), 1, archBin);
        while(!feof(archBin)){
            if(competidor.id==id){
                id_valid=1;                         //Registra que el id que ingrese ya se encontraba en uso.
            }
            fread(&competidor, sizeof(struct corredor), 1, archBin);
        }
        if(id_valid==1){
            printf("Ese id ya esta en uso, ingresa otro por favor: ");
            scanf("%d", &id);
            fflush(stdin);
        }
    }
    competidor.id=id;

    printf("Ingresa la fecha en formato dd-mes-aaaa: ");
    scanf("%s", fecha);
    fflush(stdin);
    token=strtok(fecha, "-");
    competidor.fecha.dia= atoi(token);
    token=strtok(NULL, "-");
    for (i=0;i<=strlen(token);i++){
            token[i]=tolower(token[i]);
    }
    strcpy(competidor.fecha.mes,token);
    competidor.fecha.anio= atoi(strtok(NULL, "-"));

    printf("Ingresa la edad: ");
    scanf("%d", &edad);
    fflush(stdin);

    while(edad<18 || edad>99){
        printf("Ingresa una edad correcta: ");
        scanf("%d", &edad);
        fflush(stdin);
    }

    competidor.edad= edad;

    printf("Ingresa el pais del competidor: ");
    scanf("%s", pais);
    fflush(stdin);
    strncpy(competidor.pais, toupper(pais), 3);

    printf("Ingresa el tiempo de tu competidor: ");
    scanf("%f", &tiempo);
    fflush(stdin);
    while(tiempo<100 || tiempo>500){
        printf("Ingresa un tiempo correcto entre 100 y 450: ");
        scanf("%f", &tiempo);
        fflush(stdin);
    }
    competidor.tiempo= tiempo;
    competidor.act= 1;


    printf("\nSe ingreso correctamente el competidor\n");
    printf("%d\t|%d\t |%d-%s-%d\t| %d\t| %s\t|%.6f\n",competidor.orden,competidor.id,competidor.fecha.dia,competidor.fecha.mes,competidor.fecha.anio,competidor.edad,competidor.pais,competidor.tiempo);
    fclose(archBin);
}
//Modifica la edad o el tiempo segun el orden ingresado.
void modificar(FILE *archBin, struct corredor competidor){
    int edad, orden;
    float tiempo;

    printf("Ingresa el numero de orden del competidor: ");
    scanf("%d", &orden);
    fflush(stdin);

    while(orden<0 || orden>40){             //Pido que sea positivo pero tambien le doy un tope.
        printf("\nIngresa un numero de orden valido Pueden ir desde 1 hasta 40:  ");
        scanf("%d", &orden);
        fflush(stdin);
    }
    archBin=fopen("competidores.dat", "r+b");
    fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_SET);              //Me paro en la posicion del orden.
    fread(&competidor,sizeof(struct corredor),1,archBin);                   //Leo esa linea.
    fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_SET);

    printf("\nIngrese una nueva edad o 0 para salir: ");
    scanf("%d",&edad);
    fflush(stdin);

    while(edad!=0 && (edad<18 || edad>99)){                         //Valido la edad.
        printf("\nIngresa una edad valida entre 18 y 99 anios: ");
        scanf("%d",edad);
        fflush(stdin);
    }
    if(edad=0){
        exit(1);
    }else{
        competidor.edad=edad;
    }

    printf("\nIngresa un nuevo tiempo o escribi 0 para salir: ");           //Misma logica para el cambio de tiempo.
    scanf("%f",&tiempo);
    fflush(stdin);

     while(tiempo!=0 && (tiempo<100 || tiempo>500)){
        printf("\nIngresa un tiempo valido entre 100 y 500: ");
        scanf("%f",tiempo);
        fflush(stdin);
    }

    if (tiempo=0){
        exit(1);
    }else{
        competidor.tiempo=tiempo;
    }
    printf("Tras los cambios, la edad y tiempo ahora son:\n"
           "edad:%d"
           "tiempo=%.6f%\n",competidor.edad,competidor.tiempo);

    fwrite(&competidor,sizeof(struct corredor),1,archBin);
    fclose(archBin);
    getchar();
}


//Baja logica.
void darBaja(FILE *archBin, struct corredor competidor){
    int orden;

    printf("Ingresa el numero de orden del competidor: ");
    scanf("%d", &orden);
    fflush(stdin);

    while(orden<0 || orden>40){             //Validacion del nro de orden.
        printf("\nIngresa un numero de orden valido Pueden ir desde 1 hasta 40:  ");
        scanf("%d", &orden);
        fflush(stdin);
    }

    archBin=fopen("competidores.dat", "r+b");               //Abro archivo binario.

    fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_SET);   //Me posiciono con el nro de orden.
    fread(&competidor,sizeof(struct corredor),1,archBin);        //Leo la linea correspondiente.
    competidor.act=0;                                        //Es una baja LOGICA asi que consiste en cambiar el campo de activo por un 0.

    fseek(archBin,(orden-1)*sizeof(struct corredor),SEEK_SET);   //Escribo la modificacion.
    fwrite(&competidor,sizeof(struct corredor),1,archBin);
    fclose(archBin);

    printf("\Baja logica exitosa.");
    exit(1);
}
///////////////////////////////////////////////////////////////////FIN DE 2DA OPCION DE MODIFICACIONES

