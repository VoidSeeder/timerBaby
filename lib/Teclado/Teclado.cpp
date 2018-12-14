#include "Teclado.h"

char teclas[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'},
};

Teclado::Teclado(uint8_t *ui8_linhas, uint8_t* ui8_colunas){
    this->ui8_linhas = ui8_linhas;
    this->ui8_colunas = ui8_colunas;
}

void Teclado::iniciar(){
    digitalWrite(this->ui8_linhas[0], LOW);
    digitalWrite(this->ui8_linhas[1], LOW);
    digitalWrite(this->ui8_linhas[2], LOW);
    digitalWrite(this->ui8_linhas[3], LOW);
}

char Teclado::lerTecla(){
    for(int i_cont_linha; i_cont_linha < 4; i_cont_linha++){
        digitalWrite(this->ui8_linhas[i_cont_linha], HIGH);

        for(int i_cont_coluna; i_cont_coluna < 4; i_cont_coluna++){
            if(digitalRead(this->ui8_colunas[i_cont_coluna])){
                digitalWrite(this->ui8_linhas[i_cont_linha], LOW);

                return teclas[i_cont_linha][i_cont_coluna];
            }
        }

        digitalWrite(this->ui8_linhas[i_cont_linha], LOW);
    }

    return NULL;
}