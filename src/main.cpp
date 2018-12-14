#include <Arduino.h>
#include <GerenciadorDeProcessos.h>

#include <LiquidCrystal.h>
#include <Algarismo.h>

LiquidCrystal LC_Tela(12, 11, 5, 4, 3, 2); //Declaração do objeto para controlar o display
Algarismo Ag_Dezena(10, &LC_Tela, 0); //Declaração de duas posições para exibir dezena e unidade
Algarismo Ag_Unidade(12, &LC_Tela, 1);

#include <Teclado.h>

uint16_t ui16_contador = 0; //Varíavel para armazenar os segundos

Processo P_relogio;

void relogio();

//Função padrão de inicialização do Arduino
void setup() {

  LC_Tela.begin(16, 9); //Inicialização da tela e dos algarismos
  Ag_Dezena.iniciar();
  Ag_Unidade.iniciar(); 

  LC_Tela.setCursor(0, 0);
  LC_Tela.print("#-Iniciar");
  LC_Tela.setCursor(0, 1);
  LC_Tela.print("*-Cancelar");

  b_adicionarTarefa(relogio, "Relogio", 1000, SIM, &P_relogio); //Atribuição da tarefa Relogio, que será executada a cada segundo
  b_habilitarEscalonador();
}

//Função de repetição padrão do Arduino
void loop() {
  //Inicia a execução das tarefas
  iniciarProcessos();
}

//Função que exibe o tempo decorrido na tela e incrementa o contador
void relogio() {
  uint8_t ui8_segundos = ui16_contador % 60;
  uint8_t ui8_minutos = ui16_contador / 60;

  LC_Tela.setCursor(14, 0);
  LC_Tela.print(ui8_segundos / 10);
  
  LC_Tela.setCursor(15, 0);
  LC_Tela.print(ui8_segundos % 10);

  Ag_Dezena.mudarNumero(ui8_minutos / 10);
  Ag_Unidade.mudarNumero(ui8_minutos % 10);

  (ui16_contador < 5940) ? (ui16_contador++) : (ui16_contador = 0);
}