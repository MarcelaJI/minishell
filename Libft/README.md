Proyecto Libft del Cursus de 42📚

Este proyecto implica crear una librería de más de 40 funciones desde cero, muchas de las cuales son clones de funciones ya existentes. Este proyecto es una buena manera de dominar los conceptos básicos de C y, al mismo tiempo, comenzar a aprender algunos conceptos más complejos, como las listas enlazadas.

Parte 1: Funciones de la biblioteca estándar de C
Estas funciones son clones de funciones que ya existen en C. Debemos imitar su comportamiento lo más perfectamente posible.

ft_isalpha(), ft_isdigit(), ft_isalnum(), ft_isascii() y ft_isprint() son funciones directas y simples, devuelven un entero 0 o 1 dependiendo de si el carácter enviado es alfabético, numérico, alfanumérico, un valor ASCII o un valor imprimible respectivamente.

ft_strlen() es una función simple que cuenta la longitud de una cadena y devuelve esta longitud como size_t. Este es el primer uso de size_t en el curso. Este es un tipo de datos cuyo valor máximo depende del compilador. El valor máximo de size_t es el tamaño máximo de un objeto/matriz, por lo que lo usamos para medir una cadena en esta función. Se utilizará en muchas funciones en el futuro.

ft_memset() y ft_bzero() son funciones que toman un puntero void como parámetro y modifican los valores de un número especificado de bytes. Este es el primer uso de punteros void en el curso. Para recorrer el puntero void y modificar cada byte individualmente sin ningún comportamiento indefinido, lo convertimos en una cadena, que es fácil de recorrer un byte a la vez. Por supuesto, este también es el primer uso de conversión de tipos en el curso. La conversión de tipos es simplemente la acción de convertir un tipo de datos en otro tipo de datos utilizando un operador de conversión. ft_memset() recorre el puntero void hasta una longitud especificada y cambia cada valor a un int especificado. ft_bzero() no nos permite especificar el int, y simplemente cambia los valores a 0. Por lo tanto, podemos simplemente llamar a ft_memset() en ft_bzero() y dar int 0 como parámetro.

ft_memcpy() y ft_memmove() son funciones muy similares. ft_memcpy() toma dos punteros void y copia el contenido del puntero de origen al puntero de destino, hasta una longitud especificada n . El proceso de copia comienza desde el byte 0 hasta el byte n . Esto puede causar problemas si los punteros se superponen entre sí, ya que el valor copiado final puede ser incorrecto debido a que el origen en sí se modifica en el proceso de copia. ft_memmove() resuelve esto verificando primero si el puntero de destino está ubicado antes o después del puntero de origen en la memoria, y copiando hacia atrás o usando ft_memcpy() dependiendo de la posición del puntero de destino. Por supuesto, también usamos conversión de tipos en estas funciones para recorrer los punteros void.

ft_strlcpy() hace básicamente lo mismo que ft_memcpy(), pero estrictamente para cadenas. Esta función devuelve la longitud de la fuente, independientemente de si la copia se realizó correctamente o no.

ft_strlcat() concatena una cadena de origen con el final de una cadena de destino, con una longitud especificada de la cadena final. De manera similar a ft_strlcpy(), esta función devuelve la longitud de la cadena que habría creado, independientemente de si tuvo éxito o no (como en un caso en el que la longitud especificada es menor que la longitud de la cadena de origen y destino combinadas, por lo que la concatenación no se pudo completar).

ft_toupper() y ft_tolower() simplemente toman un int y verifican si su valor es igual a un valor ASCII en minúscula o mayúscula respectivamente, y luego lo convertirán a su valor en mayúscula o minúscula.

ft_strchr() y ft_strrchr() toman una cadena y un int. La cadena se recorre carácter por carácter y cada carácter se compara con el int. Si se encuentra un valor igual al int, se devuelve su dirección. ft_strchr() devuelve la primera instancia del int desde el principio de la cadena, mientras que ft_strrchr() devuelve la última instancia del mismo. Si no se encuentra el int, se devuelve null.

ft_strncmp() toma dos cadenas y compara sus valores hasta una cantidad específica de caracteres. Si se encuentra una diferencia, devuelve la diferencia entera de los primeros caracteres diferentes que encontró. Si no se encuentra ninguna diferencia, se devuelve 0.

ft_memchr() y ft_memcmp() tienen la misma funcionalidad que ft_strchr() y ft_strncmp(), pero se aplican a punteros void. Simplemente convertimos los tipos de datos a cadenas como siempre.

