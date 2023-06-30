#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdbool.h>

struct PalavraEncontrada {/*registro para guardar as coordenadas das palvras*/
    char palavra[100];
    int i_inicial;
    int j_inicial;
    int i_final;
    int j_final;
};

void lerCacaPalavra(int tam, char mat[tam][tam]) { /*modulo para ler o caca-palavra*/
    int i;
    printf("Digite as letras do caca-palavra linha por linha:\n");
    for (i = 0; i < tam; i++) {
        printf("Linha [%d]: ", i);
        scanf(" %[^\n]s", mat[i]);
    }
}
bool verificarPalavra(int tam, char mat[tam][tam], int i_inicial, int j_inicial, int i_final, int j_final, char palavra[]) {
    int i, j;
    int p = strlen(palavra);

    if (i_final < i_inicial) {  // Verificar na direção oposta (de tras para frente)
        i = i_inicial;
        i_inicial = i_final;
        i_final = i;
        j = j_inicial;
        j_inicial = j_final;
        j_final = j;
    }

    int di = (i_final - i_inicial) / (p - 1);
    int dj = (j_final - j_inicial) / (p - 1);

    i = i_inicial;
    j = j_inicial;

    for (int k = 0; k < p; k++) {
        if (mat[i][j] != palavra[k]) {
            return false;  // Encontrou uma letra diferente, não é uma palavra valida
        }
        i += di;
        j += dj;
    }

    return true;  // Todas as letras correspondem a palavra

    
}

void buscarPalavras(int tam, char mat[tam][tam], struct PalavraEncontrada palavrasEncontradas[], int* numPalavrasEncontradas) {/*modulo para buscar as palavras*/
    int i, j, w, p = 0, i_inicial, j_inicial, i_final, j_final, ii, jj;
    char str[tam];

    while (1) {/*inicio da estrutura de repeticao para armazenar as palavras a serem buscadas*/
        printf("Digite as palavras a ser procuradas (digite '1' para finalizar): ");
        getc(stdin);
        scanf("%[^\n]s", str);

        if (strcmp(str, "1") == 0) {/*gdefinir o final da estrura de repeticao seja digitando "exit"*/
            break;
        }

        p = strlen(str);/*definindo que p recebe o tamanho da string*/
        
       

        for (ii = 0; ii < tam; ii++) {/* matriz para verificacao nas posicoes i e j da matriz */
            for (jj = 0; jj < tam; jj++) {
                i_inicial = ii;/* salva as posiÃ§oes iniciais */
                j_inicial = jj;
                i = ii;
                j = jj;
                w = 0;/* auxiliar w para a contagem de 0 ate o tamanho da palavra */
            
                while (w < p && mat[i][j] == str[w]) {/*procura para direita*/
                    i_final = i;/*salva as posicoes */
                    j_final = j;
                    w++;/* encremento do w para verificar a proxima casa do vetor da palavra */
                    j++;/*j anda 1 para a direita*/


                   if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra; /* vetor  recebe como tamanho o valor do ponteiro*/
                        (*numPalavrasEncontradas)++;/*aumenta em 1 o ponteiro*/
                
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura para esquerda */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    j--; /* 'j' anda 1 para esquerda */
                    if(j<0) /* se j for menor que 0 ele verifica a borda, ou seja o final da matriz, sendo tam-1 */
                        j=tam-1;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura para baixo */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i++; /* 'j' anda 1 para baixo */
                    if(i==tam) /* se i for == a tam, ele volta a borda 0 para verificacao  */
                        i=0;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura para cima */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i--; /* 'i' anda 1 para cima */
                    if(i<0) /* se i for < 0, ele volta a borda tam-1 para verificacao  */
                        i=tam-1;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura na diagonal direita baixo */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i++; /* 'i' anda 1 para baixo */
                    j++; /* 'j' anda ' para direita */
                    if(i==tam) /* se i == tam ele volta a borda 0 para verificaÃ§ao  */
                        i=0;
                    if(j==tam) /* se j == tam ele volta a borda 0 para verificaÃ§ao  */
                        j=0;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura na diagonal esquerda cima */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i--; /* i anda para cima */
                    j--; /* 'j' anda para esquerda */
                    if(i<0)     /* se i for < 0, ele volta a borda tam-1 para verificacao  */
                        i=tam-1;
                    if(j<0)      /* se j for < 0, ele volta a borda tam-1 para verificacao  */
                        j=tam-1;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura na diagonal esquerda baixo */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i++; /* 'i' anda 1 para baixo */
                    j--; /* 'j' anda para esquerda */
                    if(i==tam) /* se 'i' for o tamanho matriz ele volta para o 0 verificando a borda */
                        i=0;
                    if(j<0)
                        j=tam-1;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)) {/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
                i=ii;
                j=jj;
                w=0;
                while(w<p && mat[i][j]==str[w]){/* procura na diagonal direita cima */
                    i_final=i;/* salva as posicoes finais */
                    j_final=j;/*    i final e j final   */
                    w++; /* encremento do w para verificar a proxima casa do vetor da palavra */
                    i--; /* anda para cima */
                    j++; /* anda para direita */
                    if(i<0)  /* se i for < 0, ele volta a borda tam-1 para verificacao  */
                        i=tam-1;
                    if(j==tam) /* se j for o tamanho matriz ele volta para o 0 verificando a borda */
                        j=0;
                    if (w == p && verificarPalavra(tam, mat, i_inicial, j_inicial, i_final, j_final, str)){/* se encremento w for = p(tamanho da palavra) eh pq achou todas as letras da string a ser buscada */
                        struct PalavraEncontrada palavra;
                        strcpy(palavra.palavra, str);
                        palavra.i_inicial = i_inicial;
                        palavra.j_inicial = j_inicial;
                        palavra.i_final = i_final;
                        palavra.j_final = j_final;
                        palavrasEncontradas[*numPalavrasEncontradas] = palavra;
                        (*numPalavrasEncontradas)++;
                    }
                }
            }
        }
    }
}

