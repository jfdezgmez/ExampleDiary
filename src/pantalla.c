#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//funciones de la pantalla, es decir el menu principal

int presentacion(){
  int X;
       for (X=0; X<5; X++){
         if (X != 2){printf("\n****************************************************************************");
         }else{
               printf("\n*********************   GESTOR DE TAREAS DE UNA AGENDA  ********************");    
               }   }
       return 0;
}
int menu(){
  int oper;
         printf("\n\t\t\t\v1) Crear tarea");
         printf("\n\t\t\t\v2) Ver tarea");
         printf("\n\t\t\t\v3) Ver lista de tareas");
         printf("\n\t\t\t\v0) Salir");
         printf("\n\t\t\t\v¿Siguiente operacion?");
	 while(!scanf(" %i",&oper)){
	   getchar();
	   return 4;
	 }
	 return oper;
}

int menu_salida(){
  int oper;
 	system("clear");
 	printf("\n\t1)Guardar cambios y salir");
 	printf("\n\t2)Salir sin guardar");
 	printf("\n\t0)Cancelar");
 	printf("\n\tSiguiente operacion?:");
	 while(!scanf(" %i",&oper)){
	   getchar();
	   return 4;
	 }
	 return oper;
}
