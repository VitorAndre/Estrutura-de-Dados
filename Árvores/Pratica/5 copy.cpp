#include <iostream>

typedef int Dado;

using namespace std;

class Noh
{
	friend class ABB;

private:
	Noh *esquerdo;
	Noh *direito;
	Noh *pai;
	Dado valor;

public:
	Noh(Dado d);
};

Noh::Noh(Dado d)
{
	esquerdo = NULL;
	direito = NULL;
	pai = NULL;
	valor = d;
}

class ABB
{
private:
	Noh *raiz;

public:
	ABB();
	~ABB();
	void destruirABB(Noh *atual);
	void insere(Dado d);
	int conta(Noh *atual);
	int contaEsq();
	int contaDir();
	bool vazia();
};

ABB::ABB()
{
	raiz = NULL;
}

ABB::~ABB()
{
	destruirABB(raiz);
}

void ABB::destruirABB(Noh *atual)
{
	if (atual != NULL)
	{
		destruirABB(atual->esquerdo);
		destruirABB(atual->direito);
		delete atual;
	}
}

void ABB::insere(Dado dado)
{
	Noh *novo = new Noh(dado);
	if (raiz == NULL)
	{
		raiz = novo;
	}
	else
	{
		Noh *atual = raiz;
		Noh *anterior = NULL;

		while (atual != NULL)
		{
			anterior = atual;
			if (atual->valor > dado)
			{
				atual = atual->esquerdo;
			}
			else
			{
				atual = atual->direito;
			}
		}
		novo->pai = anterior;
		if (anterior->valor > novo->valor)
		{
			anterior->esquerdo = novo;
		}
		else
		{
			anterior->direito = novo;
		}
	}
}

int ABB::contaEsq()
{
	if (raiz)
	{
		return conta(raiz->esquerdo);
	}
	return 0;
}
int ABB::contaDir()
{
	if (raiz)
	{
		return conta(raiz->direito);
	}
	return 0;
}

int ABB::conta(Noh *atual)
{
	if (atual != NULL)
	{
		return conta(atual->esquerdo) + conta(atual->direito) + 1;
	}
	return 0;
}

bool ABB::vazia()
{
	if (!raiz)
	{
		return true;
	}
	return false;
}

int main()
{
	ABB arvore;
	int op;
	cin >> op;
	while (op != -1)
	{
		arvore.insere(op);
		cin >> op;
	}
	if (arvore.vazia())
	{
		cout << "0 0";
	}
	else
	{
		int esquerda = arvore.contaEsq();
		int direita = arvore.contaDir();
		cout << esquerda + direita + 1 << " " << esquerda - direita;
	}
	return 0;
}
