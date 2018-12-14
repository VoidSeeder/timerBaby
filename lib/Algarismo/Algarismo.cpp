#include "Algarismo.h"

//Matriz que armazena quais caracteres especiais serão usados para cada numero
uint8_t ui8_numeros[10][4] = {
    {1, 2, //0
     3, 4},
    {5, 6, //1
     5, 6},
    {7, 8, //2
     9, 10},
    {7, 8, //3
     11, 12},
    {13, 14, //4
     15, 16},
    {17, 0, //5
     11, 12},
    {17, 0, //6
     9, 12},
    {18, 19, //7
     5, 6},
    {17, 8, //8
     9, 12},
    {17, 8, //9
     11, 12}
};

//Matriz que armazena os caracteres especiais
uint8_t ui8_caracteres[20][8] = {
    {B11110, //0
     B11110,
     B11110,
     B00000,
     B00000,
     B00000,
     B00000,
     B11110},
    {B01111, //1
     B01111,
     B01111,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110},
    {B11110, //2
     B11110,
     B11110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110},
    {B01110, //3
     B01110,
     B01110,
     B01110,
     B01110,
     B01111,
     B01111,
     B01111},
    {B01110, //4
     B01110,
     B01110,
     B01110,
     B01110,
     B11110,
     B11110,
     B11110},
    {B00000, //5
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000},
    {B01110, //6
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110},
    {B01111, //7
     B01111,
     B01111,
     B00000,
     B00000,
     B00000,
     B00000,
     B01111},
    {B11110, //8
     B11110,
     B11110,
     B01110,
     B01110,
     B01110,
     B01110,
     B11110},
    {B01111, //9
     B01110,
     B01110,
     B01110,
     B01110,
     B01111,
     B01111,
     B01111},
    {B11110, //10
     B00000,
     B00000,
     B00000,
     B00000,
     B11110,
     B11110,
     B11110},
    {B01111, //11
     B00000,
     B00000,
     B00000,
     B00000,
     B01111,
     B01111,
     B01111},
    {B11110, //12
     B01110,
     B01110,
     B01110,
     B01110,
     B11110,
     B11110,
     B11110},
    {B01110, //13
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01111},
    {B01110, //14
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B11110},
    {B01111, //15
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000},
    {B11110, //16
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110},
    {B01111, //17
     B01111,
     B01111,
     B01110,
     B01110,
     B01110,
     B01110,
     B01111},
    {B01111, //18
     B01111,
     B01111,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000},
    {B11110, //19
     B11110,
     B11110,
     B01110,
     B01110,
     B01110,
     B01110,
     B01110
    }
};

//Construtor que apenas atribui os valores de entradas aos atributos ja destinados para eles
Algarismo::Algarismo(uint8_t ui8_cursor, LiquidCrystal *LC_tela, uint8_t ui8_indice) {
    this->ui8_cursor = ui8_cursor;
    this->LC_tela = LC_tela;
    this->ui8_indice = ui8_indice;
}

//Atualiza o numero na tela. Nessa parte não é necessário atibuir a posição dos caracteres, pois o caractere é atualizado
//automaticamente na posição onde ele foi anteriormente escrito.
void Algarismo::mudarNumero(uint8_t ui8_novo) {
    for (uint8_t ui8_contador = 0; ui8_contador < 4; ui8_contador++)
        this->LC_tela->createChar(this->ui8_indice * 4 + ui8_contador, ui8_caracteres[ui8_numeros[ui8_novo][ui8_contador]]);
}

//Atribui os carateres do numero zero e exibe na tela, no local destinado
void Algarismo::iniciar() {
    this->LC_tela->createChar(this->ui8_indice * 4 + 0, ui8_caracteres[ui8_numeros[0][0]]);
    this->LC_tela->setCursor(this->ui8_cursor, 0);
    this->LC_tela->write(byte(this->ui8_indice * 4 + 0));

    this->LC_tela->createChar(this->ui8_indice * 4 + 1, ui8_caracteres[ui8_numeros[0][1]]);
    this->LC_tela->setCursor(this->ui8_cursor + 1, 0);
    this->LC_tela->write(byte(this->ui8_indice * 4 + 1));

    this->LC_tela->createChar(this->ui8_indice * 4 + 2, ui8_caracteres[ui8_numeros[0][2]]);
    this->LC_tela->setCursor(this->ui8_cursor, 1);
    this->LC_tela->write(byte(this->ui8_indice * 4 + 2));

    this->LC_tela->createChar(this->ui8_indice * 4 + 3, ui8_caracteres[ui8_numeros[0][3]]);
    this->LC_tela->setCursor(this->ui8_cursor + 1, 1);
    this->LC_tela->write(byte(this->ui8_indice * 4 + 3));
}