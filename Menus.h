void MenuFicheiro(nodeL ListaLivrosHead, nodeC ABPBClientes, nodeE Q)
{
  int opcao;
  do
  {
    printf("1 - Guardar\n0 - Sair\n");
    scanf("%d", &opcao);
  } while (opcao > 1 || opcao < 0);

  switch (opcao)
  {
  case 0:
    break;
  case 1:
    guardar(ListaLivrosHead, ABPBClientes, Q);
    break;
  }
}

void MenuConsultarLivros(nodeL ListaLivrosHead, nodeL ListaLivrosTail)
{
  int opcao, anoPub;
  long ISBN;
  char titulo[lengthTitulo], autor[lengthFirstAuthor], editora[lengthEditora], areaCientifica[lengthAreaCientifica];

  do
  {
    printf("----------------\n");
    printf("1 - ISBN\t2 - Titulo\t3 - Autor e Ano\t4 - Editora e Area Cientifica\t0 - Sair\nOpçao: ");
    scanf("%d", &opcao);
    printf("----------------\n");
  } while (opcao < 0 || opcao > 4);
  fgetc(stdin); // le o \n que fica no stdin depois do scanf
  switch (opcao)
  {
  case 0:
    printf("---------------------------------------\n");
    break;
  case 1:
    do
    {
      printf("Insira o ISBN: ");
      scanf("%ld", &ISBN);
      printf("----------------\n");

    } while (ISBN <= 0);

    consultarLivroISBN(ListaLivrosHead, ListaLivrosTail, ISBN);
    break;
  case 2:
    printf("----------------\n");
    printf("Insira o titulo:\n");
    fgets(titulo, lengthTitulo, stdin);
    titulo[strlen(titulo) - 1] = '\0';
    consultarLivroTitulo(ListaLivrosHead, titulo, 0); // passamos 0 como flag que vai indicar se o livro foi encontrado ou não (dentro da funçao)
    break;
  case 3:
    printf("----------------\n");

    printf("Insira o autor:\n");
    fgets(autor, lengthFirstAuthor, stdin);
    autor[strlen(autor) - 1] = '\0';
    printf("Insira o ano:\n");
    scanf("%d", &anoPub);
    consultarLivroAutorAno(ListaLivrosHead, autor, anoPub, 0);
    break;
  case 4:
    if (VaziaLivro(ListaLivrosHead))
    {
      printf("----------------\n");
      printf("Lista de livros vazia.\n");
      printf("----------------\n");
      break;
    }
    printf("----------------\n");
    printf("Insira a editora:\n");
    fgets(editora, lengthEditora, stdin);
    editora[strlen(editora) - 1] = '\0';
    printf("----------------\n");
    printf("Insira a Area Cientifica:\n");
    fgets(areaCientifica, lengthAreaCientifica, stdin);
    areaCientifica[strlen(areaCientifica) - 1] = '\0';
    consultarLivroEditoraArea(ListaLivrosHead, editora, areaCientifica, 0);
    break;
  }
}

