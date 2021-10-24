#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int main()
{
    int quantidade, quantidadeInserida, i, num;
    TabelaHash *a;
    float constante;

    i = 0;

    scanf("%f", &constante);
    scanf("%d", &quantidade);
    scanf("%d", &quantidadeInserida);

    int vetorEndereco[quantidadeInserida];

    a = criar_tabela_hash(quantidade);

    while(i != quantidadeInserida){
        scanf("%d", &num);
        vetorEndereco[i] = inserir_pensando_nas_colisoes_hash_multiplicacao_hackerrank_dois(constante, num, a);

        i++;
    }

    i = 0;
    while(i != quantidadeInserida){
        printf("%d\n", vetorEndereco[i]);

        i++;
    }

    printf("Busca: ");
    scanf("%d", num);
    printf("%d", buscar_elemento_na_tabela_hash_multiplicacao_hackerrank(constante, num, a));

    desalocar_tabela_hash(a);

    return 0;
}
