void LerFicheiroLivros(nodeL *Head, nodeL *Tail)
{
    LIVRO livro;
    FILE *f;
    f = fopen("Livros.txt", "r");

    if (f == NULL)
    {
        printf("!!!!!!!!!!!!!!!!Erro leitura ficheiro Livros.txt!!!!!!!!!!!!!!!\n");
    }
    else if (VaziaLivro(*Head) == 1)
    { //Se estiver vazia, vai criar uma lista
        fscanf(f, "%ld\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%f\n%d", &livro.ISBN, livro.Titulo, livro.Idioma, livro.FirstAuthor, livro.SndAuthor, livro.Editora, &livro.AnoPub, livro.AreaCientifica, &livro.Preco, &livro.Stock);

        InserirPrimeiroElementoLivro(Head, Tail, livro);
    }
    while (fscanf(f, "%ld\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%f\n%d", &livro.ISBN, livro.Titulo, livro.Idioma, livro.FirstAuthor, livro.SndAuthor, livro.Editora, &livro.AnoPub, livro.AreaCientifica, &livro.Preco, &livro.Stock) == 10)
    {
        *Tail = InserirCaudaLivro(*Tail, livro);
    }
}

void LerFicheiroClientes(nodeC *ABPEClientes)
{
    FILE *f;
    COMPRA compraAux;
    char x;
    CLIENTE client;

    f = fopen("Clientes.txt", "r");

    if (f == NULL)
    {
        printf("!!!!!!!!!!!!!!!!Erro leitura ficheiro Clientes.txt!!!!!!!!!!!!!!!\n");
    }
    else
    {
        while (fscanf(f, "%d\n%[^\n]\n%[^\n]\n%d\n", &client.NIF, client.Nome, client.Morada, &client.Telefone) == 4)
        {
            client.ListaDeCompras = CriarCompra();

            fscanf(f, "%c", &x);
            x = fgetc(f);
            if (x == '\n')
            {
                //Leitura da Lista de compras do cliente
                while (fscanf(f, "%[^\n]\n%d %d %d\n%d\n%f\n", compraAux.Produto, &compraAux.dataCompra.Dia, &compraAux.dataCompra.Mes, &compraAux.dataCompra.Ano, &compraAux.qtd, &compraAux.preco) == 6)
                {

                    client.ListaDeCompras = InserirFimListaCompras(compraAux, client.ListaDeCompras);
                    if ((x = fgetc(f)) == ']')
                    {
                        *ABPEClientes = InserirABP(*ABPEClientes, client);
                        break;
                    }
                    else
                    {
                        fseek(f, -1, SEEK_CUR);
                    }
                }
            }
            else
            {
                fgetc(f);
                fgetc(f);
                *ABPEClientes = InserirABP(*ABPEClientes, client);
            }
        }
    }

    *ABPEClientes = CriarABEquilibrada(*ABPEClientes);
}

void InserirLivro(nodeL *Head, nodeL *Tail)
{
    LIVRO livroAux;
    do
    {
        printf("ISBN\n");
        scanf("%ld", &livroAux.ISBN);

        //Como o ISBN é unico, terá de pedir até que insira um válido
        if (ConsultarCabecaLivro(*Head, livroAux) == 1)
        {
            printf("AVISO: Esse ISBN ja esta a ser utilizado, tente novamente\n");
        }
    } while (livroAux.ISBN <= 0 || ConsultarCabecaLivro(*Head, livroAux) == 1);
    fgetc(stdin);

    printf("Titulo do Livro\n");
    fgets(livroAux.Titulo, lengthTitulo, stdin);
    livroAux.Titulo[strlen(livroAux.Titulo) - 1] = '\0';

    printf("Idioma:\n");
    fgets(livroAux.Idioma, lengthIdioma, stdin);
    livroAux.Idioma[strlen(livroAux.Idioma) - 1] = '\0';

    printf("Primeiro Autor:\n");
    fgets(livroAux.FirstAuthor, lengthFirstAuthor, stdin);
    livroAux.FirstAuthor[strlen(livroAux.FirstAuthor) - 1] = '\0';

    printf("Segundo Autor:\n");
    fgets(livroAux.SndAuthor, lengthSndAuthor, stdin);
    livroAux.SndAuthor[strlen(livroAux.SndAuthor) - 1] = '\0';

    printf("Editora:\n");
    fgets(livroAux.Editora, lengthEditora, stdin);
    livroAux.Editora[strlen(livroAux.Editora) - 1] = '\0';

    do
    {
        printf("Ano publicacao:\n");
        scanf("%d", &livroAux.AnoPub);
    } while (livroAux.AnoPub <= 0 || livroAux.AnoPub > 2021);
    fgetc(stdin);

    printf("Area cientifica:\n");
    fgets(livroAux.AreaCientifica, lengthAreaCientifica, stdin);
    livroAux.AreaCientifica[strlen(livroAux.AreaCientifica) - 1] = '\0';

    do
    {
        printf("Preco:\n");
        scanf("%f", &livroAux.Preco);
    } while (livroAux.Preco <= 0.0);
    fgetc(stdin);

    do
    {
        printf("Stock:\n");
        scanf("%d", &livroAux.Stock);
    } while (livroAux.Stock < 0);

    if (VaziaLivro(*Head))
    {
        InserirPrimeiroElementoLivro(Head, Tail, livroAux);
    }
    else
    {
        *Tail = InserirCaudaLivro(*Tail, livroAux);
    }
    printf("---------------------------\nLivro Inserido com sucesso\n---------------------------\n");
}

