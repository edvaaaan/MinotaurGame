#include <bits/stdc++.h>

using namespace std;

char** lerLabirinto(FILE *pf, int* nl, int* nc) {
    char** L = NULL;

    fscanf(pf,"%d %d\n", nl, nc); 
    L = (char**) malloc(*nl * sizeof(char*));

    for(int i = 0; i< *nl; i++) L[i] = (char*) malloc(*nc * sizeof(char));

    for(int i=0; i < *nl; i++) {
        for(int j=0; j < *nc; j++)
            fscanf(pf, "%c", &L[i][j]);
        fscanf(pf, "\n");
     }

    return L;
}

void imprimirLabirinto(char **L, int nl, int nc) {
    for(int i=0;i<nl; i++) {
        for(int j=0;j<nc; j++)
            printf("%c", L[i][j]);
        printf("\n");
    }
}

struct Entidade {
    int x = 0, y = 0, nivel = 0;
};

void posicao(char **L, int nl, int nc, Entidade &P, Entidade &M, Entidade &S) {

    for(int i=0; i < nl; i++) {
        for(int j=0; j < nc; j++) {
            if(L[i][j] == 'P') {
                P.y = i;
                P.x = j;
            } else if(L[i][j] == 'M') {
                M.y = i;
                M.x = j;
            } else if(L[i][j] == 'O') {
                S.y = i;
                S.x = j;
            }
        }
     }

}

bool vitoria(Entidade &P, Entidade &S) {
    return (P.y == S.y && P.x == S.x);
}

bool derrota(Entidade &P, Entidade &M) {
    return (P.y == M.y && P.x == M.x);
}

void movimento_jogador(char **L, Entidade &P) {

    cout << "Escolhar um direção para ir: ";

    vector<char> direcoes;
    
    if(L[P.y][P.x - 1] != '|') {
        cout << " Esquerda (a) ";
        direcoes.push_back('a');
    }
    if(L[P.y - 1][P.x] != '|') {
        cout << " Cima (w) ";
        direcoes.push_back('w');
    }
    if(L[P.y][P.x + 1] != '|') {
        cout << " Direita (d) ";
        direcoes.push_back('d');
    }
    if(L[P.y + 1][P.x] != '|') {
        cout << " Baixo (s) ";
        direcoes.push_back('s');
    }

    cout << "\n";

    char dir;
    cin >> dir;

    if(find(direcoes.begin(), direcoes.end(), dir) != direcoes.end()) {
        switch(dir) {
            case 'a':
                L[P.y][P.x] = '.';
                L[P.y][P.x - 1] = 'P';
                P.x--;
                break;
            case 'w':
                L[P.y][P.x] = '.';
                L[P.y - 1][P.x] = 'P';
                P.y--;
                break;
            case 'd':
                L[P.y][P.x] = '.';
                L[P.y][P.x + 1] = 'P';
                P.x++;
                break;
            case 's':
                L[P.y][P.x] = '.';
                L[P.y + 1][P.x] = 'P';
                P.y++;
                break;
        }
    } else {
        cout << "Direção inválida, digite novamente!\n";
    }

}

void minotauro_nivel_um(char **L, Entidade &M) {

    vector<char> direcoes;
    int tamanho = 0;
    
    if(L[M.y][M.x - 1] != '|') {
        direcoes.push_back('a');
        tamanho++;
    }
    if(L[M.y - 1][M.x] != '|') {
        direcoes.push_back('w');
        tamanho++;
    }
    if(L[M.y][M.x + 1] != '|') {
        direcoes.push_back('d');
        tamanho++;
    }
    if(L[M.y + 1][M.x] != '|') {
        direcoes.push_back('s');
        tamanho++;
    }

    int dir = tamanho > 1? rand() % tamanho : 0;
    char pos = direcoes[dir];

    switch(pos) {
        case 'a':
            L[M.y][M.x] = '.';
            L[M.y][M.x - 1] = 'M';
            M.x--;
            break;
        case 'w':
            L[M.y][M.x] = '.';
            L[M.y - 1][M.x] = 'M';
            M.y--;
            break;
        case 'd':
            L[M.y][M.x] = '.';
            L[M.y][M.x + 1] = 'M';
            M.x++;
            break;
        case 's':
            L[M.y][M.x] = '.';
            L[M.y + 1][M.x] = 'M';
            M.y++;
            break;
    }
}

