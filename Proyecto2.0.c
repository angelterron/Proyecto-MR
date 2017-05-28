#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variables globales
int IDMaquina=0;

typedef struct Producto{
    int dia;
    int mes;
    int anio;
    int num;
    struct Producto *siguienteP;
}Producto;

typedef struct Espiral{
    char nombre[30];
    char ID[2];
    int precio;
    int cantidad;
    struct Espiral *siguienteE;
    struct Producto *tope;
}Espiral;

typedef struct Maquina{
    int ID;
    char ubicacion[30];
    int tipo;
    struct Espiral *inicioE;
    struct Maquina *siguienteM;
}Maquina;

Maquina* buscarMaquina(Maquina **inicio,int idM){
    if(!(*inicio))
        return NULL;
    if((*inicio)->ID == idM){
        return (*inicio);
    }
    return buscarMaquina(&(*inicio)->siguienteM,idM);

}

void imprimirContenidoM(Espiral **inicio, int tipo){
    if(!(*inicio))
        return;
    if(tipo == 1){
        printf("\n\t\t %s %s $%d %dml.",(*inicio)->ID,(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
    }
    if(tipo == 2){
        printf("\n\t\t %s %s $%d %dgr.",(*inicio)->ID,(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
    }
    return imprimirContenidoM(&(*inicio)->siguienteE,tipo);
}
int buscarPorUbicacion(Maquina **inicio, char ubicacion[30]){
    if(!(*inicio))
        return 0;
    if(strcmp(ubicacion,(*inicio)->ubicacion) == 0)
        return 1;
    return buscarPorUbicacion(&(*inicio)->siguienteM,ubicacion);
}
void imprimirPorUbicacion(Maquina **inicio, char ubicacion[30]){
    if(!(*inicio))
        return;
    if(strcmp(ubicacion,(*inicio)->ubicacion)== 0){
        if((*inicio)->tipo == 1 && (*inicio)->inicioE != NULL){
            printf("%d Maquina de Refrescos.\n\tContenido: ",(*inicio)->ID);
            imprimirContenidoM(&(*inicio)->inicioE,1);
        }
        if((*inicio)->tipo == 2 && (*inicio)->inicioE != NULL){
            printf("%d Maquina de Golosinas.\n\tContenido: ",(*inicio)->ID);
            imprimirContenidoM(&(*inicio)->inicioE,2);
        }
    }
    return imprimirPorUbicacion(&(*inicio)->siguienteM,ubicacion);
}

Espiral* buscarProducto(Espiral **inicio,char idP[2]){

    if(!(*inicio)){
        printf("EL PUNTERO ES NULO!");
        return NULL;
    }
    printf("\n%s - %s\n",(*inicio)->ID,idP);
    if(strcmp((*inicio)->ID,idP)==0){
        printf("hola\n");
        return (*inicio);
    }else{
        return buscarProducto(&(*inicio)->siguienteE,idP);
    }
}



void despacharProducto(Espiral **inicio, int tipo){
    int credito = 0, moneda;
    do{
        printf("\nRefresco: %s",(*inicio)->nombre);
        printf("\nPrecio: %d",(*inicio)->precio);
        if(tipo == 1)printf("\nCantidad: %d ml",(*inicio)->cantidad);
        if(tipo == 2)printf("\nCantidad: %d gr",(*inicio)->cantidad);
        printf("\n0.- Regresar");
        printf("\nCredito: %d",credito);
        printf("\nIngrese una moneda: ");
        scanf("%d",&moneda);
        credito = credito + moneda;
    }while(credito<(*inicio)->precio && moneda != 0) ;
    if(moneda!=0)printf("\nCambio: %d",(credito-(*inicio)->precio));
    else printf("\nCambio: %d",credito);
    printf("\nGRACIAS POR USAR MAQUINAS AA!\n");
    system("pause");
}


void menuCliente(Maquina **inicioM){
        char ubicacion[30],idP[2];
        Maquina *auxMaquina;
        Espiral *auxEspiral;
        int idM;
        if((*inicioM) != NULL){
            while(getchar()!='\n');
            printf("%cCu%cl es su ubicaci%cn?: ",168,160,162);
            scanf("%[^\n]",ubicacion);
            if(buscarPorUbicacion(&(*inicioM),ubicacion)== 1){
                do{
                    system("cls");
                    printf("= %s =",ubicacion);
                    imprimirPorUbicacion(&(*inicioM),ubicacion);
                    printf("0.-Regresar.");
                    printf("Seleccione la maquina que desee usar: ");
                    scanf("%d",&idM);
                    if((auxMaquina = buscarMaquina(&(*inicioM),idM)) != NULL){
                        imprimirContenidoM(&auxMaquina->inicioE,auxMaquina->tipo);
                        printf("Seleccione producto: ");
                        scanf("%[^\n]",idP);
                        if((auxEspiral = buscarProducto(&(*inicioM)->inicioE,idP)) != NULL){
                                despacharProducto(&auxEspiral,auxMaquina->tipo);
                        }else{
                            printf("\nEl producto seleccionado no es valido.");
                            //system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                            system("pause");
                        }
                    }else{
                        printf("\nLa maquina que ha ingresado no es valida.");
                        //system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                        system("pause");
                    }
                }while(idM!=0);
            }else{
                printf("No existen maquinas en su ubicaci%cn.\n",162);
                //system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                system("pause");
                return;
            }
        }else{
            printf("No existen maquinas actualmente.\n");
            //system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
            system("pause");
            return;
        }
}

void MostrarProductos(Maquina **inicioM,int tipo, int ID){
        printf("-------------------------------------- ");
        printf("\n| Productos disponibles en maquina: %d |",(*inicioM)->ID);
        printf("\n -------------------------------------- ");
        if(tipo==1)
        printf("\n| Tipo: Refrescos                     |");
        else
        printf("\n| Tipo: Golosina                      |");
        printf("\n ------------------------------------- ");
        //funcion imprimir productos de ID maquina
        printf("\n");
        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
}

void RegistrarProducto(Maquina **inicioM, char nombre[30], int cantidad, char IDProducto[2],int precio){
    printf("Hol1\n");
    Espiral *EspiralM= (Espiral*) malloc(sizeof(struct Espiral));
    printf("Holi2");
    if(!EspiralM){
        printf("No se pudo reservar la memoria\n");
        return;
    }
    printf("Holi");
    strcpy(EspiralM->nombre,nombre);
    strcpy(EspiralM->ID,IDProducto);
    EspiralM->precio=precio;
    EspiralM->cantidad=cantidad;
    EspiralM->siguienteE=(*inicioM)->inicioE;
    EspiralM->tope=NULL;
    (*inicioM)->inicioE=EspiralM;
}

void RegistroDeProductos(Maquina **inicioM){
    char nombre[30],IDProducto[2];
    int cantidad,precio;
    Espiral *aux;
        printf(" -------------------------------- ");
        printf("\n| Administracion de productos |");
        printf("\n -------------------------------- ");
        while(getchar()!='\n');
        printf("\nIngrese el nombre del producto: ");
        scanf("%[^\n]",nombre);
        printf("\n%s",nombre);
        if((*inicioM)->tipo==1)
            printf("Ingrese los ML del producto: ");
        else
            printf("Ingrese los GR del producto: ");
        while(getchar()!='\n');
        scanf("%d",&cantidad);
        printf("Ingrese el precio del producto: ");
        while(getchar()!='\n');
        scanf("%d",&precio);

        do{
        while(getchar()!='\n');
        printf("Ingrese el ID del producto (Ej: A0): ");
        scanf("%[^\n]",IDProducto);
            if(IDProducto[0]<65 || IDProducto[0]>70)
                printf("Tiene que iniciar con una letra\n");
            if ( IDProducto[1]<48 || IDProducto[1]>57 )
                printf("La segunda letra debe ser un numero entre 0 y 9\n");
          //aux=buscarProducto(&(*inicioM)->inicioE,IDProducto);
          /*if(aux!=NULL){
            printf("ID repetido, ingrese otro ID\n");
            system("read -n 1 -s -p \"Presiona una tecla para re intentar...\"");
          }*/
        }while( (IDProducto[0]<65 || IDProducto[0]>70) || (  IDProducto[1]<48 || IDProducto[1]>57) );
        printf("%s 1",nombre);
        RegistrarProducto(inicioM,nombre,cantidad,IDProducto,precio);
        printf("1: %s\n",(*inicioM)->inicioE->nombre);
        printf("1. %s\n",(*inicioM)->inicioE->ID );
        system("pause");
        //printf("2: %s\n",inicioM->inicioE->siguienteE->nombre );
        //printf("2. %s\n",inicioM->inicioE->siguienteE->ID );

}


void MenuProductos(Maquina **inicioM){
    int op;
    do{
        printf(" -------------------------------- ");
        printf("\n| Administracion de productos |");
        printf("\n -------------------------------- ");
        printf("\n|1.-Registrar producto           |");
        printf("\n|2.-Insertar producto             |");
        printf("\n|3.-Eliminar producto             |");
        printf("\n|4.-Mostrar productos             |");
        printf("\n|5.-Regresar                      |");
        printf("\n -------------------------------- ");
        if((*inicioM)->tipo==1)
        printf("\n| Tipo: Refrescos                 |");
        else
        printf("\n| Tipo: Golosina                  |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                RegistroDeProductos(inicioM);
                system("clear");
                //system("cls");
                break;
        case 2:
                //fun insertar
                system("clear");
                //system("cls");
                break;
        case 3:
                //fun eliminar
                system("clear");
                //system("cls");
                break;
        case 4:
                imprimirContenidoM(&(*inicioM)->inicioE,(*inicioM)->tipo);
                system("pause");
                system("clear");
                //system("cls")
                break;
        case 5:
                break;
        default: printf("\nOpci%cn no valida.\n",162);
        }
        //system("clear");
        system("cls");
    }while(op!=5);
}


void RegistrarMaquina(Maquina **inicioM,int tipo, char ubicacion[30]){
    Maquina *NuevaMaquina= (Maquina *) malloc (sizeof(Maquina));
    if(!(NuevaMaquina)){
        printf("No se pudo reservar la memoria\n");
        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        return ;
    }
    strcpy(NuevaMaquina->ubicacion,ubicacion);
    NuevaMaquina->tipo=tipo;
    NuevaMaquina->ID=++IDMaquina;
    NuevaMaquina->inicioE=NULL;
    NuevaMaquina->siguienteM = (*inicioM);
    (*inicioM) = NuevaMaquina;
}

void ComprarMaquina(Maquina **inicioM,int tipo){
    int tamespirales;
    char ubicacion[30];
        printf(" -------------------------------- ");
        printf("\n|Proceso de registro de maquina |");
        printf("\n -------------------------------- ");
        printf("\n");
        while(getchar()!='\n');
        printf("Escriba la ubicacion de la maquina: ");
        scanf("%[^\n]",ubicacion);
        RegistrarMaquina(inicioM,tipo,ubicacion);
        if((*inicioM)!=NULL)
            {
                printf("ID %d\n",(*inicioM)-> ID);
                printf("Maquina registrada con exito\n");}
        else
            printf("Maquina no creada\n");
        //system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        system("pause");
}

void ImprimirMaquinas(Maquina **inicioM,int tipo){
    if(!(*inicioM))
        return ;
    if((*inicioM)->tipo == tipo)
        printf("%d - %s \n",(*inicioM)->ID, (*inicioM)->ubicacion );
    return(ImprimirMaquinas(&(*inicioM)->siguienteM,tipo));
}


void EstadoMaquina(Maquina **inicioM,int tipo){
    Maquina *auxMaquina;
    if((*inicioM)==NULL){
        printf("No se han agregado maquinas\n");
        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        system("clear");
        //system("pause");
        //system("cls");
        return;
    }
    int idmaquina;
        printf(" -------------------------------- ");
        printf("\n| Seleccion de maquina          |");
        printf("\n -------------------------------- ");
        printf("\n");
        ImprimirMaquinas(inicioM,tipo);
        printf("Seleccione el ID de una maquina: ");
        scanf("%d",&idmaquina);
        if((auxMaquina = buscarMaquina(&(*inicioM),idmaquina)) != NULL){//despues de la impresion de las maquinas se busca y se obtiene su posicion en la lista
            MenuProductos(&auxMaquina);//se envia puntero con posicion de la lista
        }

}

void AdministrarMaquina(Maquina **inicioM,int tipo){
        int op;
    do{
        printf(" -------------------------------- ");
        printf("\n| Registrar / Administrar Maquinas |");
        printf("\n -------------------------------- ");
        printf("\n|1.-Registrar Maquina               |");
        printf("\n|2.-Administrar Maquina           |");
        printf("\n|3.-Regresar                      |");
        printf("\n -------------------------------- ");
        if(tipo==1)
        printf("\n| Tipo: Refrescos                 |");
        else
        printf("\n| Tipo: Golosina                  |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        system("clear");
        switch(op){
        case 1:
                //system("clear");
                system("cls");
                ComprarMaquina(inicioM,tipo);
                break;
        case 2:
                //system("clear");
                system("cls");
                EstadoMaquina(inicioM,tipo);
                break;
        case 3:
                //system("clear");
                system("cls");
                break;
        default:
        printf("\nOpci%cn no valida.\n",162);

        }
        //system("clear");
        system("cls");
    }while(op!=3);
}


void MenuProveedor(Maquina **inicioM){
    int op;
    do{
        printf(" -------------------------------- ");
        printf("\n|     Registro de maquinas      |");
        printf("\n -------------------------------- ");
        printf("\n|1.-M. de Refrescos.             |");
        printf("\n|2.-M. de Golosinas.             |");
        printf("\n|3.-Regresar                     |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                //system("clear");
                system("cls");
                AdministrarMaquina(inicioM,1);
                break;
        case 2:
                //system("clear");
                system("cls");
                AdministrarMaquina(inicioM,2);
                break;
        case 3:
                //system("clear");
                system("cls");
                break;
        default: printf("\nOpci%cn no valida.\n",162);
        }
    //system("clear");
    system("cls");
    }while(op!=3);
}

int main(){
    char ubicacion[30];
    Maquina *inicioM=NULL;
    int op;
    do{
        printf(" -------------------------------- ");
        printf("\n|             MENU                |");
        printf("\n -------------------------------- ");
        printf("\n|1.-Proveedor.                    |");
        printf("\n|2.-Cliente                       |");
        printf("\n|3.-Salir                         |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                //system("clear");
                system("cls");
                MenuProveedor(&inicioM);
                break;
        case 2:
                //system("clear");
                system("cls");
                menuCliente(&inicioM);
                break;
        case 3: break;
        default:
                printf("\nOpci%cn no valida.\n",162);
        }
    //system("clear");
    system("cls");
    }while(op!=3);
    return 0;
}
//sueño
