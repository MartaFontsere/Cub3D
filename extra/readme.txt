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

04/02 -	Hay que hacer mini checkeos a la hora de hacer ala lectura del fd. Revisar
		nuevamente y agregar casos que pueden pasar.

05/02 -	revisar todo nuevamente

13/02 -	Estoy en proceso de transformar las tabulaciones a espacios, para asi poder
		tener las lines bien colocadas y no haya errores en el mapa a la hora de
		hacer el mix.
		Podria ser fallo a la hora de iterar las dos strings que queremos crear.
		Los tabs en medio de la string no funcionan

19/02 -	Tengo que hacer -2 en la len del parseo, ya que esta pillando el final de
		linea y el salto de linea tambien. Si mas adelante vemos que da error,
		podemos utilizar el rawmap y sacar la matriz con un split, asi nos quitamos
		chars que pueden estar y que no vemos.
		Mirar de limpiar todo. Volver a ordenar y nuevamente revisar trozo a trozo
		el parseo, ya que los errores de tab, deberia salir en el max size, y no
		en min_chars.
20/02 -	Podemos unificar los archivos de get_map y get_map_utils

25/02 -	PARSING:
		En caso de tener \n al final del map, los "elimino", asi no las leemos.
		El contador se queda en la linea siguiente del mapa, ya que simula el '\0'
		y asi, si el fd acaba con una linea valida de mapa, no genera error.
		->check_borders()
			se comprueba la primera y ultima linea y se evitan los '0'
			saltamos los espacios de la linea actual y si el char no es 1, fuera
		->check_esp()
			comprueba que el char siguiente tanto en x && y sean 1 o espacio
		->check_zero()
			comprueba que el char siguiente tanto en x && y sean 1 o Player
		->check_player()
			tengo que poner la comprobacion de NSWE para que funcione bien. El
			resto queda como el esp y zero
26/02 -	Esta version esta con norminette, por lo que a partir de esta fecha, todo
		lo que genere sera pensado para el bonus
		-> El  Makefile actual compila los archivos *_bonus pero hay que cambiar por
		completo la forma de compilacion
		-> Estoy haciendo la puerta, mirar porque lo toma como char invalido en
		map_control. Creo que el error viene dado por el Makefile, que no lo compila
		bien. Asi que primero he de asegurarme que este funcine perfecto para continuar
		con el parsing de la puerta
27/02 -	Al hacer el "make bonus" no genera un nuevo ejecutable. QUIZA HACER UNA
		EJECUTABLE PARA EL BONUS

		-HABEMUS BONUUUUUUUUSS!!!! El gnl lo he movido a libs, asi no tenemos que
		duplicarlo en los *_bonus. Aunque podemoos crear otro dir solo para resources
07/03 -	No recuerdo porque tenia que cambiar la X && Y de mi parseo, cuando la
		info que nos interesa esta correctamente guardada en la struct y Marta
		puede trabajar sin problema desde esa info. No puedo trabajar desde aqui
		por el SO, que la minilibx no es compatible.
13/03 -	Los rays ya estan liberados, asi como tambien ya esta unificado los mensaje
		de error. El max height es 100 y width es 120. Y mis funciones del libft
		que he tocado ya estan sustituidas.
		No puedo tocar mas porque Marta ha de pasarme su ultima version y asi
		podre trabajar con los nuevos cambios.
19/03 -	En esta rama no elimina los .o del GNL, porque en la rama mandatory lo he
		incluido en el Makefile del libft.
		He cambiado unos mensajes en assign_color del mandatory, hay que revisar
		para evitar errores,
		Tal como esta, deberia funcionar correctamente la asignacion de colores o
		paths en el floor or cealing. Debo simplificar la funcion get_color_path y
		en general todo el archivo, para poder pasar norminette.
		Me quedaria limpiar el strdup que hago para que se pueda abrir bien la
		textura en el juego
20/03 -	A priori ya tendria toda la estructura del path o RGB de F y C, me queda
		limpiar la linea para que se lea correctamente. Y limpiar todo el codigo
		y unificarlo lo que he cambiado del mandatory en su rama correspondiente.