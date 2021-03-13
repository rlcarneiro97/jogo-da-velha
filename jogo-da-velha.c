#include <stdio.h>
#include <stdlib.h>

#define DIM 3
int vez;

void LimpaTabuleiro(int tabuleiro[][DIM]){

    int i, j;

    for(i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            tabuleiro[i][j] = 0;
        }
    }
}

void ExibeTabuleiro(int tabuleiro[][DIM]){

    int i, j;

    for(i = 0; i < DIM; i++){
        printf("\n|");
        for(j = 0; j < DIM; j++){
            if(tabuleiro[i][j] == 1){
                printf(" X |");
            }else if(tabuleiro[i][j] == -1){
                printf(" O |");
            }else{
                printf("   |");
            }
        }
    }
}

void Pausar(){
    printf("\nPressione qualquer tecla para continuar. . .");
    fflush(stdin);
    getchar();
}

void LimpaTela(){
    system("cls || clear");
}

int Menu(){

    unsigned int opcao = 0;

    printf("\n|---------- Jogo da Velha ----------|\n");
    printf("\n1 - Jogar\n");
    printf("\n0 - Sair\n");
    printf("\nOpcao: ");
    scanf("%d", &opcao);

    if(opcao == 1){
        return 1;
    }else if(opcao == 0){
        return 0;
    }else{
        printf("\nDigite uma opcao valida!\n");
        Pausar();
        LimpaTela();
        return opcao;
    }

}

void Jogar(int tabuleiro[][DIM]){
    
    LimpaTabuleiro(tabuleiro);

    while(!VerificaTermino(tabuleiro)){
        LimpaTela();
        ExibeTabuleiro(tabuleiro);
        AplicarJogada(tabuleiro);
    }
}

void AplicarJogada(int tabuleiro[][DIM]){
    
    int linha = 0, coluna = 0;

    printf("\n\n>>> Jogador %d\n", vez);
    printf("\nLinha: ");
    scanf("%d", &linha);
    printf("\nColuna: ");
    scanf("%d", &coluna);

    if(VerificaInsercao(tabuleiro, linha, coluna)){
        if(vez == 1){
            tabuleiro[linha-1][coluna-1] = 1;
        }else if(vez == 2){
            tabuleiro[linha-1][coluna-1] = -1;
        }

        if(vez == 1){
        vez = 2;
        }else if(vez == 2){
            vez = 1;
        }
    }else{
        printf("\nJogada invalida! Jogue Novamente!\n");
        Pausar();
    }

}

int VerificaInsercao(int tabuleiro[][DIM], int linha, int coluna){
    
    if((tabuleiro[linha-1][coluna-1] != 0) || linha < 0 || linha > DIM || coluna < 0 || coluna > DIM){
        return 0;
    }else{
        return 1;
    }
}

int VerificaLinha(int tabuleiro[][DIM]){

    int i, j, cont = 0;

    for(i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            cont += tabuleiro[i][j];
        }

        if(cont == DIM || cont == -DIM){
            return 1;
        }
    }

    return 0;
}

int VerificaColuna(int tabuleiro[][DIM]){
    
    int i, j, cont = 0;

    for(j = 0; j < DIM; j++){
        for(i = 0; i < DIM; i++){
            cont += tabuleiro[i][j];
        }

        if(cont == DIM || cont == -DIM){
            return 1;
        }
    }

    return 0;
}

int VerificaDiagonal(int tabuleiro[][DIM]){
    
    int diagonal1 = 0, diagonal2 = 0, i;

    for(i = 0; i < DIM; i++){
        diagonal1 += tabuleiro[i][i];
        diagonal2 += tabuleiro[ (DIM-1)-i ][i];
    }

    if(diagonal1 == DIM || diagonal1 == -DIM || diagonal2 == DIM || diagonal2 == -DIM){
        return 1;
    }

    return 0;
}

int VerificaEmpate(int tabuleiro[][DIM]){
    
    int i, j;

    for(i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            if(tabuleiro[i][j] == 0){
                return 0;
            }
        }
    }

    return 1;
}

int VerificaTermino(int tabuleiro[][DIM]){
    
    if(VerificaLinha(tabuleiro) || VerificaColuna(tabuleiro) || VerificaDiagonal(tabuleiro)){
        
        ExibeTabuleiro(tabuleiro);

        if(vez == 1){
            printf("\n\nFim de jogo. O jogador %d ganhou!\n", vez+1);
        }else if(vez == 2){
            printf("\n\nFim de jogo. O jogador %d ganhou!\n", vez-1);
        }
        Pausar();
        LimpaTela();
        return 1;
    }

    if(VerificaEmpate(tabuleiro)){
        ExibeTabuleiro(tabuleiro);
        printf("\n\nJogo encerrado. Ocorreu um empate!\n");
        Pausar();
        LimpaTela();
        return 1;
    }

    return 0;
}

int main(void){

    int tabuleiro[DIM][DIM];
    int continuar = 1;

    LimpaTela();

    while(continuar){
        vez = 1;
        continuar = Menu();
        if(continuar == 1){
            Jogar(tabuleiro);
        }
    }
    
    Pausar();
    return 0;
}