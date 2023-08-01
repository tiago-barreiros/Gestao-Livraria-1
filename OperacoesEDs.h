//____________________OperacoesPrimarias.h_______________________________

void MostrarElementoLivro(LIVRO X)
{
    printf("%ld\n", X.ISBN);
    printf("%s\n", X.Titulo);
    printf("%s\n", X.Idioma);
    printf("%s\n", X.FirstAuthor);
    printf("%s\n", X.SndAuthor);
    printf("%s\n", X.Editora);
    printf("%d\n", X.AnoPub);
    printf("%s\n", X.AreaCientifica);
    printf("%f\n", X.Preco);
    printf("%d\n", X.Stock);
}

//___________________OperacoesPrimariasListaCompras.h____________________________
void MostrarElementoCompra(COMPRA X)
{
    printf("Titulo: %s\n", X.Produto);
    printf("Data Compra: %d - %d - %d\n", X.dataCompra.Dia, X.dataCompra.Mes, X.dataCompra.Ano);
    printf("Quantidade: %d\n", X.qtd);
    printf("Preço: %f\n", X.preco);
}

// comparação de 2 elementos do tipo COMPRA, segundo o campo NIF
int CompararElementosCompra(COMPRA X, COMPRA Y)
{ // devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
    if (X.Produto == Y.Produto)
        return 1;
    else
        return 0;
}

// comparação de 2 elementos do tipo INFO, segundo o campo NIF
//   devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int CompararElementosCliente(CLIENTE X, CLIENTE Y)
{
    if (X.NIF > Y.NIF)
        return 1;
    if (X.NIF < Y.NIF)
        return -1;
    return 0;
}

// comparação de 2 elementos do tipo Livro, segundo o campo ISBN
//   devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int CompararElementosLivros(LIVRO X, LIVRO Y)
{
    if (X.ISBN == Y.ISBN)
        return 1;

    return 0;
}

int VaziaCompra(nodoCompras L)
{
    if (L == NULL)
        return 1;
    else
        return 0;
}

void ListarCompra(nodoCompras L)
{
    nodoCompras P = L;
    while (P != NULL)
    {
        printf("-------------------------------\n");
        MostrarElementoCompra(P->Elemento);
        printf("-------------------------------\n");
        P = P->Prox;
    }
    printf("\n\n");
}

void MostrarCliente(CLIENTE X)
{
    printf("%d\n", X.NIF);
    printf("%s\n", X.Nome);
    printf("%s\n", X.Morada);
    printf("%d\n", X.Telefone);
    if (VaziaCompra(X.ListaDeCompras))
    {
        printf("[]\n");
    }
    else
    {
        ListarCompra(X.ListaDeCompras);
    }
}

nodeC CriarAB()
{
    nodeC T;
    T = NULL;
    return T;
}

int ABVazia(nodeC T)
{
    if (T == NULL)
        return 1;
    return 0;
}

nodeC CriarNodoAB(CLIENTE X)
{
    nodeC P = (nodeC)malloc(sizeof(struct nodoCliente));
    if (P == NULL)
        return NULL;
    P->client = X;
    P->left = NULL;
    P->right = NULL;
    return P;
}

nodeC LibertarNodoAB(nodeC P)
{
    P->left = NULL;
    P->right = NULL;
    free(P);
    P = NULL;
    return P;
}

nodeC DestruirAB(nodeC T)
{
    if (T == NULL)
        return NULL;
    T->left = DestruirAB(T->left);
    T->right = DestruirAB(T->right);
    return LibertarNodoAB(T);
}

nodeC CopiarAB(nodeC T)
{
    nodeC E, D, R; // R é a nova árvore, que é uma cópia de T
    R = CriarAB();
    if (T == NULL)
        return R;
    E = CopiarAB(T->left);
    D = CopiarAB(T->right);
    R = CriarNodoAB(T->client);
    R->left = E;
    R->right = D;
    return R;
}

int ABIguais(nodeC T, nodeC R)
{
    if (T == NULL && R == NULL) // se são ambas nulas, então são iguais
        return 1;
    if (T == NULL || R == NULL) // se uma delas é nula, então são diferentes
        return 0;
    if (CompararElementosCliente(T->client, R->client) != 0) // raízes diferentes, árvores diferentes
        return 0;
    if (ABIguais(T->left, R->left) == 0) // subárvores esq. diferentes
        return 0;
    if (ABIguais(T->right, R->right) == 0) // subárvores rights diferentes
        return 0;
    return 1; // caso contrário, são iguais
}

