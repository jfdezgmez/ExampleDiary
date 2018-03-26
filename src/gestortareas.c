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


struct tm fechaactual(){
time_t t;
struct tm *tm;
t=time(NULL); //obtiene los segundos desde 1970
tm=localtime(&t);
tm->tm_mon+=1;
tm->tm_year+=1900;
return *tm;
}


//Funcion para contar los dias que quedan


int diasquefaltan(char *fechatarea){
char *ptr=NULL;//puntero auxiliar que sirve pararecorrer el string que se le pasas
ptr=fechatarea;
int diasparafinalizar=0;
struct tm fecha1;
struct tm fecha2;
//en fecha1 almacenamos la fecha actual del ordenador, llamando a la funcion fechaactual que devulve un struct tm
 fecha1 =fechaactual();
//en fecha2 introducimos la fecha introducida por l usuario:

fecha2.tm_mday=atoi(ptr); //atoi es una funcion a la que se le pasa un puntero y te devuleve el valor numerico hasta el primer caracter "no numero", pero no mofica el puntero por eso hay que sumarle 3 posiciones
ptr=ptr+3;
fecha2.tm_mon=atoi(ptr);
ptr=ptr+3;
fecha2.tm_year=atoi(ptr);
ptr=ptr+5;
fecha2.tm_hour=atoi(ptr);
ptr=ptr+3;
fecha2.tm_min=atoi(ptr);
fecha2.tm_sec=0;
//una vez que tenemos las dos fechas, ultilizamos la siguiente funcion para calcular los segundos entre ellas:
diasparafinalizar=difftime(mktime(&fecha2),mktime(&fecha1));
return diasparafinalizar/60/60/24;
}


//funcion crear tarea


