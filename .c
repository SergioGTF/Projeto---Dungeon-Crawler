#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

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

char mapa_fase1[LARGURA_TELA_FASE1][ALTURA_TELA_FASE1] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

int mapa_fase2[LARGURA_TELA_FASE2][ALTURA_TELA_FASE2] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
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
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
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
    int portaIDfase1;
    int estaTrancadafase1;
} PortaFase1;

PortaFase1 portas_fase1[] = {
    {0, 13, 1, 1},  
};

int numPortasFase1 = sizeof(portas_fase1) / sizeof(portas_fase1[0]);

typedef struct {
    int x, y;
    int chaveIDfase1;
} PosicaoChaveFase1;

PosicaoChaveFase1 posicoes_chaves_fase1[] = {
    {1, 21, 1},  
};

int numChavesFase1 = sizeof(posicoes_chaves_fase1) / sizeof(posicoes_chaves_fase1[0]);

typedef struct {
    int x, y;
    int chaveIDfase2;
} PosicaoChaveFase2;

PosicaoChaveFase2 posicoes_chaves_fase2[] = {
    {1, 1, 1},  
};
int numChavesFase2 = sizeof(numChavesFase2) / sizeof(posicoes_chaves_fase2[0]);

typedef struct {
    int x, y;
    int portaIDfase2;
    int estaTrancadafase2;
} PortaFase2;

PortaFase2 portas_fase2[] = {
    {29, 29, 1, 1},   
};
int numPortasFase2 = sizeof(portas_fase2) / sizeof(portas_fase2[0]);

HANDLE console;