// procura um cliente X e devolve o nodo correspondente.
nodeC ProcurarCliente(nodeC ABPEClientes, CLIENTE clientAux)
{
    if (ABPEClientes == NULL)
        return ABPEClientes;
    if (CompararElementosCliente(clientAux, ABPEClientes->client) == 0) // X.NIF == (T->client).NIF)
        return ABPEClientes;
    if (CompararElementosCliente(clientAux, ABPEClientes->client) == -1) // X.NIF < (T->client).NIF)
        return ProcurarCliente(ABPEClientes->left, clientAux);
    else // X.NIF > (T->client).NIF)
        return ProcurarCliente(ABPEClientes->right, clientAux);
}

// funçao auxiliar que remove uma encomenda da fila
nodeE removerEncomendaFila(nodeE *FilaEncomendas, ENCOMENDA order)
{
    nodeE aux = *FilaEncomendas, newF = CriarFila();
    while (aux != NULL)
    {
        if (order.NIFCliente == aux->encomenda.NIFCliente && order.ISBNLivro == aux->encomenda.ISBNLivro)
        {
            aux = aux->next;
            continue;
        }
        newF = Juntar(aux->encomenda, newF);
        aux = aux->next;
    }

    return newF;
}

nodeE removerEncomendaFilaCliente(nodeE *FilaEncomendas, ENCOMENDA order)
{
    nodeE aux = *FilaEncomendas, newF = CriarFila();
    while (aux != NULL)
    {
        if (order.NIFCliente == aux->encomenda.NIFCliente)
        {
            aux = aux->next;
            continue;
        }
        newF = Juntar(aux->encomenda, newF);
        aux = aux->next;
    }

    return newF;
}

int RemoverLivroDadoISBN(nodeL *Head, nodeL *Tail, long ISBN, nodeE *FilaEncomendas)
{
    LIVRO livroAux;
    livroAux.ISBN = ISBN;
    nodeE aux = *FilaEncomendas;

    if (*Head == NULL)
    {
        return 0;
    }
    else
    {
        if (ConsultarCabecaLivro(*Head, livroAux) == 1) //Se o ISBN existir, faz tudo normal, se não existir, excusa de fazer o resto
        {
            nodeL LivroARemover = ProcurarLivro(*Head, livroAux);
            if (LivroARemover == *Head)
            {
                *Head = RemoverCabecaLivro(*Head);
            }
            else if (LivroARemover == *Tail)
            {
                *Tail = RemoverCaudaLivro(*Tail);
            }
            else if (TamanhoLivro(*Head) == 1)
            {
                RemoverUnicoElementoLivro(Head, Tail);
            }
            else
            {
                *Head = RemoverMeioLivro(*Head, livroAux);
            }

            while (aux != NULL)
            {
                if (LivroARemover->book.ISBN == aux->encomenda.ISBNLivro)
                {
                    *FilaEncomendas = removerEncomendaFila(FilaEncomendas, aux->encomenda);
                }

                aux = aux->next;
            }

            return 1;
        }
    }
    return 0;
}

