#ifndef Algarismo_H
#define Algarismo_H

#include <Arduino.h>
#include <inttypes.h>
#include <LiquidCrystal.h>
//#include <const.c>

class Algarismo
{
  private:
    uint8_t ui8_cursor;
    LiquidCrystal *LC_tela;
    uint8_t ui8_indice;
  public:
    Algarismo(uint8_t ui8_cursor, LiquidCrystal *LC_tela, uint8_t ui8_indice);
    void mudarNumero(uint8_t ui8_novo);
    void iniciar();
};

#endif