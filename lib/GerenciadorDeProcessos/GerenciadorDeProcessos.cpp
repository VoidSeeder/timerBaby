#include "GerenciadorDeProcessos.h"
#include <TimerOne.h>

Processo* p_bufferProcesso[QUANTIDADE_TAREFAS];
HardwareSerial *DEBUG = NULL;
uint8_t ui8_contadorDeTarefas = 0;

volatile uint16_t ui16_vetorDeContadoresDoSistema[QUANTIDADE_TAREFAS] = {};
volatile int16_t ui16_tempoEmExecucao = 0;
volatile uint16_t ui16_contadorDoSistema = 0;
volatile bool b_temporizadorEstourou = 0;
volatile bool b_tarefaSendoExecutada = 0;

void interrupcaoDeProcessos();

bool b_habilitarEscalonador(void){
    if (DEBUG != NULL){
        DEBUG->print("\n-> Habilitando o escalonador de processos...\n");
    }
    uint8_t ui8_contador = 0;
    b_temporizadorEstourou = NAO;
    b_tarefaSendoExecutada = NAO;
    Timer1.initialize(1000);
    Timer1.attachInterrupt(interrupcaoDeProcessos);
    while(ui8_contador > QUANTIDADE_TAREFAS){
        p_bufferProcesso[ui8_contador] = NULL;
        ui8_contador++;
    }
    return SUCESSO;
}

bool b_adicionarTarefa(PonteiroDeFuncao pf_funcaoProcesso, const char *c_nomeDoProcesso, uint16_t ui16_periodoDoProcesso, bool b_habilitarProcesso, Processo* p_processo){
    uint8_t ui8_contadorDeTarefas = 0;
    p_processo->pf_funcao = pf_funcaoProcesso;
    p_processo->c_nomeDaTarefa = c_nomeDoProcesso;
    p_processo->ui16_periodo = ui16_periodoDoProcesso;
    p_processo->b_habilitarTarefa = b_habilitarProcesso;
    if (DEBUG != NULL){
        DEBUG->print("\n-> Adicionando tarefa...\n");
        DEBUG->print("   -> Nome: ");
        DEBUG->print(c_nomeDoProcesso);
        DEBUG->print("\n");
    }
    for (ui8_contadorDeTarefas = 0; ui8_contadorDeTarefas < QUANTIDADE_TAREFAS; ui8_contadorDeTarefas++){
        if (p_bufferProcesso[ui8_contadorDeTarefas] != NULL && p_bufferProcesso[ui8_contadorDeTarefas] == p_processo){
            if (DEBUG != NULL){
                DEBUG->print("   -> Tarefa ja existente!\n");
            }
            return SUCESSO;
        }
    }
    for (ui8_contadorDeTarefas = 0; ui8_contadorDeTarefas < QUANTIDADE_TAREFAS; ui8_contadorDeTarefas++){
        if (p_bufferProcesso[ui8_contadorDeTarefas] == NULL){
            p_bufferProcesso[ui8_contadorDeTarefas] = p_processo;
            if (DEBUG != NULL){
                DEBUG->print("   -> Adicionado com sucesso!\n");
            }
            return SUCESSO;
        }
    }
    if (DEBUG != NULL){
        DEBUG->print("   -> Erro: Tarefa nao adicionada!\n");
    }
    return ERRO;
}

bool b_removerTarefa(Processo* p_tarefa){
    uint8_t ui8_contadorDeTarefas = 0;
    if (DEBUG != NULL){
        DEBUG->print("\n-> Removendo tarefa...\n");
        DEBUG->print("   -> Nome: ");
        DEBUG->print(p_tarefa->c_nomeDaTarefa);
        DEBUG->print("\n");
    }
    for (ui8_contadorDeTarefas = 0; ui8_contadorDeTarefas < QUANTIDADE_TAREFAS; ui8_contadorDeTarefas++){
        if (p_bufferProcesso[ui8_contadorDeTarefas] == p_tarefa){
            p_bufferProcesso[ui8_contadorDeTarefas] = NULL;
            if (DEBUG != NULL){
                DEBUG->print("   -> Removido com sucesso!\n");
            }
            return SUCESSO;
        }
    }
    if (DEBUG != NULL){
        DEBUG->print("   -> Erro: Tarefa nao removida!\n");
    }
    return ERRO;
}

void iniciarProcessos(void){
    if (b_temporizadorEstourou == SIM){
        for (ui8_contadorDeTarefas = 0; ui8_contadorDeTarefas < QUANTIDADE_TAREFAS; ui8_contadorDeTarefas++){
            if ((p_bufferProcesso[ui8_contadorDeTarefas] != NULL)  && ((ui16_contadorDoSistema - ui16_vetorDeContadoresDoSistema[ui8_contadorDeTarefas]) > p_bufferProcesso[ui8_contadorDeTarefas]->ui16_periodo) && (p_bufferProcesso[ui8_contadorDeTarefas]->b_habilitarTarefa == SIM)){
                b_tarefaSendoExecutada = SIM;
                ui16_tempoEmExecucao = TEMPO_MAXIMO_EXECUCAO;
                if (DEBUG != NULL){
                    DEBUG->print("\n-> Executando tarefa...\n");
                    DEBUG->print("   -> Nome: ");
                    DEBUG->print(p_bufferProcesso[ui8_contadorDeTarefas]->c_nomeDaTarefa);
                    DEBUG->print("\n");
                }
                p_bufferProcesso[ui8_contadorDeTarefas]->pf_funcao();
                b_tarefaSendoExecutada = NAO;
                ui16_vetorDeContadoresDoSistema[ui8_contadorDeTarefas] = ui16_contadorDoSistema;
            }
        }
    }
}

void interrupcaoDeProcessos(){
    b_temporizadorEstourou = SIM;
    ui16_contadorDoSistema++;
    if (b_tarefaSendoExecutada == SIM){
        ui16_tempoEmExecucao--;
        if (ui16_tempoEmExecucao == 0){         //Função travou por algum motivo
            if (DEBUG != NULL){
                DEBUG->print("\n-> O processo nao esta respondendo!");
                DEBUG->print("\n   -> Reiniciando sistema...\n");
            }
            wdt_disable();
            wdt_enable(WDTO_15MS);
            while(1);
        }
    }
}

void habilitarDepuracao(HardwareSerial *ObjetoUSART){
    DEBUG = ObjetoUSART;
}