#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player76652783{
    public:
      Player76652783(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
    private:
      int jugador_;
      Environment actual_;

};
#endif
