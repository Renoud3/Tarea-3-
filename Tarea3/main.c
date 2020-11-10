#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "list.h"
#include <string.h>

typedef struct Ciudad Ciudad;
typedef struct Ciudad{
  char nombre[30];
  HashMap* distancias;
  int dist;
  Ciudad* prev;
}Ciudad;
void importarArchivo(HashMap * ciudades, FILE * archivo);
void agregaInfo (HashMap* ciudades, char* ciudad1, char* ciudad2, int distancia);
Ciudad* crearCiudad(char * ciudad);
void ciudadCercana(HashMap * ciudades);
void crearRuta(HashMap * ciudades);
void rutaMasCorta(HashMap * ciudades, char* ciudad1, char* ciudad2);
void mejorCircuito(HashMap * ciudades, char* ciudad1, char* ciudad2, char* ciudad3);
void mostrarCiudades(HashMap * ciudades);

int main()
{
    HashMap * ciudades = createMap(100);
    FILE * archivo = fopen("distances.txt","r");
    char* ciudad1 = (char *)malloc(50*sizeof(char));
	char* ciudad2 = (char *)malloc(50*sizeof(char));
    char* ciudad3 = (char *)malloc(50*sizeof(char));
    int distancia;
	int op = 0;
	importarArchivo(ciudades, archivo);

	while (op <= 6) {
		printf("1.- Agregar ciudad\n");//funcionando
        printf("2.- Ciudad mas cercana\n");//funcionando
        printf("3.- Crear ruta\n");//funcionando
        printf("4.- Ruta mas corta entre ciudades\n");
        printf("5.- Mejor circuito\n");
        printf("Indica la opcion: ");
        scanf("%d", &op);
        fflush(stdin);

		switch (op) {
			case 1:
                printf("Ingresa el nombre de la primera ciudad\n");
                gets(ciudad1);
                printf("Ingresa el nombre de la segunda ciudad\n");
                gets(ciudad2);
                printf("Ingresa la distancia entre estas ciudades\n");
                scanf("%d",&distancia);
                agregaInfo(ciudades,ciudad1,ciudad2,distancia);
                break;

			case 2:
                ciudadCercana(ciudades);
                break;

			case 3:
                crearRuta(ciudades);
                break;

			case 4:
                printf("Ingresa el nombre de la primera ciudad\n");
                gets(ciudad1);
                //strdup(ciudad1);
                printf("Ingresa el nombre de la segunda ciudad\n");
                gets(ciudad2);
                //strdup(ciudad2);
				rutaMasCorta(ciudades,ciudad1,ciudad2);
				break;

			case 5:
                printf("Ingresa el nombre de la primera ciudad\n");
                gets(ciudad1);
                //strdup(ciudad1);
                printf("Ingresa el nombre de la segunda ciudad\n");
                gets(ciudad2);
                //strdup(ciudad2);
                printf("Ingresa el nombre de la tercera ciudad\n");
                gets(ciudad3);
                //strdup(ciudad3);
				mejorCircuito(ciudades,ciudad1,ciudad2,ciudad3);
				break;

			case 6:
                return 0;
		}
	}
    return 0;
}


void agregaInfo (HashMap* ciudades, char* ciudad1, char* ciudad2, int distancia){
	Ciudad* c1 = searchMap(ciudades,ciudad1);
	Ciudad* c2 = searchMap(ciudades,ciudad2);//se busca si ambas ciudades ingresadas se encuentran en el mapa

	if (c1 == NULL) { //si no se encuentran, entonces es una nueva ciudad, por lo que habra que crearla y luego insertarla en el mapa
		c1 = crearCiudad(ciudad1);
		insertMap(ciudades,ciudad1,c1);
	}

	if (c2 == NULL) { //se repite el procedimiento con la segunda ciudad
		c2 = crearCiudad(ciudad2);
		insertMap(ciudades,ciudad2,c2);
	}

	insertMap(c1 -> distancias,ciudad2,&distancia); //se inserta en el mapa ambas ciudades con la distancia entre ellas
	insertMap(c2 -> distancias,ciudad1,&distancia);

}