int NumeroNodosAB(nodeC T)
{
    int e, d;
    if (T == NULL)
        return 0;
    e = NumeroNodosAB(T->left);
    d = NumeroNodosAB(T->right);
    return (e + d + 1);
}

int AlturaAB(nodeC T)
{
    int e, d;
    if (T == NULL)
        return -1;
    e = AlturaAB(T->left);
    d = AlturaAB(T->right);
    if (e > d)
        return (e + 1); // e (altura da left), 1 a raiz
    else
        return (d + 1); // d (altura da right), 1 a raiz
}

void ListarPreOrdemAB(nodeC T)
{
    if (T != NULL)
    {
        MostrarCliente(T->client);
        ListarPreOrdemAB(T->left);
        ListarPreOrdemAB(T->right);
    }
}

void ListarEmOrdemAB(nodeC T)
{
    if (T != NULL)
    {
        ListarEmOrdemAB(T->left);
        MostrarCliente(T->client);
        ListarEmOrdemAB(T->right);
    }
}

void ListarPosOrdemAB(nodeC T)
{
    if (T != NULL)
    {
        ListarPosOrdemAB(T->left);
        ListarPosOrdemAB(T->right);
        MostrarCliente(T->client);
    }
}

int PesquisarABP(nodeC T, CLIENTE X)
{ // 0 = nao existe; 1 = existe
    if (T == NULL)
        return 0;
    if (CompararElementosCliente(X, T->client) == 0)
        return 1;
    if (CompararElementosCliente(X, T->client) == -1) // X.NIF < (T->client).NIF)
        return PesquisarABP(T->left, X);
    else
        return PesquisarABP(T->right, X);
}

nodeC NodoMaiorclientABP(nodeC T)
{
    if (T == NULL)
        return NULL;
    if (T->right == NULL)
        return T;
    return NodoMaiorclientABP(T->right);
}

nodeC NodoMenorclientABP(nodeC T)
{
    if (T == NULL)
        return NULL;
    if (T->left == NULL)
        return T;
    return NodoMenorclientABP(T->left);
}

nodeC InserirABP(nodeC T, CLIENTE X)
{
    if (T == NULL)
    {
        T = CriarNodoAB(X);
        return T;
    }
    if (CompararElementosCliente(X, T->client) == -1) // X.NIF < (T->client).NIF)
        T->left = InserirABP(T->left, X);
    else
        T->right = InserirABP(T->right, X);
    return T;
}

nodeC SubstituirNodoright(nodeC T, CLIENTE *X)
{
    nodeC PAux;
    if (T->left == NULL)
    {
        *X = T->client;
        PAux = T;
        T = T->right;
        PAux = LibertarNodoAB(PAux);
        return T;
    }
    T->left = SubstituirNodoright(T->left, X);
    return T;
}

nodeC SubstituirNodoleft(nodeC T, CLIENTE *X)
{
    nodeC PAux;
    if (T->right == NULL)
    {
        *X = T->client;
        PAux = T;
        T = T->left;
        PAux = LibertarNodoAB(PAux);
        return T;
    }
    T->right = SubstituirNodoleft(T->right, X);
    return T;
}

nodeC RemoverNodoABP(nodeC T)
{
    nodeC R;
    CLIENTE X;
    if (T->left == NULL && T->right == NULL)
    { // T é uma folha
        T = LibertarNodoAB(T);
        return T;
    }
    if (T->left == NULL)
    { //  só um filho direito
        R = T;
        T = T->right;
        R = LibertarNodoAB(R);
        return T;
    }
    if (T->right == NULL)
    { // só um filho esquerdo
        R = T;
        T = T->left;
        R = LibertarNodoAB(R);
        return T;
    }
    // 2 filhos (1º caso): remover o nodo sucessor (nodo mais à left da subárvore right) e copiar a sua informação
    T->right = SubstituirNodoright(T->right, &X);
    // 2 filhos (2º caso): remover o nodo antecessor (nodo mais à right da subárvore left) e copiar a sua informação
    //	T->left = SubstituirNodoleft(T->left, &X);	// 2º caso
    T->client = X;
    return T;
}

