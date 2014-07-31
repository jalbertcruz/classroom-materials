#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player76652783.h"
#include "environment.h"

using namespace std;

// Constructor
Player76652783::Player76652783(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player76652783::Perceive(const Environment & env){
    actual_=env;
}


// Funcion de valoracion para testear MiniMax y Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    if (jugador==1)
      return estado.Marcador(1);
    else
      return estado.Marcador(2);
}

    void coordenadasCasilla (const Environment &estado,int *coordenadas,int rumbo, int jugador){
        if (jugador == 1)
      switch(rumbo){
            case 1:
              coordenadas[0] = estado.Position1_X() + 1; // Calculamos la coordenada X sumandole 1 a la coordenada X del jugador 1.
              coordenadas[1] = estado.Position1_Y(); // La coordenada Y es igual a la coordenada Y del jugador 1.
              break;
            case 3:
              coordenadas[0] = estado.Position1_X() - 1;
              coordenadas[1] = estado.Position1_Y();
              break;
            case 2:
              coordenadas[0] = estado.Position1_X();
              coordenadas[1] = estado.Position1_Y() + 1;
              break;
            case 0:
              coordenadas[0] = estado.Position1_X();
              coordenadas[1] = estado.Position1_Y() - 1;
              break;
        }
        else
      switch(rumbo){
            case 1:
              coordenadas[0] = estado.Position2_X() + 1; // Calculamos la coordenada X sumandole 1 a la coordenada X del jugador 1.
              coordenadas[1] = estado.Position2_Y(); // La coordenada Y es igual a la coordenada Y del jugador 1.
              break;
            case 3:
              coordenadas[0] = estado.Position2_X() - 1;
              coordenadas[1] = estado.Position2_Y();
              break;
            case 2:
              coordenadas[0] = estado.Position2_X();
              coordenadas[1] = estado.Position2_Y() + 1;
              break;
            case 0:
              coordenadas[0] = estado.Position2_X();
              coordenadas[1] = estado.Position2_Y() - 1;
              break;
        }

    }
int *coordenadasCasillaFrente(const Environment &estado, int jugador){
    // Función auxiliar que determina las coordenadas de la casilla que hay frente al jugador
    int *coordenadas = new int[2]; // Como necesito devolver un vector, construyo uno dinámico que me sirva para devolverlo.
    int rumbo = estado.Rumbo2();
    if (jugador == 1)
        rumbo = estado.Rumbo1();

    coordenadasCasilla (estado,coordenadas,rumbo,jugador);

    return coordenadas;

}

int *coordenadasCasillaDerecha(const Environment &estado, int jugador){
    // Función auxiliar que determina las coordenadas de la casilla que hay derecha al jugador
    int *coordenadas = new int[2]; // Como necesito devolver un vector, construyo uno dinámico que me sirva para devolverlo.
    int rumbo = estado.Rumbo2();
    if (jugador == 1)
        rumbo = estado.Rumbo1();

    switch (rumbo) {  // Determino el rumbo que nos queda a la derecha
        case 0:
            rumbo = 1;
        break;
        case 1:
            rumbo = 2;
        break;
        case 2:
            rumbo = 3;
        break;
        case 3:
            rumbo = 0;
        break;
    }

    coordenadasCasilla (estado,coordenadas,rumbo,jugador);

    return coordenadas;

}

int *coordenadasCasillaIzq(const Environment &estado, int jugador){
    // Función auxiliar que determina las coordenadas de la casilla que hay izquierda al jugador
    int *coordenadas = new int[2]; // Como necesito devolver un vector, construyo uno dinámico que me sirva para devolverlo.
    int rumbo = estado.Rumbo2();
    if (jugador == 1)
        rumbo = estado.Rumbo1();

    switch (rumbo) {  // Determino el rumbo que nos queda a la izquierda
        case 0:
            rumbo = 3;
        break;
        case 1:
            rumbo = 0;
        break;
        case 2:
            rumbo = 1;
        break;
        case 3:
            rumbo = 2;
        break;
    }

    coordenadasCasilla (estado,coordenadas,rumbo,jugador);

    return coordenadas;

}

int *coordenadasCasillaDetras(const Environment &estado, int jugador){
    // Función auxiliar que determina las coordenadas de la casilla que hay detras al jugador
    int *coordenadas = new int[2]; // Como necesito devolver un vector, construyo uno dinámico que me sirva para devolverlo.
    int rumbo = estado.Rumbo2();
    if (jugador == 1)
        rumbo = estado.Rumbo1();

    switch (rumbo) {  // Determino el rumbo que nos queda detras
        case 0:
            rumbo = 2;
        break;
        case 1:
            rumbo = 3;
        break;
        case 2:
            rumbo = 0;
        break;
        case 3:
            rumbo = 1;
        break;
    }

    coordenadasCasilla (estado,coordenadas,rumbo,jugador);

    return coordenadas;

}