//Verifica se o nodo toCheck está na Head, na Tail ou no meio da Lista.
int checkPosition(nodeL Head, nodeL Tail, nodeL nodeToCheck)
{
    if (nodeToCheck == Head)
    {
        return 0;
    }
    else if (nodeToCheck == Tail)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void alterarListaComprasLivro(nodeC ABPEClientes, char titulo[], LIVRO livroAlterado)
{

    if (ABPEClientes == NULL)
    {
        return;
    }
    nodoCompras aux = ABPEClientes->client.ListaDeCompras;

    while (aux != NULL)
    {
        if (strcmp(titulo, aux->Elemento.Produto) == 0)
        {
            strcpy(aux->Elemento.Produto, livroAlterado.Titulo);
        }

        aux = aux->Prox;
    }

    alterarListaComprasLivro(ABPEClientes->left, titulo, livroAlterado);
    alterarListaComprasLivro(ABPEClientes->right, titulo, livroAlterado);
}

// Funçao que altera um livro com determinado ISBN. Pergunta o campo do livro a alterar e faz a alteração consoante a escolha.
void AlterarLivroDadoISBN(nodeL *Head, nodeL *Tail, long ISBN, nodeC *ABPEClientes)
{
    LIVRO livroAux;
    livroAux.ISBN = ISBN;
    char titulo[60];

    if (*Head == NULL)
    {
        printf("Não há livros a alterar\n");
        return;
    }
    else
    {
        int opcao;
        int flag = 0;
        if (ConsultarCabecaLivro(*Head, livroAux) == 1) //Se o ISBN existir, faz tudo normal, se não existir, excusa de fazer o resto
        {
            nodeL LivroAAlterar = ProcurarLivro(*Head, livroAux);
            strcpy(titulo, LivroAAlterar->book.Titulo);
            do
            {
                printf("O que deseja alterar?\n1-Titulo\t2-Idioma\t3-Autor 1\t4-Autor 2\t5-Editora\t6-Ano Pub\t7-Area Cientifica\t8-Preco\t9-Stock\t10-TUDO\t0-Voltar\n");
                scanf("%d", &opcao);
                getc(stdin);
                switch (opcao)
                {

                case 0:
                    if (flag)
                        printf("---------------------------\nAlterações feitas com sucesso\n---------------------------\n");
                    else
                        printf("---------------------------\nNão houve nenhuma alteração\n---------------------------\n");
                    return;

                case 1:
                    printf("Titulo do Livro\n");
                    fgets(livroAux.Titulo, lengthTitulo, stdin);
                    livroAux.Titulo[strlen(livroAux.Titulo) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.Titulo, livroAux.Titulo);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        strcpy((*Tail)->book.Titulo, livroAux.Titulo);
                    }
                    else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.Titulo, livroAux.Titulo);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    alterarListaComprasLivro(*ABPEClientes, titulo, LivroAAlterar->book);
                    flag = 1;
                    break;
                case 2:
                    printf("Idioma:\n");
                    fgets(livroAux.Idioma, lengthIdioma, stdin);
                    livroAux.Idioma[strlen(livroAux.Idioma) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.Idioma, livroAux.Idioma);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        strcpy((*Tail)->book.Idioma, livroAux.Idioma);
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.Idioma, livroAux.Idioma);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;
                    break;
                case 3:
                    printf("Primeiro Autor:\n");
                    fgets(livroAux.FirstAuthor, lengthFirstAuthor, stdin);
                    livroAux.FirstAuthor[strlen(livroAux.FirstAuthor) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.FirstAuthor, livroAux.FirstAuthor);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        strcpy((*Tail)->book.FirstAuthor, livroAux.FirstAuthor);
                    }else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.FirstAuthor, livroAux.FirstAuthor);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 4:
                    printf("Segundo Autor:\n");
                    fgets(livroAux.SndAuthor, lengthSndAuthor, stdin);
                    livroAux.SndAuthor[strlen(livroAux.SndAuthor) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.SndAuthor, livroAux.SndAuthor);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {

                        strcpy((*Tail)->book.SndAuthor, livroAux.SndAuthor);
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.SndAuthor, livroAux.SndAuthor);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 5:
                    printf("Editora:\n");
                    fgets(livroAux.Editora, lengthEditora, stdin);
                    livroAux.Editora[strlen(livroAux.Editora) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.Editora, livroAux.Editora);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        strcpy((*Tail)->book.Editora, livroAux.Editora);
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.Editora, livroAux.Editora);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 6:
                    do
                    {
                        printf("Ano publicacao:\n");
                        scanf("%d", &livroAux.AnoPub);
                    } while (livroAux.AnoPub < 0 || livroAux.AnoPub > 2021);

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        (*Head)->book.AnoPub = livroAux.AnoPub;
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        (*Tail)->book.AnoPub = livroAux.AnoPub;
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                aux->book.AnoPub = livroAux.AnoPub;
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 7:
                    printf("Area cienctifica:\n");
                    fgets(livroAux.AreaCientifica, lengthAreaCientifica, stdin);
                    livroAux.AreaCientifica[strlen(livroAux.AreaCientifica) - 1] = '\0';

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        strcpy((*Head)->book.AreaCientifica, livroAux.AreaCientifica);
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        strcpy((*Tail)->book.AreaCientifica, livroAux.AreaCientifica);
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.AreaCientifica, livroAux.AreaCientifica);
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 8:
                    do
                    {
                        printf("Preco:\n");
                        scanf("%f", &livroAux.Preco);
                    } while (livroAux.Preco <= 0.0);

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        (*Head)->book.Preco = livroAux.Preco;
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        (*Tail)->book.Preco = livroAux.Preco;
                    } else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                aux->book.Preco = livroAux.Preco;
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 9:
                    do
                    {
                        printf("Stock:\n");
                        scanf("%d", &livroAux.Stock);
                    } while (livroAux.Stock < 0);

                    //Se estiver na Head:
                    if (checkPosition(*Head, *Tail, LivroAAlterar) == 0)
                    {
                        (*Head)->book.Stock = livroAux.Stock;
                    }
                    //Se estiver na tail:
                    else if (checkPosition(*Head, *Tail, LivroAAlterar) == 1)
                    {
                        (*Tail)->book.Stock = livroAux.Stock;
                    }
                    else {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                aux->book.Stock = livroAux.Stock;
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                case 10: //Alteração de todos os campos

                    printf("Titulo do Livro\n");
                    fgets(livroAux.Titulo, lengthTitulo, stdin);
                    livroAux.Titulo[strlen(livroAux.Titulo) - 1] = '\0';
                    alterarListaComprasLivro(*ABPEClientes, titulo, LivroAAlterar->book);

                    printf("Idioma:\n");
                    fgets(livroAux.Idioma, lengthIdioma, stdin);
                    livroAux.Idioma[strlen(livroAux.Idioma) - 1] = '\0';

                    printf("Primeiro Autor:\n");
                    fgets(livroAux.FirstAuthor, lengthFirstAuthor, stdin);
                    livroAux.FirstAuthor[strlen(livroAux.FirstAuthor) - 1] = '\0';

                    printf("Segundo Autor:\n");
                    fgets(livroAux.SndAuthor, lengthSndAuthor, stdin);
                    livroAux.SndAuthor[strlen(livroAux.SndAuthor) - 1] = '\0';

                    printf("Editora:\n");
                    fgets(livroAux.Editora, lengthEditora, stdin);
                    livroAux.Editora[strlen(livroAux.Editora) - 1] = '\0';

                    do
                    {
                        printf("Ano publicacao:\n");
                        scanf("%d", &livroAux.AnoPub);
                    } while (livroAux.AnoPub < 0 || livroAux.AnoPub > 2021);
                    fgetc(stdin);

                    printf("Area cienctifica:\n");
                    fgets(livroAux.AreaCientifica, lengthAreaCientifica, stdin);
                    livroAux.AreaCientifica[strlen(livroAux.AreaCientifica) - 1] = '\0';

                    do
                    {
                        printf("Preco:\n");
                        scanf("%f", &livroAux.Preco);
                    } while (livroAux.Preco <= 0.0);
                    fgetc(stdin);

                    do
                    {
                        printf("Stock:\n");
                        scanf("%d", &livroAux.Stock);
                    } while (livroAux.Stock < 0);

                    if (LivroAAlterar == *Head)
                    {
                        strcpy((*Head)->book.Titulo, livroAux.Titulo);
                        (*Head)->book.AnoPub = livroAux.AnoPub;
                        strcpy((*Head)->book.AreaCientifica, livroAux.AreaCientifica);
                        strcpy((*Head)->book.Editora, livroAux.Editora);
                        strcpy((*Head)->book.FirstAuthor, livroAux.FirstAuthor);
                        strcpy((*Head)->book.Idioma, livroAux.Idioma);
                        (*Head)->book.Preco = livroAux.Preco;
                        strcpy((*Head)->book.SndAuthor, livroAux.SndAuthor);
                        (*Head)->book.Stock = livroAux.Stock;
                    }
                    else if (LivroAAlterar == *Tail)
                    {
                        strcpy((*Tail)->book.Titulo, livroAux.Titulo);
                        (*Tail)->book.AnoPub = livroAux.AnoPub;
                        strcpy((*Tail)->book.AreaCientifica, livroAux.AreaCientifica);
                        strcpy((*Tail)->book.Editora, livroAux.Editora);
                        strcpy((*Tail)->book.FirstAuthor, livroAux.FirstAuthor);
                        strcpy((*Tail)->book.Idioma, livroAux.Idioma);
                        (*Tail)->book.Preco = livroAux.Preco;
                        strcpy((*Tail)->book.SndAuthor, livroAux.SndAuthor);
                        (*Tail)->book.Stock = livroAux.Stock;
                    }
                    else
                    {
                        nodeL aux = *Head;
                        while (aux != NULL)
                        {
                            if (aux->book.ISBN == ISBN)
                            {
                                strcpy(aux->book.Titulo, livroAux.Titulo);
                                aux->book.AnoPub = livroAux.AnoPub;
                                strcpy(aux->book.AreaCientifica, livroAux.AreaCientifica);
                                strcpy(aux->book.Editora, livroAux.Editora);
                                strcpy(aux->book.FirstAuthor, livroAux.FirstAuthor);
                                strcpy(aux->book.Idioma, livroAux.Idioma);
                                aux->book.Preco = livroAux.Preco;
                                strcpy(aux->book.SndAuthor, livroAux.SndAuthor);
                                aux->book.Stock = livroAux.Stock;
                                break;
                            }
                            aux = aux->next;
                        }
                    }
                    flag = 1;

                    break;
                }
            } while (opcao < 0 || opcao > 10 || opcao != 0);
        }
    }
}

