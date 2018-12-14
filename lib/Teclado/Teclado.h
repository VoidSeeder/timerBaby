#ifndef Teclado_H
#define Teclado_H

#include <Arduino.h>
#include <inttypes.h>

class Teclado
{
  private:
    uint8_t *ui8_linhas, *ui8_colunas;
  public:
    Teclado(uint8_t *ui8_linhas, uint8_t *ui8_colunas);
    char lerTecla();
    void iniciar();
};

#endif