int opuesto(int j){
    if (j == 1)
        return 2;
    return 1;
}


// Funcion de valoracion para testear MiniMax y Poda Alfabeta (ESTA ES LA QUE TENEIS QUE MODIFICAR)
//
double Valoracion(const Environment &estado, int jugador){
      int total = 0; // Resultado del metodo, que va a dar la suma de todos los valores del tablero

    if (jugador==1){

      const int objIndestructibleCercanoFrente = -5;    // Fijamos un valor a la importancia de la cercanía de un obj. indestructible cercano.
      const int objIndestructibleCercanoDer = -4;
      const int objIndestructibleCercanoIzq = -4;
      const int objIndestructibleCercanoDetras = -3;

      const int objIndestructibleCercanoBloqueaBasura = -5;

      const int objDestructibleCercanoFrente = -4;
      const int objDestructibleCercanoDer = -3;
      const int objDestructibleCercanoIzq = -3;
      const int objDestructibleCercanoDetras = -2;

      const int objDestructibleCercanoBloqueaBasura = 5;

      const int objDestructibleLejano = 2;//   Fijamos un valor a la importancia de los obj. lejanos.
      const int objIndestructibleLejano = 1;

      const int BasuraDelante = 10; // Fijamos un valor a la importancia de una unidad de la Basura.
      const int BasuraDer = 8;
      const int BasuraIzq =8;
      const int BasuraDetras = 3;



      const int objIndestructibleCercanoOponenteFrente  = 5;  // Fijamos un valor a la importancia de los obstaulos cercanos al oponente
      const int objIndestructibleCercanoOponenteDerecha = 4;
      const int objIndestructibleCrcanoOponenteIzq = objIndestructibleCercanoOponenteDerecha;
      const int objetondIndestructibleCrcanoOponenteDetras = -1;

      const int objDestructibleCercanoOponenteFrente  = 5;
      const int objDestructibleCercanoOponenteDerecha = 4;
      const int objDestructibleCrcanoOponenteIzq = objDestructibleCercanoOponenteDerecha;
      const int objetoDestructibleCrcanoOponenteDetras = -1;

      const int valorMIbasura = 20; // Fijamos un valor a importancia de una unidad de basura recogida.
      const int valorSUbasura = -20;

      const int valorDispOponenteObstaculo = 50; // Fijamos valor a importancia de un disparo -> MP: Mucha perdida de basura , -> PP: Poca perdida.
      //const int valorDispHeridoMP = -50;
      //const int valorDispHeridoPP = -15;

      const int valorYOQuietoRomperGiro = 1;  //Damos valor a la importancia de no efectuar un movimiento.
      const int valorYoQuietoNODescubierto = 40;

      const int valorELQuietoRomperGiro = 2;
      const int valorvalorELQuietoNODescubierto = -40;

      const int valorPeligro = -50; // Damos un valor a la importancia de estar "a tiro" .

      int ** maze = estado.SeeMap();   // A parti de las coordenadas de la casilla de enfrente obtengo el valor que existe en esa casilla del tablero,
                                    //Si es un obstáculo indestructible acumulo en la valoración del tablero el valor de este.
      int *coordsCasilla = coordenadasCasillaFrente(estado, jugador);

      if (maze[coordsCasilla[0]][coordsCasilla[1]] == -1)
        total = total + objIndestructibleCercanoFrente;

      if (maze[coordsCasilla[0]][coordsCasilla[1]] > -1) //Analizo cuando hay basura en la casilla de enfrente (> -1)
        total = total + BasuraDelante * maze[coordsCasilla[0]][coordsCasilla[1]];

      delete []coordsCasilla;

     coordsCasilla = coordenadasCasillaDerecha(estado, jugador);
     if (maze[coordsCasilla[0]][coordsCasilla[1]] == -1)
        total = total + objIndestructibleCercanoDer;

      if (maze[coordsCasilla[0]][coordsCasilla[1]] > -1) //Analizo cuando hay basura en la casilla de enfrente (> -1)
        total = total + BasuraDer * maze[coordsCasilla[0]][coordsCasilla[1]];

     delete [] coordsCasilla;

     coordsCasilla = coordenadasCasillaIzq(estado, jugador);
     if (maze[coordsCasilla[0]][coordsCasilla[1]] == -1)
        total = total + objIndestructibleCercanoIzq;

     if (maze[coordsCasilla[0]][coordsCasilla[1]] > -1) //Analizo cuando hay basura en la casilla de enfrente (> -1)
        total = total + BasuraIzq * maze[coordsCasilla[0]][coordsCasilla[1]];


     delete [] coordsCasilla;

     coordsCasilla = coordenadasCasillaDetras(estado, jugador);
     if (maze[coordsCasilla[0]][coordsCasilla[1]] == -1)
        total = total + objIndestructibleCercanoDetras;

     if (maze[coordsCasilla[0]][coordsCasilla[1]] > -1) //Analizo cuando hay basura en la casilla de enfrente (> -1)
        total = total + BasuraDetras * maze[coordsCasilla[0]][coordsCasilla[1]];

     delete [] coordsCasilla;

     total = total + valorMIbasura * estado.Marcador(jugador); // Tenemos en cuenta la importancia de mi marcador de basura
     total = total + valorSUbasura * estado.Marcador(opuesto(jugador));

      if (estado.Last_Action(opuesto(jugador)) == Environment::actSHOOT){   //Analizamos la ultima accion de jugador
                                                                         //para saber si ha sido un disparo
         total = total + valorDispOponenteObstaculo;
      }

    }
    else
    total = total  * -1;

      return total;
}




