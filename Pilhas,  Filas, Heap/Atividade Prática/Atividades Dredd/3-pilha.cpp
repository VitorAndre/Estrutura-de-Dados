#include <iostream>

using namespace std;

class noh
{
    friend class pilha;

private:
    int dado;
    noh *proximo;

public:
    noh(int valor);
    int valorNoh();
};
noh::noh(int valor)
{
    dado = valor;
    proximo = NULL;
}
int noh::valorNoh()
{
    return dado;
}

class pilha
{
private:
    noh *topo;
    int tamanho;

public:
    pilha();
    ~pilha();
    int tamanhoPilha();
    noh topoPilha();
    void empilha(int valor);
    void imprimeTopo();
    int desempilha();
    bool vazia();
    void limpaPilha();
};

pilha::pilha()
{
    topo = NULL;
    tamanho = 0;
}

pilha::~pilha()
{
    limpaPilha();
}

int pilha::tamanhoPilha()
{
    return tamanho;
}

void pilha::empilha(int valor)
{
    noh *novo = new noh(valor);
    novo->proximo = topo;

    topo = novo;
    tamanho++;
}

noh pilha::topoPilha()
{
    return *topo;
}

int pilha::desempilha()
{
    int dado = topo->dado;
    noh *aux = topo;
    topo = topo->proximo;
    delete aux;
    tamanho--;
    return dado;
}

bool pilha::vazia()
{
    return (tamanho == 0);
}

void pilha::limpaPilha()
{
    while (tamanho > 0)
    {
        desempilha();
    }
}

int acessaElemento(pilha &p, int elemento)
{
    pilha pilhaAuxiliar;
    int dadoAuxiliar, i = 1, tamanhoPilhaOriginal = p.tamanhoPilha();

    while (i <= tamanhoPilhaOriginal)
    {
        dadoAuxiliar = p.desempilha();

        if (dadoAuxiliar == elemento)
        {
            while (pilhaAuxiliar.tamanhoPilha() > 0)
                p.empilha(pilhaAuxiliar.desempilha());

            return i;
        }
        else
        {
            pilhaAuxiliar.empilha(dadoAuxiliar);
        }
        i++;
    }
    while (pilhaAuxiliar.tamanhoPilha() > 0)
        p.empilha(pilhaAuxiliar.desempilha());

    return -1;
}

int main()
{
    pilha p1;
    int n, numero, elemento;
    cin >> n;

    while (n > 0)
    {
        cin >> numero;
        p1.empilha(numero);
        n--;
    }

    cin >> elemento;
    cout << acessaElemento(p1, elemento) << endl;
    while (not p1.vazia())
    {
        cout << p1.desempilha() << " ";
    }

    cout << endl;

    return 0;
}