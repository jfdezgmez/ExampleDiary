#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//struct Tareas para el archivo de las subtareas


 struct tarea{
 	char tipo[20];
 	int asignador;
 	char descripcion[50];
 	char usuario[20];
 	int prioridad;
 	char estado[20];
 	char plazo[20];
 	char dependencia[20] ;
 	struct tarea *sig;
 };
 typedef struct tarea Tarea;

//Funcion para calcular la fecha actual del ordenador

struct tm fechaactual();

//Funcion para contar los dias que quedan

int diasquefaltan(char *);

//funcion crear tarea

Tarea *crear_tarea(char[20] ,Tarea *,Tarea **, int *);

//funcion ver tarea
  
  void ver_tarea(Tarea **,int,char[20]);

//funcion cargar las tareas al principio del programa

  Tarea *cargarTareas(Tarea **);
  
//funcion ver la lista completa

  void ver_lista(Tarea **,char[20]);

//funcion para liberar la memoria dinamica utilizada en el programa

  void liberar_memoria(Tarea **);

//funcion para almacenar en fichero antes de salir

int almacenar_lista_fichero(Tarea **);
