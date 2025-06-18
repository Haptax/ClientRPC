# Proyecto RPC GRUPO1: Calculadora

Este repositorio contiene la implementación de una aplicación de calculadora distribuida utilizando RPC (Remote Procedure Call) en C. Este proyecto está diseñado para ser ejecutado en un entorno de máquinas virtuales Linux.

**Autores:**
* Diego Chancusig
* Miguel Morales
* Brian Flores

**Sistema Operativo Recomendado:**
* Linux Mint 22.0 (o distribuciones basadas en Debian/Ubuntu compatibles)

---

## Pasos Previos y Configuración

Sigue estos pasos detallados para configurar y ejecutar la aplicación RPC en un entorno de dos máquinas virtuales (Cliente y Servidor).

### Configuración Inicial de Carpetas

1.  **Máquinas Virtuales:** Asegúrate de tener dos máquinas virtuales configuradas: una designada como **"Cliente"** y otra como **"Servidor"**.
2.  **Creación de Carpetas:** En el escritorio de *ambas* máquinas virtuales, crea las siguientes carpetas:
    * En la máquina **Cliente**, crea una carpeta llamada `cliente`.
    * En la máquina **Servidor**, crea una carpeta llamada `servidor`.
3.  **Copia de Archivos:** Copia y pega los archivos correspondientes (tal como se describe en la sección de "Archivos para el Cliente" y "Archivos para el Servidor" en tu documentación interna) en sus respectivas carpetas.

### 1. Requisitos Previos (Instala las Bibliotecas Necesarias)

Es fundamental instalar las bibliotecas de desarrollo RPC en ambas máquinas virtuales.

En red (Wifi), abre una terminal en la carpeta `cliente` (en la máquina cliente) y en la carpeta `servidor` (en la máquina servidor) y ejecuta los siguientes comandos en cada terminal:

```bash
sudo apt update
sudo apt install rpcbind # Este es el portmapper, esencial para RPC
sudo apt install libtirpc-dev # Librería para RPC
sudo apt install libnsl-dev   # Librería de Network Services (a veces necesaria para RPC)