void MenuLivros(nodeL *H, nodeL *T, nodeE *FilaEncomendas, nodeC *ABPEClientes)
{
  int opcao;
  long ISBN;
  LIVRO aux;

  do
  {
    printf("1 - Inserir\t2 - Remover\t3 - Alterar\t4 - Consultar por:\t0 - Sair\nOpçao: ");

    scanf("%d", &opcao);
    printf("----------------\n");

  } while (opcao > 4 || opcao < 0);

  switch (opcao)
  {
  case 0:
    break;
  case 1:
    InserirLivro(H, T);
    break;
  case 2:
    printf("----------------\n");

    printf("ISBN: ");
    scanf("%ld", &ISBN);
    aux.ISBN = ISBN;
    if (ConsultarCabecaLivro(*H, aux))
    {
      if (RemoverLivroDadoISBN(H, T, ISBN, FilaEncomendas))
      {
        printf("----------------\n");
        printf("Livro Removido com sucesso\n");
        printf("----------------\n");
      }
      else
      {
        printf("----------------\n");
        printf("O Livro Não Foi Removido com sucesso. Tente novamente.\n");
        printf("----------------\n");
      }
    }
    else
    {
      printf("----------------\n");
      printf("Não temos nenhum livro com esse ISBN.\n");
      printf("----------------\n");
    }

    break;
  case 3:
    printf("----------------\n");
    printf("ISBN: ");
    scanf("%ld", &ISBN);
    aux.ISBN = ISBN;
    if (ConsultarCabecaLivro(*H, aux))
    {
      AlterarLivroDadoISBN(H, T, ISBN, ABPEClientes);
    }
    else
    {
      printf("----------------\n");
      printf("Não temos nenhum livro com esse ISBN.\n");
      printf("----------------\n");
    }
    break;
  case 4:
    MenuConsultarLivros(*H, *T);
    break;
  }
}

void MenuConsultarClientes(nodeC ABPEClientes)
{
  int opcao;
  nodeC nodoCliente;
  char nome[50], morada[80];
  int telefone;
  CLIENTE c;
  do
  {
    printf("1 - NIF\t2 - Nome\t3 - Morada\t4 - Telefone\t0 - Sair\n");
    scanf("%d", &opcao);
    printf("----------------\n");
  } while (opcao > 4 || opcao < 0);
  fgetc(stdin); // le o \n que fica no stdin depois do scanf

  switch (opcao)
  {
  case 0:
    break;
  case 1:
    printf("----------------\n");
    printf("NIF do cliente a consultar\n");
    scanf("%d", &c.NIF);
    nodoCliente = ProcurarCliente(ABPEClientes, c);
    if (nodoCliente != NULL)
    {
      printf("---------------- Informação do Cliente ----------------\n");
      MostrarCliente(nodoCliente->client);
      printf("------------------------------------------------\n");
    }
    else
    {
      printf("----------------\n");
      printf("O cliente que inseriu não existe.\n");
      printf("----------------\n");
    }
    break;
  case 2:
    printf("----------------\n");
    printf("Nome\n");
    fgets(nome, lengthNome, stdin);
    nome[strlen(nome) - 1] = '\0';
    consultarClienteNome(ABPEClientes, nome, 0);
    break;
  case 3:
    printf("----------------\n");
    printf("Morada\n");
    fgets(morada, lengthNome, stdin);
    morada[strlen(morada) - 1] = '\0';
    consultarClienteMorada(ABPEClientes, morada, 0);
    break;
  case 4:
    printf("Telefone\n");
    scanf("%d", &telefone);
    consultarClienteTelefone(ABPEClientes, telefone, 0);
    break;
  }
}

void MenuClientes(nodeC *ABPEClientes, nodeE *FilaEncomendas)
{
  int opcao;
  CLIENTE c;
  nodeC newABPEClientes;
  newABPEClientes = CriarAB();
  int nif;

  do
  {
    printf("1 - Inserir\t2 - Remover\t3 - Alterar\t4 - Consultar Cliente\t0 - Sair\n");
    scanf("%d", &opcao);
  } while (opcao > 4 || opcao < 0);

  switch (opcao)
  {
  case 0:
    break;
  case 1:
    InserirCliente(ABPEClientes);
    break;
  case 2:
    printf("----------------\n");
    printf("NIF do cliente a remover\n");
    scanf("%d", &c.NIF);
    if (ProcurarCliente(*ABPEClientes, c) != NULL)
    {
      *ABPEClientes = RemoverABP(*ABPEClientes, c);
      ENCOMENDA order;
      order.NIFCliente = c.NIF;
      *FilaEncomendas = removerEncomendaFilaCliente(FilaEncomendas, order);
    }
    else
    {
      printf("----------------\n");
      printf("O cliente que inseriu não existe.\n");
      printf("----------------\n");

      break;
    case 3:
      printf("----------------\n");
      printf("NIF do cliente a alterar\n");
      scanf("%d", &nif);
      c.NIF = nif;
      if (ProcurarCliente(*ABPEClientes, c))
      {
        alterarClienteNIF(*ABPEClientes, newABPEClientes, nif);
        newABPEClientes = CriarABEquilibrada(newABPEClientes);
        *ABPEClientes = newABPEClientes;
      }
      else
      {
        printf("----------------\n");
        printf("O cliente que inseriu não existe.\n");
        printf("----------------\n");
      }
      break;
    case 4:
      MenuConsultarClientes(*ABPEClientes);
      break;
    }
  }
}

