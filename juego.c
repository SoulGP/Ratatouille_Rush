#include "restaurant.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int GANO = 1;
const int PERDIO = -1;
const char JUGADA_VACIA = ' ';

static const char ARRIBA = 'W';
static const char ARRIBA_M = 'w';
static const char ABAJO = 'S';
static const char ABAJO_M = 's';
static const char IZQUIERDA = 'A';
static const char IZQUIERDA_M = 'a';
static const char DERECHA = 'D';
static const char DERECHA_M = 'd';
static const char ACCION_MOPA = 'O';
static const char ACCION_MOPA_M = 'o';
static const char ACCION_PATINES = 'P';
static const char ACCION_PATINES_M = 'p';
static const char ACCION_TOMAR_PEDIDO = 'T';
static const char ACCION_TOMAR_PEDIDO_M = 't';

/*
 * Pre condiciones:  "juego" debe estar correctamente inicializada.
 * Post condiciones: Devuelve "true" si el estado del juego es igual a "GANO" o "PERDIO", y
 *                   devuelve "false" en caso contrario de no cumplirse las anteriores condiciones.
 */
bool se_finalizo_partida(juego_t juego){
    return(estado_juego(juego) == GANO || estado_juego(juego) == PERDIO);
}

/*
 * Pre condiciones:  "juego" debe estar correctamente inicializada.
 * Post condiciones: Devuelve "true" si el valor de "jugada" es igual a cualquier de los siguientes valores:
 *                   'W', 'w', 'A', 'a', 'S', 's', 'D', 'd', 'O', 'o'.
 *                   Devuelve "false" en caso contrario de no cumplir las anteriores condiciones.
 */
bool es_valor_jugada_valido(char jugada){
    return(jugada != ARRIBA && jugada != ARRIBA_M && jugada != IZQUIERDA && jugada != IZQUIERDA_M && jugada != ABAJO && jugada != ABAJO_M 
            && jugada != DERECHA && jugada != DERECHA_M && jugada != ACCION_MOPA && jugada != ACCION_MOPA_M
            && jugada != ACCION_PATINES && jugada != ACCION_PATINES_M && jugada != ACCION_TOMAR_PEDIDO && jugada != ACCION_TOMAR_PEDIDO_M);
}

/*
 * Pre condiciones:  "juego" debe estar correctamente inicializada.
 * Post condiciones: verifica si el valor de "jugada" es valida. En caso contrario,
 *                   le vuelve a pedir al usuario hasta que ingrese una "jugada" valida.
 */
void verificar_valor_jugada_valida(char *jugada, juego_t *juego){
    printf("ingresa una jugada: ");
    scanf(" %c", jugada);
    while(es_valor_jugada_valido(*jugada)){
        system("clear");
        mostrar_juego(*juego);
        printf("ingresaste una jugada invalida: ");
        scanf(" %c", jugada);
    }
}

/*
 * Pre condiciones:  ~
 * Post condiciones: Inicializa con la informacion necesaria a "ratatouille_rush" y da el comienzo del juego,
 *                   mostrando los cambios del juego durante cada "jugada" y cuando finaliza su ejecución 
 *                   imprime si se gano el juego o se perdio por pantalla.
 */
void nueva_partida(){
    juego_t ratatouille_rush;
    char jugada = JUGADA_VACIA;

    inicializar_juego(&ratatouille_rush);
        
    while(!se_finalizo_partida(ratatouille_rush)){
        mostrar_juego(ratatouille_rush);
        verificar_valor_jugada_valida(&jugada, &ratatouille_rush);
        realizar_jugada(&ratatouille_rush, jugada);
        system("clear");
    } 

    destruir_juego(&ratatouille_rush);   
    
    if(estado_juego(ratatouille_rush) == GANO){
        printf("\
        ######      ###    ##    ##    ###     ######  ######## ######## \n \
       ##    ##    ## ##   ###   ##   ## ##   ##    ##    ##    ##       \n \
       ##         ##   ##  ####  ##  ##   ##  ##          ##    ##       \n \
       ##   #### ##     ## ## ## ## ##     ##  ######     ##    ######   \n \
       ##    ##  ######### ##  #### #########       ##    ##    ##       \n \
       ##    ##  ##     ## ##   ### ##     ## ##    ##    ##    ##       \n \
        ######   ##     ## ##    ## ##     ##  ######     ##    ######## \n");
    }
    else{
        printf("\
        ########  ######## ########  ########  ####  ######  ######## ######## \n \
        ##     ## ##       ##     ## ##     ##  ##  ##    ##    ##    ##       \n \
        ##     ## ##       ##     ## ##     ##  ##  ##          ##    ##       \n \
        ########  ######   ########  ##     ##  ##   ######     ##    ######   \n \
        ##        ##       ##   ##   ##     ##  ##        ##    ##    ##       \n \
        ##        ##       ##    ##  ##     ##  ##  ##    ##    ##    ##       \n \
        ##        ######## ##     ## ########  ####  ######     ##    ######## \n");  
    }
}

int main(){
    srand ((unsigned)time(NULL));

    nueva_partida();

    return 0;
}