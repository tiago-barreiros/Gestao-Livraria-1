//Operação 1
//Quantos livros foram vendidos num dado período de tempo (mês e ano)
int LivrosVendidosTempo(nodeC arvoreClientes, int mes1, int ano1, int mes2, int ano2, nodoCompras aux)
{
    int count = 0;
    if (arvoreClientes == NULL || VaziaCompra(arvoreClientes->client.ListaDeCompras))
        return 0;
    else
    {
        aux = arvoreClientes->client.ListaDeCompras;
        while (aux != NULL)
        {
            //só passa se estiver dentro do periodo de tempo
            if ((aux->Elemento.dataCompra.Ano == ano1 && aux->Elemento.dataCompra.Mes >= mes1) || (aux->Elemento.dataCompra.Ano == ano2 && aux->Elemento.dataCompra.Mes <= mes2) || (aux->Elemento.dataCompra.Ano > ano1 && aux->Elemento.dataCompra.Ano < ano2))
            {
                count = count + aux->Elemento.qtd;
            }
            aux = aux->Prox;
        }
        return count + LivrosVendidosTempo(arvoreClientes->left, mes1, ano1, mes2, ano2, aux) + LivrosVendidosTempo(arvoreClientes->right, mes1, ano1, mes2, ano2, aux);
    }
}

//Operação 2
//Determinar a data da última compra /venda de um dado livro
COMPRA determinarDataCompraLivro(nodeL ListaLivrosHead, nodeC ABPEClientes, nodeE filaEncomendas, COMPRA compraAux, nodoCompras aux)
{
    if (ABPEClientes == NULL || VaziaCompra(ABPEClientes->client.ListaDeCompras))
    {
        return compraAux;
    }

    aux = ABPEClientes->client.ListaDeCompras;
    //Percorre a lista toda de cada cliente, guarda a compra mais recente desse livro caso exista
    while (aux != NULL)
    {
        if (strcmp(aux->Elemento.Produto, compraAux.Produto) == 0)
        {
            if (aux->Elemento.dataCompra.Ano == compraAux.dataCompra.Ano && aux->Elemento.dataCompra.Mes == compraAux.dataCompra.Mes && aux->Elemento.dataCompra.Dia >= compraAux.dataCompra.Dia)
            {
                compraAux = aux->Elemento;
            }
            else if (aux->Elemento.dataCompra.Ano == compraAux.dataCompra.Ano && aux->Elemento.dataCompra.Mes > compraAux.dataCompra.Mes && aux->Elemento.dataCompra.Dia >= compraAux.dataCompra.Dia)
            {
                compraAux = aux->Elemento;
            }
            else
            {
                if (aux->Elemento.dataCompra.Ano >= compraAux.dataCompra.Ano && aux->Elemento.dataCompra.Mes > compraAux.dataCompra.Mes && aux->Elemento.dataCompra.Dia >= compraAux.dataCompra.Dia)
                {
                    compraAux = aux->Elemento;
                }
                else
                {
                    if (aux->Elemento.dataCompra.Mes > compraAux.dataCompra.Mes && aux->Elemento.dataCompra.Dia >= compraAux.dataCompra.Dia)
                    {
                        compraAux = aux->Elemento;
                    }
                }
            }
        }
        aux = aux->Prox;
    }

    COMPRA c1 = determinarDataCompraLivro(ListaLivrosHead, ABPEClientes->left, filaEncomendas, compraAux, aux);
    COMPRA c2 = determinarDataCompraLivro(ListaLivrosHead, ABPEClientes->right, filaEncomendas, compraAux, aux);
    if (c1.dataCompra.Ano == c2.dataCompra.Ano && c1.dataCompra.Mes == c2.dataCompra.Mes && c1.dataCompra.Dia >= c2.dataCompra.Dia)
    {
        compraAux = c1;
    }
    else if (c1.dataCompra.Ano == c2.dataCompra.Ano && c1.dataCompra.Mes > c2.dataCompra.Mes && c1.dataCompra.Dia >= c2.dataCompra.Dia)
    {
        compraAux = c1;
    }
    else
    {
        compraAux = c2;
    }

    while (filaEncomendas != NULL)
    {
        if (filaEncomendas->encomenda.DataCompra.Ano == compraAux.dataCompra.Ano && filaEncomendas->encomenda.DataCompra.Mes == compraAux.dataCompra.Mes && filaEncomendas->encomenda.DataCompra.Dia >= compraAux.dataCompra.Dia)
        {
            compraAux.dataCompra = filaEncomendas->encomenda.DataCompra;
        }
        else if (filaEncomendas->encomenda.DataCompra.Ano == compraAux.dataCompra.Ano && filaEncomendas->encomenda.DataCompra.Mes > compraAux.dataCompra.Mes && filaEncomendas->encomenda.DataCompra.Dia >= compraAux.dataCompra.Dia)
        {
            compraAux.dataCompra = filaEncomendas->encomenda.DataCompra;
        }
        else
        {
            if (filaEncomendas->encomenda.DataCompra.Ano >= compraAux.dataCompra.Ano && filaEncomendas->encomenda.DataCompra.Mes > compraAux.dataCompra.Mes && filaEncomendas->encomenda.DataCompra.Dia >= compraAux.dataCompra.Dia)
            {
                compraAux.dataCompra = filaEncomendas->encomenda.DataCompra;
            }
            else
            {
                if (filaEncomendas->encomenda.DataCompra.Mes > compraAux.dataCompra.Mes && filaEncomendas->encomenda.DataCompra.Dia >= compraAux.dataCompra.Dia)
                {
                    compraAux.dataCompra = filaEncomendas->encomenda.DataCompra;
                }
            }
        }
        filaEncomendas = filaEncomendas->next;
    }

    return compraAux;
}