void MenuEncomendas(nodeE *FilaEncomendas, nodeC ABPEClientes, nodeL *ListaLivros)
{
  int opcao, opcao2;
  ENCOMENDA encomendaAux1, encomendaAux2;
  LIVRO livroAux;
  CLIENTE clienteAux;
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  do
  {
    printf("1 - Inserir\t2 - Remover\t0 - Sair\n");
    scanf("%d", &opcao);
    printf("----------------\n");
  } while (opcao > 2 || opcao < 0);

  switch (opcao)
  {
  case 0:
    break;
  case 1:
    printf("----------------\n");
    printf("ISBN Livro\n");
    scanf("%d", &encomendaAux1.ISBNLivro);
    livroAux.ISBN = encomendaAux1.ISBNLivro;
    if (!ConsultarCabecaLivro(*ListaLivros, livroAux))
    {
      printf("----------------\n");
      do
      {
        printf("Tente novamente.\nISBN Livro: ");
        scanf("%d", &encomendaAux1.ISBNLivro);
        printf("----------------\n");
        livroAux.ISBN = encomendaAux1.ISBNLivro;
      } while (!ConsultarCabecaLivro(*ListaLivros, livroAux));
    }
    printf("NIF Cliente\n");
    scanf("%d", &encomendaAux1.NIFCliente);
    clienteAux.NIF = encomendaAux1.NIFCliente;
    if (!PesquisarABP(ABPEClientes, clienteAux)) //Se o NIF inserido não estiver no programa, então pede novamente
    {
      do
      {
        printf("-------------------\n1 - Tentar novamente\t2 - Inserir novo cliente\n");
        scanf("%d", &opcao2);
        printf("----------------\n");
      } while (opcao2 < 1 || opcao2 > 2);

      switch (opcao2)
      {
      case 1:
        do
        {
          printf("Insira o seu NIF\n");
          scanf("%d", &encomendaAux1.NIFCliente);
          printf("----------------\n");
          clienteAux.NIF = encomendaAux1.NIFCliente;
        } while (encomendaAux1.NIFCliente <= 0 || !PesquisarABP(ABPEClientes, clienteAux));
        break;
      case 2:
        InserirCliente(&ABPEClientes);
        break;
      }
    }
    encomendaAux1.DataCompra.Dia = timeinfo->tm_mday;
    encomendaAux1.DataCompra.Mes = timeinfo->tm_mon;
    encomendaAux1.DataCompra.Ano = 1900 + timeinfo->tm_year;

    printf("Quantidade\n");
    scanf("%d", &encomendaAux1.Qnt);
    printf("----------------\n");
    livroAux = (ProcurarLivro(*ListaLivros, livroAux))->book;
    encomendaAux1.PrecoTotal = livroAux.Preco * encomendaAux1.Qnt;
    *FilaEncomendas = Juntar(encomendaAux1, *FilaEncomendas);
    printf("Encomenda inserida com sucesso.\n");
    printf("----------------\n");
    break;
  case 2:
    /* remover encomenda: encontrar cliente, encontrar livro, adicionar livro a lista de compras, remover da fila */
    // mostrar todas as encomendas
    printf("Insira o ISBN do livro da encomenda\n");
    scanf("%d", &encomendaAux2.ISBNLivro);
    printf("----------------\n");
    printf("Insira o NIF da encomenda a remover\n");
    scanf("%d", &encomendaAux2.NIFCliente);
    printf("----------------\n");
    encomendaAux1 = procurarEncomenda(encomendaAux2, *FilaEncomendas);
    if (encomendaAux1.ISBNLivro == encomendaAux2.ISBNLivro && encomendaAux1.NIFCliente == encomendaAux2.NIFCliente)
    {
      ABPEClientes = removerEncomenda(FilaEncomendas, ABPEClientes, ListaLivros, encomendaAux1);
      printf("----------------\n");
      printf("Encomenda removida com sucesso.\n");
      printf("----------------\n");
    }
    else
    {
      printf("----------------\n");
      printf("Encomenda não encontrada.\n");
      printf("----------------\n");
    }
    break;
  }
}

