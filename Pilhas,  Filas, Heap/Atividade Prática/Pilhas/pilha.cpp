#include <iostream>

using namespace std;

class noh
{
    friend class pilha;

private:
    int valorNoh;
    noh *proximo;

public:
    noh(int valor);
    ~noh();
};

noh::noh(int valor)
{
    valorNoh = valor;
    proximo = NULL;
}

class pilha
{
private:
    noh *topo;
    int tamanho;

public:
    pilha();
    ~pilha();
    void empilha(int valor);
    void imprimeTopo();
    void desempilha();
};

pilha::pilha()
{
    topo = NULL;
    tamanho = 0;
}

pilha::~pilha()
{
    tamanho = 0;
}

void pilha::empilha(int valor)
{
    noh *novo = new noh(valor);
    novo->proximo = topo;

    topo = novo;
    tamanho++;
}

void pilha::imprimeTopo()
{
    cout << "Topo: " << topo->valorNoh << endl;
}

void pilha::desempilha()
{
    //int dado = topo->valorNoh;
    topo = topo->proximo;
    //cout << "Tchau, " << dado << endl;
    tamanho--;
    //cout << tamanho << endl;
}

int main()
{
    pilha *x = new pilha();

    return 0;
}