//Operação 3
//Conta quantidades de livros comprados por um cliente X com NIF
int QuantidadeLivrosCompradosCliente(CLIENTE clienteAux)
{
    nodoCompras aux = clienteAux.ListaDeCompras;
    int numLivros = 0;
    while (aux != NULL)
    {
        numLivros += aux->Elemento.qtd;
        aux = aux->Prox;
    }

    return numLivros;
}

//Operação 4
//Verifica se Area Cientifica nos livros todos presentes na loja
int procurarAreaCientifica(nodeL ListaLivros, char areaCientifica[])
{
    while (ListaLivros != NULL)
    {
        if (strcmp(ListaLivros->book.AreaCientifica, areaCientifica) == 0)
        {
            return 1;
        }
        ListaLivros = ListaLivros->next;
    }
    printf("----------Area cientifica nao encontrada nos livros da loja------------------\n");

    return 0;
}

nodeL getMostRecentBook(nodeL ListaLivros, char area[], int maior, nodeL Livro)
{
    if (ListaLivros == NULL)
    {
        if (Livro == NULL)
        {
            return NULL;
        }
        return Livro;
    }

    if (strcmp(ListaLivros->book.AreaCientifica, area) == 0 && ListaLivros->book.AnoPub > maior)
    {
        maior = ListaLivros->book.AnoPub;
        Livro = ListaLivros;
    }

    return getMostRecentBook(ListaLivros->next, area, maior, Livro);
}

void getKLivrosRecentesAreaCientifica(nodeL ListaLivros, char areaCientifica[], nodeL *listaAux, nodeL *listaAuxTail)
{

    if (ListaLivros == NULL)
    {
        if (listaAux == NULL)
        {
            printf("-----------------------------------\n");
            printf("Não temos livros nessa área cientifica.\n");
            printf("-----------------------------------\n");
        }
        return;
    }

    if (strcmp(ListaLivros->book.AreaCientifica, areaCientifica) == 0)
    {

        if (VaziaLivro(*listaAux))
        {
            InserirPrimeiroElementoLivro(listaAux, listaAuxTail, ListaLivros->book);
        }
        else if (ConsultarCabecaLivro(*listaAux, ListaLivros->book) == 0)
        {
            *listaAuxTail = InserirCaudaLivro(*listaAuxTail, ListaLivros->book);
        }
    }

    getKLivrosRecentesAreaCientifica(ListaLivros->next, areaCientifica, listaAux, listaAuxTail);
}

