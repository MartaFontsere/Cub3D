/* ************************************************************************** */
/*                                                                            */
/*                            Archivo para los                                */
/*                           comentarios de Yaja                              */
/*                                                                            */
/*                                                                            */
/* ************************************************************************** */

10/01 -	El makefile ya funciona salvo por la MLX, hay que mirar como colocar
		bien la libreria. El resto ok
15/01 -	Makefile no imprime los Dirs cuando fclean. Parsing ya comprueba bien la
		extension del mapa
16/01 -	Empezando el parsing, estamos comprobando los chars que tenemos en el
		raw_map sean los pedidos por el subject. Y saliendo en caso de error.
		(falg1)
17/01 -	Debo hacer una lectura de cada linea del mapa spliteado en el que guarde
		la longitud de j y hacer una comparacion de i con i - 1, para ver si la
		linea actual es > o <, y asi decir que esta es la mayor y que el mapa en
		[j] tendra esa anchura y lo mismo con el mapa el [i], para saber su
		altura real. Y que los sitios donde no encuentre ningun char, lo rellene
		con espacio hasta convertir todo el mapa en rectangular.

		Hemos acordado cambiar los espacios vacios por una R, para indicar que el
		mapa contiene un obstaculo, y por lo tanto el player se ha de chocar
		(segun subject: UPTOYOU)
20/01 -	Hay que reducir las lineas en complete map. Ahora procedemos a agregar
		tantos chars como larga sea la linea y luego hacemos el rawline
21/01 -	He quitado un par de lineas de CMake que se mostraban al hacer make
		fd(Findglfw3.cmake y CMakeLists.txt)
24/01 -	Ya tenemos la rawline, el mapa spliteado y rellenado con 'R's. Tengo el
		fsanitize comentado por el leak del split. Lo miro mas adelante.
		Procedo a completar el mapa con los chars que me interesan