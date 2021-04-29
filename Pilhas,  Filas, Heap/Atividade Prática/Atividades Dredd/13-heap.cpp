#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class maxHeap
{
private:
    int *heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void arruma();
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);

public:
    maxHeap(int cap);
    maxHeap(int vet[], int tam, int cap);
    ~maxHeap();
    void imprime();
    int espiaRaiz();
    int retiraRaiz();
    void insere(int dado);
};

maxHeap::maxHeap(int cap)
{
    capacidade = cap;
    tamanho = 0;
    heap = new int[cap];
}

maxHeap::maxHeap(int vet[], int tam, int cap)
{
    capacidade = cap;
    heap = new int[capacidade];
    memcpy(heap, vet, capacidade * sizeof(int));

    tamanho = tam;
    arruma();
}

maxHeap::~maxHeap()
{
    delete[] heap;
}

int maxHeap::pai(int i)
{
    return (i - 1) / 2;
}

int maxHeap::esquerdo(int i)
{
    return 2 * i + 1;
}

int maxHeap::direito(int i)
{
    return 2 * i + 2;
}

void maxHeap::arruma()
{
    for (int i = (tamanho / 2 - 1); i >= 0; i--)
    {
        corrigeDescendo(i);
    }
}

void maxHeap::corrigeDescendo(int i)
{
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;

    if ((esq <= tamanho - 1) and (heap[esq] > heap[maior]))
    {
        maior = esq;
    }
    if ((dir <= tamanho - 1) and (heap[dir] > heap[maior]))
    {
        maior = dir;
    }
    if (maior != i)
    {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void maxHeap::corrigeSubindo(int i)
{
    int p = pai(i);
    if ((heap[i] > heap[p]) and (p >= 0))
    {
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

int maxHeap::espiaRaiz()
{
    return heap[0];
}

void maxHeap::imprime()
{
    for (int i = 0; i < tamanho; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}

int maxHeap::retiraRaiz()
{
    if (tamanho == 0)
    {
        cerr << "Erro ao retirar raiz" << endl;
        exit(EXIT_FAILURE);
    }
    int aux = heap[0];
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

void maxHeap::insere(int dado)
{
    if (tamanho == capacidade)
    {
        cerr << "Erro ao inserir" << endl;
        exit(EXIT_FAILURE);
    }
    heap[tamanho] = dado;
    corrigeSubindo(tamanho);
    tamanho++;
}

int main()
{
    int vetor[20];
    for (int i = 0; i < 15; i++)
    {
        cin >> vetor[i];
    }
    maxHeap *h = new maxHeap(vetor, 15, 20);
    h->imprime();
    int novoDado;
    for (int i = 0; i < 5; i++)
    {
        cin >> novoDado;
        h->insere(novoDado);
    }
    h->imprime();

    for (int i = 0; i < 20; i++)
    {
        cout << h->retiraRaiz() << " ";
    }

    return 0;
}
