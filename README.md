# Aplicación RPC - Calculadora (GRUPO1)

**Autores:** Diego Chancusig, Miguel Morales, Brian Flores  
**Sistema Operativo:** Linux Mint 22.0  
**Proyecto:** Aplicación RPC de una calculadora usando dos máquinas virtuales (Cliente-Servidor)

---

## 📁 Estructura Inicial

1. **Crea las carpetas necesarias:**
   - En la máquina **cliente**, crea una carpeta llamada `cliente` en el escritorio.
   - En la máquina **servidor**, crea una carpeta llamada `servidor` en el escritorio.

2. **Ubica los archivos:**
   - Copia los archivos fuente del cliente dentro de la carpeta `cliente`.
   - Copia los archivos fuente del servidor dentro de la carpeta `servidor`.

---

## ✅ Requisitos Previos

Ejecuta los siguientes comandos en **ambas máquinas virtuales** (cliente y servidor):

```bash
sudo apt update
sudo apt install rpcbind
sudo apt install libtirpc-dev
sudo apt install libnsl-dev
```
---
## 🛠️ Compilación del Proyecto

Ubícate en la carpeta correspondiente (cliente o servidor) en cada máquina y ejecuta:
```bash
make
```
---
## 🌐 Configuración de Red

Configura ambas máquinas en adaptador puente y asigna las siguientes IPs:

    Servidor

        IP: 192.168.101.10

        Máscara: 255.255.255.0 (/24)

        Gateway: 192.168.101.1

    Cliente

        IP: 192.168.101.20

        Máscara: 255.255.255.0 (/24)

        Gateway: 192.168.101.1
---
## ▶️ Ejecución del Programa
En la máquina servidor:
```bash
./calculadora_server
```
En la máquina cliente:
```bash
./calculadora_client 192.168.101.10
```
---
## ✅ Prueba de Funcionamiento

Realiza las operaciones solicitadas en la consola del cliente y verifica que el resultado sea procesado correctamente por el servidor.

¡Listo! Tu calculadora RPC está funcionando correctamente entre dos máquinas virtuales 🎉