ft_strnstr() toma una cadena de tipo “pajar” y una cadena de tipo “aguja”. Hasta una longitud especificada, busca la cadena de tipo aguja en la cadena de tipo pajar y, si la encuentra, devuelve el puntero a su comienzo en la cadena de tipo pajar. Si no la encuentra, devuelve un valor nulo.

ft_atoi() convierte una cadena en un entero, siempre que la cadena cumpla ciertas condiciones. La cadena puede comenzar con cualquier cantidad de espacios en blanco. Solo puede contener un carácter más o menos, y el número debe colocarse inmediatamente después. Una vez que se encuentra un valor no numérico, no se convierte ningún valor posterior. Por supuesto, si se encuentra un valor no numérico antes de cualquier valor numérico, no se realiza ninguna conversión y se devuelve 0 por defecto.

ft_calloc() usa malloc() para asignar una cantidad específica de memoria y llena todo este bloque de memoria con valores 0. Para hacer esto, podemos utilizar la función ft_bzero() creada previamente. Debemos asegurarnos de que el tamaño de asignación deseado no exceda el valor máximo de size_t, o de lo contrario el valor se desbordará y asignará una cantidad incorrecta de espacio. Este es también el primer uso de malloc() en este proyecto. Debemos verificar correctamente que la asignación se haya realizado correctamente cada vez que se use malloc() para evitar errores de segmentación. Si malloc() falla, devolvemos null. Este será el caso en cada función que use malloc() en el futuro.

ft_strdup() devuelve un duplicado recién asignado de una cadena, creando la nueva cadena usando malloc() y copiando el contenido de la cadena tomada como parámetro.

Parte 2 — Funciones adicionales
Estas funciones no forman parte de la biblioteca estándar de C o existen en un formato ligeramente diferente. El archivo de tema del proyecto especifica cómo deben comportarse estas funciones.

ft_substr() toma una cadena, un índice como un entero y una longitud. Desde el índice especificado hasta la longitud especificada, el contenido de la cadena se duplica en una cadena recién asignada que se devuelve. Si el índice excede la longitud de la cadena, o la longitud especificada es 0, se devuelve una cadena en blanco (¡no es lo mismo que devolver un valor nulo!).

ft_strjoin() toma dos cadenas y las une para formar una nueva cadena asignada. Si una de las cadenas es nula, se devuelve un duplicado de la otra cadena.

ft_strtrim() toma dos cadenas. La primera cadena será “recortada” y la segunda cadena es el conjunto de caracteres que se recortarán del principio y el final de la primera cadena. La cadena recortada resultante se devuelve como una cadena recién asignada. Podemos utilizar la función ft_strchr() creada previamente en esta función. Pasamos cada carácter de la cadena a ft_strchr() junto con el conjunto de caracteres que se recortarán y, si se devuelve alguna dirección, sabemos que se ha encontrado uno de los caracteres.

ft_split() toma una cadena y un carácter. La función divide la cadena utilizando el carácter especificado como separador y devuelve una nueva matriz de cadenas que contienen las nuevas cadenas que se han dividido. Este es el primer uso de punteros/matrices dobles en el curso 42. Podemos movernos a través de una matriz de cadenas utilizando un índice, tal como lo haríamos a través de una cadena. Debemos asignar correctamente la cantidad correcta de punteros, por lo que tenemos una función que cuenta cuántas cadenas resultan de dividir la cadena dada con el carácter dado. Asignamos un puntero adicional para terminar con nulo la matriz doble, tal como lo hacemos con una cadena.

ft_itoa() toma un entero y lo convierte en una cadena recién asignada. Usamos una función que cuenta la cantidad de dígitos (incluido el símbolo menos en el caso de un número negativo) para poder asignar la cantidad correcta de espacio para la cadena.

ft_strmapi() y ft_striteri() toman una cadena y un puntero a una función. Este es el primer uso de punteros a funciones en el curso 42. Tanto ft_strmapi() como ft_striteri() aplican la función pasada a cada carácter de la cadena pasada individualmente, sin embargo ft_striteri() modifica la cadena directamente mientras que ft_strmapi() devuelve una cadena recién asignada con el resultado.