nodeC RemoverABP(nodeC T, CLIENTE X)
{
    if (CompararElementosCliente(X, T->client) == 0)
    {
        T = RemoverNodoABP(T);
        return T;
    }
    if (CompararElementosCliente(X, T->client) == -1)
        T->left = RemoverABP(T->left, X);
    else
        T->right = RemoverABP(T->right, X);
    return T;
}

//_____________________ArvoresBinariasBalanceadas.h_____________________________________
void ABPEqInsercaoBinaria(nodeC *TE, CLIENTE L[], int inicio, int fim)
{
    int meio;
    if (inicio > fim)
        return;
    if (inicio == fim)
    {
        *TE = InserirABP(*TE, L[inicio]);
        return;
    }

    meio = (inicio + fim) / 2;
    *TE = InserirABP(*TE, L[meio]);
    ABPEqInsercaoBinaria(TE, L, inicio, meio - 1);
    ABPEqInsercaoBinaria(TE, L, meio + 1, fim);
}

void CriarSequenciaEmOrdem(nodeC T, CLIENTE L[], int *N)
{
    if (T != NULL)
    {
        CriarSequenciaEmOrdem(T->left, L, N);
        L[*N] = T->client;
        *N = (*N) + 1;
        CriarSequenciaEmOrdem(T->right, L, N);
    }
}

nodeC CriarABEquilibrada(nodeC T)
{
    CLIENTE *Lista;
    nodeC TE;
    int N = 0, Num;
    TE = CriarAB();
    Num = NumeroNodosAB(T);
    if (T == NULL)
        return NULL;
    Lista = (CLIENTE *)malloc(Num * sizeof(CLIENTE));
    if (Lista == NULL)
        return NULL;
    CriarSequenciaEmOrdem(T, Lista, &N);
    ABPEqInsercaoBinaria(&TE, Lista, 0, N - 1);
    return TE;
}

//____________________________EADFilas.h___________________________________
// Operações sobre o Nodo

nodeE CriarNodoFila(ENCOMENDA X)
{
    nodeE P;
    P = (nodeE)malloc(sizeof(struct nodeEncomenda));
    if (P == NULL)
        return NULL;
    P->encomenda = X;
    P->next = NULL;
    return P;
}

nodeE LibertarNodoFila(nodeE P)
{
    free(P);
    P = NULL;
    return P;
}

// Operações sobre a Pilha

nodeE CriarFila()
{
    nodeE P;
    P = NULL;
    return P;
}

int FilaVazia(nodeE Fila)
{
    if (Fila == NULL)
        return 1;
    else
        return 0;
}

nodeE Juntar(ENCOMENDA X, nodeE Fila)
{
    nodeE Novo, PAnt;
    Novo = CriarNodoFila(X);
    if (Novo == NULL)
        return Fila;
    if (FilaVazia(Fila))
    {
        Fila = Novo;
        return Fila;
    }
    PAnt = Fila;
    while (PAnt->next != NULL)
        PAnt = PAnt->next;
    PAnt->next = Novo;
    return Fila;
}

nodeE Remover_Fila(nodeE Fila)
{
    nodeE P;
    P = Fila;
    Fila = Fila->next;
    P = LibertarNodoFila(P);
    return Fila;
}

ENCOMENDA Frente(nodeE Fila)
{
    return Fila->encomenda;
}

void MostrarEncomenda(ENCOMENDA X)
{
    printf("%d\n", X.ISBNLivro);
    printf("%d\n", X.NIFCliente);
    printf("%d %d %d\n", X.DataCompra.Dia, X.DataCompra.Mes, X.DataCompra.Ano);
    printf("%d\n", X.Qnt);
    printf("%f\n", X.PrecoTotal);
}

//_________________________ListasLigadasDuplas.h__________________________
void CriarLivro(nodeL *Head, nodeL *Tail)
{
    *Head = NULL;
    *Tail = NULL;
}