// Funçao que mostra um livro com determinado ISBN
void consultarLivroISBN(nodeL H, nodeL T, long ISBN)
{
    LIVRO livroAux;
    livroAux.ISBN = ISBN;

    if (H == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    if (ConsultarCabecaLivro(H, livroAux))
    {
        nodeL livro = ProcurarLivro(H, livroAux);
        printf("-------------------------------\n");
        MostrarElementoLivro(livro->book);
        printf("-------------------------------\n");
    }
    else
    {
        printf("Nao existe esse ISBN\n");
    }
}

// Função que mostra um livro cujo título contenha a frase escrita pelo utilizador
void consultarLivroTitulo(nodeL ListaLivros, char phrase[], int flag)
{
    if (ListaLivros == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Livro não existente!\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (strstr(ListaLivros->book.Titulo, phrase) != NULL)
    {
        printf("-------------------------------\n");
        MostrarElementoLivro(ListaLivros->book);
        flag = 1;
        printf("-------------------------------\n");
    }

    consultarLivroTitulo(ListaLivros, phrase, flag);
}

// Função que mostra todos os livros de um dado autor (segundo ou primeiro) lançados num dado ano
void consultarLivroAutorAno(nodeL ListaLivros, char author[], int year, int flag)
{
    if (ListaLivros == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Livro não existente!\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (ListaLivros->book.AnoPub == year)
    {
        if (strcmp(author, ListaLivros->book.FirstAuthor) == 0 || strcmp(author, ListaLivros->book.SndAuthor) == 0)
        {
            printf("-------------------------------\n");
            MostrarElementoLivro(ListaLivros->book);
            flag = 1;
            printf("-------------------------------\n");
        }
    }

    consultarLivroAutorAno(ListaLivros->next, author, year, flag);
}

// função que mostra recursivamente todos os livros de uma específica editora cuja área coincide com a area introduzida pelo utilizador.
void consultarLivroEditoraArea(nodeL ListaLivros, char editora[], char area[], int flag)
{
    if (ListaLivros == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Livro não existente!\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (strcmp(ListaLivros->book.Editora, editora) == 0 && strcmp(ListaLivros->book.AreaCientifica, area) == 0)
    {
        printf("-------------------------------\n");
        MostrarElementoLivro(ListaLivros->book);
        flag = 1;
        printf("-------------------------------\n");
    }

    consultarLivroEditoraArea(ListaLivros->next, editora, area, flag);
}

/*  ################################################## FUNÇÕES PARA O MENU DE CLIENTES ################################################*/

// Função que pede os dados do cliente a inserir e o insere na árvore dos clientes (arvore binaria equilibrada)
void InserirCliente(nodeC *T)
{
    CLIENTE clienteAux, L[1];

    printf("NIF\n");
    scanf("%d", &clienteAux.NIF);
    fgetc(stdin);
    printf("Nome\n");
    fgets(clienteAux.Nome, lengthAreaCientifica, stdin);
    clienteAux.Nome[strlen(clienteAux.Nome) - 1] = '\0';
    printf("Morada\n");
    fgets(clienteAux.Morada, lengthMorada, stdin);
    clienteAux.Morada[strlen(clienteAux.Morada) - 1] = '\0';
    printf("Telefone\n");
    scanf("%d", &clienteAux.Telefone);
    clienteAux.ListaDeCompras = CriarCompra();
    L[0] = clienteAux;
    ABPEqInsercaoBinaria(T, L, 0, 0);
}

// funçao para guardar a árvore dos clientes no ficheiro Clientes.txt
void guardarClientes(nodeC ABPEClientes, int flag)
{

    FILE *f;

    if (flag == 1)
    {
        f = fopen("Clientes.txt", "a");
    }
    else
    {
        f = fopen("Clientes.txt", "w");
    }

    flag = 1;

    char x = '[';
    char c = ']';
    nodoCompras aux;

    if (ABPEClientes == NULL)
    {
        return;
    }

    fprintf(f, "%d\n%s\n%s\n%d\n", ABPEClientes->client.NIF, ABPEClientes->client.Nome, ABPEClientes->client.Morada, ABPEClientes->client.Telefone);

    if (!VaziaCompra(ABPEClientes->client.ListaDeCompras))
    {
        aux = ABPEClientes->client.ListaDeCompras;
        fprintf(f, "%c\n", x);

        while (aux != NULL)
        {
            fprintf(f, "%s\n%d %d %d\n%d\n%f\n", aux->Elemento.Produto, aux->Elemento.dataCompra.Dia, aux->Elemento.dataCompra.Mes, aux->Elemento.dataCompra.Ano, aux->Elemento.qtd, aux->Elemento.preco);
            aux = aux->Prox;
        }
        fprintf(f, "%c\n", c);
    }
    else
    {
        fprintf(f, "%c %c\n", x, c);
    }
    fclose(f);
    guardarClientes(ABPEClientes->left, flag);
    guardarClientes(ABPEClientes->right, flag);

}

// Função que altera um cliente com um dado nif
// a função percorre a árvore, procurando o cliente a ser alterado. Enquanto o cliente não é encontrado, adiciona todos os outros elementos a uma nova árvore que irá substituir a árvore antiga. Quando encontra o cliente a ser alterado, pede as informações novas e adiciona à nova árvore. Quando acabar de percorrer a árvore original, retorna a nova árvore.
nodeC alterarClienteNIF(nodeC ABPEClientes, nodeC newABPEClientes, int nif)
{
    if (ABPEClientes == NULL)
    {
        return ABPEClientes;
    }

    if (ABPEClientes->client.NIF == nif)
    {
        CLIENTE clienteAux;
        clienteAux.NIF = nif;
        fgetc(stdin);
        printf("Nome\n");
        fgets(clienteAux.Nome, lengthAreaCientifica, stdin);
        clienteAux.Nome[strlen(clienteAux.Nome) - 1] = '\0';
        printf("Morada\n");
        fgets(clienteAux.Morada, lengthMorada, stdin);
        clienteAux.Morada[strlen(clienteAux.Morada) - 1] = '\0';
        printf("Telefone\n");
        scanf("%d", &clienteAux.Telefone);

        newABPEClientes = InserirABP(newABPEClientes, clienteAux);
    }
    else
    {
        newABPEClientes = InserirABP(newABPEClientes, ABPEClientes->client);
    }

    alterarClienteNIF(ABPEClientes->right, newABPEClientes, nif);
    alterarClienteNIF(ABPEClientes->left, newABPEClientes, nif);

    return newABPEClientes;
}

void alterarClienteListaCompras(nodeC ABPEClientes, CLIENTE clienteAux)
{
    if (ABPEClientes == NULL)
    {
        return;
    }

    if (CompararElementosCliente(ABPEClientes->client, clienteAux) == 0)
    {

        ListarCompra(clienteAux.ListaDeCompras);
        ABPEClientes->client.ListaDeCompras = clienteAux.ListaDeCompras;
        return;
    }

    alterarClienteListaCompras(ABPEClientes->right, clienteAux);
    alterarClienteListaCompras(ABPEClientes->left, clienteAux);
}

void consultarClienteNome(nodeC ABPEClientes, char nome[lengthAreaCientifica], int flag)
{
    if (ABPEClientes == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Não temos nenhum cliente registado com esse nome.\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (strcmp(ABPEClientes->client.Nome, nome) == 0)
    {
        printf("-------------------------------\n");
        MostrarCliente(ABPEClientes->client);
        flag = 1;
        printf("-------------------------------\n");
    }

    consultarClienteNome(ABPEClientes->left, nome, flag);
    consultarClienteNome(ABPEClientes->right, nome, flag);
}

void consultarClienteMorada(nodeC ABPEClientes, char morada[lengthMorada], int flag)
{
    if (ABPEClientes == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Não temos nenhum cliente registado com essa morada.\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (strstr(ABPEClientes->client.Morada, morada) != NULL)
    {
        printf("-------------------------------\n");
        MostrarCliente(ABPEClientes->client);
        flag = 1;
        printf("-------------------------------\n");
    }

    consultarClienteMorada(ABPEClientes->left, morada, flag);
    consultarClienteMorada(ABPEClientes->right, morada, flag);
}

void consultarClienteTelefone(nodeC ABPEClientes, int telefone, int flag)
{
    if (ABPEClientes == NULL)
    {
        if (!flag)
        {
            printf("-------------------------------\n");
            printf("Não temos nenhum cliente registado com esse número de telefone.\n");
            printf("-------------------------------\n");
        }
        return;
    }

    if (ABPEClientes->client.Telefone == telefone)
    {
        printf("-------------------------------\n");
        MostrarCliente(ABPEClientes->client);
        flag = 1;
        printf("-------------------------------\n");
    }

    consultarClienteTelefone(ABPEClientes->left, telefone, flag);
    consultarClienteTelefone(ABPEClientes->right, telefone, flag);
}

void LerFicheiroEncomendas(nodeE *FilaEncomendas)
{
    FILE *f = fopen("Encomendas.txt", "r");
    ENCOMENDA encomendaAux;
    if (f == NULL)
    {
        printf("!!!!!!!!!!!!!!!!Erro leitura ficheiro Encomendas.txt!!!!!!!!!!!!!!!\n");
    }

    while (fscanf(f, "%d\n%d\n%d %d %d\n%d\n%f\n", &encomendaAux.ISBNLivro, &encomendaAux.NIFCliente, &encomendaAux.DataCompra.Dia, &encomendaAux.DataCompra.Mes, &encomendaAux.DataCompra.Ano, &encomendaAux.Qnt, &encomendaAux.PrecoTotal) == 7)
    {
        *FilaEncomendas = Juntar(encomendaAux, *FilaEncomendas);
    }
}

void guardar(nodeL ListaLivrosHead, nodeC ABPEClientes, nodeE FilaEncomendas)
{
    FILE *fLivros, *fEncomendas;
    if (!VaziaLivro(ListaLivrosHead))
    {
        fLivros = fopen("Livros.txt", "w");

        while (ListaLivrosHead != NULL)
        {
            fprintf(fLivros, "%ld\n", ListaLivrosHead->book.ISBN);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.Titulo);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.Idioma);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.FirstAuthor);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.SndAuthor);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.Editora);
            fprintf(fLivros, "%d\n", ListaLivrosHead->book.AnoPub);
            fprintf(fLivros, "%s\n", ListaLivrosHead->book.AreaCientifica);
            fprintf(fLivros, "%f\n", ListaLivrosHead->book.Preco);
            fprintf(fLivros, "%d\n", ListaLivrosHead->book.Stock);

            ListaLivrosHead = ListaLivrosHead->next;
        }
        fclose(fLivros);
    }

    if (!ABVazia(ABPEClientes))
    {
        guardarClientes(ABPEClientes, 0);
    }

    if (!FilaVazia(FilaEncomendas))
    {

        fEncomendas = fopen("Encomendas.txt", "w");

        while (FilaEncomendas != NULL)
        {
            fprintf(fEncomendas, "%d\n", FilaEncomendas->encomenda.ISBNLivro);
            fprintf(fEncomendas, "%d\n", FilaEncomendas->encomenda.NIFCliente);
            fprintf(fEncomendas, "%d %d %d\n", FilaEncomendas->encomenda.DataCompra.Dia, FilaEncomendas->encomenda.DataCompra.Mes, FilaEncomendas->encomenda.DataCompra.Ano);
            fprintf(fEncomendas, "%d\n", FilaEncomendas->encomenda.Qnt);
            fprintf(fEncomendas, "%f\n", FilaEncomendas->encomenda.PrecoTotal);
            FilaEncomendas = FilaEncomendas->next;
        }
        fclose(fEncomendas);
    }
    else
    {
        fEncomendas = fopen("Encomendas.txt", "w"); // abre o ficheiro e apaga tudo o que lá está.
        fclose(fEncomendas);
    }
}

// devolve 1 se o livro existir e 0 caso o livro não exista
int checkBookByTitle(nodeL ListaLivros, char phrase[], LIVRO *livroAEncomendar)
{

    if (ListaLivros == NULL)
    {
        return 0;
    }

    if (strcmp(ListaLivros->book.Titulo, phrase) == 0)
    {
        printf("________________________LIVRO____________________\n");
        MostrarElementoLivro(ListaLivros->book);
        printf("____________________________________________\n");
        *livroAEncomendar = ListaLivros->book;
        return 1;
    }

    return checkBookByTitle(ListaLivros->next, phrase, livroAEncomendar);
}

// funçao para encontrar um dado cliente e substituir
nodeC Compras(nodeC ABPEClientes, nodeL *ListaLivros, nodeE *FilaEncomendas)
{
    CLIENTE clienteAux;
    LIVRO bookAux;
    COMPRA compra;
    nodeL livroEncomendar;
    int qtd, opcao;
    int existe;

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    do
    {
        printf("Insira o seu NIF\n");
        scanf("%d", &clienteAux.NIF);
    } while (clienteAux.NIF <= 0);

    if (!PesquisarABP(ABPEClientes, clienteAux)) //Se o NIF inserido não estiver no programa, então pede novamente
    {
        do
        {
            printf("1 - Tentar novamente\t2 - Inserir novo cliente\n");
            scanf("%d", &opcao);
        } while (opcao < 1 || opcao > 2);

        switch (opcao)
        {
        case 1:
            do
            {
                printf("Insira o seu NIF\n");
                scanf("%d", &clienteAux.NIF);
            } while (clienteAux.NIF <= 0 || !PesquisarABP(ABPEClientes, clienteAux));
            break;
        case 2:
            InserirCliente(&ABPEClientes);
            break;
        }
    }
    fgetc(stdin);
    printf("Insira o nome do livro\n");
    fgets(bookAux.Titulo, lengthTitulo, stdin);
    bookAux.Titulo[strlen(bookAux.Titulo) - 1] = '\0';
    int opcaoQuerInserir;

    LIVRO LivroQuerEncomendar;
    existe = checkBookByTitle(*ListaLivros, bookAux.Titulo, &LivroQuerEncomendar);
    ENCOMENDA encomenda;

    nodeC cliente = ProcurarCliente(ABPEClientes, clienteAux);

    if (!existe)
    {
        printf("O livro não existe\n");
    }
    else
    {
        livroEncomendar = ProcurarLivro(*ListaLivros, LivroQuerEncomendar);

        if (livroEncomendar->book.Stock == 0) //Se existir mas não houver stock, temos de encomendar
        {
            do
            {
                printf("Nao temos stock de livro com esse titulo, deseja encomendar?\n1 - Sim\t2 - Nao / sair\n");
                scanf("%d", &opcaoQuerInserir);
                switch (opcaoQuerInserir)
                {
                case 1:
                    encomenda.ISBNLivro = livroEncomendar->book.ISBN;
                    encomenda.NIFCliente = clienteAux.NIF;
                    encomenda.DataCompra.Dia = timeinfo->tm_mday;
                    encomenda.DataCompra.Mes = timeinfo->tm_mon;
                    encomenda.DataCompra.Ano = timeinfo->tm_year + 1900;
                    do
                    {
                        printf("Quantidade a encomendar: ");
                        scanf("%d", &qtd);
                    } while (qtd <= 0);
                    encomenda.Qnt = qtd;

                    encomenda.PrecoTotal = qtd * livroEncomendar->book.Preco;
                    *FilaEncomendas = Juntar(encomenda, *FilaEncomendas);
                    printf("-------------------------Encomenda inserida com sucesso.-----------------------------\n");
                    break;
                case 2:
                    return ABPEClientes;
                }
            } while (opcaoQuerInserir < 1 || opcaoQuerInserir > 2);
        }
        else //Como há stock então é uma compra normal
        {
            nodeL aux = *ListaLivros;
            do
            {
                printf("Quantidade a comprar\n");
                scanf("%d", &qtd);
            } while (qtd <= 0);

            if (qtd > livroEncomendar->book.Stock)
            {
                do
                {
                    printf("Nao temos o stock que pretende desse livro, deseja encomendar?\n1 - Sim\t2 - Nao / sair\n");
                    scanf("%d", &opcaoQuerInserir);
                    switch (opcaoQuerInserir)
                    {
                    case 1:
                        encomenda.ISBNLivro = livroEncomendar->book.ISBN;
                        encomenda.NIFCliente = clienteAux.NIF;
                        encomenda.DataCompra.Dia = timeinfo->tm_mday;
                        encomenda.DataCompra.Mes = timeinfo->tm_mon;
                        encomenda.DataCompra.Ano = 1900 + timeinfo->tm_year;
                        do
                        {
                            printf("Quantidade a encomendar\n");
                            scanf("%d", &qtd);
                        } while (qtd <= 0);
                        encomenda.Qnt = qtd;

                        encomenda.PrecoTotal = qtd * livroEncomendar->book.Preco;
                        *FilaEncomendas = Juntar(encomenda, *FilaEncomendas);
                        printf("Encomenda inserida com sucesso.\n");
                        break;
                    case 2:
                        return ABPEClientes;
                    }
                } while (opcaoQuerInserir < 1 || opcaoQuerInserir > 2);
            }
            else
            {
                while (aux != NULL)
                {
                    if (strcmp(aux->book.Titulo, bookAux.Titulo) == 0 && aux->book.Stock >= qtd)
                    {
                        aux->book.Stock -= qtd;
                        strcpy(compra.Produto, bookAux.Titulo);
                        compra.dataCompra.Dia = timeinfo->tm_mday;
                        compra.dataCompra.Mes = timeinfo->tm_mon;
                        compra.dataCompra.Ano = 1900 + timeinfo->tm_year;
                        compra.qtd = qtd;
                        compra.preco = aux->book.Preco * qtd;
                        cliente->client.ListaDeCompras = InserirInicioCompra(compra, cliente->client.ListaDeCompras);
                        alterarClienteListaCompras(ABPEClientes, cliente->client);
                        printf("---------------------------\nCompra efetuada com sucesso!\n---------------------------\n");
                        break;
                    }
                    aux = aux->next;
                }
            }
        }
    }

    return ABPEClientes;
}

// funçao auxiliar que procura uma encomenda na fila de encomendas.
ENCOMENDA procurarEncomenda(ENCOMENDA order, nodeE FilaEncomendas)
{
    nodeE aux = FilaEncomendas;

    while (aux != NULL && (order.NIFCliente != aux->encomenda.NIFCliente || order.ISBNLivro != aux->encomenda.ISBNLivro))
    {
        aux = aux->next;
    }

    if (Frente(aux).ISBNLivro == order.ISBNLivro && Frente(aux).NIFCliente == order.NIFCliente)
        return Frente(aux);
    return order;
}

// funçao principal que chama as funçoes procurarEncomenda para encontrar uma dada encomenda, removerEncomendaFile para a remover da file e depois adiciona-a  à lista de compras do cliente cujo nif estava associado à encomenda.
nodeC removerEncomenda(nodeE *FilaEncomendas, nodeC ABPEClientes, nodeL *ListaLivros, ENCOMENDA order)
{
    CLIENTE clientToSearch;
    nodeC client;
    LIVRO bookToSearch;
    nodeL book;
    COMPRA toAdd;
    ENCOMENDA orderComplete;

    clientToSearch.NIF = order.NIFCliente;
    bookToSearch.ISBN = order.ISBNLivro;

    client = ProcurarCliente(ABPEClientes, clientToSearch);

    book = ProcurarLivro(*ListaLivros, bookToSearch);

    orderComplete = procurarEncomenda(order, *FilaEncomendas);
    printf("NIF: %d\n\n", orderComplete.NIFCliente);

    toAdd.dataCompra.Dia = orderComplete.DataCompra.Dia;
    toAdd.dataCompra.Mes = orderComplete.DataCompra.Mes;
    toAdd.dataCompra.Ano = orderComplete.DataCompra.Ano;
    toAdd.preco = orderComplete.PrecoTotal;
    toAdd.qtd = orderComplete.Qnt;
    strcpy(toAdd.Produto, book->book.Titulo);

    client->client.ListaDeCompras = InserirInicioCompra(toAdd, client->client.ListaDeCompras);

    alterarClienteListaCompras(ABPEClientes, client->client);

    *FilaEncomendas = removerEncomendaFila(FilaEncomendas, orderComplete);

    return ABPEClientes;
}