void minotauro_nivel_tres(char **L, Entidade &P, Entidade &M) {

    if(M.x != P.x || M.y != P.y) {

        vector<char> direcoes;
    
        int tamanho = 0;

        if(L[M.y - 1][M.x] != '|') {
            if(M.y > P.y) {
                direcoes.push_back('w');
                tamanho++;
            }
        } 
        
        if(L[M.y + 1][M.x] != '|') {
            if(M.y < P.y) {
                direcoes.push_back('s');
                tamanho++;
            }
        } 
        
        if(L[M.y][M.x - 1] != '|') {
            if(M.x > P.x) {
                direcoes.push_back('a');
                tamanho++;
            }
        } 
        
        if(L[M.y][M.x + 1] != '|') {
            if(M.x < P.x) {
                direcoes.push_back('d');
                tamanho++;
            }
        }

        if(tamanho == 0) {
            if(L[M.y - 1][M.x] != '|') {
                direcoes.push_back('w');
                tamanho++;
            }

            if(L[M.y + 1][M.x] != '|') {
                direcoes.push_back('s');
                tamanho++;
            } 
            
            if(L[M.y][M.x - 1] != '|') {
                direcoes.push_back('a');
                tamanho++;
            } 
            
            if(L[M.y][M.x + 1] != '|') {
                direcoes.push_back('d');
                tamanho++;
            }
        }
    
        int dir = tamanho > 1? rand() % tamanho : 0;
        char pos = direcoes[dir];

        switch(pos) {
            case 'a':
                L[M.y][M.x] = '.';
                L[M.y][M.x - 1] = 'M';
                M.x--;
                break;
            case 'w':
                L[M.y][M.x] = '.';
                L[M.y - 1][M.x] = 'M';
                M.y--;
                break;
            case 'd':
                L[M.y][M.x] = '.';
                L[M.y][M.x + 1] = 'M';
                M.x++;
                break;
            case 's':
                L[M.y][M.x] = '.';
                L[M.y + 1][M.x] = 'M';
                M.y++;
                break;
        }

    }

}

void movimento_minotauro(char **L, Entidade &P, Entidade &M) {
    if(M.nivel == 1) {
        minotauro_nivel_um(L, M);
    } else if(M.nivel == 2) {
        minotauro_nivel_um(L, M);
        minotauro_nivel_um(L, M);
    } else if(M.nivel == 3) {
        minotauro_nivel_tres(L, P, M);
    }
}

char selecao_nivel_fase() {
    cout << "Selecione o nível da fase: 1, 2 ou 3\n";
    char nivel = '9';
    while(nivel != '1' && nivel != '2' && nivel != '3') {
        cin >> nivel;

        if(nivel == '1' || nivel == '2' || nivel == '3') return nivel;
        
        cout << "Nível inválido, tente novamente!\n";
    }
}

void selecao_nivel_minotauro(Entidade &M) {
    cout << "Selecione o nível do minotauro: 1, 2 ou 3\n";
    char nivel = '9';
    while(nivel != '1' && nivel != '2' && nivel != '3') {
        cin >> nivel;

        if(nivel == '1') {
            M.nivel = 1;
        } else if(nivel == '2') {
            M.nivel = 2;
        } else if(nivel == '3') {
            M.nivel = 3;
        } else {
            cout << "Nível inválido, tente novamente!\n";
        }
    }
}

int main(){

    char **L = NULL;
    int nl = 0, nc = 0;
    FILE *pf = NULL;

    Entidade P, M, S;

    char fase = selecao_nivel_fase();

    if(fase == '1') {
        pf = fopen("nivel1.txt", "r");
    } else if(fase == '2') {
        pf = fopen("nivel2.txt", "r");
    } else {
        pf = fopen("nivel3.txt", "r");
    }

    if(pf == NULL) { 
        printf("Falha ao ler o aquivo!\n\n");
    } else {
        L = lerLabirinto(pf, &nl, &nc);
        fclose(pf);

        selecao_nivel_minotauro(M);

        posicao(L, nl, nc, P, M, S); 
        imprimirLabirinto(L, nl, nc);

        movimento_jogador(L, P);
        movimento_minotauro(L, P, M);

        imprimirLabirinto(L, nl, nc);

        while(true) {
            movimento_jogador(L, P);
            movimento_minotauro(L, P, M);

            if(vitoria(P, S)) {
                imprimirLabirinto(L, nl, nc);
                cout << "Você Venceu!\n";
                break;
            } else if(derrota(P, M)) {
                imprimirLabirinto(L, nl, nc);
                cout << "Você Perdeu!\n";
                break;
            }

            imprimirLabirinto(L, nl, nc);
        }        

        for(int i=0; i <nl; i++) free(L[i]);
        free(L);
    }

    return 0;
}