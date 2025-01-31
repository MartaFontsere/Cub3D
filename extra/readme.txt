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

27/01 -	Quiero hacer una lectura del FD y asignar en las estructuras, el path
		correspondiente a cada una. Asi como tambien indicar, desde que punto
		empieza el mapa, para asi pasar esa len y sacar la matriz desde X.
		No hago push porque no quiero sobreescribir el progeso hasta ahora.

29/01 -	He agregado una flag para saber si hay error en cuanto a shader, y pondre
		para cuando el mapa haya iniciado
31/01 -	Tenemos ya parseados los paths y colores. Me queda modificar que, cuando
		un color tengo error, no siga adelante con el resto de lecturas
		Y en cuanto a los colores, ya sabemos que solo hay 3, los rangos de estos
		- Ya casi tenemos completado la primera parte de la lectura del fd, todos los
		paths estan ok, y los colores tambien.
		- IMP!! Me queda codear la forma de evitar que intente sobreescribir
		un param que ya este puesto. Y salir de los errores de colores con el msg
		Una vez tengamos eso hecho, ya podremos hacer el merge de la matrix.(REVISAR!!!)