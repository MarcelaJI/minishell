# 🐚 Minishell

Minishell es una shell personalizada desarrollada en C como parte del currículo de 42 Madrid
. Este proyecto busca replicar algunas de las funcionalidades esenciales de una shell UNIX como bash, permitiendo ejecutar comandos, gestionar redirecciones, pipes, señales, y más, todo desde cero y sin usar system().

---

## 📌 Objetivos del Proyecto 🎯

- Comprender en profundidad cómo funciona una shell en sistemas UNIX.

- Practicar el manejo de procesos (fork, execve, wait).

- Implementar el control de señales del sistema (ej. Ctrl+C, Ctrl+\).

- Trabajar con redirecciones de entrada/salida y pipelines.

- Desarrollar e integrar comandos internos (built-ins).

- Usar estructuras de datos eficientes como listas doblemente enlazadas para manejar tokens y variables de entorno.

---

## 🧠 Conceptos Clave Utilizados

| Concepto      | Descripción |
|---------------|-------------|
| `readline()`  | Lee la entrada del usuario y permite historial de comandos. |
| `fork()`      | Crea un proceso hijo para ejecutar comandos. |
| `execve()`    | Sustituye el proceso hijo por el programa a ejecutar. |
| `wait()`      | Espera a que el proceso hijo termine. |
| `pipe()`      | Conecta la salida de un proceso con la entrada de otro. |
| `dup2()`      | Redirige la entrada/salida estándar. |
| Señales       | Captura `SIGINT`, `SIGQUIT`, etc., para controlar el comportamiento de la shell. |
| Lista doblemente enlazada | Usada para representar tokens y entorno (`env`) de forma eficiente. |

---

## 🧱 Estructura General del Proyecto

```c
typedef struct s_data {
	t_dlist *env;           // Entorno (variables de entorno)
	char *input;            // Entrada del usuario
	t_dlist *tokens;        // Tokens generados del input
	char **instructions;    // Instrucciones para ejecutar
	int *in_fds;            // FDs de entrada para cada comando
	int *out_fds;           // FDs de salida para cada comando
	pid_t *pids;            // PIDs de los procesos hijos
	int cmd_count;          // Número de comandos
	int exit_status;        // Último estado de salida
	int pipe_fds[2];        // Pipe para comunicación entre procesos
	int prev_pipe_fd;       // FD de pipe anterior
	int open_fail;          // Error al abrir archivos
} t_data;

```

✅ Comandos internos (Built-ins)

- echo	

- cd

- pwd

- export

- unset

- env

- exit

---


🔄 Flujo General de Ejecución
```
1. readline()                 // Lee el input del usuario
2. parse_input()              // Tokeniza la entrada
3. expand_all_tokens()        // Expande variables ($USER, etc.)
4. execution()                // Ejecuta comandos y maneja procesos
5. free_all()                 // Limpia toda la memoria usada al terminar
```

---

🧪 Ejemplos de uso

```
$ echo "Hola Mundo"
Hola Mundo

$ ls -l | grep ".c" > archivos_c.txt

$ export USERNAME=42coder

$ echo $USERNAME
42coder

$ cat << EOF
Hola
EOF
Hola
```

---



🧩 Bonus Implementados

- ✅ Soporte para heredoc (<<)

- ✅ Manejo de comillas simples y dobles

- ✅ Expansión de variables ($VAR)

- ✅ Soporte para múltiples pipes

- ✅ Soporte parcial de redirecciones >, >>, <

---

📁 Compilación

```
make
./minishell
```

---


🧷 Notas Adicionales

Este proyecto fue una experiencia intensa para aprender a bajo nivel cómo funciona una shell real.

No tiene dependencias externas aparte de la librería readline y está escrito íntegramente en C.

---


🧪 ¿Quieres probarlo?
Clona el repositorio:

```
git clone https://github.com/MarcelaJI/minishell.git
cd minishell
make
./minishell
```

---

🧑‍💻 Autoras

ingjimen & iranieri :)

📘 Proyecto realizado en [42 Madrid](https://www.42madrid.com/)

---