Ciudad* crearCiudad(char* ciudad){
  Ciudad * nuevo = (Ciudad *) malloc (sizeof(Ciudad)); //se hace un malloc para agregar la ciudad nueva
  strcpy(nuevo -> nombre, ciudad); //se copia el nombre de la ciudad ingresada en la funcion y se le asigna como el nombre de la nueva ciudad
  return nuevo; //se retorna la ciudad creada
}

void ciudadCercana(HashMap * ciudades) {
  char * nombre = (char *)malloc(50* sizeof(char));
  Ciudad * city;
  Pair * info;
  int lower = 1000000;
  char * namelower;
  int chartoint;
    printf("------------------------\n");
  printf("Ingresa el nombre de la ciudad: \n");
  gets(nombre); //se inserta el nombre de una ciudad en la funcion
  city = searchMap(ciudades, nombre); //se busca si la ciudad ingresada se encuentra en el mapa
  if(city != NULL){ //se pregunta si la ciudad fue encontrada
        info = firstMap(city->distancias);
    while(info != NULL){
        printf("Ciudad cercana encontrada: %s a %s KM de distancia \n", info->key,info->value); //si la ciudad fue encontrada, se imprime en pantalla todas las ciudades adyacentes a la ingresada
        chartoint = atoi(info->value);
        if(chartoint<lower){
            namelower = info->key;
            lower = chartoint;
        }
        info = nextMap(city->distancias);
    }
  }
  else if(city == NULL){
    printf("no se encontro la ciudad\n"); //si la ciudad no fue encontrada en el mapa, se imprime este mensaje
  }
    printf("Ciudad mas cercana: %s a %d KM\n",namelower,lower); //imprime la ciudad mas cercana a la ciudad ingresada
    printf("------------------------\n");


}

void crearRuta(HashMap * ciudades){
    char * nombre = (char *)malloc(50* sizeof(char));
    Ciudad * city;
    Pair * info;
    int opcion = 0;
    char * ruta = (char *)malloc(50 * sizeof(char));
    char * distance = (char *)malloc(50 * sizeof(char));
    int count = 0;
    char * cities[50];
    int i = 0;
    printf("------------------------\n");
    printf("Ingresa el nombre de la ciudad: \n");
    gets(nombre); //se inserta el nombre de una ciudad en la funcion
    fflush(stdin);
    cities[i] = _strdup(nombre);
    while(opcion != 1){

        city = searchMap(ciudades, nombre); //se busca si la ciudad ingresada se encuentra en el mapa
        if (city == NULL) {
            printf("no se encontro la ciudad\n"); //si no se encuentra, se imprime este mensaje y se termina la funcion
            break;
        }
        info = firstMap(city->distancias);
        while(info != NULL){ //si la ciudad fue encontrada, la funcion sigue
            printf("Ciudad cercana encontrada: %s a %s KM de distancia \n", info->key,info->value); //se imprimen las ciudades adyacentes a la ingresada
            info = nextMap(city->distancias);

    }
        printf("Escoge una ciudad para establecer la ruta: \n"); //se escoge una de las ciudades adyacentes para seguir la ruta
        fflush(stdin);
        gets(ruta); //se escribe la ciudad deseada
i++;
        cities[i]=(char *)malloc(50*sizeof(char));
        strcpy(cities[i],ruta);
        printf("-Ciudad guardada nombre %s\n",cities[i]); //se imprime este mensaje indicando la ciudad seleccionada por elusuario
        distance = searchMap(city->distancias, ruta);
        nombre = ruta;
        count = count + atoi(distance); //se suman las distancias entre las ciuudades
        printf("------------------------\n");
        printf("0 PARA CONTINUAR CON LA RUTA | 1 PARA FINALIZAR: \n"); //se pregunta si se quiere continuar con la ruta o se desea finalizar
        fflush(stdin);
        scanf("%d",&opcion);
    }
    printf("Ciudades en la ruta: \n"); //se imprimen las ciudades que conforman esta ruta
    for(int j=0;j<=i;j++){
        printf("%d .- %s \n",j,cities[j]);
    }
    printf("KM Totales de la ruta: %d\n",count); //se imprimen los kms totales de la ruta, desde la ciudad de inicio hasta la ciudad de llegada
    printf("------------------------\n");
}

