# Ratatouille Rush

Este proyecto implementa un juego inspirado en el universo de "Ratatouille", donde el jugador toma el rol de Linguini, el mozo principal del famoso restaurante de Remy. El objetivo es gestionar el servicio del restaurante atendiendo clientes, tomando pedidos, entregándolos, y manteniendo el lugar limpio y ordenado.

## Índice

- [Introducción](#introducción)
- [Objetivo del Proyecto](#objetivo-del-proyecto)
- [Requisitos del Sistema](#requisitos-del-sistema)
- [Instalación y Uso](#instalación-y-uso)
- [Jugabilidad](#jugabilidad)
  - [Elementos del Juego](#elementos-del-juego)
  - [Comandos de Movimiento](#comandos-de-movimiento)
- [Estructura del Código](#estructura-del-código)
- [Compilación y Ejecución](#compilación-y-ejecución)
- [Autores](#autores)

## Introducción

Ratatouille Rush es un juego por turnos desarrollado en C, donde los jugadores deben alcanzar un monto objetivo de dinero al atender correctamente a los clientes en un restaurante. El juego involucra manejo de memoria dinámica, uso de estructuras de datos, y aplicación de buenas prácticas de programación.

## Objetivo del Proyecto

1. Diseñar y desarrollar funcionalidades para gestionar los elementos del restaurante y las interacciones del mozo.
2. Implementar una biblioteca modular que facilite la extensión del proyecto.
3. Garantizar que el código cumpla con buenas prácticas: claridad, modularidad y reutilización.
4. Crear una interfaz clara y funcional para el usuario.

## Requisitos del Sistema

- Sistema operativo: Linux (probado en Ubuntu 24.04.1 LTS).
- Compilador: GCC compatible con el estándar C99.
- Librerías requeridas: stdlib, stdio, stdbool, time.

## Instalación y Uso

1. Clona este repositorio:
   ```bash
   git clone <URL_DEL_REPOSITORIO>
   cd <CARPETA_DEL_REPOSITORIO>
   ```

2. Compila el proyecto:
   ```bash
   gcc *.c -o juego -std=c99 -Wall -Wconversion -Werror -lm
   ```

3. Ejecuta el juego:
   ```bash
   ./juego
   ```

## Jugabilidad

### Elementos del Juego

- **Linguini (Jugador):** Representado por `L`. Es el encargado de realizar las acciones del restaurante.
- **Mesas:** Pueden ser para 1 o 4 comensales (`T`).
- **Cocina:** Lugar donde se preparan los pedidos (`C`).
- **Obstáculos:** Charcos (`H`) y cucarachas (`U`).
- **Herramientas:** Mopa (`O`), monedas (`M`) y patines (`P`).
- **Platos:** Milanesa (`1`), hamburguesa (`2`), parrilla (`3`), y ratatouille (`4`).

### Comandos de Movimiento

- **Movimiento:**
  - `W`: Arriba
  - `S`: Abajo
  - `A`: Izquierda
  - `D`: Derecha
- **Acciones especiales:**
  - `O`: Tomar o soltar la mopa.
  - `T`: Tomar pedidos.
  - `P`: Activar patines.

El juego termina al completar 200 turnos o alcanzar el objetivo monetario de 150,000.

## Estructura del Código

- **restaurant.h:** Declaración de estructuras y funciones principales del juego.
- **restaurant.c:** Implementación de la lógica principal y manejo de memoria dinámica.
- **juego.c:** Archivo principal que gestiona la ejecución y flujo del juego.

## Compilación y Ejecución

El proyecto se compila con el siguiente comando:

```bash
gcc *.c -o juego -std=c99 -Wall -Wconversion -Werror -lm
```

Para ejecutar el juego:

```bash
./juego
```

## Autores

- Diego Jose Fernández Giraldo
  Alumno de Fundamentos de Programación - Curso Méndez, 2024.

**Nota:** Este proyecto fue desarrollado como parte de los trabajos prácticos 1 y 2 de la materia Fundamentos de Programación en el segundo cuatrimestre de 2024.


