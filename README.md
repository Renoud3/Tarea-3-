# Tarea-3-

---------- Readme de la tarea 2 ----------

Integrantes del equipo:

Pablo Julio
Fernando Melillan
Nicolás Oñate
Sebastian Yañez

Opciones que funcionan correctamente:

2.- Ciudad mas cercana
3.- Crear ruta

Opciones que no funcionan correctamente:

1.- Agregar ciudad
4.- Ruta mas corta entre ciudades
5.- Mejor circuito


Datos adicionales de la tarea:

En la opción 2, si se ingresa una ciudad que no existe en el archivo, además de mostrar el mensaje "no se encontro la ciudad", se mostrarán datos basura porque la función intentará buscar la ciuadad mas cercana a una que no existe.

En la opción 3, si se ingresa una ciudad que no existe en el archivo, además de mostrar el mensaje "no se encontro la ciudad", se mostrará una ruta de 0 km que conforma esta ciudad inexistente.

Si se inserta una(s) ciudad(es) que si existe(n), pero luego se inserta una que no existe, se imprimirá el mensaje "no se encontro la ciudad" y una ruta de 0 km conformada por la(s) ciudad(es) existentes y por la que no existe.

Si se inserta una ciudad existente, pero luego se inserta una ciudad que no es adyacente, la distancia entre estas 2 ciuades no se tomará en cuenta en la ruta final, debido a que la distancia entre estas 2 ciuades que no son adyacentes es 0. Por lo tanto, es posible hacer una ruta que mezcla ciudades que son adyacentes con otras que no lo son.


Problemas de la tarea:

A pesar de que se hizo el intento, la opción 1 no funciona correctamente, ya que se cae y no se insertan las ciudades con sus distancias entre si de manera correcta.
Sospechamos que es debido a una mala implementación de la función crearCiudad que usó para la opción 1.

Las opciones 4 y 5 no fueron realizadas. 
