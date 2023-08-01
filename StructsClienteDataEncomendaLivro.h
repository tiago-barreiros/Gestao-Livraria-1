#define lengthTitulo 60
#define lengthIdioma 20
#define lengthFirstAuthor 30
#define lengthSndAuthor 30
#define lengthEditora 30
#define lengthAreaCientifica 30

#define lengthNome 50
#define lengthMorada 80

typedef struct{
  long ISBN;
  char Titulo[lengthTitulo];
  char Idioma[lengthIdioma];
  char FirstAuthor[lengthFirstAuthor];
  char SndAuthor[lengthSndAuthor];
  char Editora[lengthEditora];
  int AnoPub;
  char AreaCientifica[lengthAreaCientifica];
  float Preco;
  int Stock;
}LIVRO;

typedef struct{
  int Dia;
  int Mes;
  int Ano;
}DATA;

typedef struct{
  int ISBNLivro;
  int NIFCliente;
  DATA DataCompra;
  int Qnt;
  float PrecoTotal; 
}ENCOMENDA;   

typedef struct {
  char Produto[lengthTitulo];
  DATA dataCompra;
  int qtd;
  float preco;
} COMPRA;

struct Nodo
{
    COMPRA Elemento;
    struct Nodo *Prox;
};

typedef struct Nodo *nodoCompras;

typedef struct{
  int NIF;
  char Nome[lengthNome];
  char Morada[lengthMorada];
  int Telefone;
  nodoCompras ListaDeCompras;
}CLIENTE;


struct nodeL{
  LIVRO  book;
  struct nodeL *next;
  struct nodeL *prev;
};

typedef struct nodeL *nodeL;

//Arvore Binaria Balanceada
struct nodoCliente {
	CLIENTE  client;
	struct nodoCliente *left;
	struct nodoCliente *right;
};

typedef struct nodoCliente *nodeC;

//Fila

struct nodeEncomenda {
  ENCOMENDA  encomenda;
  struct nodeEncomenda *next;
};

typedef struct nodeEncomenda *nodeE;

