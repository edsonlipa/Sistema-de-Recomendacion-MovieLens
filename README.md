# Sistema-de-Recomendacion-MovieLens
## Alamcenamiento y levantamiento de la base de datos
   Nosotos Logramos Cargar La base de datos de movielens de 27 millones, en 110 segundos y ocupando un espacio en memoria ram de 2.1 Gb 
## Implementacion del KNN (Proceso)
  Estamos utlizando las Distancias Vistas en clase:
  - Distancia Ecludeana
  - Distancia de Manhattan
  - Correlacion de Pearson
  - Distancia del Coseno
  para obtener los Knn obtenemos las distancias de un usuario dado con cada uno de los usuarios existentes que tengan recomendaciones. 
## Lenguaje de Programacion + Librerias
Desarrollamos el Programa en c++, junto con la libreria OpenMP para paralelizar el algoritmo KNN
## Proceso del Sistema de Recomendacion
1. Primero cargamos la data en un map de map esto nos demora 110 seg aproximadamente, y ocpupamos 2.1 GB s 
1. Despues dado un usuario dado y un k para los primero k usuarios
1. en este punto podemos hacer una recomendacion de pelicualas al usario o dado una pelicula podemos dar una proyeccion de la puntuacion de esta pelicula segun los usarios compatibles que ya hayan visto dicha pelicula.
## Pruebas
### Input 
   En el archivo input podemos ver los casos de prueba separados por espacios
   - El primer codigo, el el codigo del usuario
   - Seguido por la distancia >pearson coseno Eclideana o Manhattan
   - Enseguida los k usuarios (para el algoritmo de knn)
   - por ultimo las  n peliculas a recomendar (si no se tiene suficientes peliculas se recomiendas todas las que resulten)
#### Ejemplo
      16006
      -1 5 10
## informe
