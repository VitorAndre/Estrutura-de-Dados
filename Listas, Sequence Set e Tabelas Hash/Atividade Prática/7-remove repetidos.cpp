//Vitor André de Oliveira Tenório 10A
#include <iostream>

using namespace std;

typedef int Dado;

class noh
{
	friend class listadup;

private:
	const Dado dado;
	noh *proximo;
	noh *anterior;

public:
	noh(Dado d = 0);
};
noh::noh(Dado d) : dado(d)
{
	proximo = NULL;
	anterior = NULL;
}

class listadup
{
private:
	noh *primeiro;
	noh *ultimo;
	int tamanho;

public:
	listadup();
	listadup(const listadup &lista);
	~listadup();
	void insereNoFim(Dado dado);
	void imprime();
	inline bool vazia();
	void removeRepetidos();
};

listadup::listadup()
{
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
};

//construtor de copia
listadup::listadup(const listadup &lista)
{
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

	noh *aux = lista.primeiro;

	while (aux != NULL)
	{
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
};
listadup::~listadup()
{
	noh *atual = primeiro;
	while (atual != NULL)
	{
		noh *aux = atual;
		atual = atual->proximo;
		delete aux;
	}
};
void listadup::insereNoFim(Dado dado)
{

	noh *novo = new noh(dado);

	if (vazia())
	{
		primeiro = novo;
		ultimo = novo;
	}
	else
	{
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
};

void listadup::imprime()
{
	// imprime normal
	noh *aux = primeiro;
	while (aux != NULL)
	{
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;

	// imprime reverso
	aux = ultimo;

	while (aux != NULL)
	{
		cout << aux->dado << " ";
		aux = aux->anterior;
	}

	cout << endl;
};

bool listadup::vazia()
{
	return (tamanho == 0);
}

void listadup::removeRepetidos()
{
	noh *aux = primeiro;
	noh *auxFora = primeiro;
	for (int i = 0; i < tamanho - 1; i++)
	{
		while (aux->proximo != NULL)
		{

			if (aux->proximo->dado == auxFora->dado)
			{
				if (aux->proximo == ultimo)
				{
					aux->proximo = NULL;
					ultimo = aux;
				}
				else
				{
					aux->proximo = aux->proximo->proximo;
					aux->proximo->anterior = aux;
				}
				tamanho--;
			}
			else
				aux = aux->proximo;
		}
		auxFora = auxFora->proximo;
		aux = auxFora;
	}
}
int main()
{
	listadup lista;
	int n, dado;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> dado;
		lista.insereNoFim(dado);
	}
	lista.removeRepetidos();
	lista.imprime();
	return 0;
}
