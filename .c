#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

#define TECLA_CIMA 'w'
#define TECLA_ESQUERDA 'a'
#define TECLA_BAIXO 's'
#define TECLA_DIREITA 'd'
#define CHAVE_INTERATIVA 'i'

#define LARGURA_TELA_FASE1 15
#define ALTURA_TELA_FASE1 15

#define LARGURA_TELA_FASE2 30
#define ALTURA_TELA_FASE2 30

int espinhos_tocados = 0;
int jogador_x = LARGURA_TELA_FASE1 / 2;
int jogador_y = ALTURA_TELA_FASE1 / 2;
int jogador_vida = 3;
int contador_reiniciar_jogo = 0;
int fase_atual = 1;
int jogo_em_execucao = 1;

char mapa_fase1[ALTURA_TELA_FASE1][LARGURA_TELA_FASE1] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

char mapa_fase2[ALTURA_TELA_FASE2][LARGURA_TELA_FASE2] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

typedef struct {
    int x, y;
    int portaID;
    int estaTrancada;
} PortaFase1;

PortaFase1 portas[] = {
    {0, 13, 1, 1},  
};

int numPortas = sizeof(portas) / sizeof(portas[0]);

typedef struct {
    int x, y;
    int chaveID;
} PosicaoChaveFase1;

PosicaoChaveFase1 posicoes_chaves[] = {
    {1, 9, 1},  
};

int numChaves = sizeof(posicoes_chaves) / sizeof(posicoes_chaves[0]);

typedef struct {
    int x1, y1;
} Monstro_nivel1;

Monstro_nivel1 monstro;

typedef struct {
    int x2, y2;
} Monstro_nivel2;

Monstro_nivel2 monstro2;

typedef struct {
    int x3, y3; 
    int x4, y4;
} Teleporte;

Teleporte teletransportes[] = {
    {28, 11, 1, 13},  
};

int numTeleportes = sizeof(teletransportes) / sizeof(teletransportes[0]);

typedef struct {
    int x, y;
    int portaIDfase2;
    int estaTrancada;
} PortaFase2;

PortaFase2 portasfase2[] = {
    {29, 27, 1, 1},  
};

int numPortasfase2 = sizeof(portasfase2) / sizeof(portasfase2[0]);

typedef struct {
    int x, y;
    int chaveIDfase2;
} PosicaoChaveFase2;

PosicaoChaveFase2 posicoes_chaves_fase2[] = {
    {1, 1, 1},  
};

int numChavesfase2 = sizeof(posicoes_chaves_fase2) / sizeof(posicoes_chaves_fase2[0]);

typedef struct {
    int x5, y5;
    int botaoIDfase2;
} BotaoFase2;

BotaoFase2 botaofase2[] = {
    {5, 5, 1},  
};

int numBotaofase2 = sizeof(botaofase2) / sizeof(botaofase2[0]);

void movimento_cima_fase1() {
	int i;
    if (jogador_y > 0 && mapa_fase1[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortas; i++) {
            if (next_x == portas[i].x && next_y == portas[i].y && portas[i].estaTrancada) {
                return; 
            }
        }

        jogador_y--;
    }
}

void movimento_esquerda_fase1() {
	int i;
    if (jogador_x > 0 && mapa_fase1[jogador_y][jogador_x - 1] != '*') {
        int next_x = jogador_x - 1;
        int next_y = jogador_y;

        for (i = 0; i < numPortas; i++) {
            if (next_x == portas[i].x && next_y == portas[i].y && portas[i].estaTrancada) {
                return; 
            }
        }

        jogador_x--;
    }
}

void movimento_baixo_fase1() {
    if (jogador_y < LARGURA_TELA_FASE1 - 1 && mapa_fase1[jogador_y + 1][jogador_x] != '*') {
        jogador_y++;
    }
}

void movimento_direita_fase1() {
    if (jogador_x < LARGURA_TELA_FASE1 - 1 && mapa_fase1[jogador_y][jogador_x + 1] != '*') {
        jogador_x++;
    }
}

void movimento_cima_fase2() {
	int i;
    if (jogador_y > 0 && mapa_fase2[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortas; i++) {
            if (next_x == portas[i].x && next_y == portas[i].y && portas[i].estaTrancada) {
                return; 
            }
        }

        jogador_y--;
    }
}

