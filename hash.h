typedef struct hashT TabelaHash;

TabelaHash* criar_tabela_hash(unsigned int tamanhoDaTabela);
//static int hashing_por_resto_da_divisao(int chave, int tamanhoDaTabela);
//static int hashing_por_multiplicacao(unsigned float constante, int chave, int tamanhoTabela);
//static int reHash_hackerrank(int endereco_original, int chave, int tentativa, int tamanhoTabela);
//static int reHash_overflow_progressivo(int endereco_original, int tamanhoTabela, int tentativa);
bool inserir_sem_pensar_nas_colisoes_hash_multiplicacao(float constante, int chave, TabelaHash *tabela);
bool inserir_sem_pensar_nas_colisoes_hash_resto_divisao(int chave, TabelaHash *tabela);
bool inserir_pensando_nas_colisoes_hash_multiplicacao_hackerrank(float constante, int chave, TabelaHash *tabela);
bool inserir_pensando_nas_colisoes_hash_multiplicacao(float constante, int chave, TabelaHash *tabela);
int inserir_pensando_nas_colisoes_hash_multiplicacao_hackerrank_dois(float constante, int chave, TabelaHash *tabela);
bool desalocar_tabela_hash(TabelaHash *a);
