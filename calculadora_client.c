/*
 * calculadora_client.c
 * Cliente RPC para la calculadora
 */

#include "calculadora.h" // Incluye el archivo de encabezado generado por rpcgen
#include <stdio.h>       // Para printf, scanf
#include <stdlib.h>      // Para exit
#include <string.h>      // Para strlen (aunque no se usa directamente, es común en C)
#include <math.h>        // Para isnan() y isinf()

// Función que maneja la llamada RPC y el retorno de resultados
// El parámetro 'host' no se pasa a esta función ya que el clnt ya está creado.
float perform_calculation(float n1, float n2, char opr, CLIENT *clnt)
{
    float *result_ptr; // Puntero para el resultado de la llamada RPC
    inputs args;       // Estructura para pasar los argumentos

    args.num1 = n1;
    args.num2 = n2;
    args.operador = opr; // El operador se envía al servidor (aunque el servidor lo determina por la función RPC)

    // Realiza la llamada RPC según el operador
    if (opr == '+') {
        result_ptr = sum_1(&args, clnt);
    } else if (opr == '-') {
        result_ptr = res_1(&args, clnt);
    } else if (opr == '*') {
        result_ptr = mul_1(&args, clnt);
    } else if (opr == '/') {
        if (n2 == 0.0) {
            printf("Cliente: Error: División por cero no es válida.\n");
            return NAN; // Retorna Not a Number para indicar el error
        }
        result_ptr = div_1(&args, clnt);
    } else {
        printf("Cliente: Error: Operador no válido.\n");
        return NAN; // Retorna Not a Number para indicar el error
    }

    // Verifica si la llamada RPC fue exitosa
    if (result_ptr == (float *)NULL) {
        clnt_perror(clnt, "Error en la llamada RPC"); // Muestra un mensaje de error RPC
        return NAN; // Retorna Not a Number para indicar el error
    }

    // Retorna el valor desreferenciado del puntero
    return *result_ptr;
}

int main(int argc, char *argv[])
{
    char *host;   // Nombre del host del servidor
    float num1, num2; // Números para la operación
    char operator_char; // Caracter del operador
    CLIENT *clnt; // Puntero al manejador de cliente RPC
    float final_result; // Variable para almacenar el resultado final

    // Verifica si se proporcionó el host del servidor como argumento
    if (argc < 2) {
        printf("Uso: %s <server_host>\n", argv[0]);
        exit(1); // Salir con código de error
    }

    host = argv[1]; // Obtiene el nombre del host del primer argumento de la línea de comandos

    // Muestra el menú de la calculadora
    printf("\n****************\n");
    printf("**** Calculadora RPC ****\n");
    printf("**************\n");
    printf("(+) Suma\n");
    printf("(-) Resta\n");
    printf("(*) Multiplicacion\n");
    printf("(/) Division\n");
    printf("**************\n");

    // Solicita al usuario los números y el operador
    printf("Ingrese el 1er numero: ");
    if (scanf("%f", &num1) != 1) {
        printf("Entrada invalida para el primer numero.\n");
        exit(1);
    }

    printf("Ingrese el 2do numero: ");
    if (scanf("%f", &num2) != 1) {
        printf("Entrada invalida para el segundo numero.\n");
        exit(1);
    }

    printf("Ingrese el operador (+, -, *, /): ");
    // Un espacio antes de %c es crucial para consumir el caracter de nueva línea
    // que quedó en el buffer de entrada de la función scanf anterior.
    if (scanf(" %c", &operator_char) != 1) {
        printf("Entrada invalida para el operador.\n");
        exit(1);
    }

    // Crea el manejador de cliente RPC
    // Se usa "udp" como protocolo de transporte.
    clnt = clnt_create(host, CALCULADORA_PROG, CALCULADORA_VER, "udp");

    // Verifica si la creación del cliente fue exitosa
    if (clnt == NULL) {
        clnt_pcreateerror(host); // Muestra un mensaje de error si no se pudo crear el cliente
        exit(1);                 // Salir con código de error
    }

    // Llama a la función que realiza la operación RPC
    final_result = perform_calculation(num1, num2, operator_char, clnt);

    // Muestra el resultado al usuario
    if (isnan(final_result)) { // Verifica si el resultado es NaN (Not a Number)
        printf("No se pudo calcular el resultado debido a un error.\n");
    } else {
        printf("El resultado es = %f\n", final_result);
    }

    // Destruye el manejador de cliente RPC para liberar recursos
    clnt_destroy(clnt);

    exit(0); // Salir del programa con éxito
}