void rutaMasCorta(HashMap * ciudades, char* ciudad1, char* ciudad2){

}

void mejorCircuito(HashMap * ciudades, char* ciudad1, char* ciudad2, char* ciudad3){

}
void importarArchivo(HashMap * ciudades, FILE * archivo){
    char * linea = (char *)malloc(50*sizeof(char));//usada para leer linea a linea el fichero
    char * datos[50];//usado para guardar las palabras encontradas en linea y separarlas
    char  * palabra = (char *)malloc(50*sizeof(char));
    char * token = (char *)malloc(50*sizeof(char));
    Ciudad * ciudad1;
    Ciudad * ciudad2;
    char * distancia = (char*)malloc(50*sizeof(char));
    const char espacio [2] = " ";
    int count = 0;//usado para contar cuantas lineas guarda
    while(fgets(linea, 99, archivo)!= NULL){//lee linea a linea
            count++;//aumenta contador
        token = strtok(linea, espacio);//separa la linea primera linea hasta encontrar el primer espacio
        int i = 0;//iterador para guardar en el array de datos[0]=1ra ciudad / datos[1]=2da ciudad / datos[2]=distancia
        while(token != NULL){//lo sigue haciendo hasta que se acabe la linea
            datos[i] = _strdup(token);//guarda la palabra encontrada en el array
            token = strtok(NULL, espacio);
            i++;
        }
        if(searchMap(ciudades, datos[0])==NULL){//verifica que no exista la ciudad en el mapa de Ciudades
            ciudad1 = crearCiudad(datos[0]);//crea la ciudad
            ciudad1->distancias = createMap(100);
            insertMap(ciudad1->distancias, datos[1],datos[2]);//guarda la 2da ciudad de la linea en el mapa de la ciudad
            insertMap(ciudades, ciudad1->nombre, ciudad1);
        }
        else if(searchMap(ciudades, datos[0])!= NULL){//en caso de existir la ciudad
            ciudad1 = searchMap(ciudades, datos[0]);
            if(searchMap(ciudad1->distancias, datos[1])==NULL){//verifica que la 2da ciudad de la linea se encuentre en el mapa de distancias de la ciudad
                insertMap(ciudad1->distancias, datos[1],datos[2]);//en caso de que no, guarda la ciudad
            }
        }
        if(searchMap(ciudades, datos[1])==NULL){
            ciudad2 = crearCiudad(datos[1]);
            ciudad2->distancias = createMap(100);
            insertMap(ciudad2->distancias, datos[0],datos[2]);
            insertMap(ciudades, ciudad2->nombre, ciudad2);
        }
        else if(searchMap(ciudades, datos[1])!= NULL){
            ciudad2 = searchMap(ciudades, datos[1]);
            if(searchMap(ciudad2->distancias, datos[0])==NULL){
                insertMap(ciudad2->distancias, datos[0], datos[2]);
            }
        }
    }
}
/*char palabrita[80]= "esto es una prueba para cortar lineas";
    char * palabra;
    const char breakin[2] = " ";
    printf("palabra %s", palabrita);
    palabra = strtok(palabrita, breakin);
    while(palabra != NULL){
        printf("wea encontrada: %s\n",palabra);
        palabra = strtok(NULL, breakin);
    }
    */

void mostrarCiudades(HashMap * ciudades){//testing
    //Ciudad * recorrido = firstMap(ciudades);
    Pair * recorr = firstMap(ciudades);
    char buscador[30];
        while(recorr!=NULL){
                char * aux = recorr->key;
            printf("ciudad encontrada de nombre %s\n", aux);
            recorr = nextMap(ciudades);
        }

}