// ------------------- Los tres metodos anteriores no se pueden modificar



// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j, int giros){
    j=0;
    for (int i=0; i<5; i++){
        if (aplicables[i]){
           if (i==0) { // Doy más probabilidad a usar actFORWARD
              for (int k=0; k<4; k++){
                  opciones[j]=0;
                  j++;
              }
           }
           if ( (i==1 or i==2) and  ( (!aplicables[4] and j==0) or giros==0  ) ){
                  opciones[j]=i;
                  j++;
           }
           if (i==4) { // Doy más probabilidad a usar actSHOOT
              for (int k=0; k<2; k++){
                  opciones[j]=4;
                  j++;
              }
           }
        }
    }
}



// Algoritmo MINIMAX
double MiniMax (const Environment & tablero, int jug, int prof, int limite, Environment::ActionType & accion){
  const double INF = 100000000.0, mINF = -100000000.0, gano = 99999999, pierdo = -99999999;
  Environment::ActionType accion_anterior;
  bool opciones[5];
  double mejor, aux;

  if (prof==limite){ // Condicion de parada
      return Valoracion(tablero,jug);
  }
  else { // Proceso recursivo de calculo de MiniMax
      int n_act = tablero.possible_actions(opciones); // Determino cuantas acciones se pueden realizar

      if (n_act==0){ // Si no se puede realizar ninguna acción
          if (prof%2==0) // En los niveles pares juega MAX
             return pierdo; // Yo no puedo mover y entonces pierdo
          else
             return gano;   // El que n puede mover es el adversario y gano
      }

      // Inicializo el mejor valor en funcion del nivel

      if (prof%2==0)
        mejor = mINF; // Inicializar un nivel MAX
      else
        mejor = INF;  // Inicializar un nivel MIN


      int ult_act=-1;
      Environment hijo = tablero.GenerateNextMove(ult_act); // Genero el siguiente tablero

      while (!(hijo==tablero)){ // Condicion de que sigo pudiendo aplicar nuevas acciones al tablero
          aux = MiniMax(hijo,jug,prof+1,limite,accion_anterior); // Evaluo el valor del hijo

          if (prof % 2 == 0){ // Juega MAX
              if (aux>mejor){
                  mejor=aux;
                  accion = static_cast <Environment::ActionType > (ult_act);
              }
          }
          else {         // Juega MIN
              if (aux<mejor){
                  mejor=aux;
                  accion = static_cast <Environment::ActionType > (ult_act);
              }
          }

          hijo = tablero.GenerateNextMove(ult_act); // Genero el siguiente descendiente del tablero
      }

      return mejor;

  }


}




// Invoca el siguiente movimiento del jugador
Environment::ActionType Player76652783::Think(){
    const int PROFUNDIDAD_MINIMAX = 10;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 16; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[5]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si actFORWARD es aplicable
                        // aplicables[1]==true si actTURN_LEFT es aplicable
                        // aplicables[2]==true si actTURN_RIGHT es aplicable
                        // aplicables[3]==true si actIDLE es aplicable (aplicables[3] siempre es FALSE)
                        // aplicables[4]==true si actSHOOT es aplicable

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    cout << " Acciones aplicables para Jugador ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<5; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;



    //--------------------- COMENTAR Desde aqui
    /*cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones, actual_.Giros(jugador_));

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }
     */
    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------
    // Opcion: Metodo Minimax
    // NOTA: La parametrizacion es solo orientativa
    valor = MiniMax(actual_, jugador_, 0, PROFUNDIDAD_MINIMAX, accion);
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;



    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, PROFUNDIDAD_ALFABETA, accion, alpha, beta);


    return accion;
}