void movimento_esquerda_fase2() {
	int i;
    if (jogador_x > 0 && mapa_fase2[jogador_y][jogador_x - 1] != '*') {
        int next_x = jogador_x - 1;
        int next_y = jogador_y;
        jogador_x--;
    }
}

void movimento_baixo_fase2() {
    if (jogador_y < LARGURA_TELA_FASE2 - 1 && mapa_fase2[jogador_y + 1][jogador_x] != '*') {
        jogador_y++;
    }
}

void movimento_direita_fase2() {
    if (jogador_x < LARGURA_TELA_FASE2 - 1 && mapa_fase2[jogador_y][jogador_x + 1] != '*') {
        jogador_x++;
    }
}

void definir_posicao_inicial_monstro() {
    do {
        monstro.x1 = rand() % LARGURA_TELA_FASE1;
        monstro.y1 = rand() % ALTURA_TELA_FASE1;
    } while (mapa_fase1[monstro.y1][monstro.x1] == '*');
}

void movimento_monstro_nivel1() {
    int direcao = rand() % 4;

    switch (direcao) {
        case 0:
            if (mapa_fase1[monstro.y1 - 1][monstro.x1] != '*' && monstro.y1 > 0) {
                monstro.y1--;
            }
            break;
        case 1:
            if (mapa_fase1[monstro.y1 + 1][monstro.x1] != '*' && monstro.y1 < ALTURA_TELA_FASE1 - 1) {
                monstro.y1++;
            }
            break;
        case 2:
            if (mapa_fase1[monstro.y1][monstro.x1 - 1] != '*' && monstro.x1 > 0) {
                monstro.x1--;
            }
            break;
        case 3:
            if (mapa_fase1[monstro.y1][monstro.x1 + 1] != '*' && monstro.x1 < LARGURA_TELA_FASE1 - 1) {
                monstro.x1++;
            }
            break;
        default:
            break;
    }
}

void definir_posicao_inicial_monstro2() {
    do {
        monstro2.x2 = rand() % LARGURA_TELA_FASE2;
        monstro2.y2 = rand() % ALTURA_TELA_FASE2;
    } while (mapa_fase2[monstro2.y2][monstro2.x2] == '*' || 
             (monstro2.x2 == jogador_x && monstro2.y2 == jogador_y) ||
             (monstro2.x2 == monstro.x1 && monstro2.y2 == monstro.y1) ||
             (monstro2.x2 == jogador_x && monstro2.y2 == jogador_y) ||
             (monstro2.x2 == monstro.x1 && monstro2.y2 == monstro.y1) ||
             (monstro2.x2 < 0 || monstro2.x2 >= LARGURA_TELA_FASE2 || monstro2.y2 < 0 || monstro2.y2 >= ALTURA_TELA_FASE2));
}

void movimento_monstro_nivel2() {
    int dx = jogador_x - monstro2.x2;
    int dy = jogador_y - monstro2.y2;

    if (abs(dx) <= 1 && abs(dy) <= 1) {
        if (dx > 0 && mapa_fase2[monstro2.y2][monstro2.x2 + 1] != '*') {
            monstro2.x2++;
        } else if (dx < 0 && mapa_fase2[monstro2.y2][monstro2.x2 - 1] != '*') {
            monstro2.x2--;
        } else if (dy > 0 && mapa_fase2[monstro2.y2 + 1][monstro2.x2] != '*') {
            monstro2.y2++;
        } else if (dy < 0 && mapa_fase2[monstro2.y2 - 1][monstro2.x2] != '*') {
            monstro2.y2--;
        }
    }  else {
        int random_move = rand() % 4;
        	switch (random_move) {
            case 0:
                if (mapa_fase2[monstro2.y2 - 1][monstro2.x2] != '*') {
                    monstro2.y2--;
                }
               	break;
            case 1:
                if (mapa_fase2[monstro2.y2 + 1][monstro2.x2] != '*') {
                    monstro2.y2++;
                }
                break;
            case 2:
                if (mapa_fase2[monstro2.y2][monstro2.x2 - 1] != '*') {
                    monstro2.x2--;
                }
            break;
            case 3:
                if (mapa_fase2[monstro2.y2][monstro2.x2 + 1] != '*') {
                    monstro2.x2++;
                }
            break;
        	}
    	}
}

