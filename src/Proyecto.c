#include<string.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"pantalla.h"
#include"gestortareas.h"

#define    CREAR 1
#define    VER 2
#define    LISTAR 3
#define    SALIR 0
#define    GUARDAR 1
#define    SINGUARDAR 2


int main(){
  int salir=0;
  system("clear");
  Tarea *ini=NULL;
  int cambio=0;
  Tarea *ultima=NULL;
  ultima=cargarTareas(&ini);
  char usuario[20];
  int a,b,y;
   presentacion();
      printf("\n\n\t\t\t\vIntroduzca su identificador: ");
    fscanf(stdin," %[^\n]",usuario);
    fflush(stdin);
    do{
           a=menu();
		 switch (a){
           case CREAR:
	       ultima= crear_tarea(usuario,ultima,&ini,&cambio);
	     break;
	   case VER:
		   printf("Introduzca el identificador de tarea: ");
		   scanf("%i",&y);
		    ver_tarea(&ini,y,usuario);
		   break;
           case LISTAR:
	     ver_lista(&ini,usuario);
		   break;
	   case SALIR:
	     if(cambio==1){ //cambio indica si se ha creado una nueva tarea
      		  b=menu_salida();
	           switch(b){
					 case GUARDAR://salir salvando
					   almacenar_lista_fichero(&ini);
					   liberar_memoria(&ini);
					   system("clear");
					   salir=1;
break;
					 
					case SINGUARDAR: 
					system("clear");
									liberar_memoria(&ini);
					salir=1;
break;
					
					case SALIR: 
					system("clear");
					break;
		   default: printf("\n\t\vOpcion no valida. Pulse 0 para volver al menu principal o alguna de las opciones validas\n");
		     salir=0;
			}
		   }
					 
			else{
			system("clear");
						liberar_memoria(&ini);	    
				}
	     salir=1;
	     break;
		   default:
	     printf("\n\n\t\t\vELECCION INCORRECTA, PULSAR 1,2,3 o 0\n\n");break;
        }
    }while(salir!=1);
    return 0; 
}           