void MenuOperacoes(nodeL ListaLivros, nodeC arvoreClientes, nodeE FilaEncomendas)
{
  int mes1, ano1, mes2, ano2;
  char *areaMaisComprada;
  char auxStr[60] = " ";
  int opcao;
  time_t rawtime;
  struct tm *timeinfo;
  CLIENTE clienteAux;
  nodeL auxAH, auxAT;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  do
  {
    printf("0 - Sair\n1 - Quantos livros foram vendidos num dado periodo de tempo (mes e ano)\n2 - Data da ultima compra de um livro\n3 - Quantos livros comprados p/ cliente\n4 - K livros mais recentes Area Cientifica\n5 - K livros mais vendidos num dado periodo (mes e ano)\n6 - Área Cientifica com mais livros\n7 - Cliente com mais livros comprados\n8 - Mostrar os Clientes por ordem decrescente do número de compras\n9 - Ano com mais publicacoes\n10 - Cliente que mais gastou num dado período (mês e ano)\n11 - Desperdício  de memória\n12 - Autor Best Seller\n13 - Livro mais caro\n14 - Area Cientifica mais comprada\n15 - Area Cientifica mais cara\n");
    scanf("%d", &opcao);
  } while (opcao > 15 || opcao < 0);

  int k, y = 0, tamanhoLista, n = 0;
  LIVRO bookAux;
  nodeL bookToSearch;
  LIVRO maiorLivro;
  COMPRA compra;
  nodeL auxH, auxT, aux2;
  CriarLivro(&auxH, &auxT);
  CLIENTE *array;
  char areaCientifica[50];
  nodeL listaAux, listaAuxTail;
  nodeL nodoAux;
  nodeL listaAux2H, listaAux2T;

  switch (opcao)
  {
  case 0:
    break;

  case 1:

    printf("Insira o mes inferior:\t");
    scanf("%d", &mes1);
    printf("Insira o ano inferior:\t");
    scanf("%d", &ano1);
    do
    {
      printf("Insira o mes superior:\t");
      scanf("%d", &mes2);
      printf("Insira o ano superior:\t");
      scanf("%d", &ano2);
    } while (mes2 < mes1 || ano2 > 1900 + timeinfo->tm_year);
    nodoCompras aux = CriarCompra();
    printf("Foram vendidos %d livros nesse mês e ano\n", LivrosVendidosTempo(arvoreClientes, mes1, ano1, mes2, ano2, aux));
    break;
  case 2:
    printf("Insira o ISBN do livro a procurar:\t");
    scanf("%ld", &bookAux.ISBN);
    if (ConsultarCabecaLivro(ListaLivros, bookAux))
    {
      bookToSearch = ProcurarLivro(ListaLivros, bookAux);
      strcpy(compra.Produto, bookToSearch->book.Titulo);
      compra.dataCompra.Dia = 0;
      compra.dataCompra.Ano = 0;
      compra.dataCompra.Mes = 0;
      nodoCompras aux = CriarCompra();
      compra = determinarDataCompraLivro(ListaLivros, arvoreClientes, FilaEncomendas, compra, aux);
      printf("A data da venda mais recende do livro '%s' é: %d-%d-%d\n", compra.Produto, compra.dataCompra.Dia, compra.dataCompra.Mes, compra.dataCompra.Ano);
      break;
    }

    printf("Livro não existe.\n");
    break;
  case 3:
    do
    {
      printf("Insira NIF:\n");
      scanf("%d", &clienteAux.NIF);
    } while (clienteAux.NIF <= 0 || PesquisarABP(arvoreClientes, clienteAux) == 0);

    clienteAux = (ProcurarCliente(arvoreClientes, clienteAux))->client;

    printf("O cliente já comprou %d livros\n", QuantidadeLivrosCompradosCliente(clienteAux));
    break;
  case 4:
    CriarLivro(&listaAux2H, &listaAux2T);
    CriarLivro(&listaAux, &listaAuxTail);

    do
    {
      printf("Insira k: ");
      scanf("%d", &k);
    } while (k <= 0 || k > TamanhoLivro(ListaLivros));
    fgetc(stdin); // senão não funciona

    do
    {
      printf("Insira a area cientifica:\t");
      fgets(areaCientifica, lengthAreaCientifica, stdin);
      areaCientifica[strlen(areaCientifica) - 1] = '\0';

    } while (procurarAreaCientifica(ListaLivros, areaCientifica) != 1);

    getKLivrosRecentesAreaCientifica(ListaLivros, areaCientifica, &listaAux, &listaAuxTail);

    tamanhoLista = TamanhoLivro(listaAux);
    if (tamanhoLista < k)
    {
      printf("Nao temos %d livros para mostrar\n", k);
      return;
    }
    while (y < k)
    {
      nodoAux = getMostRecentBook(listaAux, areaCientifica, 0, listaAux2H);

      printf("-------------------------------\n");
      MostrarElementoLivro(nodoAux->book);
      printf("-------------------------------\n");

      if (RemoverLivroDadoISBN(&listaAux, &listaAuxTail, nodoAux->book.ISBN, &FilaEncomendas))
      {
        y++;
      }
      else
      {
        break;
      }
    }
    break;
  case 5:
    do
    {
      printf("Insira k: ");
      scanf("%d", &k);
    } while (k <= 0);
    int maior = 0;
    printf("Insira o mes inferior:\t");
    scanf("%d", &mes1);
    printf("Insira o ano inferior:\t");
    scanf("%d", &ano1);
    do
    {
      printf("Insira o mes superior:\t");
      scanf("%d", &mes2);
      printf("Insira o ano superior:\t");
      scanf("%d", &ano2);
    } while (mes2 > timeinfo->tm_mon || ano2 > 1900 + timeinfo->tm_year);

    auxH = MostrarKMaisVendidosPeriodo(arvoreClientes, ListaLivros, mes1, ano1, mes2, ano2, k, &auxH, &auxT);
    n = 0;
    aux2 = auxH;
    if (TamanhoLivro(auxH) >= k)
    {
      printf("_________OS %d MAIS VENDIDOS_________\n", k);
      while (n < k)
      {
        aux2 = auxH;
        maior = aux2->book.Stock;

        while (aux2 != NULL)
        {
          if (aux2->book.Stock >= maior)
          {
            maiorLivro = aux2->book;
            maior = aux2->book.Stock;
          }
          aux2 = aux2->next;
        }
        printf("-------------------------------\n");
        MostrarElementoLivro(maiorLivro);
        printf("-------------------------------\n");
        if (RemoverLivroDadoISBN(&auxH, &auxT, maiorLivro.ISBN, &FilaEncomendas))
        {
          n++;
        }
        else
        {
          break;
        }
      }
    }
    else
    {
      printf("Não temos %d livros para mostrar.\n", k);
    }

    break;
  case 6:
    AreaCientificaComMaisLivros(ListaLivros);
    break;
  case 7:
    n = ClienteMaisLivrosComprados(arvoreClientes, &clienteAux, 0);
    printf("O cliente com mais livros comprados é:\n-------------- INFORMAÇÃO CLIENTE --------------\n");
    MostrarCliente(clienteAux);
    printf("-------------------------------\n");
    printf("O cliente comprou um total de %d livros\n", n);
    printf("-------------------------------\n");
    break;
  case 8:

    if (ABVazia(arvoreClientes))
    {
      printf("---------------------------\n");
      printf("Árvore vazia.\n");
      printf("---------------------------\n");
      break;
    }

    n = NumeroNodosAB(arvoreClientes);
    array = (CLIENTE *)malloc(n * sizeof(CLIENTE));
    y = 0;
    getVetorClientes(arvoreClientes, array, &y);

    while (y > 0)
    {
      k = getIndexClienteMaiorLista(array, y);

      MostrarCliente(array[k]);
      for (int j = k; j < y - 1; j++)
      {
        array[j] = array[j + 1];
      }
      y--;
    }
    break;
  case 9:
    AnoComMaisPublicacoes(ListaLivros);
    break;
  case 10:
    printf("Insira o mes inferior:\t");
    scanf("%d", &mes1);
    printf("Insira o ano inferior:\t");
    scanf("%d", &ano1);
    do
    {
      printf("Insira o mes superior:\t");
      scanf("%d", &mes2);
      printf("Insira o ano superior:\t");
      scanf("%d", &ano2);
    } while (mes2 > timeinfo->tm_mon || ano2 > 1900 + timeinfo->tm_year);

    clienteAux = arvoreClientes->client;
    float gastos = 0;

    clienteAux = CalcularClienteMaisGastos(arvoreClientes, mes1, ano1, mes2, ano2, clienteAux, &gastos);

    if (gastos == 0)
    {
      printf("Não há nenhum cliente com compras feitas nesse período de tempo\n");
    }
    else
    {
      printf("O cliente com mais livros comprados é:\n-------------- INFORMAÇÃO CLIENTE --------------\n");
      MostrarCliente(clienteAux);
      printf("O cliente gastou um total de %f euros\n", gastos);
    }
    break;
  case 11:
    printf("__DESPERDICIO = %d__\n", DesperdicioMemoriaCliente(arvoreClientes, 0) + DesperdicioMemoriaLivro(ListaLivros, 0));
    break;
  case 12:

    CriarLivro(&auxAH, &auxAT);
    printf("Insira o mes:\t");
    scanf("%d", &mes1);
    do
    {
      printf("Insira o ano:\t");
      scanf("%d", &ano1);
    } while (ano1 < 0 && ano1 > 1900 + timeinfo->tm_year);

    AutorBestSeller(arvoreClientes, ListaLivros, mes1, ano1, &auxAH, &auxAT);
    int maiorStock = 0;

    while (auxAH != NULL)
    {
      if (auxAH->book.Stock > maiorStock)
      {
        maiorLivro = auxAH->book;
        maiorStock = auxAH->book.Stock;
      }
      auxAH = auxAH->next;
    }

    printf("____________AUTOR BEST SELLER____________\n");
    maiorLivro = (ProcurarLivro(ListaLivros, maiorLivro))->book;
    printf("\t\t%s\n", maiorLivro.FirstAuthor);
    break;
  case 13:
    LivroMaisCaro(ListaLivros);
    break;
  case 14:
    areaMaisComprada = areaCientificaMaisComprada(arvoreClientes, FilaEncomendas, ListaLivros, auxStr, 0);
    printf("____________AREA CIENTIFICA MAIS COMPRADA_____________\n");
    printf("\t\t%s\n\n", areaMaisComprada);
    break;

  case 15:
    AreaCientificaMaisCara(ListaLivros);
    break;
  }
}