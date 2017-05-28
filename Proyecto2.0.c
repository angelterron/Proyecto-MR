#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void imprimirContenidoM(Espiral **inicio, int tipo){
    if(!(*inicio))
        return;
    if(tipo == 1){
        printf("\n\t\t%s $%d %dml.",(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
    }
    if(tipo == 2){
        printf("\n\t\t%s $%d %dgr.",(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
    }
    return imprimirContenidoM(&(*inicio)->siguienteE,tipo);
}
int buscarPorUbicacion(Maquina **inicio, char ubicacion[30]){
    if(!(*inicio))
        return 0;
    if(strcasecmp(ubicacion,(*inicio)->ubicacion) == 1)
        return 1;
    return buscarPorUbicacion(&(*inicio)->siguienteM,ubicacion);
}
void imprimirPorUbicacion(Maquina **inicio, char ubicacion[30]){
    if(!(*inicio))
        return;
    if(strcmp(ubicacion,(*inicio)->ubicacion)== 1){
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
void menuCliente(Maquina **inicioM){
        char ubicacion[30];
        if((*inicioM) != NULL){
            while(getchar()!='\n');
            printf("%cCu%cl es su ubicaci%cn?: ",168,160,162);
            scanf("%[^\n]",ubicacion);
            if(buscarPorUbicacion(&(*inicioM),ubicacion)== 1){
                imprimirPorUbicacion(&(*inicioM),ubicacion);
                printf("Seleccione la maquina que desee usar: ");
                return;
            }else{
                printf("No existen maquinas en su ubicaci%cn.\n",162);
                system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                //system("pause");
                return;
            }
        }else{
            printf("No existen maquinas actualmente.\n");
            system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
            //system("pause");
            return;
        }
}


//Si estan bien esos parametros? Si, estan super bien < 3 :) que mas procd? te voy a enviar las funciones de busqueda por ubicacion oc oie , eu modifique aquí
void MenuProductos(Maquina **inicioM,int tipo, int ID){

        int op;
    do{
         system("clear");
        printf(" -------------------------------- ");
        printf("\n| Administracion de productos |");
        printf("\n -------------------------------- ");
        printf("\n|1.-Registrar productor           |");
        printf("\n|2.-Insertar producto             |");
        printf("\n|3.-Eliminar producto             |");
        printf("\n|4.-Regresar                      |");
        printf("\n -------------------------------- ");
        if(tipo==1)
        printf("\n| Tipo: Refrescos                 |");
        else
        printf("\n| Tipo: Golosina                  |");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        system("clear");
        switch(op){
        case 1:
                //fun registrar
                system("clear");
                break;
        case 2:
                //fun insertar
                system("clear");
                break;
        case 3: 
                //fun eliminar
                system("clear");
                break;
        case 4:
                break;
        default: printf("\nOpci%cn no valida.\n",162);
                 system("clear");
        }
    }while(op!=4);
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
        //funcion insertar Maquina en Lista
        if((*inicioM)!=NULL)
            printf("Maquina registrada con exito\n");
        else
            printf("Maquina no creada\n");
        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        system("clear");
}


void EstadoMaquina(Maquina **inicioM,int tipo){
    if((*inicioM)==NULL){
        printf("No se han agregado maquinas\n");
        system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        system("clear");
        return;
    }
    int idmaquina;
        printf(" -------------------------------- ");
        printf("\n| Seleccion de maquina          |");
        printf("\n -------------------------------- ");
        printf("\n");
        //funcion aqui de impresion de maquina
        printf("Seleccione el ID de una maquina: ");
        scanf("%d",&idmaquina);
        MenuProductos(inicioM,tipo,idmaquina);
        system("clear");
}

void AdministrarMaquina(Maquina **inicioM,int tipo){
        int op;
    do{
         system("clear");
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
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        system("clear");
        switch(op){
        case 1:
                ComprarMaquina(inicioM,tipo);
                system("clear");
                break;
        case 2:
                EstadoMaquina(inicioM,tipo);
                system("clear");
                break;
        case 3: 
                system("clear");
                break;
        default: 
        system("clear");
        printf("\nOpci%cn no valida.\n",162);
                 
        }
    }while(op!=3);
}


void MenuProveedor(Maquina **inicioM){
    int op;
    do{
         system("clear");
        printf(" -------------------------------- ");
        printf("\n|     Registro de maquinas      |");
        printf("\n -------------------------------- ");
        printf("\n|1.-M. de Refrescos.    |");
        printf("\n|2.-M. de Golosinas.    |");
        printf("\n|3.-Regresar                      |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        system("clear");
        switch(op){
        case 1:
                AdministrarMaquina(inicioM,1);
                system("clear");
                break;
        case 2:
                AdministrarMaquina(inicioM,2);
                system("clear");
                break;
        case 3: 
                system("clear");
                break;
        default: printf("\nOpci%cn no valida.\n",162);
                 system("clear");
        }
    }while(op!=3);
}

int main(){
    char ubicacion[30];
    Maquina *inicioM=NULL;//que apunte a null al inicio v: Ah si, tambien se lo puse yo te mando este v:? si, y te mando el mio deja lo valido y te lo mando UwU Ok uwu <3 vas a seguir viendome :v? nel, seguire con el codigo :u :u
    int op;
    do{
         system("clear");
        printf(" -------------------------------- ");
        printf("\n|             MENU                |");
        printf("\n -------------------------------- ");
        printf("\n|1.-Proveedor.                    |");
        printf("\n|2.-Cliente                       |");
        printf("\n|3.-Salir                         |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        system("clear");
        switch(op){
        case 1:
        system("clear");
                MenuProveedor(&inicioM);
                break;
        case 2:
                menuCliente(&inicioM);
                break;
        case 3: break;
        default: system("clear");
                printf("\nOpci%cn no valida.\n",162);
                 
        }
    }while(op!=3);
    return 0;
}
//Es magia negra :o aguanta que no me aparece a mi el cambio :vvv