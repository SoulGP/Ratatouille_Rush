#include "restaurant.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEXTO_RESET_TOTAL "\e[0m" 
#define TEXTO_NEGRITA     "\e[1m"
#define TEXTO_PARPADEANTE "\e[5m"

#define TEXTO_GRIS_CLARO    "\e[90m"
#define TEXTO_VERDE_BRILLANTE "\e[92m"
#define TEXTO_AMARILLO_BRILLANTE "\e[93m"
#define TEXTO_AZUL_BRILLANTE "\e[94m"
#define TEXTO_MAGENTA_BRILLANTE "\e[95m"
#define TEXTO_CIAN_BRILLANTE "\e[96m"
#define TEXTO_BLANCO_BRILLANTE "\e[97m"

#define TEXTO_ROJO     "\e[31m"
#define TEXTO_VERDE    "\e[32m"
#define TEXTO_AMARILLO "\e[33m"
#define TEXTO_AZUL     "\e[34m"
#define TEXTO_BLANCO   "\e[37m"

const char ARRIBA = 'W';
const char ARRIBA_M = 'w';
const char ABAJO = 'S';
const char ABAJO_M = 's';
const char IZQUIERDA = 'A';
const char IZQUIERDA_M = 'a';
const char DERECHA = 'D';
const char DERECHA_M = 'd';
const char ACCION_MOPA = 'O';
const char ACCION_MOPA_M = 'o';
const char ACCION_PATINES = 'P';
const char ACCION_PATINES_M = 'p';
const char ACCION_TOMAR_PEDIDO = 'T';
const char ACCION_TOMAR_PEDIDO_M = 't';

const char LINGUINI = 'L';
const char MESAS = 'T';
const char COCINA = 'C';
const char CUCARACHA = 'U';
const char CHARCOS = 'H';
const char MOPA = 'O';
const char MONEDAS = 'M';
const char PATINES = 'P';
const char MILANESA_NAPOLITANA = 'M';
const char HAMBURGUESA = 'H';
const char PARRILLA = 'P';
const char RATATOUILLE = 'R';
const char MESA_OCUPADA = 'X';
const char PEDIDO_LISTO = 'g';
const char MESA_LISTA = 'G';
const char VACIO = ' ';

const int EXCLUIR_MOZO = -1;
const int EXCLUIR_COCINA = -1;

const int TOTAL_MESAS_INDIVIDUALES = 6;
const int TOPE_MESA_INDIVIDUAL = 1;
const int TOTAL_MESAS_GRUPALES = 4;
const int TOPE_MESA_GRUPAL = 4;
const int TOTAL_MESAS = TOTAL_MESAS_INDIVIDUALES + TOTAL_MESAS_GRUPALES; 

const int MAX_MOPAS = 1;
const int MAX_PATINES = 5;
const int MAX_MONEDAS = 8;
const int TOPE_MOPA = MAX_MOPAS;
const int TOPE_PATINES = MAX_MOPAS + MAX_PATINES;
const int TOPE_MONEDAS = MAX_MOPAS + MAX_PATINES + MAX_MONEDAS;
const int TOTAL_HERRAMIENTAS = MAX_MOPAS + MAX_PATINES + MAX_MONEDAS;

const int CUCARACHAS_INICIALES = 0;
const int MAX_CHARCOS = 5;
const int TOPE_CUCARACHAS = CUCARACHAS_INICIALES;
const int TOPE_CHARCOS = CUCARACHAS_INICIALES + MAX_CHARCOS;
const int TOTAL_OBSTACULOS = MAX_CHARCOS + CUCARACHAS_INICIALES;

const int DISTANCIA_MINIMA_ENTRE_MESAS = 4;
const int DISTANCIA_MINIMA_ACCION_PEDIDO = 1;
const int DISTANCIA_MINIMA_MOLESTIA_PACIENCIA = 2;

const int MOVIMIENTOS_INICIAL = 0;
const int DINERO_INICIAL = 0;
const int MAXIMOS_MOVIMIENTOS = 200;
const int META_DINERO = 150000;

const int GANO_JUEGO = 1;
const int PERDIO_JUEGO = -1;
const int CONTINUA_JUEGO = 0;

const char PEDIDO_TOMADO = 'S';
const char PEDIDO_NO_TOMADO = 'N';

const int MIN_CANTIDAD_COMENSALES = 1;
const int MAX_CANTIDAD_COMENSALES = 4;
const int COSTE_MESA_INDIVIDUAL = 5000;
const int COSTE_MESA_GRUPAL = 20000;

const int LIMITE_PACIENCIA = 0;
const int PERDIDA_NORMAL_PACIENCIA = 1;
const int PERDIDA_CONDICIONADA_PACIENCIA = 2;

const int MILANESA_NAPOLITANA_ID= 1;
const int PRODUCIR_MILANESA_NAPOLITANA = 30;
const int HAMBURGUESA_ID = 2;
const int PRODUCIR_HAMBURGUESA = 15;
const int PARRILLA_ID = 3;
const int PRODUCIR_PARRILLA = 20;
const int RATATOUILLE_ID = 4;
const int PRODUCIR_RATATOUILLE = 25;

const int VALOR_MONEDAS = 1000;

const int NO_ENCONTRO_HERRAMIENTA = -1;
const int NO_ENCONTRO_OBSTACULO = -1;

const int OCURRENCIA_NUEVOS_COMENSALES = 15;
const int OCURRENCIA_CUCARACHAS = 25;

const int MESA_LIBRE = 0;
const int SIN_PEDIDOS = 0;
const int PLATO_LISTO = 0;
const int CANTIDAD_MIN_PACIENCIA = 100;
const int CANTIDAD_MAX_PACIENCIA = 101;
const int CANTIDAD_MIN_COMENSALES = 1;
const int CANTIDAD_MAX_COMENSALES = 4;
const int INICIO_MENU = 1;
const int FIN_MENU = 4;

const int NO_TIENE_PATINES = 0;
const int BANDEJA_VACIA = 0;

const int LIMITE_GRAFICO_TRES_DIGITOS_PACIENCIA = 100;
const int LIMITE_GRAFICO_DOS_DIGITOS_PACIENCIA = 10;

/*
 * Pre condiciones:  ~
 * Post condiciones: Devuelve "true" si ambas posiciones poseen los mismos valores.
 *                   Devuelve "false" en caso contrario.   
 */
