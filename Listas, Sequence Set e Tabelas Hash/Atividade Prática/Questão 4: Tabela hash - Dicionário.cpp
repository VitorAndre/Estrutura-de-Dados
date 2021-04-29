#include <iostream>
#include <string>

using namespace std;

int calculaHash(string chave)
{
	int hash = (chave.size() % 23);
	return hash;
}

class noh
{
	friend class tabelaHash;

private:
	string chave;
	string valor;
	noh *proximo;

public:
	noh(string c, string v);
};

noh::noh(string c, string v)
{
	chave = c;
	valor = v;
	proximo = NULL;
}
class tabelaHash
{
private:
	noh **tabela;
	int capacidade;

public:
	tabelaHash(int cap = 23);
	~tabelaHash();
	void insere(string chave, string valor);
	string busca(string c);
};

tabelaHash::tabelaHash(int cap)
{
	tabela = new noh *[cap];
	capacidade = cap;

	for (int i = 0; i < cap; i++)
	{
		tabela[i] = NULL;
	}
}

tabelaHash::~tabelaHash()
{
	for (int i = 0; i < capacidade; i++)
	{
		noh *atual = tabela[i];
		while (atual != NULL)
		{
			noh *ant = atual;
			atual = atual->proximo;
			//cout << ant->valor << endl;
			delete ant;
		}
	}
	delete[] tabela;
}

void tabelaHash::insere(string chave, string valor)
{
	int posicao = calculaHash(chave);

	if (tabela[posicao] == NULL)
	{
		noh *novo = new noh(chave, valor);
		tabela[posicao] = novo;
	}
	else
	{
		noh *atual = tabela[posicao];
		while (atual->proximo != NULL)
		{
			atual = atual->proximo;
		}

		noh *novo = new noh(chave, valor);
		atual->proximo = novo;
	}
}

string tabelaHash::busca(string chave)
{
	int posicao = calculaHash(chave);
	if (tabela[posicao] != NULL and tabela[posicao]->chave == chave)
		return tabela[posicao]->valor;
	else
	{
		noh *atual = tabela[posicao];
		while ((atual != NULL) and (atual->chave != chave))
		{
			atual = atual->proximo;
		}
		if ((atual != NULL) and (atual->chave == chave))
		{
			return atual->valor;
		}
		else
		{
			return "NULL";
		}
	}
}

int main()
{
	tabelaHash hash(23);

	int qtd;
	cin >> qtd;

	string chave, valor;
	for (int i = 0; i < qtd; i++)
	{
		cin >> chave;
		cin.ignore();
		getline(cin, valor);

		hash.insere(chave, valor);
	}

	string aux;
	cin >> aux;
	while (aux != "-1")
	{
		valor = hash.busca(aux);
		cout << "[" << aux << "] => " << valor << endl;
		cin >> aux;
	}

	return 0;
}