//Operacao 5
// funçao auxiliar que indica se um livro com determinado titulo existe na lista
int pesquisarLivroTitulo(nodeL ListaLivros, LIVRO bookAux)
{
    nodeL aux = ListaLivros;

    if (ListaLivros == NULL)
    {
        return 0;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->book.Titulo, bookAux.Titulo) == 0)
        {
            return 1;
        }
        aux = aux->next;
    }

    return 0;
}

// funçao auxiliar que incrementa o stock de um dado livro numa lista auxiliar
int incrementarStockLista(nodeL *ListaLivros, LIVRO bookAux, int qtd)
{
    nodeL aux = *ListaLivros;

    if (ListaLivros == NULL)
    {
        return 0;
    }

    while (aux != NULL)
    {
        if (strcmp(aux->book.Titulo, bookAux.Titulo) == 0)
        {
            aux->book.Stock += qtd;
            return 1;
        }
        aux = aux->next;
    }

    return 0;
}

nodeL MostrarKMaisVendidosPeriodo(nodeC arvoreClientes, nodeL Livros, int mes1, int ano1, int mes2, int ano2, int k, nodeL *auxLivrosH, nodeL *auxLivrosT)
{
    nodoCompras auxCompras;
    LIVRO bookAux;

    if (arvoreClientes == NULL)
    {
        return *auxLivrosH;
    }

    if (!VaziaCompra(arvoreClientes->client.ListaDeCompras))
    {

        auxCompras = arvoreClientes->client.ListaDeCompras;

        while (auxCompras != NULL)
        {
            if ((auxCompras->Elemento.dataCompra.Ano == ano1 && auxCompras->Elemento.dataCompra.Mes >= mes1) || (auxCompras->Elemento.dataCompra.Ano == ano2 && auxCompras->Elemento.dataCompra.Mes <= mes2) || (auxCompras->Elemento.dataCompra.Ano > ano1 && auxCompras->Elemento.dataCompra.Ano < ano2))
            {
                bookAux.Stock = auxCompras->Elemento.qtd;
                strcpy(bookAux.Titulo, auxCompras->Elemento.Produto);
                nodeL aux = Livros;
                while (aux != NULL)
                {
                    if (strcmp(aux->book.Titulo, bookAux.Titulo) == 0)
                    {
                        bookAux.ISBN = aux->book.ISBN;
                        break;
                    }
                    aux = aux->next;
                }
                nodeL livro = ProcurarLivro(Livros, bookAux);
                bookAux.AnoPub = livro->book.AnoPub;
                strcpy(bookAux.AreaCientifica, livro->book.AreaCientifica);
                strcpy(bookAux.Editora, livro->book.Editora);
                strcpy(bookAux.FirstAuthor, livro->book.FirstAuthor);
                strcpy(bookAux.SndAuthor, livro->book.SndAuthor);
                strcpy(bookAux.Idioma, livro->book.Idioma);
                bookAux.Preco = livro->book.Preco;

                if (pesquisarLivroTitulo(*auxLivrosH, livro->book))
                {
                    incrementarStockLista(auxLivrosH, livro->book, auxCompras->Elemento.qtd);
                }
                else
                {
                    if (VaziaLivro(*auxLivrosH))
                    {
                        InserirPrimeiroElementoLivro(auxLivrosH, auxLivrosT, bookAux);
                    }
                    else
                    {
                        *auxLivrosT = InserirCaudaLivro(*auxLivrosT, bookAux);
                    }
                }
            }

            auxCompras = auxCompras->Prox;
        }
        *auxLivrosH = MostrarKMaisVendidosPeriodo(arvoreClientes->left, Livros, mes1, ano1, mes2, ano2, k, auxLivrosH, auxLivrosT);
        *auxLivrosH = MostrarKMaisVendidosPeriodo(arvoreClientes->right, Livros, mes1, ano1, mes2, ano2, k, auxLivrosH, auxLivrosT);
    }
    else
    {
        *auxLivrosH = MostrarKMaisVendidosPeriodo(arvoreClientes->left, Livros, mes1, ano1, mes2, ano2, k, auxLivrosH, auxLivrosT);
        *auxLivrosH = MostrarKMaisVendidosPeriodo(arvoreClientes->right, Livros, mes1, ano1, mes2, ano2, k, auxLivrosH, auxLivrosT);
    }

    return *auxLivrosH;
}