nodeL CriarNodoLivro(LIVRO X)
{
    nodeL P;
    P = (nodeL)malloc(sizeof(struct nodeL));
    if (P == NULL)
        return NULL;
    P->book = X;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

nodeL LibertarNodoLivro(nodeL P)
{
    free(P);
    P = NULL;
    return P;
}

int VaziaLivro(nodeL Head)
{
    if (Head == NULL)
        return 1;
    else
        return 0;
}

void ListarLivro(nodeL Head)
{
    nodeL P = Head;
    while (P != NULL)
    {
        MostrarElementoLivro(P->book);
        P = P->next;
    }
    printf("\n\n");
}

void ListarLivroContrario(nodeL Tail)
{
    nodeL P = Tail;
    while (P != NULL)
    {
        MostrarElementoLivro(P->book);
        P = P->prev;
    }
    printf("\n\n");
}

int TamanhoLivro(nodeL Head)
{
    nodeL P = Head;
    int tam = 0;
    while (P != NULL)
    {
        tam++;
        P = P->next;
    }
    return tam;
}

// consultar/pesquisar elemento a partir da cabeça
int ConsultarCabecaLivro(nodeL Head, LIVRO X)
{
    nodeL P = Head;
    if (Head == NULL)
        return 0;
    while (CompararElementosLivros(P->book, X) != 1 && P->next != NULL)
        P = P->next;
    if (CompararElementosLivros(P->book, X) == 1)
        return 1;
    return 0;
}

// procurar o nodo com um elemento X a partir da cabeça (existe nodo com X)
nodeL ProcurarLivro(nodeL Head, LIVRO X)
{
    nodeL P = Head;
    while (CompararElementosLivros(P->book, X) != 1)
        P = P->next;
    return P;
}

void InserirPrimeiroElementoLivro(nodeL *Head, nodeL *Tail, LIVRO X)
{
    nodeL P;
    P = CriarNodoLivro(X);
    if (P != NULL)
    {
        *Head = P;
        *Tail = P;
    }
}

nodeL InserirCabecaLivro(nodeL Head, LIVRO X)
{
    nodeL P;
    P = CriarNodoLivro(X);
    if (P == NULL)
        return Head;
    P->next = Head;
    Head->prev = P;
    Head = P;
    return Head;
}

nodeL InserirCaudaLivro(nodeL Tail, LIVRO X)
{
    nodeL P;
    P = CriarNodoLivro(X);
    if (P == NULL)
        return Tail;
    Tail->next = P;
    P->prev = Tail;
    Tail = P;
    return Tail;
}

void RemoverUnicoElementoLivro(nodeL *Head, nodeL *Tail)
{
    nodeL P = *Head;
    *Head = NULL;
    *Tail = NULL;
    P = LibertarNodoLivro(P);
}

nodeL RemoverCabecaLivro(nodeL Head)
{
    nodeL P = Head;
    Head->next->prev = NULL;
    Head = Head->next;
    P = LibertarNodoLivro(P);
    return Head;
}

nodeL RemoverCaudaLivro(nodeL Tail)
{
    nodeL P = Tail;
    Tail->prev->next = NULL;
    Tail = Tail->prev;
    P = LibertarNodoLivro(P);
    return Tail;
}

nodeL RemoverMeioLivro(nodeL Head, LIVRO X)
{

    nodeL P;
    P = ProcurarLivro(Head, X);
    P->prev->next = P->next;
    P->next->prev = P->prev;
    P = LibertarNodoLivro(P);
    return Head;
}

nodoCompras CriarCompra()
{
    nodoCompras L;
    L = NULL;
    return L;
}

nodoCompras CriarNodoCompra(COMPRA X)
{
    nodoCompras P;
    P = (nodoCompras)malloc(sizeof(struct Nodo));
    if (P == NULL)
        return NULL;
    P->Elemento = X;
    P->Prox = NULL;
    return P;
}

void LibertarNodoCompra(nodoCompras P)
{
    free(P);
    P = NULL;
}

void ListarCompraRec(nodoCompras L)
{
    if (L != NULL)
    {
        MostrarElementoCompra(L->Elemento);
        ListarCompraRec(L->Prox);
    }
}

void ListarCompraContrarioRec(nodoCompras L)
{
    if (L != NULL)
    {
        ListarCompraContrarioRec(L->Prox);
        MostrarElementoCompra(L->Elemento);
    }
}

nodoCompras InserirInicioCompra(COMPRA X, nodoCompras L)
{
    nodoCompras P;
    P = CriarNodoCompra(X);
    if (P == NULL)
        return L;
    P->Prox = L;
    L = P;
    return L;
}

int PesquisarCompra(COMPRA X, nodoCompras L)
{
    while (L != NULL && CompararElementosCompra(L->Elemento, X) != 0)
        L = L->Prox;
    if (L == NULL)
        return 0;
    else
        return 1;
}

int PesquisarCompraRec(COMPRA X, nodoCompras L)
{
    if (L == NULL)
        return 0;
    if (CompararElementosCompra(L->Elemento, X) == 0)
        return 1;
    else
        return PesquisarCompraRec(X, L->Prox);
}

nodoCompras ProcurarAnteriorCompra(COMPRA X, nodoCompras L)
{
    nodoCompras Ant = NULL;
    while (L != NULL && CompararElementosCompra(L->Elemento, X) != 0)
    {
        Ant = L;
        L = L->Prox;
    }
    return Ant;
}

nodoCompras ProcurarAnteriorCompraRec(COMPRA X, nodoCompras L)
{
    if (CompararElementosCompra(L->Elemento, X) == 0)
        return NULL; //  só acontece se X estiver no início de L
    if (CompararElementosCompra(L->Prox->Elemento, X) == 0)
        return L;
    return ProcurarAnteriorCompraRec(X, L->Prox);
}

// RemoverCompra X da lista L, em que X está na lista
nodoCompras RemoverCompra(COMPRA X, nodoCompras L)
{
    nodoCompras P, PAnt;
    PAnt = ProcurarAnteriorCompra(X, L);
    if (PAnt == NULL)
    { // remover elemento do início de L
        P = L;
        L = L->Prox;
    }
    else
    {
        P = PAnt->Prox;
        PAnt->Prox = P->Prox; // ou (PAnt->Prox)->Prox
    }
    LibertarNodoCompra(P);
    return L;
}

// RemoverCompra X da lista L, em que X está na lista
nodoCompras RemoverCompraRec(COMPRA X, nodoCompras L, nodoCompras LAux)
{
    nodoCompras P;
    if (CompararElementosCompra(L->Elemento, X) == 0)
    { // X está no início da Lista L
        P = L;
        L = L->Prox;
        free(P);
        return L;
    }
    if (CompararElementosCompra(LAux->Prox->Elemento, X) == 0)
    {
        // X está na lista L, mas não no inicio
        P = LAux->Prox;
        LAux->Prox = P->Prox; // ou LAux->Prox->Prox;
        free(P);
        return L;
    }
    return RemoverCompraRec(X, L, LAux->Prox);
}

int TamanhoCompra(nodoCompras L)
{
    int tam = 0;
    while (L != NULL)
    {
        tam++;
        L = L->Prox;
    }
    return tam;
}

int TamanhoCompraRec(nodoCompras L)
{
    if (L == NULL)
        return 0;
    else
        return 1 + TamanhoCompraRec(L->Prox);
}

nodoCompras InserirFimListaCompras(COMPRA X, nodoCompras L)
{
    nodoCompras P, PAux;
    P = CriarNodoCompra(X);
    if (P == NULL)
        return L;
    if (L == NULL)
        return P;
    PAux = L;
    while (PAux->Prox != NULL) // marcar o elemento do fim de L
        PAux = PAux->Prox;
    PAux->Prox = P;
    return L;
}

nodoCompras InserirFimListaComprasRec(COMPRA X, nodoCompras L)
{
    nodoCompras P;
    if (L == NULL)
    { // só acontece se a lista inicial for VaziaCompra
        P = CriarNodoCompra(X);
        if (P != NULL)
            L = P;
        return L;
    }
    if (L->Prox == NULL)
    { // fim da lista L
        P = CriarNodoCompra(X);
        if (P != NULL)
            L->Prox = P;
    }
    else
        InserirFimListaComprasRec(X, L->Prox); // o que devolve não interessa
    return L;                                  // devolve o início da lista
}

// assume-se que a lista está ordenada por ordem crescente
nodoCompras ProcurarInserirOrdemCompraCompra(COMPRA X, nodoCompras L)
{
    nodoCompras Ant = NULL;
    while (L != NULL && CompararElementosCompra(L->Elemento, X) < 0)
    {
        Ant = L;
        L = L->Prox;
    }
    return Ant;
}

nodoCompras InserirOrdemCompra(COMPRA X, nodoCompras L)
{
    nodoCompras P, PAnt;
    P = CriarNodoCompra(X);
    if (P == NULL)
        return L;
    if (L == NULL)
        return P; // a lista L inicia-se em P
    PAnt = ProcurarInserirOrdemCompraCompra(X, L);
    if (PAnt == NULL)
    { // inserir no início de L
        P->Prox = L;
        return P;
    }
    P->Prox = PAnt->Prox;
    PAnt->Prox = P;
    return L;
}
