#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

//Hashing: processamento de uma chave(parte do conteudo de um item) resultando em um endereço(posição no arranjo)

struct hashT{
    unsigned int tamanho;
    int *buckets;
};

TabelaHash* criar_tabela_hash(unsigned int tamanhoDaTabela){
    TabelaHash *a;
    int i;

    a = (TabelaHash*)malloc(sizeof(TabelaHash));

    a->tamanho = tamanhoDaTabela;
    a->buckets = (int*)malloc(sizeof(int) * tamanhoDaTabela);

    for(i=0; i<a->tamanho; i++){
        a->buckets[i] = -1;
    }

    return a;
}

static int hashing_por_resto_da_divisao(int chave, int tamanhoDaTabela){
    return chave % tamanhoDaTabela;
}

static int hashing_por_multiplicacao(float constante, int chave, int tamanhoTabela){
    float parteDecimal, resultado;
    int parteInteira = -1;

    if(constante > 0 && constante < 1){
        resultado = constante * chave;
        parteDecimal = resultado - (int)resultado;

        resultado = tamanhoTabela * parteDecimal;

        parteInteira = (int)resultado;
    }
    return parteInteira;
}

bool inserir_sem_pensar_nas_colisoes_hash_multiplicacao(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == -1){
            tabela->buckets[enderecoResultante] = chave;

            return true;
        }
    }
    return false;
}

bool inserir_sem_pensar_nas_colisoes_hash_resto_divisao(int chave, TabelaHash *tabela){
    int enderecoResultante;

    if(tabela != NULL){
        enderecoResultante = hashing_por_resto_da_divisao(chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == -1){
            tabela->buckets[enderecoResultante] = chave;

            return true;
        }
    }
    return false;
}

static int reHash_overflow_progressivo(int endereco_original, int tamanhoTabela, int tentativa){
    return (endereco_original + tentativa) % tamanhoTabela;
}

static int reHash_hackerrank(int endereco_original, int chave, int tentativa, int tamanhoTabela){
    int h2;

    h2 = 1 + chave % (tamanhoTabela - 1);

    return (endereco_original + tentativa * h2) % tamanhoTabela;
}

bool inserir_pensando_nas_colisoes_hash_multiplicacao_hackerrank(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;
    int i, reHashEndereco;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == -1){
            tabela->buckets[enderecoResultante] = chave;

            return true;
        }
        else{ // enderecoResultante não vazio
            i = 1;
            reHashEndereco = enderecoResultante;

            while((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] != chave) && (tabela->buckets[reHashEndereco] != -1)){
                reHashEndereco = reHash_hackerrank(enderecoResultante, chave, i, tabela->tamanho);

                i++;
            }

            if((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] == -1)){
                tabela->buckets[reHashEndereco] = chave;

                return true;
            }
        }
    }
    return false;
}

int inserir_pensando_nas_colisoes_hash_multiplicacao_hackerrank_dois(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;
    int i, reHashEndereco;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == -1){
            tabela->buckets[enderecoResultante] = chave;

            //printf("\nInserir: %d\n", tabela->buckets[enderecoResultante]);

            return enderecoResultante;
        }
        else{ // enderecoResultante não vazio
            i = 1;
            reHashEndereco = enderecoResultante;

            while((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] != chave) && (tabela->buckets[reHashEndereco] != -1)){
                reHashEndereco = reHash_hackerrank(enderecoResultante, chave, i, tabela->tamanho);

                i++;
            }

            if((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] == -1)){
                tabela->buckets[reHashEndereco] = chave;

                //printf("\nInserir ReHash: %d\n", tabela->buckets[reHashEndereco]);

                return reHashEndereco;
            }
        }
    }
    return -1;
}

bool inserir_pensando_nas_colisoes_hash_multiplicacao(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;
    int i, reHashEndereco;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == -1){
            tabela->buckets[enderecoResultante] = chave;

            return true;
        }
        else{ // enderecoResultante não vazio
            i = 1;
            reHashEndereco = enderecoResultante;

            while((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] != chave) && (tabela->buckets[reHashEndereco] != -1)){
                reHashEndereco = reHash_overflow_progressivo(enderecoResultante, tabela->tamanho, i);

                i++;
            }

            if((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] == -1)){
                tabela->buckets[reHashEndereco] = chave;

                return true;
            }
        }
    }
    return false;
}

int buscar_elemento_na_tabela_hash_multiplicacao(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;
    int i, reHashEndereco;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == chave){
            return enderecoResultante;
        }
        else if(tabela->buckets[enderecoResultante] != -1){ // enderecoResultante não vazio
            i = 1;
            reHashEndereco = enderecoResultante;

            while((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] != chave) && (tabela->buckets[reHashEndereco] != -1)){
                reHashEndereco = reHash_overflow_progressivo(enderecoResultante, tabela->tamanho, i);

                i++;
            }

            if((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] == -1)){
                return reHashEndereco;
            }
        }
    }
    return -1;
}

int buscar_elemento_na_tabela_hash_multiplicacao_hackerrank(float constante, int chave, TabelaHash *tabela){
    int enderecoResultante;
    int i, reHashEndereco;

    if(tabela != NULL){
        enderecoResultante = hashing_por_multiplicacao(constante, chave, tabela->tamanho);

        if(tabela->buckets[enderecoResultante] == chave){
            return enderecoResultante;
        }
        else if(tabela->buckets[enderecoResultante] != -1){ // enderecoResultante não vazio
            i = 1;
            reHashEndereco = enderecoResultante;

            while((i <= tabela->tamanho) && (tabela->buckets[reHashEndereco] != chave) && (tabela->buckets[reHashEndereco] != -1)){
                reHashEndereco = reHash_hackerrank(enderecoResultante, chave, i, tabela->tamanho);

                i++;
            }

            if((i < tabela->tamanho) && (tabela->buckets[reHashEndereco] == -1)){
                return reHashEndereco;
            }
        }
    }
    return -1;
}

bool desalocar_tabela_hash(TabelaHash *a){
    if(a != NULL){
        free(a);
        return true;
    }
    return false;
}