bool posiciones_son_iguales(coordenada_t posicion_a_verificar, coordenada_t posicion_a_comparar){
    return(posicion_a_verificar.fil == posicion_a_comparar.fil && posicion_a_verificar.col == posicion_a_comparar.col);
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Devuelve la distancia entre la posicion "origen" y la posicion "destino".
 */
int calcular_distancia_manhattan(coordenada_t origen, coordenada_t destino){
    return abs(origen.fil - destino.fil) + abs(origen.col - destino.col);
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Genera una fila y una columna con valores aleatorios entre 0 y el valor definido para "MAX_FILAS" Y "MAX_COLUMNAS", y 
 *                   los guarda en una posicion (cordenada_t).
 */
void ubicar_elemento(coordenada_t *posicion){
    int fila = rand() % (MAX_FILAS);
    int columna = rand() % (MAX_COLUMNAS);

    (*posicion) = (coordenada_t){fila, columna};
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Devuelve "true" si el indice de la mesa evaluada es una mesa grupal. Y
 *                   devuelve "false" si el indice de la mesa evaluada es una mesa individual.
 */
bool indice_es_mesa_grupal(int indice_mesa){
    return(indice_mesa < TOTAL_MESAS_GRUPALES);     
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" tiene que estar inicializada previamente.
 * Post condiciones: devuelve "true" si las posiciones del indice de mesa_t evaluado no colisiona con las posiciones del resto de indices
 *                   de mesas_t, y a su vez la distancia entre la posicion del indice de mesa_t evaluado y las posiciones de los distintos
 *                   indices de mesas_t es mayor a "DISTANCIA_MINIMA_ENTRE_MESAS". Y
 *                   devuelve "false" en caso de que la posicion del indice de mesa_t evaluado colisione con algun otro indice de mesa_t o 
 *                   la distancia entre las posiciones sean menor a "DISTANCIA_MINIMA_ENTRE_MESAS".
 */
bool hay_espacio_entre_mesas(mesa_t mesa[MAX_MESAS], int indice_mesa_a_verificar, int tope_mesas){
    bool espacio_entre_mesas = true;
    
    for(int mesa_actual = 0; mesa_actual < tope_mesas; mesa_actual++){
        if(indice_es_mesa_grupal(tope_mesas)){
            for(int posicion_actual = 0; posicion_actual < TOPE_MESA_GRUPAL; posicion_actual++){
                if(calcular_distancia_manhattan(mesa[mesa_actual].posicion[posicion_actual], mesa[indice_mesa_a_verificar].posicion[posicion_actual]) < DISTANCIA_MINIMA_ENTRE_MESAS){
                    espacio_entre_mesas = false;
                }
            }
        }
        else{
            if(calcular_distancia_manhattan(mesa[mesa_actual].posicion[0], mesa[indice_mesa_a_verificar].posicion[0]) < DISTANCIA_MINIMA_ENTRE_MESAS){
                    espacio_entre_mesas = false;
            }
        }
    }
    return espacio_entre_mesas;
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Dado una fila y una columna generada aleatoriamente con valores entre 0 y "MAX_FILAS/MAX_COLUMNAS" respectivamente,
 *                   las asigna al indice posicion correspondiente dependiendo del indice de la mesa actual: indice posicion 0 si es una mesa individual,
 *                   indice posicion 0,1,2,3 si es una mesa grupal.
 */
void ubicar_mesa_t(mesa_t mesa[MAX_MESAS], int mesa_actual){
    int fila_inicial = rand() % (MAX_FILAS-1);
    int columna_inicial = rand() % (MAX_COLUMNAS-1);
    
    if(indice_es_mesa_grupal(mesa_actual)){
        mesa -> posicion[0] = (coordenada_t){fila_inicial, columna_inicial};
        mesa -> posicion[1] = (coordenada_t){fila_inicial, columna_inicial + 1};
        mesa -> posicion[2] = (coordenada_t){fila_inicial + 1, columna_inicial};
        mesa -> posicion[3] = (coordenada_t){fila_inicial + 1, columna_inicial + 1};
        for(int posicion_vacia = TOPE_MESA_GRUPAL; posicion_vacia < MAX_POSICION; posicion_vacia++){
            mesa -> posicion[posicion_vacia] = (coordenada_t){-1, -1};
        }
        mesa -> cantidad_lugares = TOPE_MESA_GRUPAL;
    }
    else{
        mesa -> posicion[0] = (coordenada_t){fila_inicial, columna_inicial};
        for(int posicion_vacia = TOPE_MESA_INDIVIDUAL; posicion_vacia < MAX_POSICION; posicion_vacia++){
            mesa -> posicion[posicion_vacia] = (coordenada_t){-1, -1};
        }
        mesa -> cantidad_lugares = TOPE_MESA_INDIVIDUAL;
    }
    mesa -> cantidad_comensales = MESA_LIBRE;
    mesa -> paciencia = LIMITE_PACIENCIA;
    mesa -> pedido_tomado = false;
}

/*
 * Pre condiciones:  "juego -> cantidad_mesas" debe ser inicializado en 0.
 * Post condiciones: Inicializa la estructura "juego.mesas[MAX_MESAS]" junto a toda su informacion inicial y cuyas posiciones de cada una es distinta entre si.
 */
void inicializar_mesas(juego_t *juego){
    for(int mesa_actual = 0; mesa_actual < TOTAL_MESAS; mesa_actual++){
        ubicar_mesa_t(&juego -> mesas[mesa_actual], mesa_actual);
        while(!hay_espacio_entre_mesas(juego -> mesas, mesa_actual, juego -> cantidad_mesas)){
            ubicar_mesa_t(&juego -> mesas[mesa_actual], mesa_actual);
        }
        juego -> cantidad_mesas++;
    }          
}

/*
 * Pre condiciones:  "juego" debe estar incializada correctamente y con valores validos.
 * Post condiciones: Devuelve "true" en caso de que los valores de "fila" y "columna sean iguales a la posicion de las mesas,
 *                   o de los obstaculos, o de las herramientas, o de la cocina, o del mozo. Y
 *                   devuelve "false" en caso de que ninguna de las condiciones anteriores se cumpla.
 */
bool hay_elemento_en_coordenada(juego_t juego, int fila, int columna, int excluir){
    int mesa_actual = 0;
    int herramienta_actual = 0;
    int obstaculo_actual = 0;
    bool hay_elemento = false;

    if(posiciones_son_iguales((coordenada_t){fila, columna}, juego.mozo.posicion) && EXCLUIR_MOZO != excluir && EXCLUIR_COCINA != excluir){
        hay_elemento = true;
    }
    if(posiciones_son_iguales((coordenada_t){fila, columna}, juego.cocina.posicion) && EXCLUIR_COCINA != excluir){
        hay_elemento = true;
    }
    while(mesa_actual < juego.cantidad_mesas && !hay_elemento){
        int posicion_actual = 0;
        while(posicion_actual < juego.mesas[mesa_actual].cantidad_lugares && !hay_elemento){
            if(posiciones_son_iguales((coordenada_t){fila, columna}, juego.mesas[mesa_actual].posicion[posicion_actual])){
                hay_elemento = true;
            }

            posicion_actual++;
        }

        mesa_actual++;
    }
    while(herramienta_actual < juego.cantidad_herramientas && !hay_elemento){
        if(posiciones_son_iguales((coordenada_t){fila, columna}, juego.herramientas[herramienta_actual].posicion) && herramienta_actual != excluir){
            hay_elemento = true;
        }

        herramienta_actual++;
    }
    while(obstaculo_actual < juego.cantidad_obstaculos && !hay_elemento){
        if(posiciones_son_iguales((coordenada_t){fila, columna}, juego.obstaculos[obstaculo_actual].posicion) && obstaculo_actual != excluir){
            hay_elemento = true;
        }

        obstaculo_actual++;
    }
    return hay_elemento;
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Inicializa la estructura "juego.mozo" junto a toda su informacion inicial.
 */
void inicializar_mozo(juego_t *juego){
    ubicar_elemento(&juego -> mozo.posicion);
    while(hay_elemento_en_coordenada(*juego, juego -> mozo.posicion.fil, juego -> mozo.posicion.col, EXCLUIR_MOZO)){
        ubicar_elemento(&juego -> mozo.posicion);
    }
    juego -> mozo.cantidad_patines = 0;
    juego -> mozo.cantidad_pedidos = 0; 
    juego -> mozo.cantidad_bandeja = 0;
    juego -> mozo.tiene_mopa = false; 
    juego -> mozo.patines_puestos = false;
}

/*
 * Pre condiciones:  ~
 *                   
 * Post condiciones: Inicializa los vectores dinamicos de la cocina junto a sus topes a cero.
 *                   
 */
void crear_vector_dinamico_cocina(cocina_t *cocina){
    cocina -> platos_preparacion = NULL;
    cocina -> platos_listos = NULL;
    cocina -> cantidad_preparacion = 0;
    cocina -> cantidad_listos = 0;
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Inicializa la estructura "juego.cocina" junto a toda su informacion inicial.
*/
void inicializar_cocina(juego_t *juego){
    ubicar_elemento(&juego -> cocina.posicion);
    while(hay_elemento_en_coordenada(*juego, juego -> cocina.posicion.fil, juego -> cocina.posicion.col, EXCLUIR_COCINA)){
        ubicar_elemento(&juego -> cocina.posicion);
    }
    crear_vector_dinamico_cocina(&juego -> cocina);
}

/*
 * Pre condiciones:  "juego -> cantidad_herramientas" debe ser inicializado en 0.
 * Post condiciones: Inicializa la estructura "juego.herramientas[MAX_HERRAMIENTAS]" junto a toda su informacion inicial y cuyas posiciones de cada una es distinta entre si.
 */
void inicializar_herramientas(juego_t *juego){
    for(int herramienta_actual = 0; herramienta_actual < TOTAL_HERRAMIENTAS; herramienta_actual++){
        ubicar_elemento(&juego -> herramientas[herramienta_actual].posicion);
        while(hay_elemento_en_coordenada(*juego, juego -> herramientas[herramienta_actual].posicion.fil, juego -> herramientas[herramienta_actual].posicion.col, herramienta_actual)){
            ubicar_elemento(&juego -> herramientas[herramienta_actual].posicion);
        }
        if(herramienta_actual < TOPE_MOPA){
            juego -> herramientas[herramienta_actual].tipo = MOPA;
        }
        else if(herramienta_actual < TOPE_PATINES){
            juego -> herramientas[herramienta_actual].tipo = PATINES;
        }
        else if(herramienta_actual < TOPE_MONEDAS){
            juego -> herramientas[herramienta_actual].tipo = MONEDAS;
        }
        juego -> cantidad_herramientas++;
    }                                                                    
}

/*
 * Pre condiciones:  "juego -> cantidad_obstaculos" debe ser inicializado en 0.
 * Post condiciones: Inicializa la estructura "juego.obstaculos[MAX_OBSTACULOS]" junto a toda su informacion inicial y cuyas posiciones de cada una es distinta entre si.
 */
void inicializar_obstaculos(juego_t *juego){
    for(int obstaculo_actual = 0; obstaculo_actual < TOTAL_OBSTACULOS; obstaculo_actual++){
        ubicar_elemento(&juego -> obstaculos[obstaculo_actual].posicion);
        while(hay_elemento_en_coordenada(*juego, juego -> obstaculos[obstaculo_actual].posicion.fil, juego -> obstaculos[obstaculo_actual].posicion.col, obstaculo_actual)){
            ubicar_elemento(&juego -> obstaculos[obstaculo_actual].posicion);
        }
        if(obstaculo_actual < TOPE_CUCARACHAS){
            juego -> obstaculos[obstaculo_actual].tipo = CUCARACHA;
        }
        else if(obstaculo_actual < TOPE_CHARCOS){
            juego -> obstaculos[obstaculo_actual].tipo = CHARCOS;
        }
        juego -> cantidad_obstaculos++;
    }
}

/*
 * Pre condiciones:  -
 * Post condiciones: Inicializará el juego , cargando toda la información inicial de Linguini , las
 *                   mesas , las herramientas y los obstáculos.
 */
void inicializar_juego(juego_t *juego){
    juego -> movimientos = MOVIMIENTOS_INICIAL;
    juego -> dinero = DINERO_INICIAL;
    juego -> cantidad_mesas = 0;
    juego -> cantidad_herramientas = 0;
    juego -> cantidad_obstaculos = 0;
    juego -> cocina.posicion = (coordenada_t){-1, -1};

    inicializar_mesas(juego);
    inicializar_mozo(juego);
    inicializar_cocina(juego);
    inicializar_herramientas(juego);
    inicializar_obstaculos(juego);
}

/*
 * Pre condiciones:  "terreno" debe estar inicializada respetando los tamaños correspondientes a "MAX_FILAS" Y "MAX_COLUMNAS".                   
 *                   "juego" debe estar incializada correctamente y con valores validos.
 * Post condiciones: Recibe una matriz la cual rellena inicialmente a cada indice con "VACIO" y
 *                   posteriormente reemplaza los valores de "juego" en los indices correspondientes a la matriz.
 *                   si "tiene_mopa" = true, la posicion de la mopa sera la misma a la posicion del mozo
 *                   hasta que "tiene_mopa" = false.                 
 */
void rellenar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
    for(int fila = 0; fila < MAX_FILAS; fila++){
        for(int columna = 0; columna < MAX_COLUMNAS; columna++){
            terreno[fila][columna] = VACIO;
        }
    }

    terreno[juego.cocina.posicion.fil][juego.cocina.posicion.col] = COCINA;
    for(int mesa_actual = 0; mesa_actual < juego.cantidad_mesas; mesa_actual++){
        for (int posicion_actual = 0; posicion_actual < juego.mesas[mesa_actual].cantidad_lugares; posicion_actual++){
            if(juego.mesas[mesa_actual].cantidad_comensales != MESA_LIBRE){
                    terreno[juego.mesas[mesa_actual].posicion[posicion_actual].fil][juego.mesas[mesa_actual].posicion[posicion_actual].col] = MESA_OCUPADA;
            }
            else{
                    terreno[juego.mesas[mesa_actual].posicion[posicion_actual].fil][juego.mesas[mesa_actual].posicion[posicion_actual].col] = MESAS;
            }
            for(int pedido_actual = 0; pedido_actual < juego.mozo.cantidad_bandeja; pedido_actual++){
                if(juego.mesas[mesa_actual].cantidad_comensales != MESA_LIBRE && juego.mozo.bandeja[pedido_actual].id_mesa == mesa_actual){
                    terreno[juego.mesas[mesa_actual].posicion[posicion_actual].fil][juego.mesas[mesa_actual].posicion[posicion_actual].col] = MESA_LISTA;
                } 
            }
            if(juego.cocina.cantidad_listos > SIN_PEDIDOS){
                for(int pedido_actual = 0; pedido_actual < juego.cocina.cantidad_listos; pedido_actual++){
                    if(juego.mesas[mesa_actual].cantidad_comensales != MESA_LIBRE && juego.cocina.platos_listos[pedido_actual].id_mesa == mesa_actual){
                        terreno[juego.mesas[mesa_actual].posicion[posicion_actual].fil][juego.mesas[mesa_actual].posicion[posicion_actual].col] = PEDIDO_LISTO;
                    } 
                }
            }
        }
    }
    for(int herramienta_actual = 0; herramienta_actual < juego.cantidad_herramientas; herramienta_actual++){
        terreno[juego.herramientas[herramienta_actual].posicion.fil][juego.herramientas[herramienta_actual].posicion.col] = juego.herramientas[herramienta_actual].tipo;
    }
    for(int obstaculo_actual = 0; obstaculo_actual < juego.cantidad_obstaculos; obstaculo_actual++){
        terreno[juego.obstaculos[obstaculo_actual].posicion.fil][juego.obstaculos[obstaculo_actual].posicion.col] = juego.obstaculos[obstaculo_actual].tipo;
    }
    terreno[juego.mozo.posicion.fil][juego.mozo.posicion.col] = LINGUINI;
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Retorna 'S' si es "true", retorna 'N' si es "false".
 */
char es_verdadero(bool variable_juego ){
    if(variable_juego == true){
        return PEDIDO_TOMADO;
    }
    return PEDIDO_NO_TOMADO;
}


/*
 * Pre condiciones:  ~
 * Post condiciones: Imprime los controles del juego por pantalla.
 */
void imprimir_controles(){ 
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t| controles (es válido usar tanto el formato mayúscula como minúscula):       |\n");
    printf("\t| -W (arriba) -S (abajo) -A (izquierda) -D (derecha) -O (agarrar/soltar mopa) |\n");
    printf("\t|                   -T (tomar pedido) -P (usar patines)                       |\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" debe estar incializada correctamente y con valores validos.
 * Post condiciones: Imprime informacion de las mesas como: "mesa_actual", "paciencia", "cantidad_comensales" y "pedido_tomado" por pantalla.
 */
void imprimir_estado_mesas(mesa_t mesas[MAX_MESAS], int cantidad_mesas){                                                                    
    printf(" ----------------------------------------------------------------------------------------------------\n");
    for(int mesa_actual = 0; mesa_actual < cantidad_mesas; mesa_actual++){
        if(mesas[mesa_actual].paciencia >= LIMITE_GRAFICO_TRES_DIGITOS_PACIENCIA){
            printf(" |  mesa %i   -->   -paciencia: %i         -cantidad de comensales: %i          -pedido tomado:  %c   |\n", 
                mesa_actual, mesas[mesa_actual].paciencia, mesas[mesa_actual].cantidad_comensales, es_verdadero(mesas[mesa_actual].pedido_tomado));
        }
        else if(mesas[mesa_actual].paciencia >= LIMITE_GRAFICO_DOS_DIGITOS_PACIENCIA && mesas[mesa_actual].paciencia < LIMITE_GRAFICO_TRES_DIGITOS_PACIENCIA){
            printf(" |  mesa %i   -->   -paciencia: %i          -cantidad de comensales: %i          -pedido tomado:  %c   |\n", 
                mesa_actual, mesas[mesa_actual].paciencia, mesas[mesa_actual].cantidad_comensales, es_verdadero(mesas[mesa_actual].pedido_tomado));
        }
        else{
            printf(" |  mesa %i   -->   -paciencia: %i           -cantidad de comensales: %i          -pedido tomado:  %c   |\n", 
                mesa_actual, mesas[mesa_actual].paciencia, mesas[mesa_actual].cantidad_comensales, es_verdadero(mesas[mesa_actual].pedido_tomado));
        }
    }
    printf(" ----------------------------------------------------------------------------------------------------\n");
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Imprime la cantidad de movimientos realizados y el dinero total por pantalla.
 */
void imprimir_parte_superior_grafica(int movimientos, int dinero, int cantidad_patines){
    printf("movimientos realizados » %i         cantidad de patines » %i               dinero total » $%i\n", movimientos, cantidad_patines, dinero);
    printf("┌────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
} 


/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" debe estar incializada correctamente y con valores validos.
 * Post condiciones: Imprime informacion general acerca del juego por pantalla.
 */
void imprimir_parte_inferior_grafica(mesa_t mesas[MAX_MESAS], int cantidad_mesas){
    printf("└────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    imprimir_controles();
    imprimir_estado_mesas(mesas, cantidad_mesas);
} 

/*
 * Pre condiciones:  "juego" debe estar inicializada correctamente y con valores validos.
 * Post condiciones: Imprime "terreno[MAX_FILAS][MAX_COLUMNAS]" por pantalla.
 */
void imprimir_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
    imprimir_parte_superior_grafica(juego.movimientos, juego.dinero, juego.mozo.cantidad_patines);
    for(int fila = 0; fila < MAX_FILAS; fila++){
        for (int columna = 0; columna < MAX_COLUMNAS; columna++){
            if(columna == 0){
                if(terreno[fila][columna] == MESA_OCUPADA){
                    printf("│" TEXTO_ROJO "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MESA_LISTA){
                    printf("│" TEXTO_VERDE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PEDIDO_LISTO){
                    printf("│" TEXTO_VERDE_BRILLANTE "| " TEXTO_PARPADEANTE "%c" TEXTO_RESET_TOTAL TEXTO_VERDE_BRILLANTE " |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MONEDAS){
                    printf("│" TEXTO_AMARILLO_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CHARCOS){
                    printf("│" TEXTO_CIAN_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MOPA){
                    printf("│" TEXTO_GRIS_CLARO "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PATINES){
                    printf("│" TEXTO_AZUL_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CUCARACHA){
                    printf("│" TEXTO_GRIS_CLARO TEXTO_NEGRITA "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == COCINA){
                    printf("│" TEXTO_MAGENTA_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == LINGUINI){
                    printf("│|" TEXTO_BLANCO_BRILLANTE TEXTO_NEGRITA " %c " TEXTO_RESET_TOTAL "|", terreno[fila][columna]);
                }
                else{
                    printf("│| %c |", terreno[fila][columna]);
                }
            }
            else if(columna == MAX_COLUMNAS -1){
                if(terreno[fila][columna] == MESA_OCUPADA){
                    printf(TEXTO_ROJO "| %c |" TEXTO_RESET_TOTAL "│", terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MESA_LISTA){
                    printf(TEXTO_VERDE "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PEDIDO_LISTO){
                    printf(TEXTO_VERDE_BRILLANTE "| " TEXTO_PARPADEANTE "%c" TEXTO_RESET_TOTAL TEXTO_VERDE_BRILLANTE " |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MONEDAS){
                    printf(TEXTO_AMARILLO_BRILLANTE "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CHARCOS){
                    printf(TEXTO_CIAN_BRILLANTE "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MOPA){
                    printf(TEXTO_GRIS_CLARO "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PATINES){
                    printf(TEXTO_AZUL_BRILLANTE "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CUCARACHA){
                    printf(TEXTO_GRIS_CLARO TEXTO_NEGRITA "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == COCINA){
                    printf(TEXTO_MAGENTA_BRILLANTE "| %c |" TEXTO_RESET_TOTAL "│" , terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == LINGUINI){
                    printf("|" TEXTO_BLANCO_BRILLANTE TEXTO_NEGRITA " %c " TEXTO_RESET_TOTAL "|│" , terreno[fila][columna]);
                }
                else{
                    printf("| %c |│", terreno[fila][columna]);
                }
            }
            else{
                if(terreno[fila][columna] == MESA_OCUPADA){
                    printf(TEXTO_ROJO "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MESA_LISTA){
                    printf(TEXTO_VERDE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PEDIDO_LISTO){
                    printf(TEXTO_VERDE_BRILLANTE "| " TEXTO_PARPADEANTE "%c" TEXTO_RESET_TOTAL TEXTO_VERDE_BRILLANTE " |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MONEDAS){
                    printf(TEXTO_AMARILLO_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CHARCOS){
                    printf(TEXTO_CIAN_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == MOPA){
                    printf(TEXTO_GRIS_CLARO "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == PATINES){
                    printf(TEXTO_AZUL_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == CUCARACHA){
                    printf(TEXTO_GRIS_CLARO TEXTO_NEGRITA "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == COCINA){
                    printf(TEXTO_MAGENTA_BRILLANTE "| %c |" TEXTO_RESET_TOTAL, terreno[fila][columna]);
                }
                else if(terreno[fila][columna] == LINGUINI){
                    printf( "|" TEXTO_BLANCO_BRILLANTE TEXTO_NEGRITA " %c " TEXTO_RESET_TOTAL "|" , terreno[fila][columna]);
                }
                else{
                    printf("| %c |", terreno[fila][columna]);
                }
            }
        }
        printf("\n");
    }
    imprimir_parte_inferior_grafica(juego.mesas, juego.cantidad_mesas);
}

/*
 * Pre condiciones:  El juego debe estar inicializado previamente con `inicializar_juego `.
 * Post condiciones: Imprime el juego por pantalla.
 */
void mostrar_juego(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];

    rellenar_terreno(terreno, juego);
    imprimir_terreno(terreno, juego);
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.herramientas[MAX_HERRAMIENTAS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si la posicion del mozo coincide con la posicion de una mopa, moneda o patin.
 *                   Devuelve "false" en caso contrario.
 */
bool mozo_esta_sobre_herramienta(coordenada_t posicion_mozo, objeto_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas){ 
    int herramienta_actual = 0;
    bool esta_sobre_herramienta = false;

    while(herramienta_actual < cantidad_herramientas && !esta_sobre_herramienta){
        if((posiciones_son_iguales(posicion_mozo, herramientas[herramienta_actual].posicion))){
            esta_sobre_herramienta = true;
        }

        herramienta_actual++;
    }
    
    return esta_sobre_herramienta;
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.herramientas[MAX_HERRAMIENTAS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Retorna el indice de "juego.herramientas[MAX_HERRAMIENTAS]" que coincida con la posicion del mozo, y el "tipo" sea igual a "MOPA", "MONEDAS" o "PATIN".
 *                   Retorna -1 en caso de no encontrar ninguna coincidencia. 
 */
int obtener_indice_herramienta(coordenada_t posicion_mozo, objeto_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas){
    int herramienta_actual = 0;
    int indice_herramienta = NO_ENCONTRO_HERRAMIENTA;
    bool encontro_herramienta = false;
    
    while(herramienta_actual < cantidad_herramientas && !encontro_herramienta){    
        if(posiciones_son_iguales(posicion_mozo, herramientas[herramienta_actual].posicion)){
            indice_herramienta = herramienta_actual;
            encontro_herramienta = true;
        }

        herramienta_actual++;
    }
    return indice_herramienta;
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.obstaculos[MAX_OBSTACULOS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si la posicion del mozo coincide con la posicion de una cucaracha o charco.
 *                   Devuelve "false" en caso contrario.
 */
bool mozo_esta_sobre_obstaculo(coordenada_t posicion_mozo, objeto_t obstaculos[MAX_OBSTACULOS], int cantidad_obstaculos){ 
    int obstaculo_actual = 0;
    bool esta_sobre_obstaculo = false;

    while(obstaculo_actual < cantidad_obstaculos && !esta_sobre_obstaculo){
        if((posiciones_son_iguales(posicion_mozo, obstaculos[obstaculo_actual].posicion))){
            esta_sobre_obstaculo = true;
        }

        obstaculo_actual++;
    }
    
    return esta_sobre_obstaculo;
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.obstaculos[MAX_OBSTACULOS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Retorna el indice de "juego.obstaculos[MAX_OBSTACULOS]" que coincida con la posicion del mozo, y el "tipo" sea igual a "CUCARACHAS" o "CHARCOS".
 *                   Retorna -1 en caso de no encontrar ninguna coincidencia. 
 */
int obtener_indice_obstaculo(coordenada_t posicion_mozo, objeto_t obstaculos[MAX_OBSTACULOS], int cantidad_obstaculos){
    int obstaculo_actual = 0;
    int indice_obstaculo = NO_ENCONTRO_OBSTACULO;
    bool encontro_obstaculo = false;
    
    while(obstaculo_actual < cantidad_obstaculos && !encontro_obstaculo){    
        if(posiciones_son_iguales(posicion_mozo, obstaculos[obstaculo_actual].posicion)){
            indice_obstaculo = obstaculo_actual;
            encontro_obstaculo = true;
        }

        obstaculo_actual++;
    }
    return indice_obstaculo;
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.mesas[MAX_MESAS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si en la posicion evaluada del mozo hay una mesa, y
 *                   devuelve "false" en caso contrario.
 */
bool mozo_choca_mesa(coordenada_t posicion_mozo, mesa_t mesas[MAX_MESAS], int cantidad_mesas){
    int mesa_actual = 0;
    bool hay_mesa = false;

    while(mesa_actual < cantidad_mesas && !hay_mesa){
        int posicion_actual = 0; 
        while(posicion_actual < mesas[mesa_actual].cantidad_lugares && !hay_mesa){
            if(posiciones_son_iguales(posicion_mozo, mesas[mesa_actual].posicion[posicion_actual])){
                hay_mesa = true;
            }

            posicion_actual++;
        }

        mesa_actual++;
    }
    return hay_mesa;
}

/*
 * Pre condiciones:  "juego.mozo.posicion", "juego.cocina", "juego.herramientas[MAX_HERRAMIENTAS]", "juego.obstaculos[MAX_OBSTACULOS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "false" si la posicion del mozo se superpone con las posiciones de la cocina, obstaculos y herramientas (excluyendo a la del indice "excluir_mopa_agarrada"). y
 *                   devuelve "true" en caso contrario al no cumplirse ninguna de las anteriores condiciones.
 */
bool hay_espacio_debajo_mozo(coordenada_t posicion_mozo, coordenada_t posicion_cocina, objeto_t obstaculos[MAX_OBSTACULOS], int cantidad_obstaculos, objeto_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas){
    bool hay_espacio = true;
    
    if(posiciones_son_iguales(posicion_mozo, posicion_cocina)){
        hay_espacio = false;
    }
    for(int obstaculo_actual = 0; obstaculo_actual < cantidad_obstaculos; obstaculo_actual++){ 
        if(posiciones_son_iguales(posicion_mozo, obstaculos[obstaculo_actual].posicion)){
            hay_espacio = false;
        }
    }
    for(int herramienta_actual = 0; herramienta_actual < cantidad_herramientas; herramienta_actual++){
        if(posiciones_son_iguales(posicion_mozo, herramientas[herramienta_actual].posicion)){
            hay_espacio = false;
        }
    }
    return hay_espacio;
}

/*
 * Pre condiciones:  "juego.mozo" debe estar incializada correctamente y con valores validos.
 * Post condiciones: Modifica el estado de "mozo.tiene_mopa" a "true" e elimina la mopa fisicamente del vector herramientas.
 */
void agarrar_mopa(objeto_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas, mozo_t *mozo){ 
    int indice_mopa = obtener_indice_herramienta(mozo -> posicion, herramientas, *cantidad_herramientas);

    if(herramientas[indice_mopa].tipo == MOPA && indice_mopa != NO_ENCONTRO_HERRAMIENTA){
        herramientas[indice_mopa] = herramientas[*cantidad_herramientas -1];
        (*cantidad_herramientas)--;

        mozo -> tiene_mopa = true;
    }
}

/*
 * Pre condiciones:  "juego.mozo", "juego.herramientas[MAX_HERRAMIENTAS]" deben estar incializados correctamente y con valores validos.
 * Post condiciones: Modifica el estado de "mozo.tiene_mopa" a "false" y el "tipo" de la herramienta cuyo indice
 *                   coincida con la posicion del mozo y sea de "tipo" igual a "VACIO", lo modifica a "MOPA".
 */
void dejar_mopa(objeto_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas, mozo_t *mozo){
    if(!mozo_esta_sobre_herramienta(mozo -> posicion, herramientas, *cantidad_herramientas) && *cantidad_herramientas < MAX_HERRAMIENTAS){
        herramientas[*cantidad_herramientas].tipo = MOPA;
        herramientas[*cantidad_herramientas].posicion = mozo -> posicion;
        mozo -> tiene_mopa = false;
        
        (*cantidad_herramientas)++;
    }
}

/*
 * Pre condiciones:  "juego.mozo.posicion", deben estar incializados correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si se realiza un movimiento valido que no produzca conflictos con el programa, y
 *                   devuelve "false" en caso contrario.
 */
bool es_posicion_valida(coordenada_t posicion, mesa_t mesas[MAX_MESAS], int cantidad_mesas, char accion){
    if(accion == ARRIBA || accion == ARRIBA_M){
        return(posicion.fil >= 0 && !mozo_choca_mesa(posicion, mesas, cantidad_mesas));
    }
    else if(accion == ABAJO || accion == ABAJO_M){
        return(posicion.fil < MAX_FILAS && !mozo_choca_mesa(posicion, mesas, cantidad_mesas));
    }
    else if(accion == IZQUIERDA || accion == IZQUIERDA_M){
        return(posicion.col >= 0 && !mozo_choca_mesa(posicion, mesas, cantidad_mesas));
    }
    else if(accion == DERECHA || accion == DERECHA_M){
        return(posicion.col < MAX_COLUMNAS && !mozo_choca_mesa(posicion, mesas, cantidad_mesas));
    }
    return false;
}

/*
 * Pre condiciones:  "juego.mozo.posicion", "juego.herramientas[MAX_HERRAMIENTAS]" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si se realiza una accion valida que no produzca conflictos con el programa, y
 *                   devuelve "false" en caso contrario.
 */
bool es_accion_mopa_valida(mozo_t mozo, objeto_t herramientas[MAX_HERRAMIENTAS], int cantidad_herramientas, char accion){
    if(accion == ACCION_MOPA || accion == ACCION_MOPA_M){
        return(mozo_esta_sobre_herramienta(mozo.posicion, herramientas, cantidad_herramientas) && mozo.tiene_mopa == false);
    }
    return false;
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" y "juego.obstaculos[MAX_OBSTACULOS]" deben estar incializadas correctamente y con valores validos.               
 * Post condiciones: Disminuye en 1 la paciencia de los comensales, o en 3 en caso de que haya una cucaracha a distancia manhattan 2 de los comensales.
 */
void disminuir_paciencia(mesa_t mesas[MAX_MESAS], int tope_mesas, objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){
    for(int mesa_actual = 0; mesa_actual < tope_mesas; mesa_actual++){
    bool comensal_vio_cucaracha = false;
        for(int posicion_actual = 0; posicion_actual < mesas[mesa_actual].cantidad_lugares; posicion_actual++){
            int obstaculo_actual = 0;
            while(obstaculo_actual < tope_obstaculos && !comensal_vio_cucaracha){
                if(mesas[mesa_actual].paciencia > LIMITE_PACIENCIA){
                    int distancia = calcular_distancia_manhattan(obstaculos[obstaculo_actual].posicion, mesas[mesa_actual].posicion[posicion_actual]);
                    if(distancia <= DISTANCIA_MINIMA_MOLESTIA_PACIENCIA && obstaculos[obstaculo_actual].tipo == CUCARACHA){
                        mesas[mesa_actual].paciencia -= PERDIDA_CONDICIONADA_PACIENCIA;
                        comensal_vio_cucaracha = true;
                    }
                }

                obstaculo_actual++;
            }
        }
        if(mesas[mesa_actual].paciencia > LIMITE_PACIENCIA){
            mesas[mesa_actual].paciencia -= PERDIDA_NORMAL_PACIENCIA;
        }
    }
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" y "juego.mozo" deben estar incializadas correctamente y con valores validos.                  
 * Post condiciones: Devuelve "true" en caso de que "accion" sea igual a 'T' y
 *                   el mozo este a distancia manhattan 1 de cualquier mesa con comensales.
 *                   Devuelve "false" en caso contrario.
 */
bool es_accion_tomar_pedido_valida(mozo_t mozo, mesa_t mesas[MAX_MESAS], int tope_mesas, char accion){
    int mesa_actual = 0;
    int posicion_actual = 0;
    bool hay_mesa_cercana_ocupada = false;

    if(accion == ACCION_TOMAR_PEDIDO_M || accion == ACCION_TOMAR_PEDIDO){
        while(mesa_actual < tope_mesas && !hay_mesa_cercana_ocupada){
            posicion_actual = 0;
            while(posicion_actual < mesas[mesa_actual].cantidad_lugares && !hay_mesa_cercana_ocupada){
                int distancia = calcular_distancia_manhattan(mozo.posicion, mesas[mesa_actual].posicion[posicion_actual]);
                if(distancia == DISTANCIA_MINIMA_ACCION_PEDIDO && mesas[mesa_actual].cantidad_comensales != MESA_LIBRE){
                    hay_mesa_cercana_ocupada = true;
                }
                posicion_actual++;
            }
            mesa_actual++;
        }
    }
    return hay_mesa_cercana_ocupada;
}

/*
 * Pre condiciones:  ~                 
 * Post condiciones: Retorna un pedido aleatorio entre 'M', 'H', 'P', 'R'.             
 */
char asignar_pedido(){
    int nuevo_pedido_id = rand() % FIN_MENU + INICIO_MENU;
    char nuevo_pedido = ' ';

    if(nuevo_pedido_id == MILANESA_NAPOLITANA_ID){
        nuevo_pedido = MILANESA_NAPOLITANA;
    }
    else if(nuevo_pedido_id == HAMBURGUESA_ID){
        nuevo_pedido = HAMBURGUESA;
    }
    else if(nuevo_pedido_id == PARRILLA_ID){
        nuevo_pedido = PARRILLA;
    }
    else if(nuevo_pedido_id == RATATOUILLE_ID){
        nuevo_pedido = RATATOUILLE;
    }
    return nuevo_pedido;
}

/*
 * Pre condiciones:  "platos[MAX_PLATOS]" debe estar incializado y con valores validos.           
 * Post condiciones: Dado un vector de "platos" verifica elemento a elemento y
 *                   devuelve el mayor "tiempo_preparacion" encontrado.
 */
int asignar_tiempo_preparacion(char platos[MAX_PLATOS], int tope_platos){
    int tiempo_preparacion_actual = 0;
    int mayor_tiempo_preparacion = 0;

    for(int plato_actual = 0; plato_actual < tope_platos; plato_actual++){
        if(platos[plato_actual] == MILANESA_NAPOLITANA){
            tiempo_preparacion_actual = PRODUCIR_MILANESA_NAPOLITANA;
        }
        else if(platos[plato_actual] == HAMBURGUESA){
            tiempo_preparacion_actual = PRODUCIR_HAMBURGUESA;
        }
        else if(platos[plato_actual] == PARRILLA){
            tiempo_preparacion_actual = PRODUCIR_PARRILLA;
        }
        else if(platos[plato_actual] == RATATOUILLE){
            tiempo_preparacion_actual = PRODUCIR_RATATOUILLE;
        }
        if(tiempo_preparacion_actual > mayor_tiempo_preparacion){
            mayor_tiempo_preparacion = tiempo_preparacion_actual;
        }
    }

    return mayor_tiempo_preparacion;
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" y "juego.mozo" deben estar incializadas correctamente y con valores validos.            
 * Post condiciones: Devuelve "True" si el mozo se encuentra a distancia manhattan 1 de cualquier mesa, tiene espacio para tomar pedidos 
 *                   y "mozo.pedido_tomado" es igual a false.
 *                   Devuelve "False" en caso contrario.
 */
bool se_puede_tomar_pedido(coordenada_t posicion_mozo, coordenada_t posicion_mesa, int cantidad_pedidos, bool pedido_tomado){
    return (calcular_distancia_manhattan(posicion_mozo, posicion_mesa) == DISTANCIA_MINIMA_ACCION_PEDIDO && cantidad_pedidos < MAX_PEDIDOS && pedido_tomado == false);
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" y "juego.mozo" deben estar incializadas correctamente y con valores validos.          
 * Post condiciones: Toma el pedido de los comensales y los guarda con sus campos correspondientes en "mozo.pedidos[MAX_PEDIDOS]".              
 */
void tomar_pedido(mozo_t *mozo, mesa_t mesas[MAX_MESAS], int tope_mesas, char accion) {
    if(es_accion_tomar_pedido_valida(*mozo, mesas, tope_mesas, accion)){    
        mozo -> pedidos[mozo -> cantidad_pedidos].tiempo_preparacion = 0;
        mozo -> pedidos[mozo -> cantidad_pedidos].cantidad_platos = 0;

        for(int mesa_actual = 0; mesa_actual < tope_mesas; mesa_actual++){
            for(int posicion_actual = 0; posicion_actual < mesas[mesa_actual].cantidad_lugares; posicion_actual++){
                if(se_puede_tomar_pedido(mozo -> posicion, mesas[mesa_actual].posicion[posicion_actual], mozo -> cantidad_pedidos, mesas[mesa_actual].pedido_tomado)){
                    mozo -> pedidos[mozo -> cantidad_pedidos].id_mesa = mesa_actual;
                    for(int plato_actual = 0; plato_actual < mesas[mesa_actual].cantidad_comensales; plato_actual++){
                        char pedido_asignado = asignar_pedido();
                        mozo -> pedidos[mozo -> cantidad_pedidos].platos[plato_actual] = pedido_asignado;
                        mozo -> pedidos[mozo -> cantidad_pedidos].cantidad_platos++;
                    }
                    mozo -> pedidos[mozo -> cantidad_pedidos].tiempo_preparacion = asignar_tiempo_preparacion(mozo -> pedidos[mozo -> cantidad_pedidos].platos, mesas[mesa_actual].cantidad_comensales);
                    mesas[mesa_actual].pedido_tomado = true;
                    mozo -> cantidad_pedidos++;
                }
            }
        }
    }
}

/*
 * Pre condiciones:  "juego.mozo.posicion" y "juego.cocina.posicion" deben estar incializadas correctamente y con valores validos.
 * Post condiciones: Devuelve "true" si la posicion del mozo coincide con la posicion de la cocina.
 *                   Devuelve "false" en caso contrario.
 */
bool mozo_esta_sobre_cocina(coordenada_t posicion_mozo, coordenada_t posicion_cocina){ 
    return (posiciones_son_iguales(posicion_mozo, posicion_cocina));
}

/*
 * Pre condiciones:  "juego.cocina" y "juego.mozo" deben estar incializadas correctamente y con valores validos.                   
 * Post condiciones: asigna memoria al vector dinamico "cocina.platos_preparacion" dependiendo de la cantidad de pedidos que tenga el mozo y
 *                   despacha los mismos al vector dinamico.
 */
void despachar_pedido(mozo_t *mozo, cocina_t *cocina){
    if(mozo_esta_sobre_cocina(mozo -> posicion, cocina -> posicion) && cocina -> cantidad_preparacion < MAX_PEDIDOS){
        long unsigned int tope_platos_preparacion = (long unsigned int) mozo -> cantidad_pedidos + (long unsigned int) cocina -> cantidad_preparacion;
        
        if(mozo -> cantidad_pedidos != SIN_PEDIDOS){
            pedido_t *platos_preparacion_aux = realloc(cocina -> platos_preparacion, sizeof(pedido_t) * tope_platos_preparacion);
            if (platos_preparacion_aux == NULL) {
                printf("Error: no se pudo reasignar memoria para platos_preparacion.\n");
                return;
            }

            cocina -> platos_preparacion = platos_preparacion_aux;
            for(int pedido_actual = 0; pedido_actual < mozo -> cantidad_pedidos; pedido_actual++){
                cocina -> platos_preparacion[cocina -> cantidad_preparacion + pedido_actual] = mozo -> pedidos[pedido_actual];
            }
            cocina -> cantidad_preparacion += mozo -> cantidad_pedidos;
            mozo -> cantidad_pedidos = SIN_PEDIDOS;
        }
    }
}

/*
 * Pre condiciones:  "juego.cocina.platos_preparacion" debe tener memoria asignada y datos validos.                
 * Post condiciones: disminuye en 1 "tiempo_preparacion" de los pedidos que se encuentren en el vector dinamico.            
 */
void disminuir_tiempo_coccion(cocina_t *cocina, int tope_platos_preparacion){
    for(int plato_actual = 0; plato_actual < tope_platos_preparacion; plato_actual++){
        cocina -> platos_preparacion[plato_actual].tiempo_preparacion--;
    }
}

/*
 * Pre condiciones:  "juego.cocina.platos_preparacion" debe tener memoria asignada y datos validos.                
 * Post condiciones: cuando un pedido dentro de "platos_preparacion" su campo "tiempo_preparacion" sea igual a 0,
 *                   traspasara el pedido con todos sus datos al vector dinamico "platos_listos" asignandole su memoria correspondiente.               
 */
void cocinar_pedido(cocina_t *cocina, int tope_platos_preparacion){
    if(tope_platos_preparacion > SIN_PEDIDOS){
        disminuir_tiempo_coccion(cocina, tope_platos_preparacion);
    }

    for(int plato_actual = 0; plato_actual < tope_platos_preparacion; plato_actual++){
        if(cocina -> platos_preparacion[plato_actual].tiempo_preparacion == PLATO_LISTO){
            cocina -> cantidad_listos++;
            pedido_t *platos_listos_aux = realloc(cocina -> platos_listos, sizeof(pedido_t) * (long unsigned int)cocina -> cantidad_listos);
            if(platos_listos_aux == NULL){
                printf("Error: No se pudo reseasignar memoria para \"cocina -> platos_listos\".\n");
                free(cocina -> platos_preparacion);
                cocina -> platos_preparacion = NULL;
                return;
            }
            cocina -> platos_listos = platos_listos_aux;
            
            cocina -> platos_listos[cocina -> cantidad_listos - 1] = cocina -> platos_preparacion[plato_actual];
            cocina -> platos_preparacion[plato_actual] = cocina -> platos_preparacion[cocina -> cantidad_preparacion - 1];
            cocina -> cantidad_preparacion--;
            plato_actual--;
            tope_platos_preparacion--;
        }
    }
    if(cocina -> cantidad_preparacion > SIN_PEDIDOS){
        pedido_t *nuevos_platos_preparacion = realloc(cocina -> platos_preparacion, sizeof(pedido_t) * (unsigned long)cocina -> cantidad_preparacion);
        if(nuevos_platos_preparacion == NULL){
            printf("Error: No se pudo reasignar memoria para \"cocina -> platos_preparacion\".\n");
            free(cocina -> platos_preparacion);
            cocina -> platos_preparacion = NULL;
            return;
        }
        cocina -> platos_preparacion = nuevos_platos_preparacion;
    } 
    else{
        free(cocina -> platos_preparacion);
        cocina -> platos_preparacion = NULL;
    }
}

/*
 * Pre condiciones:  "juego.cocina.platos_listos" debe tener memoria asignada y datos validos.                   
 * Post condiciones: cuando el mozo este sobre la cocina y el vector dinamico "platos_listos" tiene pedidos,
 *                   traspasara los pedidos a "mozo.bandeja[MAX_BANDEJA]" respetando su tope.
 */
void poner_pedidos_listos_en_bandeja(mozo_t *mozo, cocina_t *cocina, int tope_platos_listos){
    int platos_pasados = 0;
    int plato_listo_actual = 0;
    int espacio_bandeja = MAX_BANDEJA - (mozo -> cantidad_bandeja);
    
    if(tope_platos_listos > PLATO_LISTO && mozo_esta_sobre_cocina(mozo -> posicion, cocina -> posicion) && mozo -> cantidad_bandeja < MAX_BANDEJA){
        while(plato_listo_actual < espacio_bandeja && plato_listo_actual < tope_platos_listos){
            mozo -> bandeja[mozo -> cantidad_bandeja] = cocina -> platos_listos[plato_listo_actual];
            mozo -> cantidad_bandeja++;
            platos_pasados++;

            plato_listo_actual++;
        }
    }
    if(platos_pasados == tope_platos_listos){
        free(cocina -> platos_listos);
        cocina -> platos_listos = NULL; 
        cocina -> cantidad_listos = 0;
    }
    else{
        int platos_restantes = cocina -> cantidad_listos - platos_pasados;
        pedido_t *nuevos_platos_listos = realloc(cocina -> platos_listos, sizeof(pedido_t) * (unsigned long)platos_restantes);
        if(nuevos_platos_listos == NULL && platos_restantes > SIN_PEDIDOS){
            printf("Error: No se pudo asignar memoria para los platos restantes.\n");
            return;
        }

        cocina -> platos_listos = nuevos_platos_listos;
        cocina -> cantidad_listos = platos_restantes;
    }
}

/*
 * Pre condiciones:  ~                  
 * Post condiciones: Retorna una "coordenada_t" alterada dependiendo de la accion ingresada.               
 */
coordenada_t obtener_probable_posicion(coordenada_t posicion, char accion){
    if(accion == ARRIBA_M || accion == ARRIBA){
        posicion.fil--;
    } 
    else if (accion == ABAJO_M || accion == ABAJO){
        posicion.fil++;
    } 
    else if (accion == IZQUIERDA_M || accion == IZQUIERDA){
        posicion.col--;
    } 
    else if (accion == DERECHA_M || accion == DERECHA){
        posicion.col++;
    }

    return posicion;
}

/*
 * Pre condiciones:  El juego debe estar inicializado previamente con `inicializar_juego ` y la acción
 *                   debe ser válida.
 * Post condiciones: Realizará la acción recibida por parámetro (case insensitive):
 *                   - 'W','A','S','D' -> mover al jugador.
 *                   - 'O' -> agarrar/soltar la mopa.
 *                   - 'P' -> usar patines.
 */
void realizar_accion(juego_t *juego, char accion){
    
    coordenada_t posicion;
    posicion.fil = juego -> mozo.posicion.fil;
    posicion.col = juego -> mozo.posicion.col;
    posicion = obtener_probable_posicion(posicion, accion);

    if(es_posicion_valida(posicion, juego -> mesas, juego -> cantidad_mesas, accion)){
        juego -> mozo.posicion = posicion;
        juego -> movimientos++;
        disminuir_paciencia(juego -> mesas, juego -> cantidad_mesas, juego -> obstaculos, juego -> cantidad_obstaculos);
        cocinar_pedido(&juego -> cocina, juego -> cocina.cantidad_preparacion);
    } 
    
    if(es_accion_mopa_valida(juego -> mozo, juego -> herramientas, juego -> cantidad_herramientas, accion)){
        agarrar_mopa(juego -> herramientas, &juego -> cantidad_herramientas, &juego -> mozo); 
    }
    else if(hay_espacio_debajo_mozo(juego -> mozo.posicion, juego -> cocina.posicion, juego -> obstaculos, juego -> cantidad_obstaculos, juego -> herramientas, juego -> cantidad_herramientas)){
        if((accion == ACCION_MOPA_M || accion == ACCION_MOPA) && juego -> mozo.tiene_mopa == true && juego -> mozo.patines_puestos == false){    
            dejar_mopa(juego -> herramientas, &juego -> cantidad_herramientas, &juego -> mozo);
        }
    }
}

/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: si movimientos realizados es multiplo de 15 (exceptuando 0) asigna aleatoriamente comensales a una mesa y
 *                   les asigna una cantidad de paciencia aleatoria entre CANTIDAD_MIN_PACIENCIA y CANTIDAD_MAX_PACIENCIA.
 */
void asignar_comensales(mesa_t mesas[MAX_MESAS], int tope_mesas, int movimientos_realizados){
    int mesa_actual = 0;
    bool hay_mesa_libre = false;

    if(movimientos_realizados % OCURRENCIA_NUEVOS_COMENSALES == 0 && movimientos_realizados != MOVIMIENTOS_INICIAL){
    int cantidad_comensales_nuevos = rand() % CANTIDAD_MAX_COMENSALES + CANTIDAD_MIN_COMENSALES;
    int cantidad_paciencia_comensales = rand() % CANTIDAD_MAX_PACIENCIA + CANTIDAD_MIN_PACIENCIA;

        while(mesa_actual < tope_mesas && !hay_mesa_libre){
            if(mesas[mesa_actual].cantidad_comensales == MESA_LIBRE){
                if(mesas[mesa_actual].cantidad_lugares == TOPE_MESA_INDIVIDUAL && cantidad_comensales_nuevos == CANTIDAD_MIN_COMENSALES){
                    mesas[mesa_actual].cantidad_comensales = cantidad_comensales_nuevos;
                    mesas[mesa_actual].paciencia = cantidad_paciencia_comensales;
                    hay_mesa_libre = true;
                } 
                else if(mesas[mesa_actual].cantidad_lugares != TOPE_MESA_INDIVIDUAL && cantidad_comensales_nuevos >= CANTIDAD_MIN_COMENSALES){
                    mesas[mesa_actual].cantidad_comensales = cantidad_comensales_nuevos;
                    mesas[mesa_actual].paciencia = cantidad_paciencia_comensales;
                    hay_mesa_libre = true;
                }
            }

            mesa_actual++;
        }
    }
}

/*
 * Pre condiciones:  "juego.mozo.bandeja[MAX_BANDEJA]" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: Si el mozo tiene pedidos listos en "bandeja[MAX_BANDEJA]" y esta a distancia manhattan 1 de una mesa ocupada,
 *                   si coincide "id_mesa" se le entregara el pedido disminuyendo el tope de la bandeja y 
 *                   recibiendo el dinero correspondiente: COSTE_MESA_INDIVIDUAL o COSTE_MESA_GRUPAL.
 */
void entregar_platos_comensal(mesa_t mesas[MAX_MESAS], int tope_mesas, mozo_t *mozo, int *dinero){
    for(int pedido_actual_mozo = 0; pedido_actual_mozo < mozo -> cantidad_bandeja; pedido_actual_mozo++){
        for(int mesa_actual = 0; mesa_actual < tope_mesas; mesa_actual++){
            for(int posicion_actual = 0; posicion_actual < mesas[mesa_actual].cantidad_lugares; posicion_actual++){
                if(mesas[mesa_actual].cantidad_comensales != MESA_LIBRE && calcular_distancia_manhattan(mozo -> posicion, mesas[mesa_actual].posicion[posicion_actual]) == DISTANCIA_MINIMA_ACCION_PEDIDO){
                    if(mozo -> bandeja[pedido_actual_mozo].id_mesa == mesa_actual){
                        mesas[mesa_actual].paciencia = LIMITE_PACIENCIA;
                        mesas[mesa_actual].cantidad_comensales = MESA_LIBRE;
                        mesas[mesa_actual].pedido_tomado = false;
                        
                        if(mesas[mesa_actual].cantidad_lugares == TOPE_MESA_GRUPAL){
                            *dinero += COSTE_MESA_GRUPAL;
                        }
                        else if(mesas[mesa_actual].cantidad_lugares == TOPE_MESA_INDIVIDUAL){
                            *dinero += COSTE_MESA_INDIVIDUAL;
                        }
                        
                        if(pedido_actual_mozo != mozo -> cantidad_bandeja -1){    
                            mozo -> bandeja[pedido_actual_mozo] = mozo -> bandeja[mozo -> cantidad_bandeja -1];
                            mozo -> cantidad_bandeja -= 1;
                        }
                        else if(pedido_actual_mozo < mozo -> cantidad_bandeja){
                            mozo -> cantidad_bandeja -= 1;
                            pedido_actual_mozo -= 1;
                        }
                    } 
                }
            }
        }
    }
}

/*
 * Pre condiciones:  "juego.mozo" y "juego.obstaculos[MAX_OBSTACULOS]" debene star inicializadas correctamente y con valores validos.                 
 * Post condiciones: Devuelve "True" si el mozo se encuentra sobre un charco.
 *                   Devuelve "False" en caso contrario.
 */
bool mozo_esta_sobre_charco(mozo_t mozo, objeto_t obstaculos[MAX_OBSTACULOS], int cantidad_obstaculos, int indice_charco){
    return(obstaculos[indice_charco].tipo == CHARCOS && mozo_esta_sobre_obstaculo(mozo.posicion, obstaculos, cantidad_obstaculos) && indice_charco != NO_ENCONTRO_OBSTACULO);
}

/*
 * Pre condiciones:  "peididos[MAX_PEDIDOS]" debe estar inicializada corectamente y con valores validos.                  
 * Post condiciones: elimina del vector aquel pedido que sea igual a "id_mesa".                   
 */
void eliminar_pedidos(pedido_t pedidos[MAX_PEDIDOS], int *cantidad_pedidos, int mesa_actual){
    for (int pedido_actual_mozo = 0; pedido_actual_mozo < *cantidad_pedidos; pedido_actual_mozo++) {
        if(pedidos[pedido_actual_mozo].id_mesa == mesa_actual){
            pedidos[pedido_actual_mozo] = pedidos[(*cantidad_pedidos) - 1];
            (*cantidad_pedidos)--;
            pedido_actual_mozo--;
        }
    }
}


/*
 * Pre condiciones:  "juego.mesas[MAX_MESAS]", "juego.obstaculos[MAX_OBSTACULOS]", "juego.mozo" y "juego.cocina" deben estar incializadas correctamente y 
 *                   con valores validos.
 * Post condiciones: Libera una mesa eliminando el pedido relacionado de todas sus ubicaciones, si solo si, "mesas.paciencia" es igual a 0 o 
 *                   la posicion del mozo coincide con la posicion de un charco y "mozo.tiene_mopa" es igual a "False".
 */
void despachar_comensales(mesa_t mesas[MAX_MESAS], int tope_mesas, objeto_t obstaculos[MAX_OBSTACULOS], int cantidad_obstaculos, mozo_t *mozo, cocina_t *cocina){ 
    int indice_charco = obtener_indice_obstaculo(mozo -> posicion, obstaculos, cantidad_obstaculos);
    
    for(int mesa_actual = 0; mesa_actual < tope_mesas; mesa_actual++){
        if(mesas[mesa_actual].cantidad_comensales != MESA_LIBRE && mesas[mesa_actual].paciencia <= LIMITE_PACIENCIA){
            mesas[mesa_actual].cantidad_comensales = MESA_LIBRE;
            mesas[mesa_actual].pedido_tomado = false;

            eliminar_pedidos(mozo -> pedidos, &mozo -> cantidad_pedidos, mesa_actual);
            eliminar_pedidos(mozo -> bandeja, &mozo -> cantidad_bandeja, mesa_actual);
            eliminar_pedidos(cocina -> platos_preparacion, &cocina -> cantidad_preparacion, mesa_actual);
            eliminar_pedidos(cocina -> platos_listos, &cocina -> cantidad_listos, mesa_actual);
        }
        else if(indice_charco != NO_ENCONTRO_OBSTACULO){
            if(mozo_esta_sobre_charco(*mozo, obstaculos, cantidad_obstaculos, indice_charco) && mozo -> tiene_mopa == false && mozo -> cantidad_bandeja > BANDEJA_VACIA){
                for(int pedido_actual = 0; pedido_actual < mozo -> cantidad_bandeja; pedido_actual++){
                    if(mozo -> bandeja[pedido_actual].id_mesa == mesa_actual){
                        eliminar_pedidos(mozo -> bandeja, &mozo -> cantidad_bandeja, mesa_actual);
                        mesas[mesa_actual].paciencia = LIMITE_PACIENCIA;
                        mesas[mesa_actual].cantidad_comensales = MESA_LIBRE;
                        mesas[mesa_actual].pedido_tomado = false;
                    }
                }
            }
        }
    }
}

/*
 * Pre condiciones:  "juego.herramientas[MAX_HERRAMIENTAS]" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: Si la posicion del mozo coincide con la de una moneda obtiene el indice de esta moneda,
 *                   la elimina del vector herramientas y se agrega a "juego.dinero" -> VALOR_MONEDAS. 
 */
void agarrar_monedas(coordenada_t posicion_mozo, objeto_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas, int *dinero){
    int indice_moneda = obtener_indice_herramienta(posicion_mozo, herramientas, *cantidad_herramientas);

    if(mozo_esta_sobre_herramienta(posicion_mozo, herramientas, *cantidad_herramientas) && herramientas[indice_moneda].tipo == MONEDAS && indice_moneda != NO_ENCONTRO_HERRAMIENTA){
        herramientas[indice_moneda] = herramientas[*cantidad_herramientas -1];
        (*cantidad_herramientas)--; 

        *dinero += VALOR_MONEDAS;
    }
}

/*
 * Pre condiciones:  "juego.mozo", "juego.obstaculos[MAX_OBSTACULOS]" deben estar inicializadas correctamente y con valores validos.                   
 * Post condiciones: Si la posicion del mozo coincide con la de un charco obtiene el indice de este charco y
 *                   lo elimina del vector obstaculo si "mozo.tiene_mopa" es igual a "True".             
 */
void limpiar_charcos(mozo_t mozo, objeto_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos){
    int indice_charco = obtener_indice_obstaculo(mozo.posicion, obstaculos, *cantidad_obstaculos);

    if(indice_charco != NO_ENCONTRO_OBSTACULO){
        if(mozo_esta_sobre_charco(mozo, obstaculos, *cantidad_obstaculos, indice_charco)){
            obstaculos[indice_charco] = obstaculos[*cantidad_obstaculos -1];
            (*cantidad_obstaculos)--; 
        }
    }
}

/*
 * Pre condiciones:  "juego.herramientas[MAX_HERRAMIENTAS]" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: Si la posicion del mozo coincide con la de un patin obtiene el indice de este patin y
 *                   la elimina del vector herramientas y aumenta en 1 "mozo.cantidad_patines". 
 */
void agarrar_patines(mozo_t *mozo, objeto_t herramientas[MAX_HERRAMIENTAS], int *cantidad_herramientas){
    int indice_patines = obtener_indice_herramienta(mozo -> posicion, herramientas, *cantidad_herramientas);

    if(mozo_esta_sobre_herramienta(mozo -> posicion, herramientas, *cantidad_herramientas) && herramientas[indice_patines].tipo == PATINES && indice_patines != NO_ENCONTRO_HERRAMIENTA){
        mozo -> cantidad_patines++;
        herramientas[indice_patines] = herramientas[*cantidad_herramientas -1];
        (*cantidad_herramientas)--; 
    }
}

/*
 * Pre condiciones:  "juego" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: si movimientos realizados es multiplo de 25 (exceptuando 0) asigna aleatoriamente una cucaracha al terreno y
 *                   aumenta en 1 el tope de obstaculos sin pasarse de "MAX_OBSTACULOS".
 */
void invocar_cucarachas(juego_t *juego){
    if(juego -> movimientos % OCURRENCIA_CUCARACHAS == 0 && juego -> movimientos != MOVIMIENTOS_INICIAL && juego -> cantidad_obstaculos < MAX_OBSTACULOS){
        ubicar_elemento(&juego -> obstaculos[juego -> cantidad_obstaculos].posicion);
        while(hay_elemento_en_coordenada(*juego, juego -> obstaculos[juego -> cantidad_obstaculos].posicion.fil, juego -> obstaculos[juego -> cantidad_obstaculos].posicion.col, juego -> cantidad_obstaculos)){
            ubicar_elemento(&juego -> obstaculos[juego -> cantidad_obstaculos].posicion);
        }
        juego -> obstaculos[juego -> cantidad_obstaculos].tipo = CUCARACHA;
        juego -> cantidad_obstaculos++;
    }
}

/*
 * Pre condiciones:  "juego.mozo", "juego.obstaculos[MAX_OBSTACULOS]" deben estar inicializadas correctamente y con valores validos.                   
 * Post condiciones: Si la posicion del mozo coincide con la de una cucaracha obtiene el indice de esa cucaracha y
 *                   la elimina del vector obstaculos.             
 */
void aplastar_cucaracha(coordenada_t posicion_mozo, objeto_t obstaculos[MAX_OBSTACULOS], int *cantidad_obstaculos){
    int indice_cucaracha = obtener_indice_obstaculo(posicion_mozo, obstaculos, *cantidad_obstaculos);

    if(mozo_esta_sobre_obstaculo(posicion_mozo, obstaculos, *cantidad_obstaculos) && obstaculos[indice_cucaracha].tipo == CUCARACHA && indice_cucaracha != NO_ENCONTRO_OBSTACULO){
        obstaculos[indice_cucaracha] = obstaculos[*cantidad_obstaculos -1];
        (*cantidad_obstaculos)--; 
    }
}

/*
 * Pre condiciones:  "juego" debe estar incializada correctamente y con valores validos.                  
 * Post condiciones: Desplazara al mozo "n" posiciones en la direccion indicada hasta chocar con los limites del terreno o
 *                   chocar con una mesa, durante el trayecto interacciona con los elementos cercanos a el.
 */
void usar_patines(juego_t *juego, char accion){
    if((accion == ACCION_PATINES_M || accion == ACCION_PATINES) && juego -> mozo.patines_puestos == false && juego -> mozo.cantidad_patines > NO_TIENE_PATINES){
        juego -> mozo.patines_puestos = true;
    }
    else if(juego -> mozo.patines_puestos == true){
        coordenada_t posicion = juego -> mozo.posicion;
        posicion = obtener_probable_posicion(posicion, accion);
        
        while(es_posicion_valida(posicion, juego -> mesas, juego -> cantidad_mesas, accion)){
            juego -> mozo.posicion = posicion;

            if(juego -> mozo.tiene_mopa == true){
                limpiar_charcos(juego -> mozo, juego -> obstaculos, &juego -> cantidad_obstaculos);
            }
            else{
                despachar_pedido(&juego -> mozo, &juego -> cocina);
                poner_pedidos_listos_en_bandeja(&juego -> mozo, &juego -> cocina, juego -> cocina.cantidad_listos);
                entregar_platos_comensal(juego -> mesas, juego -> cantidad_mesas, &juego -> mozo, &juego -> dinero);
                agarrar_monedas(juego -> mozo.posicion, juego -> herramientas, &juego -> cantidad_herramientas, &juego -> dinero);
                agarrar_patines(&juego -> mozo, juego -> herramientas, &juego -> cantidad_herramientas);
                aplastar_cucaracha(juego -> mozo.posicion, juego -> obstaculos, &juego -> cantidad_obstaculos);
                despachar_comensales(juego -> mesas, juego -> cantidad_mesas, juego -> obstaculos, juego -> cantidad_obstaculos, &juego -> mozo, &juego -> cocina);
            }

            posicion = obtener_probable_posicion(posicion, accion);    
        }
        
        juego -> movimientos++;
        juego -> mozo.cantidad_patines--; 
        juego -> mozo.patines_puestos = false;
    }
}

/*
 * Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego ` y la acción
 * debe ser válida.
 * Post condiciones: Realizará la acción recibida por parámetro.
 */
void realizar_jugada(juego_t *juego, char accion){
    if(juego -> mozo.tiene_mopa == true){
        if(juego -> mozo.patines_puestos == true){
            usar_patines(juego, accion);
        }
        else{
            realizar_accion(juego, accion);
            limpiar_charcos(juego -> mozo, juego -> obstaculos, &juego -> cantidad_obstaculos);
        }
    }
    else if(juego -> mozo.patines_puestos == true && juego -> mozo.tiene_mopa == false){ 
        if(es_accion_mopa_valida(juego -> mozo, juego -> herramientas, juego -> cantidad_herramientas, accion)){
            agarrar_mopa(juego -> herramientas, &juego -> cantidad_herramientas, &juego -> mozo); 
        }
        else if(hay_espacio_debajo_mozo(juego -> mozo.posicion, juego -> cocina.posicion, juego -> obstaculos, juego -> cantidad_obstaculos, juego -> herramientas, juego -> cantidad_herramientas)){
            if((accion == ACCION_MOPA_M || accion == ACCION_MOPA) && juego -> mozo.tiene_mopa == true && juego -> mozo.patines_puestos == false){    
                dejar_mopa(juego -> herramientas, &juego -> cantidad_herramientas, &juego -> mozo);
            }
        }
        if(juego -> mozo.patines_puestos == true && juego -> mozo.tiene_mopa == false){
            usar_patines(juego, accion);
        } 
    }
    else{
        realizar_accion(juego, accion);
        tomar_pedido(&juego -> mozo, juego -> mesas, juego -> cantidad_mesas, accion);
        despachar_pedido(&juego -> mozo, &juego -> cocina);
        poner_pedidos_listos_en_bandeja(&juego -> mozo, &juego -> cocina, juego -> cocina.cantidad_listos);
        entregar_platos_comensal(juego -> mesas, juego -> cantidad_mesas, &juego -> mozo, &juego -> dinero);
        agarrar_monedas(juego -> mozo.posicion, juego -> herramientas, &juego -> cantidad_herramientas, &juego -> dinero);
        agarrar_patines(&juego -> mozo, juego -> herramientas, &juego -> cantidad_herramientas);
        aplastar_cucaracha(juego -> mozo.posicion, juego -> obstaculos, &juego -> cantidad_obstaculos);
        usar_patines(juego, accion);
    }
    invocar_cucarachas(juego);
    asignar_comensales(juego -> mesas, juego -> cantidad_mesas, juego -> movimientos);
    despachar_comensales(juego -> mesas, juego -> cantidad_mesas, juego -> obstaculos, juego -> cantidad_obstaculos, &juego -> mozo, &juego -> cocina);
}

/*
 * Pre condiciones:  El juego deberá estar inicializado previamente con `inicializar_juego `
 * Post condiciones: Devuelve:
 *                   --> 1 si es ganado
 *                   --> -1 si es perdido
 *                   --> 0 si se sigue jugando
 *                   El juego se dará por ganado cuando se termina el día y se consiguieron las monedas necesarias.
 *                   Se dará por perdido si se termina el día y no se llegó al monto.
 */
int estado_juego(juego_t juego){
    if(juego.movimientos == MAXIMOS_MOVIMIENTOS && juego.dinero >= META_DINERO){
        return GANO_JUEGO;
    }
    else if(juego.movimientos == MAXIMOS_MOVIMIENTOS && juego.dinero != META_DINERO){
        return PERDIO_JUEGO;
    }
    return CONTINUA_JUEGO;
}

/*  Pre condiciones: Los campos `platos_preparacion` y `platos_listos` del campo `cocina` del juego deben estar inicializados.
    Post condiciones: Libera la memoria dinámica reservada para el juego.
*/
void destruir_juego(juego_t *juego){
    if (juego->cocina.platos_listos != NULL) {
        free(juego -> cocina.platos_listos);
        juego -> cocina.platos_listos = NULL;
    }
    if (juego -> cocina.platos_preparacion != NULL) {
        free(juego->cocina.platos_preparacion);
        juego -> cocina.platos_preparacion = NULL;
    }
}