//Operacao 6
void AreaCientificaComMaisLivros(nodeL ListaLivros)
{
    char AreaCAux[50];
    char AreaCMaisLivrosForSure[50];
    int max = 0;
    int counter2 = 0;
    nodeL Aux = ListaLivros;

    while (Aux != NULL)
    {
        strcpy(AreaCAux, ListaLivros->book.AreaCientifica);
        while (ListaLivros->next != NULL)
        {
            if (strcmp(ListaLivros->book.AreaCientifica, AreaCAux) == 0)
            {
                counter2++;
            }
            ListaLivros = ListaLivros->next;
        }

        if (strcmp(ListaLivros->book.AreaCientifica, AreaCAux) == 0)
        {
            counter2++;
        }

        if (counter2 >= max)
        {
            max = counter2;
            strcpy(AreaCMaisLivrosForSure, AreaCAux);
        }

        while (ListaLivros->prev != NULL) // Para voltar atrás
        {
            ListaLivros = ListaLivros->prev;
        }
        Aux = Aux->next;
    }
    printf("A area cientifica com mais livros é %s\n", AreaCMaisLivrosForSure);
}
//Operacao 7
//Cliente com mais livros comprados

int ClienteMaisLivrosComprados(nodeC arvoreClientes, CLIENTE *compraAux, int count)
{
    if (arvoreClientes == NULL || VaziaCompra(arvoreClientes->client.ListaDeCompras))
    {
        return count;
    }
    MostrarCliente(arvoreClientes->client);

    nodoCompras aux = arvoreClientes->client.ListaDeCompras;
    int counter = 0;

    while (aux != NULL)
    {
        counter += aux->Elemento.qtd;
        aux = aux->Prox;
    }

    if (counter >= count)
    {
        *compraAux = arvoreClientes->client;
        count = counter;
    }

    int c1 = ClienteMaisLivrosComprados(arvoreClientes->left, compraAux, count);
    int c2 = ClienteMaisLivrosComprados(arvoreClientes->right, compraAux, count);

    if (c1 >= c2)
    {
        return c1;
    }

    return c2;
}

// Operação 8
// Mostrar os Clientes por ordem decrescente do numero de compras

// funçao auxiliar que retorna o index do cliente com maior lista de compras
int getIndexClienteMaiorLista(CLIENTE *arrayClientesAux, int n)
{
    int maior = 0;
    int index = 0;

    for (int i = 0; i < n; i++)
    {
        if (TamanhoCompra(arrayClientesAux[i].ListaDeCompras) >= maior)
        {
            maior = TamanhoCompra(arrayClientesAux[i].ListaDeCompras);
            index = i;
        }
    }

    return index;
}