void removePorta(int portaID) {
    int i, j;
    for (i = 0; i < numPortas; i++) {
        if (portas[i].portaID == portaID) {
            for (j = i; j < numPortas - 1; j++) {
                portas[j] = portas[j + 1];
            }
            numPortas--;
            break;
        }
    }
}

void removePortafase2(int portaIDfase2) {
    int i, j;
    for (i = 0; i < numPortasfase2; i++) {
        if (portasfase2[i].portaIDfase2 == portaIDfase2) {
            for (j = i; j < numPortasfase2 - 1; j++) {
                portasfase2[j] = portasfase2[j + 1];
            }
            numPortasfase2--;
            break;
        }
    }
}

void interacao_fase1() {
    int i;

    for (i = 0; i < numChaves; i++) {
        if (jogador_x == posicoes_chaves[i].x && jogador_y == posicoes_chaves[i].y) {
            printf("Voce pegou a chave %d!\n", posicoes_chaves[i].chaveID);
            Sleep(1000);

            int j;
            for (j = i; j < numChaves - 1; j++) {
                posicoes_chaves[j] = posicoes_chaves[j + 1];
            }
            numChaves--;

            int k;
            for (k = 0; k < numPortas; k++) {
                if (posicoes_chaves[i].chaveID == portas[k].portaID) {
                    portas[k].estaTrancada = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves[i].chaveID);
                    Sleep(1000);

                    mapa_fase1[portas[k].y][portas[k].x] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void interacao_fase2() {
    int i;

    for (i = 0; i < numChavesfase2; i++) {
        if (jogador_x == posicoes_chaves_fase2[i].x && jogador_y == posicoes_chaves_fase2[i].y) {
            printf("Voce pegou a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
            Sleep(1000);

            int j;
            for (j = i; j < numChavesfase2 - 1; j++) {
                posicoes_chaves_fase2[j] = posicoes_chaves_fase2[j + 1];
            }
            numChavesfase2--;

            int k;
            for (k = 0; k < numPortasfase2; k++) {
                if (posicoes_chaves_fase2[i].chaveIDfase2 == portasfase2[k].portaIDfase2) {
                    portasfase2[k].estaTrancada = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
                    Sleep(1000);

                    mapa_fase2[portasfase2[k].y][portasfase2[k].x] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void resetar_mapa_fase1(char mapa_fase1[ALTURA_TELA_FASE1][LARGURA_TELA_FASE1]) {
    jogador_x = LARGURA_TELA_FASE1 / 2;
    jogador_y = ALTURA_TELA_FASE1 / 2;
    jogador_vida = 3;
}

void resetar_mapa_fase2(char mapa_fase1[ALTURA_TELA_FASE2][LARGURA_TELA_FASE2]) {
    jogador_x = LARGURA_TELA_FASE2 / 2;
    jogador_y = ALTURA_TELA_FASE2 / 2;
    jogador_vida = 3;
}

void checa_dano_espinho() {
    if (mapa_fase1[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1 vez!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase1(mapa_fase1);
            }
        }
    }
}

void checa_dano_espinho_fase2() {
    if (mapa_fase2[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1 vez!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase2(mapa_fase2);
            }
        }
    }
}

void resetar_jogo() {
    if (contador_reiniciar_jogo >= 3) {
        contador_reiniciar_jogo = 0;
        jogo_em_execucao = 0; 
    }
}


void checa_dano_monstro() {
    if (jogador_x == monstro.x1 && jogador_y == monstro.y1) {
        jogador_vida--;
        printf("Voce foi atingido pelo monstro! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1 vez!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase1(mapa_fase1);
            }
        }
    }
}

void checa_dano_monstro2() {
    if (jogador_x == monstro2.x2 && jogador_y == monstro2.y2) {
        jogador_vida--;
        printf("Voce foi atingido pelo monstro nível 2! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou a fase!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase2(mapa_fase2);
            }
        }
    }
}

void desenhar_vida() {
    printf("Vida: ");
    int i;
    for (i = 0; i < jogador_vida; i++) {
        printf("&");
    }
    printf("\n");
}

int verificar_teleporte() {
    int i;
    for (i = 0; i < numTeleportes; i++) {
        if (jogador_x == teletransportes[i].x3 && jogador_y == teletransportes[i].y3) {
            jogador_x = teletransportes[i].x4;
            jogador_y = teletransportes[i].y4;
            return 1;
        } else if (jogador_x == teletransportes[i].x4 && jogador_y == teletransportes[i].y4) {
            jogador_x = teletransportes[i].x3;
            jogador_y = teletransportes[i].y3;
            return 1; 
        }
    }
    return 0; 
}

void interagir_com_botao() {
    int acao = rand() % 2;  
	
	if (jogador_x == botaofase2[0].x5 && jogador_y == botaofase2[0].y5) {
    	switch (acao) {
        	case 0:
            	printf("O botão causou dano ao jogador!\n");
            	jogador_vida--;
					if (jogador_vida <= 0) {
            			printf("|          GAME OVER!        |\n");
           				printf("|Você reiniciou a fase!|\n");
            			Sleep(1000);
            			contador_reiniciar_jogo++;
            				if (contador_reiniciar_jogo >= 3) {
                				jogo_em_execucao = 0;
            				} else {
                				resetar_mapa_fase2(mapa_fase2);
            				}
        				} 
            break;
        	case 1:
            	printf("O botão concedeu uma vida extra ao jogador!\n");
            	jogador_vida++;  
            break;
        default:
        	break;
    	}
	} 
}

int verificar_chegada_porta_transicao() {
    if (fase_atual == 1 && jogador_x == 0 && jogador_y == 13) {
        fase_atual = 2;
        jogador_x = LARGURA_TELA_FASE2 / 2;
        jogador_y = ALTURA_TELA_FASE2 / 2;
        definir_posicao_inicial_monstro();
        definir_posicao_inicial_monstro2();
		verificar_teleporte();
		interacao_fase2();
        return 1;
    }
    return 0;
}

void loop_da_fase1() {
    int y, x, k;
    
    while (jogo_em_execucao) {
        if (fase_atual == 1) {
            for (y = 0; y < ALTURA_TELA_FASE1; y++) {
                for (x = 0; x < LARGURA_TELA_FASE1; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        printf("&");
                    } else if (x == monstro.x1 && y == monstro.y1) {
                        printf("X");
                    } else {
                        int containsKey = 0;
                        for (k = 0; k < numChaves; k++) {
                            if (x == posicoes_chaves[k].x && y == posicoes_chaves[k].y) {
                                containsKey = 1;
                                break;
                            } 
                        }
                        if (containsKey) {
                            printf("@");
                        } else {
                            printf("%c", mapa_fase1[y][x]);
                        }
                    }
                }
                printf("\n");
            }
        }
        desenhar_vida();

        char input = getch();
        switch (input) {
            case TECLA_CIMA:
                movimento_cima_fase1();
                break;
            case TECLA_ESQUERDA:
                movimento_esquerda_fase1();
                break;
            case TECLA_BAIXO:
                movimento_baixo_fase1();
                break;
            case TECLA_DIREITA:
                movimento_direita_fase1();
                break;
            case CHAVE_INTERATIVA:
                interacao_fase1();
                break;
            default:
                break;
        }
        movimento_monstro_nivel1();
		checa_dano_monstro();
        checa_dano_espinho();
        system("cls");
        
        if (verificar_chegada_porta_transicao()) {
            fase_atual = 2;
            resetar_mapa_fase1(mapa_fase1);
            definir_posicao_inicial_monstro();
            break;
        }
    }
    if (fase_atual == 2) {
        loop_da_fase2(); 
    }
}

void loop_da_fase2() {
    int y, x, k;

    while (jogo_em_execucao) {
        if (fase_atual == 2) {
            for (y = 0; y < ALTURA_TELA_FASE2; y++) {
                for (x = 0; x < LARGURA_TELA_FASE2; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        printf("&");
                    } else if (x == monstro.x1 && y == monstro.y1) {
                        printf("X");
                    } else if (x == monstro2.x2 && y == monstro2.y2) {
                        printf("V");
                    } else if (x == teletransportes[0].x3 && y == teletransportes[0].y3) {
            			printf(">");
        			} else if (x == teletransportes[0].x4 && y == teletransportes[0].y4) {
            			printf(">");
        			} else if (x == botaofase2[0].x5 && y == botaofase2[0].y5) {
                        printf("O");
                    } else {
                        int containsKeyfase2 = 0;
                        for (k = 0; k < numChavesfase2; k++) {
                            if (x == posicoes_chaves_fase2[k].x && y == posicoes_chaves_fase2[k].y) {
                                containsKeyfase2 = 1;
                                break;
                            } 
                        }
                        if (containsKeyfase2) {
                            printf("@");
                        } else {
                            printf("%c", mapa_fase2[y][x]);
                        }
                    }
                }
                printf("\n");
            }
        }
        movimento_monstro_nivel1();
        movimento_monstro_nivel2();
        checa_dano_monstro();
        checa_dano_monstro2();
        desenhar_vida();
		verificar_teleporte();
		interacao_fase2();
		interagir_com_botao();
		checa_dano_espinho_fase2();
        char input = getch();
        switch (input) {
            case TECLA_CIMA:
                movimento_cima_fase2();
                break;
            case TECLA_ESQUERDA:
                movimento_esquerda_fase2();
                break;
            case TECLA_BAIXO:
                movimento_baixo_fase2();
                break;
            case TECLA_DIREITA:
                movimento_direita_fase2();
                break;
            default:
                break;
        }
        system("cls");
    }
}

void mostrar_menu() {
#define INICIAR '1'
#define TUTORIAL '2'
#define SAIR '3'

	system("cls");
 	printf(" \n");
    printf(" |TTTTT|  |EEEEE|  |CCCCC|  |H| |H|  |DDDD|   |U| |U|  |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|      /11111|\n");
	printf("   \\T/    |E|      |C|      |H|_|H|  |D|  D|  |U| |U|  |NN||N|  |G|      |E|     |O| |O| |NN||N| |S|         /11||11|\n");
	printf("   |T|    |EEEE|   |C|      |HHHHH|  |D|  D|  |U| |U|  |N|N|N|  |G| GG|  |EEEE|  |O| |O| |N|N|N| |SSSSS|         |11|\n");
	printf("   |T|    |E|      |C|      |H| |H|  |D|  D|  |U| |U|  |N||NN|  |G|  G|  |E|     |O| |O| |N||NN|     |S|  	 |11|\n");
	printf("   |T|    |EEEEE|  |CCCCC|  |H| |H|  |DDDD|    |UUU|   |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|  	 |11|\n");
    printf("           |1| Iniciar jogo\n");
    printf("           |2| Tutorial\n");
	printf("           |3|  Sair\n");
}


void show_tutorial() {
	system("cls");
    printf("           === TUTORIAL ===\n");
	printf("- Objetivo: Passar por três níveis, coletando uma chave em cada para abrir uma porta.\n");
    printf("- Comandos: W (cima), A (esquerda), S (baixo), D (direita), I (interagir).\n");
	printf(" - Símbolos:\n");
	printf(" & = Jogador.\n");
	printf(" * = Parede (não atravessável).\n");
	printf(" @ = Chave.\n");
   	printf(" D = Porta fechada.\n");
	printf(" = = Porta aberta (após pegar a chave).\n");
	printf(" O = Botão (interagir ao ficar em cima).\n");
	printf(" # = Espinho (reinicia fase ao tocar).\n");
	printf(" > = Teletransporte (em pares).\n");
	printf(" ¬ = Monstro nível 1 (movimento aleatório).\n");
	printf(" K = Monstro nível 2 (segue jogador).\n");
	printf(" Pressione qualquer tecla para continuar.\n");
    getch();
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 1);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = 0;
    SetConsoleCursorInfo(console, &cursor_info);
    system("mode con: cols=80 lines=24");
    system("cls");

    while (1) {
        mostrar_menu();
        char escolha = getch();

        switch (escolha) {
            case INICIAR:
                fase_atual = 1;
                definir_posicao_inicial_monstro();
                loop_da_fase1();
                definir_posicao_inicial_monstro2();
                break;
            case TUTORIAL:
                show_tutorial();
                break;
            case SAIR:
                return 0; 
                break;
            default:
                printf("Escolha invalida. Por favor, tente novamente.\n");
                Sleep(500);
                break;
        }
    }
    return 0;
}
