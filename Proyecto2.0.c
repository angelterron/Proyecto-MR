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
        printf("\n\t\t%s $%d %sml.",(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
    }
    if(tipo == 2){
        printf("\n\t\t%s $%d %sgr.",(*inicio)->nombre,(*inicio)->precio,(*inicio)->cantidad);
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
int main(){
    Maquina *inicioM = NULL;
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
                break;
        case 2:
                //system("clear");
                system("cls");
                menuCliente(&inicioM);
                break;
        case 3: break;
        default: printf("\nOpci%cn no valida.",162);
                 system("clear");
        }
        //system("clear");
        system("cls");
    }while(op!=3);
    return 0;
}