void imprimirMatrizCaixaAlta(int tam, char mat[tam][tam]) {
    int i, j;
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            printf("%c ", toupper(mat[i][j]));
        }
        printf("\n");
    }
}
void imprimirPalavrasEncontradas(struct PalavraEncontrada palavrasEncontradas[], int numPalavrasEncontradas) {
    int i;
    printf("Palavras encontradas:\n");
    for (i = 0; i < numPalavrasEncontradas; i++) {
        printf("Palavra: %s (%d,%d) - (%d,%d)\n", palavrasEncontradas[i].palavra, palavrasEncontradas[i].i_inicial, palavrasEncontradas[i].j_inicial, palavrasEncontradas[i].i_final, palavrasEncontradas[i].j_final);
    }
    
}
void exibirCabecalho() {
    system("cls");
    printf("========================================================================================================\n");
    printf("============================================ CACA - PALAVRA ============================================\n");
    printf("========================================================================================================\n");
}

int main() {
    bool reiniciar = true;
    char resposta;
    int tam;
    while (reiniciar) {
        exibirCabecalho();
        printf("Quantas linhas tem o caca-palavra?: "); /*define o tamanho do caÃ§a palavra*/
        scanf("%d", &tam);

        char mat[tam][tam];
        struct PalavraEncontrada palavrasEncontradas[tam]; /*inicia o vetor*/
        int numPalavrasEncontradas = 0; /*inicia a variavel ponteiro*/

        lerCacaPalavra(tam, mat);/*invoca o modulo e manda as variaveis a serem utilizadas no msm*/
        
        exibirCabecalho();
        imprimirMatrizCaixaAlta(tam, mat);
        buscarPalavras(tam, mat, palavrasEncontradas, &numPalavrasEncontradas);/*invoca o modulo e manda as variaveis a serem utilizadas no msm 
        /*                                                                     (sendo &numPalavrasEncontradas o q recebe o endereÃ§o do ponteiro )*/
        exibirCabecalho();
        imprimirMatrizCaixaAlta(tam, mat);
        imprimirPalavrasEncontradas(palavrasEncontradas, numPalavrasEncontradas);
        
        
        printf("Deseja reiniciar o programa? (s/n): ");
        scanf(" %c", &resposta);

        if (resposta != 's' && resposta != 'S') {
            reiniciar = false;
        }
    } 
    return 0;
}
