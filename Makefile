# Define el compilador C por defecto
CC = gcc

# Nombre del archivo .x de la definición RPC
RPC_XFILE = calculadora.x

# Archivos fuente generados por rpcgen
RPCGEN_CLIENT_STUB = calculadora_clnt.c
RPCGEN_SERVER_STUB = calculadora_svc.c
RPCGEN_XDR = calculadora_xdr.c
RPCGEN_HEADER = calculadora.h

# Tus archivos fuente principales
CLIENT_SRC = calculadora_client.c
#SERVER_SRC = calculadora_server.c

# Todos los archivos fuente necesarios (generados y manuales)
RPC_SRCS = $(CLIENT_SRC) $(SERVER_SRC) $(RPCGEN_CLIENT_STUB) $(RPCGEN_SERVER_STUB) $(RPCGEN_XDR)
RPC_HDRS = $(RPCGEN_HEADER)

# Nombres de los ejecutables
CLIENT_PROG = calculadora_client
#SERVER_PROG = calculadora_server

# CFLAGS para incluir la ruta de los headers de tirpc
# -g para depuración, -Wall y -Wextra para advertencias útiles
# -I/usr/include/tirpc indica la ruta de los headers de libtirpc
CFLAGS = -g -Wall -Wextra -I/usr/include/tirpc

# LDFLAGS para enlazar con las bibliotecas necesarias
# -ltirpc es la biblioteca principal RPC
# -lnsl es la Network Services Library (necesaria en algunos sistemas)
# -lm para funciones matemáticas como isnan()
LDFLAGS = -ltirpc -lnsl -lm

# La regla "all" es la regla por defecto y construirá ambos ejecutables
all: $(CLIENT_PROG)

# Regla para generar los stubs RPC a partir del archivo .x
# Si calculadora.x cambia, estos archivos se regenerarán
$(RPCGEN_CLIENT_STUB) $(RPCGEN_SERVER_STUB) $(RPCGEN_XDR) $(RPCGEN_HEADER): $(RPC_XFILE)
	rpcgen $(RPC_XFILE)

# Regla para compilar el programa cliente
# Depende de sus archivos objeto y de los stubs RPC generados
$(CLIENT_PROG): $(CLIENT_SRC:.c=.o) $(RPCGEN_XDR:.c=.o) $(RPCGEN_CLIENT_STUB:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar el programa servidor
# Depende de sus archivos objeto y de los stubs RPC generados
$(SERVER_PROG): $(SERVER_SRC:.c=.o) $(RPCGEN_XDR:.c=.o) $(RPCGEN_SERVER_STUB:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regla genérica para compilar archivos .c a .o
# %.o significa cualquier archivo .o
# %.c significa el archivo .c correspondiente
# $(RPCGEN_HEADER) se añade como dependencia para que cualquier cambio en el .h regenere los .o
%.o: %.c $(RPCGEN_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla clean para limpiar todos los archivos generados durante la compilación
clean:
	rm -f *.o $(CLIENT_PROG) $(SERVER_PROG) $(RPCGEN_CLIENT_STUB) $(RPCGEN_SERVER_STUB) $(RPCGEN_XDR) $(RPCGEN_HEADER)