ft_putchar_fd(), ft_putstr_fd(), ft_putendl_fd() y ft_putnbr_fd() escriben un carácter, una cadena, una cadena con una nueva línea y un entero en el descriptor de archivo especificado. Este es el primer uso de descriptores de archivo en el curso. Un descriptor de archivo es un número que se utiliza para hacer referencia a un proceso en ejecución. Para los fines de este proyecto, solo es necesario comprender los descriptores de archivo de los tres flujos estándar: entrada estándar identificada por 0, salida estándar identificada por 1 y error estándar identificado por 2. Al pasar un descriptor de archivo como el primer parámetro de la función write(), podemos elegir dónde va la salida de la función write().

Parte 3 — Funciones adicionales
Estas funciones nos introducen a la creación de estructuras y listas enlazadas. Una estructura, comúnmente llamada struct, es un tipo de datos en el que podemos agrupar varias variables y declararlas todas a la vez simplemente declarando la estructura. Una estructura la proporciona el archivo subject, que debemos agregar a nuestro archivo de encabezado. Esta estructura simplemente contiene un puntero void que contiene cualquier contenido que elijamos almacenar en ella, y un puntero a una estructura “next” del mismo tipo, para crear una lista enlazada. Esta estructura proporcionada se llama t_list.

ft_lstnew() se utiliza para inicializar una lista enlazada recién asignada. Toma un puntero nulo “contenido” y establece el contenido de la lista enlazada en él. El puntero de la lista enlazada a “siguiente” se establece en nulo. Así es como creamos “nodos” para nuestra lista enlazada.

ft_lstadd_front() toma un puntero al encabezado (primer nodo) de la lista y un nodo que se agregará al frente (inicio) de la lista. El puntero “next” del nuevo nodo se establece en el encabezado actual, y el puntero al encabezado se establece en el nuevo nodo, por lo que se convierte en el nuevo encabezado de la lista.

ft_lstsize() devuelve la cantidad de nodos de una lista. Esto se logra mediante un bucle while simple que recorre los nodos de la lista hasta que el puntero “next” llega a null, contando cada nodo.

ft_lstlast() devuelve un puntero al último nodo de la lista. De manera similar a ft_lstsize(), recorremos la lista hasta que el puntero “next” del nodo actual sea nulo y devolvemos el nodo.

ft_lstadd_back() toma un puntero al principio de la lista y un nodo que se agregará al final de la lista. Podemos usar el ft_lstlast() creado previamente para obtener el último nodo de la lista y establecer su puntero “next” al nuevo nodo.

ft_lstdelone() toma un nodo y un puntero a una función llamada “del”. Suponiendo que esta función libera cualquier contenido que le pasemos, simplemente llamamos a la función y pasamos el contenido del nodo. Luego liberamos el puntero al nodo.

ft_lstclear() aplica ft_lstdelone() en una lista completa y establece el puntero al encabezado de la lista en nulo.

ft_lstiter() y ft_lstmap() toman un puntero al encabezado de la lista y un puntero a función. La función se aplica al contenido de cada nodo de la lista. ft_lstiter() modifica la lista directamente, mientras que ft_lstmap() crea una lista recién asignada con el resultado. Debido a que ft_lstmap() asigna una nueva lista, también toma un puntero a una función “del”, de modo que en caso de que la asignación de algún nodo falle, podemos usar ft_lstclear() en la nueva lista y devolver null.

Proyecto finalizado el 13 de Octubre de 2024 con bonificación (125/100).

<img width="643" alt="Captura de pantalla 2024-10-13 203220" src="https://github.com/user-attachments/assets/5a4d0174-c534-412e-8b7d-700dea1b0609">

Recursos: 

1.Makefile 

https://makefiletutorial.com/

2.Typecasting

https://www.geeksforgeeks.org/c-typecasting/

3.Memoria

https://www.geeksforgeeks.org/memory-layout-of-c-program/

https://www.cs.ru.nl/~erikpoll/sws1/slides/hic4.pdf

4.Punteros

https://www.geeksforgeeks.org/void-pointer-c-cpp/?ref=lbp/

https://www.geeksforgeeks.org/dangling-void-null-wild-pointers/

https://www.javatpoint.com/c-dereference-pointer

5.Funciones

https://pvs-studio.com/en/blog/posts/cpp/0360/

6.Tipos de datos

https://www.arm.linux.org.uk/docs/faqs/signedchar.php

7.Errores

https://www.geeksforgeeks.org/segmentation-fault-sigsegv-vs-bus-error-sigbus/

8.Descriptores de archivos

https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

9.Listas enlazadas

https://www.geeksforgeeks.org/linked-list-data-structure/










