// funçao principal que cria uma vetor auxiliar
void getVetorClientes(nodeC ABPEClientes, CLIENTE *arrayClientesAux, int *i)
{
    int flag = 0;
    if (ABPEClientes == NULL)
    {
        return;
    }

    for (int j = 0; j < *i; j++)
    {
        if (arrayClientesAux[j].NIF == ABPEClientes->client.NIF)
        {
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        arrayClientesAux[*i] = ABPEClientes->client;
        *i = *i + 1;
    }

    getVetorClientes(ABPEClientes->left, arrayClientesAux, i);
    getVetorClientes(ABPEClientes->right, arrayClientesAux, i);
}

//Operação 9
void AnoComMaisPublicacoes(nodeL ListaLivros)
{
    int AnoAux;
    int AnoMaisLivrosForSure;
    int max = 0;
    int counter2 = 0;
    nodeL Aux = ListaLivros;

    while (Aux != NULL)
    {
        AnoAux = ListaLivros->book.AnoPub;
        while (ListaLivros->next != NULL)
        {
            if (ListaLivros->book.AnoPub == AnoAux)
            {
                counter2++;
            }
            ListaLivros = ListaLivros->next;
        }

        if (ListaLivros->book.AnoPub == AnoAux)
        {
            counter2++;
        }

        if (counter2 >= max)
        {
            max = counter2;
            AnoMaisLivrosForSure = AnoAux;
        }

        while (ListaLivros->prev != NULL) // Para voltar atrás
        {
            ListaLivros = ListaLivros->prev;
        }
        Aux = Aux->next;
    }
    printf("O ano com mais publicacoes e %d\n", AnoMaisLivrosForSure);
    printf("-------------------------------\n");
}

// Operção 10
// Calcular o cliente que mais gastou num dado período (mês e ano)

CLIENTE CalcularClienteMaisGastos(nodeC arvoreClientes, int mes1, int ano1, int mes2, int ano2, CLIENTE maior, float *count)
{
    float counterAux = 0;
    float lAux;
    float rAux;
    if (arvoreClientes == NULL)
    {
        return maior;
    }

    nodoCompras aux = arvoreClientes->client.ListaDeCompras;
    while (aux != NULL)
    {

        if ((aux->Elemento.dataCompra.Ano == ano1 && aux->Elemento.dataCompra.Mes >= mes1) || (aux->Elemento.dataCompra.Ano == ano2 && aux->Elemento.dataCompra.Mes <= mes2) || (aux->Elemento.dataCompra.Ano > ano1 && aux->Elemento.dataCompra.Ano < ano2))
        {
            counterAux += aux->Elemento.preco;
        }

        aux = aux->Prox;
    }

    if (counterAux >= *count)
    {
        maior = arvoreClientes->client;
        *count = counterAux;
    }

    CLIENTE left = CalcularClienteMaisGastos(arvoreClientes->left, mes1, ano1, mes2, ano2, maior, count);
    lAux = *count;
    CLIENTE right = CalcularClienteMaisGastos(arvoreClientes->right, mes1, ano1, mes2, ano2, maior, count);
    rAux = *count;

    if (lAux >= rAux)
    {
        return left;
    }

    return right;
}

// Operção 11
// Determinar o desperdício de memória (no caso em que por exemplo num livro, no campo TITULO tenham char TITULO[100], se os TITULOS forem mais pequenos existe muito desperdício
int DesperdicioMemoriaLivro(nodeL Listalivros, int count)
{
    if (Listalivros == NULL)
    {
        return count;
    }
    else
    {
        count = count + (50 - strlen(Listalivros->book.AreaCientifica));
        count = count + (30 - strlen(Listalivros->book.Editora));
        count = count + (30 - strlen(Listalivros->book.FirstAuthor));
        count = count + (30 - strlen(Listalivros->book.SndAuthor));
        count = count + (60 - strlen(Listalivros->book.Titulo));
        return DesperdicioMemoriaLivro(Listalivros->next, count);
    }
}
int DesperdicioMemoriaCOMPRAS(nodoCompras ListarCompra, int count)
{
    if (ListarCompra == NULL)
    {
        return count;
    }
    else
    {
        count = count + (lengthTitulo - strlen(ListarCompra->Elemento.Produto));
        return DesperdicioMemoriaCOMPRAS(ListarCompra->Prox, count);
    }
}

int DesperdicioMemoriaCliente(nodeC arvoreClientes, int count)
{
    if (arvoreClientes == NULL)
    {
        return count;
    }
    else
    {
        count = count + (lengthMorada - strlen(arvoreClientes->client.Morada));
        count = count + (lengthNome - strlen(arvoreClientes->client.Nome));
        count = count + DesperdicioMemoriaCOMPRAS(arvoreClientes->client.ListaDeCompras, 0);

        return DesperdicioMemoriaCliente(arvoreClientes->left, count) + DesperdicioMemoriaCliente(arvoreClientes->left, count);
    }
}

//o livro mais caro
void LivroMaisCaro(nodeL ListaLivros)
{
    float precomin = 0;
    LIVRO maisCaro;
    while (ListaLivros != NULL)
    {
        if (ListaLivros->book.Preco > precomin)
        {
            precomin = ListaLivros->book.Preco;
            maisCaro = ListaLivros->book;
        }
        ListaLivros = ListaLivros->next;
    }
    printf("__O Livro mais caro é__\n");
    MostrarElementoLivro(maisCaro);
    printf("________________________\n");
}

nodeL getBookNAME(nodeL ListaLivros, char titulo[])
{
    while (ListaLivros != NULL)
    {
        if (strcmp(ListaLivros->book.Titulo, titulo) == 0)
        {
            return ListaLivros;
        }
        ListaLivros = ListaLivros->next;
    }

    return NULL;
}

void incrementarQtdLista(nodeL *ListaLivros, int qtd, char autor[])
{
    nodeL aux = *ListaLivros;

    while (aux != NULL)
    {
        if (strcmp(autor, aux->book.FirstAuthor) == 0)
        {
            aux->book.Stock += qtd;
            break;
        }
        aux = aux->next;
    }
}
void AutorBestSeller(nodeC ABPEClientes, nodeL ListaLivros, int mes, int ano, nodeL *auxautorH, nodeL *auxautorT)
{
    int qtd = 0;
    LIVRO bookAux;
    nodeL nodoLivrosAux;
    nodoCompras aux;

    if (ABPEClientes == NULL)
    {
        return;
    }

    if (!VaziaCompra(ABPEClientes->client.ListaDeCompras))
    {
        aux = ABPEClientes->client.ListaDeCompras;
        while (aux != NULL)
        {

            if (aux->Elemento.dataCompra.Mes == mes && aux->Elemento.dataCompra.Ano == ano)
            {
                nodoLivrosAux = getBookNAME(ListaLivros, aux->Elemento.Produto);

                if (nodoLivrosAux == NULL)
                {
                    aux = aux->Prox;
                    continue;
                }
                bookAux.AnoPub = nodoLivrosAux->book.AnoPub;
                bookAux.ISBN = nodoLivrosAux->book.ISBN;
                strcpy(bookAux.AreaCientifica, nodoLivrosAux->book.AreaCientifica);
                strcpy(bookAux.Titulo, nodoLivrosAux->book.Titulo);
                strcpy(bookAux.Editora, nodoLivrosAux->book.Editora);
                strcpy(bookAux.FirstAuthor, nodoLivrosAux->book.FirstAuthor);
                strcpy(bookAux.SndAuthor, nodoLivrosAux->book.SndAuthor);
                strcpy(bookAux.Idioma, nodoLivrosAux->book.Idioma);
                bookAux.Preco = nodoLivrosAux->book.Preco;
                bookAux.Stock = 0;
                if (ConsultarCabecaLivro(*auxautorH, bookAux))
                {
                    qtd = aux->Elemento.qtd;
                    incrementarQtdLista(auxautorH, qtd, bookAux.FirstAuthor);
                }
                else
                {
                    bookAux.Stock = aux->Elemento.qtd;
                    if (VaziaLivro(*auxautorH))
                    {
                        InserirPrimeiroElementoLivro(auxautorH, auxautorT, bookAux);
                    }
                    else
                    {
                        *auxautorT = InserirCaudaLivro(*auxautorT, bookAux);
                    }
                }
            }
            aux = aux->Prox;
        }
    }

    AutorBestSeller(ABPEClientes->right, ListaLivros, mes, ano, auxautorH, auxautorT);
    AutorBestSeller(ABPEClientes->left, ListaLivros, mes, ano, auxautorH, auxautorT);
}

int countComprasArea(nodoCompras lista, nodeL livros, char area[60], LIVRO livroAux)
{
    int count = 0;
    nodoCompras auxlista = lista;

    while (auxlista != NULL)
    {
        if (strcmp(livroAux.Titulo, auxlista->Elemento.Produto) == 0 && strcmp(livroAux.AreaCientifica, area) == 0)
        {

            count += auxlista->Elemento.qtd;
        }

        auxlista = auxlista->Prox;
    }

    return count;
}

char *areaCientificaMaisComprada(nodeC ABPEClientes, nodeE FilaEncomendas, nodeL ListaLivros, char *areaMaior, int maior)
{
    if (ABPEClientes == NULL)
    {
        return areaMaior;
    }

    int count = 0;
    nodoCompras auxCompras = ABPEClientes->client.ListaDeCompras;
    while (auxCompras != NULL)
    {
        nodeL livroAux = getBookNAME(ListaLivros, auxCompras->Elemento.Produto);

        if (livroAux == NULL)
        {
            continue;
        }

        count = countComprasArea(ABPEClientes->client.ListaDeCompras, ListaLivros, livroAux->book.AreaCientifica, livroAux->book);
        if (count > maior)
        {
            maior = count;
            strcpy(areaMaior, livroAux->book.AreaCientifica);
        }
        auxCompras = auxCompras->Prox;
    }

    char *maiorLeft = areaCientificaMaisComprada(ABPEClientes->left, FilaEncomendas, ListaLivros, areaMaior, maior);
    int maiorCountL = maior;

    char *maiorRight = areaCientificaMaisComprada(ABPEClientes->right, FilaEncomendas, ListaLivros, areaMaior, maior);
    int maiorCountR = maior;

    if (maiorCountR >= maiorCountL)
    {
        strcpy(areaMaior, maiorRight);
        maior = maiorCountR;
    }
    else
    {
        strcpy(areaMaior, maiorLeft);
        maior = maiorCountL;
    }

    nodeE auxEncomenda = FilaEncomendas;

    while (auxEncomenda != NULL)
    {
        LIVRO b;
        b.ISBN = auxEncomenda->encomenda.ISBNLivro;
        nodeL livroAux = ProcurarLivro(ListaLivros, b);
        if (livroAux == NULL)
        {
            continue;
        }
        if (auxEncomenda->encomenda.Qnt > maior)
        {
            maior = auxEncomenda->encomenda.Qnt;
            strcpy(areaMaior, livroAux->book.AreaCientifica);
        }

        auxEncomenda = auxEncomenda->next;
    }

    return areaMaior;
}

void AreaCientificaMaisCara(nodeL ListaLivros)
{
    char AreaCAux[50];
    char AreaCMaisCaraForSure[50];
    nodeL Aux = ListaLivros;
    float counter;
    float max = 0;
    int flag = 0;

    while (Aux != NULL)
    {        
        counter = 0;
        strcpy(AreaCAux, Aux->book.AreaCientifica);
        while (ListaLivros->next != NULL)
        {
            if (strcmp(ListaLivros->book.AreaCientifica, AreaCAux) == 0)
            {
                counter = counter + ListaLivros->book.Preco;
            }
            ListaLivros = ListaLivros->next;
        }
        if (strcmp(ListaLivros->book.AreaCientifica, AreaCAux) == 0)
        {
            counter = counter + ListaLivros->book.Preco;
        }
        if (counter >= max)
        {
            max = counter;
            strcpy(AreaCMaisCaraForSure, AreaCAux);
        }
        while (ListaLivros->prev != NULL) // Para voltar atrás
        {
            ListaLivros = ListaLivros->prev;
        }
        while (Aux->next != NULL && strcmp(Aux->next->book.AreaCientifica, AreaCAux) == 0)
        {
            Aux = Aux->next;
            flag = 1;
        }
        if (flag == 0)
        {
            Aux = Aux->next;
        }else
        {
            flag = 0;
        }
    }
    printf("A area cientifica mais cara e %s (%f euros total)\n", AreaCMaisCaraForSure, max);
}
