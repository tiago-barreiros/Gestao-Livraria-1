#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "StructsClienteDataEncomendaLivro.h"
#include "OperacoesEDs.h"
#include "functions.h"
#include "operacoes.h"
#include "Menus.h"

int main()
{
  int saved = 0;
  int sair;
  nodeL ListaLivrosHead, ListaLivrosTail;
  CriarLivro(&ListaLivrosHead, &ListaLivrosTail);

  nodeC ABPEClientes;
  ABPEClientes = CriarAB();

  nodeE FilaEncomendas;
  FilaEncomendas = CriarFila();

  int opcao, qnt;

  do
  {
    printf("1 - Nova ED Livro (LLD)\n2 - Nova ED Cliente (ABPB)\n3 - Nova ED Livro & Nova ED Cliente\n4 - Abrir\n"); //ADICIONAR AMBOS
    scanf("%d", &opcao);
  } while (opcao > 4 || opcao <= 0);

  switch (opcao)
  {
  case 1: //Criar n Livros
    LerFicheiroClientes(&ABPEClientes);
    LerFicheiroEncomendas(&FilaEncomendas);
    do
    {
      printf("Quantos livros deseja inserir?\n");
      scanf("%d", &qnt);
    } while (qnt <= 0);

    for (int i = 0; i < qnt; i++)
    {
      InserirLivro(&ListaLivrosHead, &ListaLivrosTail); //Insere livros na lista
    }
    break;

  case 2:
    LerFicheiroLivros(&ListaLivrosHead, &ListaLivrosTail);
    LerFicheiroEncomendas(&FilaEncomendas);
    do
    {
      printf("Quantos clientes deseja inserir?\n");
      scanf("%d", &qnt);
    } while (qnt <= 0);

    for (int i = 0; i < qnt; i++)
    {
      InserirCliente(&ABPEClientes);
    }

    break;
  case 3:
    LerFicheiroEncomendas(&FilaEncomendas);

    printf("------------------------------------------\n");

    do
    {
      printf("Quantos livros deseja inserir?\n");
      scanf("%d", &qnt);
    } while (qnt <= 0);

    for (int i = 0; i < qnt; i++)
    {
      InserirLivro(&ListaLivrosHead, &ListaLivrosTail); //Insere livros na lista
    }

    do
    {
      printf("Quantos clientes deseja inserir?\n");
      scanf("%d", &qnt);
    } while (qnt <= 0);

    for (int i = 0; i < qnt; i++)
    {
      InserirCliente(&ABPEClientes);
      printf("------------------------------------------\n");
    }

    break;
  case 4:
    LerFicheiroClientes(&ABPEClientes);
    LerFicheiroLivros(&ListaLivrosHead, &ListaLivrosTail);
    LerFicheiroEncomendas(&FilaEncomendas);
    break;
  }

  printf("------------------------------------------\n");

  do
  {

    do
    {
      printf("1 - Ficheiro\t2 - Livros\t3 - Clientes\t4 - Encomendas\t5 - Operacoes\t6 - Comprar\t7 - Sair\n");
      scanf("%d", &opcao);
    } while (opcao > 7 || opcao < 1);

    switch (opcao)
    {
    case 1:
      printf("------------------------------------------\n");
      MenuFicheiro(ListaLivrosHead, ABPEClientes, FilaEncomendas);
      printf("------------------------------------------\n");
      saved = 1;
      break;
    case 2:
      printf("------------------------------------------\n");
      MenuLivros(&ListaLivrosHead, &ListaLivrosTail, &FilaEncomendas, &ABPEClientes);
      printf("------------------------------------------\n");
      saved = 0;
      break;
    case 3:
    printf("------------------------------------------\n");
      MenuClientes(&ABPEClientes, &FilaEncomendas);
    printf("------------------------------------------\n");
      saved = 0;
      break;
    case 4:
    printf("------------------------------------------\n");
      MenuEncomendas(&FilaEncomendas, ABPEClientes, &ListaLivrosHead);
      saved = 0;
    printf("------------------------------------------\n");
      break;
    case 5:
    printf("------------------------------------------\n");
      MenuOperacoes(ListaLivrosHead, ABPEClientes, FilaEncomendas);
      saved = 0;
    printf("------------------------------------------\n");
      break;
    case 6:
    printf("------------------------------------------\n");
      ABPEClientes = Compras(ABPEClientes, &ListaLivrosHead, &FilaEncomendas);
    printf("------------------------------------------\n");
      saved = 0;
      break;
    case 7:
      if (saved)
      {
        break;
      }
      else
      {
        do
        {
          printf("Tem alterações por guardar.\n1 - Guardar\n2 - Sair\n");
          scanf("%d", &sair);
        } while (sair < 1 || sair > 2);

        switch (sair)
        {
        case 1:
          guardar(ListaLivrosHead, ABPEClientes, FilaEncomendas);
          break;
        case 2:
          break;
        }
      }
      printf("------------------------------------------\n");
    }
  } while (opcao != 7);

  return 0;
}
