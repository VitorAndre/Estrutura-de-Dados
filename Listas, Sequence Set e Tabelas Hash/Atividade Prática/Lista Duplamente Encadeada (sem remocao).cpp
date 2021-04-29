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
	listadup(const listadup &umaLista);
	~listadup();

	//Ver depois
	listadup &operator=(const listadup &umaLista);
	//----------

	inline void insere(Dado dado);
	void insereNoFim(Dado dado);
	void insereNoInicio(Dado dado);
	void insereNaPosicao(int posicao, Dado dado);
	int procura(Dado valor);

	void imprime();
	inline bool vazia();
};

listadup::listadup()
{
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
};

//construtor de copia
listadup::listadup(const listadup &umaLista)
{
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

	noh *aux = umaLista.primeiro;

	while (aux != NULL)
	{
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
};
listadup::~listadup()
{
	// destroi a lista
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

	if (tamanho == 0)
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

void listadup::insereNoInicio(Dado dado)
{

	noh *novo = new noh(dado);

	if (tamanho == 0)
	{
		primeiro = novo;
		ultimo = novo;
	}
	else
	{
		novo->proximo = primeiro;
		primeiro->anterior = novo;
		primeiro = novo;
	}
	tamanho++;
};

void listadup::insereNaPosicao(int posicao, Dado dado)
{

	noh *novo = new noh(dado);

	if ((posicao <= tamanho) and (posicao >= 0))
	{
		if (tamanho == 0)
		{
			primeiro = novo;
			ultimo = novo;
		}
		else if (posicao == 0)
		{
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}
		else if (posicao == tamanho)
		{
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}
		else
		{
			noh *aux = primeiro;
			int posAux = 0;

			while (posAux < (posicao - 1))
			{
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
		tamanho++;
	}
	else
	{
		cerr << "Posição inexistente!" << endl;
		exit(EXIT_FAILURE);
	}
};

int listadup::procura(Dado dado)
{
	noh *aux = primeiro;
	int posAux = 0;

	while ((aux != NULL) and (aux->dado != dado))
	{
		posAux++;
		aux = aux->proximo;
	}
	if (aux == NULL)
	{
		posAux = -1;
	}
	return posAux;
}

void listadup::imprime()
{
	// método básico que *percorre* uma lista, imprimindo seus elementos
	noh *aux = primeiro;
	while (aux != NULL)
	{
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;

	// imprime reverso (para mostrar duplo encadeamento)
	aux = ultimo;

	while (aux != NULL)
	{
		cout << aux->dado << " ";
		aux = aux->anterior;
	}

	cout << endl;
};

// NÃO MODIFICAR
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
	lista.imprime();
	return 0;
}