Tarea *crear_tarea(char usuario[],Tarea *aux4,Tarea **ini, int *cambio){

  
  //variables temporales para trabajar con mensajes de error

  
  char destar[50],plazotar[17],dependenciatar[20];
  int prioridadtar;

    //declaraciones principales
    
    Tarea *aux5;
    Tarea *auxtmp;
    char cadaux2[10];
int asigtmp;
 char center;

 
//codigo

 
aux5=malloc(sizeof(Tarea));

if(aux4==NULL){//si no hay ninguna tarea antes, es la primera en crearse
  aux5->asignador=1;
  aux5->sig=NULL;
 }
 else{
   aux4->sig=aux5;
 }

 printf("\n\t\vIntroduzca el tipo de tarea (simple/con_plazo):\n");
 scanf(" %[^\n]",cadaux2);

     if (strcmp(cadaux2,"simple")==0) {
       printf("\n\tIntroducir descripcion de la tarea: ");
       scanf(" %[^\n]",destar);
       printf("\n\tIntroducir la prioridad: ");
       scanf(" %i",&prioridadtar);
       printf("\n\tIntroducir dependencias separadas por comas(0 si no se establecen dependencias): ");
        scanf(" %s",dependenciatar);
	 }
     else{ if(strcmp(cadaux2,"con_plazo")==0){
    printf("\n\tIntroducir plazo: (dd/mm/aa):(hh:mm)");
    scanf(" %s",plazotar);
      printf("\n\tIntroducir descripcion de la tarea: ");
      scanf(" %[^\n]",destar);
       printf("\n\tIntroducir la prioridad: ");
       scanf(" %i",&prioridadtar);
       printf("\n\tIntroducir dependencias (0 si no se establecen dependencias): ");
       scanf(" %s",dependenciatar);
     }

     else{
   	printf("Por favor introduzca un tipo de tarea valido.");
   	return aux4; //modificar
   }
     }
     
///////////////////////////zona de aviso de errores//////////////////////////

  //aviso de tarea ya existente
     
       auxtmp=*ini;
       while(auxtmp!=NULL){
	 if( strcmp(auxtmp->descripcion,destar)==0){
	   printf("\nLa tarea ya existe\n");
	   do{printf("\nPulse ENTER para volver al menu principal\n");
	     while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
	   free(aux5);
	   aux5=NULL;
	   return aux4;//modificar
	 }
	 else{
	   auxtmp=auxtmp->sig;
	 }
       }

      
       //aviso plazo menor a 7 dias:

       
       if(strcmp(cadaux2,"con_plazo")==0){
	 int k=diasquefaltan(plazotar); //Llama a la funcion diasquefaltan para calcular los dias que quedan
	 if(k<=7){
	   printf("\n\t\vPlazo menor a 7 dias\n\t\vIntroduzca una fecha valida\n");
	  do{printf("\nPulse ENTER para volver al menu principal\n");
	    while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
	  free(aux5);
	  aux5=NULL;
	  return aux4; //modificar
	 }
       }

                 
       //aviso para comprobar si existen las tareas indicadas en la dependencia 

       int dependenciatar_2;
       dependenciatar_2=atoi(dependenciatar);
       
       if(dependenciatar_2!=0){      

       char cadaux4[20];
       char *temp;
       int tmp5;
       Tarea *aux8;
       strcpy(cadaux4,dependenciatar);
       temp=strtok(cadaux4,",");//coje hasta la primera coma
       tmp5=atoi(temp);
       aux8=*ini;
       
	      while(aux8->asignador!=tmp5){
       aux8=aux8->sig;
     if(aux8==NULL){
       printf("\n\t\vLa tarea indicada en la dependencia no es valida o no existe");
      do{printf("\nPulse ENTER para volver al menu principal\n");
	while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
      return aux4; //cambiar
     }
     }
     aux8=*ini;
     while((temp=strtok(NULL,","))!=NULL){ //coje el resto de numeros que hay entre comas a no ser que llegue al final
       tmp5=atoi(temp);
       while(aux8->asignador!=tmp5){
	 aux8=aux8->sig;
	 if(aux8==NULL){
       printf("\n\t\vLa tarea indicada en la dependencia no es valida o no existe");
       do{printf("\nPulse ENTER para volver al menu principal\n");
	 while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
       free(aux5);
       return aux4; //cambiar
	 }
       }
       }

       }
    

       //zona del codigo de copia en el nuevo struct
       

     if(aux4==NULL){
	 *ini=aux5;
       }
      strcpy(aux5->tipo,cadaux2);
      strcpy(aux5->descripcion,destar);
      strcpy(aux5->usuario,usuario);
      aux5->prioridad=prioridadtar;
      strcpy(aux5->estado,"pendiente");
      if(strcmp(cadaux2,"simple")==0){
	strcpy(aux5->plazo,"-");
      }
      else{if(strcmp(cadaux2,"con_plazo")==0){
	  strcpy(aux5->plazo,plazotar);
	}
	}

      int dependenciatar_3;
      dependenciatar_3=atoi(dependenciatar);
      
     if(dependenciatar_3==0){
	  strcpy(aux5->dependencia,"-");//si no existen dependencias se tiene que poer un guion
	}
	else{
	strcpy(aux5->dependencia,dependenciatar);
	}
	aux5->sig=NULL;
if(aux4==NULL){
asigtmp=1;
aux5->asignador=asigtmp;}
 
       else{ if(aux4!=NULL){
asigtmp=aux4->asignador;
       aux5->asignador=asigtmp+1;
       }}
       (*cambio)=1; //indicador para la tarea salir de si se ha utilizado la funicion crear tarea
       
 return aux5; //Retorna la direccion del ultimo nodo de la lista
}



//funcion ver tarea



void ver_tarea(Tarea **ini,int ident,char usuario[]) {

  //declaraciones principales
  
  Tarea *aux6;
  int diasfinalizar;

    //declaraciones para dependencias indirectas
  
  char cadaux10[20];
  char *temp;
  int tmp10;
  Tarea *aux10,*aux11;
  char center;
  
  //codigo
  
    aux6=*ini;

  while(aux6->asignador!=ident){ 
    aux6=aux6->sig;
     if(aux6==NULL){
    printf("\n\tTarea no existente\n");
    do{printf("\nPulse ENTER para volver al menu principal\n");
     while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
	     return; //modificar
	     }
  }
  if(strcmp(aux6->usuario,usuario)!=0){
    printf("\n\tOperacion no permitida sobre esta tarea\n");
   do{printf("\nPulse ENTER para volver al menu principal\n");
     while(getchar()!='\n'){};
	     center=getchar();}while(center!= '\n');
    return;
  }
     
 if(strcmp(aux6->tipo,"simple")==0){
     diasfinalizar=0;
}
   
  
if((aux6->asignador=ident) && strcmp(aux6->usuario,usuario)==0){
         printf("\tDescripcion: %s\n",aux6->descripcion);
	 printf("\tPrioridad: %i\n",aux6->prioridad);
	 printf("\tEstado: %s\n",aux6->estado);
	 printf("\tTipo: %s\n",aux6->tipo);
	 printf("\tPlazo: %s\n",aux6->plazo);
		
if(strcmp(aux6->tipo,"con_plazo")==0){
diasfinalizar= diasquefaltan(aux6->plazo);
if(diasfinalizar>0){
printf("\tDias para terminar la tarea: %i \n",diasfinalizar);
}
}
	 printf("\n\tTareas que dependen de la tarea: \n");
	 printf("\t\vDirectamente: %s ",aux6->dependencia);
	 if(strcmp(aux6->dependencia,"-")==0){
	   printf("\n\t\vIndirectamente: - ");}
	 else{printf("\n\t\vIndirectamente:");
	 strcpy(cadaux10,aux6->dependencia);
aux10=*ini;
 
   temp=strtok(cadaux10,",");
   tmp10=atoi(temp);
     while(aux10->asignador != tmp10){
	    aux10=aux10->sig;
	     }
   if(aux10->asignador==tmp10){
	 printf(" %s",aux10->dependencia);
	 }
   while((temp=strtok(NULL,","))!=NULL){
       tmp10=atoi(temp);
       while(aux10->asignador != tmp10){
	 aux10=aux10->sig;
       }
       if(aux10->asignador==tmp10){
	  printf(",%s",aux10->dependencia);
	 }
       else{printf("-");
       }
     }
	 }
 }

printf("\nTareas dependientes directamente de la tarea: ");

 
//Tareas dependientes directamente de la tarea

 
aux11=*ini;

while(aux11!=NULL){
strcpy(cadaux10,aux11->dependencia);
temp=strtok(cadaux10,",");
tmp10=atoi(temp);
if(tmp10==ident){
printf(" %i",aux11->asignador);
}
 while((temp=strtok(NULL,","))!=NULL){
   tmp10=atoi(temp);
   if(tmp10==ident){
     printf(" %i",aux11->asignador);}
 }
aux11=aux11->sig;
}

do{printf("\nPulse ENTER para volver al menu principal\n");
  while(getchar()!='\n'){};
  center=getchar();}while(center!= '\n');
	   
  
  return;

}

//funcion cargar las tareas al principio del programa


Tarea *cargarTareas(Tarea **ini){
  
  //declaraciones principales

   Tarea *fin=NULL;
   Tarea *aux2, *aux3;
  char cadaux[50];
  FILE *archivo;
  Tarea *auxiliar;

  //codigo
  
  if((archivo=fopen("tareas.txt","r"))==NULL){
    return NULL;
  }
  else{
  rewind(archivo);
  for(;;){
    if(feof(archivo)){
	break;
      }
    if(*ini==NULL){
      rewind(archivo);
      auxiliar=malloc(sizeof(Tarea));
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->tipo, cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      auxiliar->asignador=atoi(cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->descripcion,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->usuario,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      auxiliar->prioridad=atoi(cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->estado,cadaux);
       fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->plazo,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->dependencia,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      auxiliar->sig=NULL;
      fin=auxiliar;
      aux2=fin;
      *ini=auxiliar;   
    }
    else{
      aux3=malloc(sizeof(Tarea));
      fin->sig=aux3;
      aux3->sig=NULL;
      auxiliar=aux3;
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->tipo, cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      auxiliar->asignador=atoi(cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->descripcion,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->usuario,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      auxiliar->prioridad=atoi(cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->estado,cadaux);
       fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->plazo,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      strcpy(auxiliar->dependencia,cadaux);
      fscanf(archivo," %[^\n]",cadaux);
      fin=aux3;
      }
   }
   fin->sig=NULL;
   fclose(archivo);
    }
  return fin;
  }  


//funcion ver la lista completa


void ver_lista(Tarea **ini,char usuario[]){

  
  //declaraciones principales

  
  Tarea *aux7;
  int eleccion,eleccion_2,dias;
  char cadaux3[50];
  FILE *arch2;
  int salir=0;

  //codigo

  aux7=*ini;
 
  do{ printf("\n\t1)Pendientes");
  printf("\n\t2)Terminadas");
  printf("\n\t3)Todas");
  printf("\n\t0)Cancelar\n");
printf("\n\tTipo de tareas a presentar?:\n");
 scanf(" %i",&eleccion);

 switch(eleccion){
   case 1:
   printf("\n\t1)Por pantalla\n\t");
   printf("\n\t2)A fichero\n\t");
   printf("\n\t0)Cancelar\n\t");
   printf("\n\tPresentacion del resultado?:\n\t");
   scanf(" %i",&eleccion_2);

switch(eleccion_2){

   case 1:
     while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if(dias>0 &&(strcmp(aux7->usuario,usuario)==0)){
       strcpy(cadaux3,(aux7->tipo));
       printf("%s\n",cadaux3);
 printf("%i\n",(aux7->asignador));
 strcpy(cadaux3,aux7->descripcion);
       printf("%s\n",cadaux3);
       printf("%i\n",aux7->prioridad);
       strcpy(cadaux3,(aux7->estado));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->plazo));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->dependencia));
       printf("%s\n",cadaux3);
        if(aux7->sig!=NULL){
	  printf("*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     
     printf("\n\t\vPulse una tecla para continuar\n\t");
while(getchar()!='\n'){};
 getchar();
     salir=1;
     break;

     
     case 2:
       arch2=fopen("Pendientes.txt","w");
     while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if((dias>0) && (strcmp(aux7->usuario,usuario)==0)){ 
     	 fprintf(arch2,"%s\n",(aux7->tipo));
	 fprintf(arch2,"%i\n",(aux7->asignador));
	 fprintf(arch2,"%s\n",(aux7->descripcion));
	 fprintf(arch2,"%i\n",(aux7->prioridad));
	 fprintf(arch2,"%s\n",(aux7->estado));
	 fprintf(arch2,"%s\n",(aux7->plazo));
	 fprintf(arch2,"%s\n",(aux7->dependencia));
        if(aux7->sig!=NULL){
	  fprintf(arch2,"*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     fclose(arch2);
          printf("\n\t\vPulse una tecla para continuar\n\t");
fflush(stdin);
	  getchar();
     salir=1;
     
     break;

     case 0:
     break;
     }     
   break;

   case 2:
   printf("\n\t1)Por pantalla\n\t");
   printf("\n\t2)A fichero\n\t");
   printf("\n\t0)Cancelar\n\t");
   printf("\n\tPresentacion del resultado?:\n\t");
   
   scanf(" %i",&eleccion_2);

   switch(eleccion_2){

   case 1:
     while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if((dias<=0) &&(strcmp(aux7->usuario,usuario)==0) && (strcmp(aux7->tipo,"con_plazo")==0)){
       strcpy(cadaux3,(aux7->tipo));
       printf("%s\n",cadaux3);
 printf("%i\n",(aux7->asignador));
 strcpy(cadaux3,aux7->descripcion);
       printf("%s\n",cadaux3);
       printf("%i\n",aux7->prioridad);
       strcpy(cadaux3,(aux7->estado));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->plazo));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->dependencia));
       printf("%s\n",cadaux3);
       if(aux7->sig!=NULL){
	  printf("*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     
     printf("\n\t\vPulse una tecla para continuar\n\t");
while(getchar()!='\n'){};
 getchar();
     salir=1;
     break;

   case 2:
     arch2=fopen("Terminadas.txt","w");
     while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if((dias<=0) && (strcmp(aux7->usuario,usuario)==0) && (strcmp(aux7->tipo,"con_plazo")==0)){ 
     	 fprintf(arch2,"%s\n",(aux7->tipo));
	 fprintf(arch2,"%i\n",(aux7->asignador));
	 fprintf(arch2,"%s\n",(aux7->descripcion));
	 fprintf(arch2,"%i\n",(aux7->prioridad));
	 fprintf(arch2,"%s\n",(aux7->estado));
	 fprintf(arch2,"%s\n",(aux7->plazo));
	 fprintf(arch2,"%s\n",(aux7->dependencia));
        if(aux7->sig!=NULL){
	  fprintf(arch2,"*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     fclose(arch2);
          printf("\n\t\vPulse una tecla para continuar\n\t");
fflush(stdin);
	  getchar();
     salir=1;
     break;

   case 0:
     break;
}     
   break;

 case 3:
   printf("\n\t1)Por pantalla\n\t");
   printf("\n\t2)A fichero\n\t");
   printf("\n\t0)Cancelar\n\t");
   printf("\n\tÂ¿Presentacion del resultado?:\n\t");
   
   scanf(" %i",&eleccion_2);

   switch(eleccion_2){
     case 1:
     while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if(strcmp(aux7->usuario,usuario)==0){
       strcpy(cadaux3,(aux7->tipo));
       printf("%s\n",cadaux3);
 printf("%i\n",(aux7->asignador));
 strcpy(cadaux3,aux7->descripcion);
       printf("%s\n",cadaux3);
       printf("%i\n",aux7->prioridad);
       strcpy(cadaux3,(aux7->estado));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->plazo));
       printf("%s\n",cadaux3);
       strcpy(cadaux3,(aux7->dependencia));
       printf("%s\n",cadaux3);
       if(aux7->sig!=NULL){
	  printf("*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     
     printf("\n\t\vPulse una tecla para continuar\n\t");
while(getchar()!='\n'){};
 getchar();
     salir=1;
     break;

     case 2:
     arch2=fopen("Todas.txt","w");
       while(aux7!=NULL){
       dias=diasquefaltan(aux7->plazo);
       if(strcmp(aux7->usuario,usuario)==0){ 
     	 fprintf(arch2,"%s\n",(aux7->tipo));
	 fprintf(arch2,"%i\n",(aux7->asignador));
	 fprintf(arch2,"%s\n",(aux7->descripcion));
	 fprintf(arch2,"%i\n",(aux7->prioridad));
	 fprintf(arch2,"%s\n",(aux7->estado));
	 fprintf(arch2,"%s\n",(aux7->plazo));
	 fprintf(arch2,"%s\n",(aux7->dependencia));
      if(aux7->sig!=NULL){
	  fprintf(arch2,"*\n");
	}
       aux7=aux7->sig;
       }
       else{aux7=aux7->sig;
       }
     }
     fclose(arch2);
          printf("\n\t\vPulse una tecla para continuar\n\t");
fflush(stdin);
	  getchar();
     salir=1;

     break;

     case 0:
     break;
}
   break;
 case 0:
   salir=1;
   break;
   default:
printf("\n\tSeleccione una opcion valida o pulse 0 para cancelar y salir al menu\n");
 }
}while(salir!=1);
}


//funcion para almacenar la nueva lista en el fichero de texto


int almacenar_lista_fichero(Tarea **ini){
	Tarea *aux; //puntero para recorrer los nodos de la lista
	FILE *pf;
	pf=fopen("tareas.txt","w");
	if(*ini==NULL){ //Si la lista esta vacia se sale
		return 0;
	}
	aux=*ini;
	while(aux!=NULL){
	fprintf(pf,"%s\n",(aux->tipo));
        fprintf(pf,"%i\n",(aux->asignador));
        fprintf(pf,"%s\n",(aux->descripcion));
        fprintf(pf,"%s\n",(aux->usuario));
        fprintf(pf,"%i\n",(aux->prioridad));
        fprintf(pf,"%s\n",(aux->estado));
        fprintf(pf,"%s\n",(aux->plazo));
        fprintf(pf,"%s\n",(aux->dependencia));
	if(aux->sig!=NULL){
	  fprintf(pf,"*\n");
	}
        aux=aux->sig;	
	}	
	return 0;
}



//funcion para liberar la memoria dinamica utilizada en el programa


void liberar_memoria(Tarea **ini){
	Tarea *aux,*aux1;
	aux1=*ini;
	aux=*ini;
	while(aux){         
		if(aux->sig==NULL){
			free(aux);
			aux=NULL;
		}
		else{
			aux=aux->sig;
			aux1->sig=NULL;
			free(aux1);
			aux1=aux;
		}
	}
	return;	
}
