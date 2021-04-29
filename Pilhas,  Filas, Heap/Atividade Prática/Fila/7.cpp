#include <iostream>

using namespace std;

struct senha
{
    string tipo;
    string nomeCliente;
};

class noh
{
    friend class fila;

private:
    senha dados;
    noh *proximo;

public:
    noh(senha dadosSenha);
    senha valorNoh();
};
noh::noh(senha dadosSenha)
{
    dados = dadosSenha;
    proximo = NULL;
}
senha noh::valorNoh()
{
    return dados;
}
class fila
{
private:
    noh *inicio;
    noh *fim;
    unsigned tamanho;

public:
    fila();
    ~fila();
    void limpaFila();
    bool filaVazia();
    noh inicioFila();
    void enfileira(senha dado);
    senha desenfileira();
};

fila::fila()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

fila::~fila()
{
    limpaFila();
}

void fila::limpaFila()
{
    while (tamanho > 0)
    {
        desenfileira();
    }
}

bool fila::filaVazia()
{
    return (tamanho == 0);
}

//Conferir se vai usar
noh fila::inicioFila()
{
    return *inicio;
}

void fila::enfileira(senha dado)
{
    noh *novo = new noh(dado);
    if (filaVazia())
    {
        inicio = novo;
    }
    else
    {
        fim->proximo = novo;
    }

    fim = novo;
    tamanho++;
}

senha fila::desenfileira()
{
    senha dado = inicio->dados;
    noh *aux = inicio;
    inicio = inicio->proximo;
    delete aux;
    tamanho--;
    if (filaVazia())
    {
        fim = NULL;
    }

    return dado;
}

int main()
{
    fila fila1;
    int n = 10;
    senha dado;
    for (int i = 0; i < n; i++)
    {
        cout << "Tipo: ";
        cin >> dado.tipo;
        cout << "Nome do cliente: ";
        cin >> dado.nomeCliente;
        fila1.enfileira(dado);
    }
    while (not fila1.filaVazia())
    {
        cout << fila1.desenfileira().nomeCliente << " ";
    }

    return 0;
}