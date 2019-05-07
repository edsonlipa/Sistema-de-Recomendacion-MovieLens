# Sistema-de-Recomendacion-MovieLens
   **Edson Lipa y Christian Condori**
   
## Base de Datos
   Utilizamos la base de datos [Movielens](https://grouplens.org/datasets/movielens/latest/).
   Version Completa : 27,000,000 calificaciones y 1,100,000 aplicaciones de etiquetas aplicadas a 58,000 películas por 280,000 usuarios. Incluye datos del genoma de la etiqueta con 14 millones de puntuaciones de relevancia en 1.100 etiquetas. Última actualización 9/2018.

    ml-latest.zip  (tamaño: 265 MB)

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
##### Ejemplo
       16006
       -1 5 10
      283228
       -2 8 10
      30503
       2 10 10
      4598
       -1 10 10
      16006
       -2 5 10
      283228
       -2 8 10
      30503
       2 10 10
      4598
       -2 10 10
### Output
      la carga de datos a tardado: 111.889s
      START: 
      16006
      option: -1
       K : 5
      Recomendacion: 10
      KNNN
      1.00003  --  123250
      1.00001  --  136420
      1.00001  --  130242
      1.00001  --  140141
      1.00001  --  51639
      207854
      RECOM : knn size:  207854
      RECOMENDACION 10 tam 
      Dancer in the Dark (2000) punt 5
      "Equalizer punt 5
      Simple Simon (I rymden finns inga känslor) (2010) punt 4.5
      Juno (2007) punt 4.5
      "Beautiful Mind punt 4.5
      Interstellar (2014) punt 4.5
      Schindler's List (1993) punt 4
      Needful Things (1993) punt 3
      Sherlock: The Abominable Bride (2016) punt 2.5
      "Streetcar Named Desire punt 2
      la consulta a tardado: 67.2195s
      TAM: 10

   En el Archivo Output podemos encontrar la salida de los casos de prueba
      - aqui podemos observar que el usario 1006
      - con la distacia de pearson 
      - un K de 5
      - 10 como el numero de peliculas a recomendar 
      - seguido de la imprecion de los k usarios mas cercanos      
      - seguido por la recomendacion de peliculas con nombre y puntaje
   como ultimo en la penultima linea antes de la linea punteada **************
   tenemos el tiempo de consulta que varia dependiendo de cada usuario, para este ejemplo obtuvimos 67.2195s para la obtencion de los knn y la recomendacion
   **El archivo output contiene el resultado de todas las pruebas, demaciado grande para explicar mostrar cada una**
###### Conclucion
  | USUARIO |OPCION (distancia)| K | N |TIEMPO DE CONSULTA (segundos)|
| ----- | ---- | ---- | ---- | ---- |
| 16006 | -1(pearson) | 5 | 10 | 67.2195|
## informe