void movimento_cima_fase1() {
	int i;
    if (jogador_y > 0 && mapa_fase1[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortasFase1; i++) {
            if (next_x == portas_fase1[i].x && next_y == portas_fase1[i].y && portas_fase1[i].estaTrancadafase1) {
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

        for (i = 0; i < numPortasFase1; i++) {
            if (next_x == portas_fase1[i].x && next_y == portas_fase1[i].y && portas_fase1[i].estaTrancadafase1) {
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



void removePortaFase1(int portaIDfase1) {
    int i, j;
    for (i = 0; i < numPortasFase1; i++) {
        if (portas_fase1[i].portaIDfase1 == portaIDfase1) {
            for (j = i; j < numPortasFase1 - 1; j++) {
                portas_fase1[j] = portas_fase1[j + 1];
            }
            numPortasFase1--;
            break;
        }
    }
}

void interacao() {
    int i;

    for (i = 0; i < numChavesFase1; i++) {
        if (jogador_x == posicoes_chaves_fase1[i].x && jogador_y == posicoes_chaves_fase1[i].y) {
            printf("Voce pegou a chave %d!\n", posicoes_chaves_fase1[i].chaveIDfase1);
            Sleep(500);

            int j;
            for (j = i; j < numChavesFase1 - 1; j++) {
                posicoes_chaves_fase1[j] = posicoes_chaves_fase1[j + 1];
            }
            numChavesFase1--;

            int k;
            for (k = 0; k < numPortasFase1; k++) {
                if (posicoes_chaves_fase1[i].chaveIDfase1 == portas_fase1[k].portaIDfase1) {
                    portas_fase1[k].estaTrancadafase1 = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase1[i].chaveIDfase1);
                    Sleep(500);

                    mapa_fase1[portas_fase1[k].y][portas_fase1[k].x] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void checa_dano_espinho() {
    if (mapa_fase1[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(500);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1 vez!|\n");
            Sleep(2000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                reset_map(mapa_fase1);
            }
        }
    }
}


void reset_game() {
    reset_map(mapa_fase1);
    espinhos_tocados = 0;
    contador_reiniciar_jogo++;

    if (contador_reiniciar_jogo >= 3) {
        contador_reiniciar_jogo = 0;
        jogo_em_execucao = 0; 
    }
}

void reset_map_fase2(char map[ALTURA_TELA_FASE2][LARGURA_TELA_FASE2]) {
    jogador_x = LARGURA_TELA_FASE2 / 2;
    jogador_y = ALTURA_TELA_FASE2 / 2;
    jogador_vida = 3;
}

void reset_map(char map[ALTURA_TELA_FASE1][LARGURA_TELA_FASE1]) {
    jogador_x = LARGURA_TELA_FASE1 / 2;
    jogador_y = ALTURA_TELA_FASE1 / 2;
    jogador_vida = 3;
}

void desenhar_vida() {
    printf("Vida: ");
    int i;
    for (i = 0; i < jogador_vida; i++) {
        printf("&");
    }
    printf("\n");
}

int verificar_chegada_porta_transicao() {
    if (fase_atual == 1 && jogador_x == 0 && jogador_y == 13) {
        return 1; 
    }
    return 0; 
}

void game_loop_fase1() {
    int y, x, k;
    
    while (jogo_em_execucao) {
        if (fase_atual == 1) {
            for (y = 0; y < ALTURA_TELA_FASE1; y++) {
                for (x = 0; x < LARGURA_TELA_FASE1; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        printf("&");
                    } else {
                        int containsKey = 0;
                        for (k = 0; k < numChavesFase1; k++) {
                            if (x == posicoes_chaves_fase1[k].x && y == posicoes_chaves_fase1[k].y) {
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
            
            if (verificar_chegada_porta_transicao()) {
                fase_atual = 2; 
                reset_map(mapa_fase2); 
            }
        } 
		  else if (fase_atual == 2) {
            game_loop_fase2(); 
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
                interacao();
                break;
            default:
                break;
        }
        checa_dano_espinho();
        system("cls");
        SetConsoleCursorPosition(console, (COORD){0, 0});
    }
}


void movimento_cima_fase2() {
    int i;
    if (jogador_y > 0 && mapa_fase2[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortasFase2; i++) {
            if (next_x == portas_fase2[i].x && next_y == portas_fase2[i].y && portas_fase2[i].estaTrancadafase2) {
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

        for (i = 0; i < numPortasFase2; i++) {
            if (next_x == portas_fase2[i].x && next_y == portas_fase2[i].y && portas_fase2[i].estaTrancadafase2) {
                return; 
            }
        }

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

void checa_dano_espinho_fase2() {
    if (mapa_fase2[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(500);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1 vez!|\n");
            Sleep(2000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                reset_map_fase2(mapa_fase2);
            }
        }
    }
}

void interacao_fase2() {
    int i;
    for (i = 0; i < numChavesFase2; i++) {
        if (jogador_x == posicoes_chaves_fase2[i].x && jogador_y == posicoes_chaves_fase2[i].y) {
            printf("Voce pegou a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
            Sleep(500);

            int j;
            for (j = i; j < numChavesFase2 - 1; j++) {
                posicoes_chaves_fase2[j] = posicoes_chaves_fase2[j + 1];
            }
            numChavesFase2--;

            int k;
            for (k = 0; k < numPortasFase2; k++) {
                if (posicoes_chaves_fase2[i].chaveIDfase2 == portas_fase2[k].portaIDfase2) {
                    portas_fase2[k].estaTrancadafase2 = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
                    Sleep(500);

                    mapa_fase2[portas_fase2[k].y][portas_fase2[k].x] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void game_loop_fase2() {
    int y, x, k;

    while (jogo_em_execucao) {
        for (y = 0; y < ALTURA_TELA_FASE2; y++) {
            for (x = 0; x < LARGURA_TELA_FASE2; x++) {
                if (x == jogador_x && y == jogador_y) {
                    printf("&");
                } else {
                    int containsKey = 0;
                    for (k = 0; k < numChavesFase2; k++) {
                        if (x == posicoes_chaves_fase2[k].x && y == posicoes_chaves_fase2[k].y) {
                            containsKey = 1;
                            break;
                        } 
                    }
                    if (containsKey) {
                        printf("@");
                    } else {
                        printf("%c", mapa_fase2[y][x]);
                    }
                }
            }
            printf("\n");
        }
        desenhar_vida();

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
            case CHAVE_INTERATIVA:
                interacao_fase2();
                break;
            default:
                break;
        }
        checa_dano_espinho_fase2();

        system("cls");
        SetConsoleCursorPosition(console, (COORD){0, 0});
    }
}

void mostrar_menu() {
#define INICIAR '1'
#define TUTORIAL '2'
#define SAIR '3'

	system("cls");
 	printf(" \n");
    printf(" |TTTTT|  |EEEEE|  |CCCCC|  |H| |H|  |DDDD|   |U| |U|  |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|  /11111|						\n");
	printf("   \\T/   |E|      |C|      |H|_|H|  |D|  D|  |U| |U|  |NN||N|  |G|      |E|     |O| |O| |NN||N| |S|     /11||11|					\n");
	printf("   |T|    |EEEE|   |C|      |HHHHH|  |D|  D|  |U| |U|  |N|N|N|  |G| GG|  |EEEE|  |O| |O| |N|N|N| |SSSSS|      11|						\n");
	printf("   |T|    |E|      |C|      |H| |H|  |D|  D|  |U| |U|  |N||NN|  |G|  G|  |E|     |O| |O| |N||NN|     |S|  	 |11|					\n");
	printf("   |T|    |EEEEE|  |CCCCC|  |H| |H|  |DDDD|    |UUU|   |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|  	 |11|						\n");
    printf("           |1| Iniciar jogo\n");
    printf("           |2| Tutorial\n");
	printf("           |3|  Sair\n");
}


void show_tutorial() {
	system("cls");
    printf("                            === TUTORIAL ===\n");
	printf("  O jogo e uma aventura/quebra-cabeca onde o objetivo e passar por tres niveis.\n");
	printf("  Em cada nivel, voce deve se mover para recolher uma chave para abrir uma \n porta fechada.\n");
    printf("                 Voce pode usar os seguintes comandos:\n");
	printf(" |W | = Mover uma unidade para cima.\n");
	printf(" |A | = Move uma unidade para a esquerda.\n");
	printf(" |S | = Mover uma unidade para baixo.\n");
	printf(" |D | = Move uma unidade para a direita.\n");
   	printf(" |I | = Interagir com um objeto.\n");
	printf(" |& | = Simbolo que representa o jogador.\n");
	printf(" |* | = Simbolo que representa uma parede, o jogador ao se movimentar nÃ£o pode passar pela parede.\n");
	printf(" |@ | = Simbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave.\n");
	printf(" |D | =  Simbolo que representa a porta fechada.\n");
	printf(" |= | =  Simbolo que representa a porta aberta quando o jogador interage com a chave.\n");
	printf(" |O | = Simbolo que representa um botao que o usuario pode interagir, o botao fica no chao e o jogador deve ficar em cima dele para poder interagir.\n");
	printf(" |# | =  Simbolo que representa um espinho. A fase e reiniciada quando o jogador toca no espinho, caso a fase seja reiniciada tres vezes, o jogo volta para o menu principal.\n");
	printf(" |> | = Simbolo que representa um teletransporte. O teletransporte sempre deve vir em pares, quando o jogador toca em um ele e transportado para o outro e vice-versa.\n");
	printf(" |¬ | =  Simbolo que representa o monstro nivel 1. O mostro tem um movimento aleatório, logo, ele movimenta um bloco para cima ou para direita ou para esquerda ou para baixo. O mostro sempre faz uma movimentação depois do usuario se movimentar ou interagir com um objeto.\n");
	printf(" |K | =  Simbolo que representa o monstro nivel 2. O monstro nivel dois tem uma inteligência de se movimentar na direção do jogador. O monstro não precisa saber desviar de obstaculos, ele sempre vai andar em linha reta em direÃ§ao do jogador.\n");
	printf("                    Pressione qualquer tecla para continuar...\n");
    getch();
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 1);
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = 0;
    SetConsoleCursorInfo(console, &cursor_info);
    system("mode con: cols=80 lines=24");
    system("cls");

    while (jogo_em_execucao) {
        mostrar_menu();
        char escolha = getch();

        switch (escolha) {
            case INICIAR:
                fase_atual = 1;
                game_loop_fase1();
                break;
            case TUTORIAL:
                show_tutorial();
                break;
            case SAIR:
                jogo_em_execucao = 0;
                break;

            default:
                printf("Escolha invalida. Por favor, tente novamente.\n");
                Sleep(500);
                break;
        }

        system("cls");
	}
	return 0;
}
