#include <iostream>

using namespace std;

class noh
{
    friend class fila;

private:
    int nomeCliente;
    noh *proximo;

public:
    noh(int info)
    {
        nomeCliente = info;
        proximo = NULL;
    }
    ~noh()
    {
        proximo = NULL;
        delete proximo;
    }
    int valorNoh();
};

int noh::valorNoh()
{
    return nomeCliente;
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
    bool estaVazia();
    void enfileira(int nome);
    int desenfileira();
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
        cout << desenfileira() << endl;
    }
}

bool fila::estaVazia()
{
    return (tamanho == 0);
}

void fila::enfileira(int nome)
{
    noh *novo = new noh(nome);
    if (tamanho == 0)
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

int fila::desenfileira()
{
    int nome = inicio->nomeCliente;
    noh *aux = inicio;
    inicio = inicio->proximo;
    delete aux;
    tamanho--;
    if (tamanho == 0)
    {
        fim = NULL;
    }
    return nome;
}

int main()
{
    fila filaNormal;
    filaNormal.enfileira(0);
    filaNormal.enfileira(1);
    int a = 0, b = 0;
    for (int i = 0; i < 10; i++)
    {
        a = filaNormal.desenfileira();
        b = filaNormal.desenfileira();
        filaNormal.enfileira(a + b);
        filaNormal.enfileira(b);
        filaNormal.enfileira(a);
    }
    filaNormal.limpaFila();

    /*
    int op, nome;
    int qtdPrioridade = 0; //guarda quantos pacientes prioritários foram atendidos em sequencia
    while (op != "fim")
    {
        cin >> op;
        if (op == "normal")
        {
            cin >> nome;
            filaNormal.enfileira(nome);
        }
        if (op == "prioridade")
        {
            cin >> nome;
            filaPrioridade.enfileira(nome);
        }
        if (op == "atender")
        {
            if (filaPrioridade.estaVazia() and filaNormal.estaVazia())
            {
                cout << "AGUARDE" << endl;
                qtdPrioridade = 0;
            }
            else
            {
                if ((qtdPrioridade >= 3 and not filaNormal.estaVazia()) or filaPrioridade.estaVazia())
                {
                    cout << filaNormal.desenfileira() << endl;
                    qtdPrioridade = 0;
                }
                else
                {
                    if ((qtdPrioridade < 3 and not filaPrioridade.estaVazia()) or filaNormal.estaVazia())
                    {
                        cout << filaPrioridade.desenfileira() << endl;
                        qtdPrioridade++;
                    }
                }
            }
        }
    }
*/
    return 0;
}