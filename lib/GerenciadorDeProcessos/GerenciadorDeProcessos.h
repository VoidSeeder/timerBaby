#ifndef GerenciadorDeProcessos_H
#define GerenciadorDeProcessos_H

#define QUANTIDADE_TAREFAS 10
#define TEMPO_MAXIMO_EXECUCAO 3000

#include <avr/wdt.h>
#include <inttypes.h>
#include <stdio.h>
#include <Arduino.h>

#define SUCESSO       true
#define ERRO          false

#define SIM           true
#define NAO           false

typedef void(*PonteiroDeFuncao)();

typedef struct{
  PonteiroDeFuncao pf_funcao;
  const char *c_nomeDaTarefa;
  uint16_t ui16_periodo;
  bool b_habilitarTarefa; 
}Processo;

bool b_habilitarEscalonador(void);
bool b_adicionarTarefa(PonteiroDeFuncao pf_funcaoProcesso, const char *c_nomeDoProcesso, uint16_t ui16_periodoDoProcesso, bool b_habilitarProcesso, Processo* p_processo); 
bool b_removerTarefa(Processo* p_tarefa);
void iniciarProcessos(void);
void habilitarDepuracao(HardwareSerial *ObjetoUSART);

#endif