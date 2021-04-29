// Vitor André de Oliveira Tenório
// Turma 10A
// Questão 13: Estrutura de dados AVL recursiva - Festival de Cinema
// n deu 100
#include <iostream>
#include <stdexcept>

using namespace std;

struct dado
{
    unsigned ano; // ano é a chave para ordenação na AVL
    string cidadeRealizacao;
    unsigned qtdadeFilmesApresentados;
};

ostream &operator<<(ostream &saida, const dado &e)
{
    saida << "(" << e.ano << "," << e.cidadeRealizacao << "," << e.qtdadeFilmesApresentados << ")";
    return saida;
}

istream &operator>>(istream &entrada, dado &e)
{
    entrada >> e.ano >> e.cidadeRealizacao >> e.qtdadeFilmesApresentados;
    return entrada;
}
typedef unsigned tipoChave;

class noh
{
    friend class avl;
    friend unsigned informarAltura(noh *umNoh);
    friend void atualizarAltura(noh *umNoh);
    friend int fatorBalanceamento(noh *umNoh);

private:
    dado elemento;
    noh *esq;
    noh *dir;
    unsigned altura;

public:
    noh(const dado &umDado) : elemento(umDado), esq(NULL), dir(NULL), altura(1) {}
    ~noh() {}
};

unsigned informarAltura(noh *umNoh)
{
    if (umNoh == NULL)
        return 0;
    else
        return umNoh->altura;
}

void atualizarAltura(noh *umNoh)
{
    unsigned altArvEsq = informarAltura(umNoh->esq);
    unsigned altArvDir = informarAltura(umNoh->dir);
    if (altArvEsq > altArvDir)
    {
        umNoh->altura = 1 + altArvEsq;
    }
    else
    {
        umNoh->altura = 1 + altArvDir;
    }
}

int fatorBalanceamento(noh *umNoh)
{
    unsigned altArvEsq = informarAltura(umNoh->esq);
    unsigned altArvDir = informarAltura(umNoh->dir);
    int fatorBal = altArvEsq - altArvDir;
    return fatorBal;
}

class avl
{
    friend ostream &operator<<(ostream &output, avl &arvore);

private:
    noh *raiz;

    // percorrimento em ordem para fazer o levantamento do ano
    // com a maior quantidade de filmes apresentados
    unsigned percorreEmOrdemAux(noh *atual); //fazer

    // funções auxiliares para remoção
    noh *encontraMenor(noh *raizSub); //feito
    noh *removeMenor(noh *raizSub);   //feito

    // funções auxiliares para inserção e remoção usando método recursivo
    // retorna o nó para ajustar o pai ou o raiz
    noh *insereAux(noh *umNoh, const dado &umDado); //feito
    noh *removeAux(noh *umNoh, tipoChave chave);    //feito

    // métodos para manutenção do balanceamento
    noh *rotacaoEsquerda(noh *umNoh);     //feito
    noh *rotacaoDireita(noh *umNoh);      //feito
    noh *arrumaBalanceamento(noh *umNoh); //feito

    // busca, método iterativo
    noh *buscaAux(tipoChave chave); //feito

    // função auxiliar do destrutor, usa percorrimento pós-ordem
    void destruirRecursivamente(noh *umNoh); //feito

    // Impressão já veio feita
    void imprimirDir(const std::string &prefixo, const noh *meuNoh);
    void imprimirEsq(const std::string &prefixo, const noh *meuNoh, bool temIrmao);

    //feito
    void levantamentoAux(noh *umNoh, unsigned *ptrAnoProcurado, unsigned *ptrMaiorNumFilmesApres);

public:
    avl() { raiz = NULL; }
    ~avl();
    void imprimir();

    // inserção e remoção são recursivos
    void insere(const dado &umDado);
    void remove(tipoChave chave);

    // busca retorna uma cópia do objeto armazenado
    dado busca(tipoChave chave);

    // efetua levantamento do ano com maior número de filmes apresentados
    unsigned levantamento();
};

// destrutor
avl::~avl()
{
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh *umNoh)
{
    if (umNoh != NULL)
    {
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        //cout << "Deletou " << umNoh->elemento << endl;
        delete umNoh;
    }
}

void avl::insere(const dado &umDado)
{
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh *avl::insereAux(noh *umNoh, const dado &umDado)
{
    if (umNoh == NULL)
    {
        noh *novo = new noh(umDado);
        return novo;
    }
    else if (umDado.ano < umNoh->elemento.ano)
    {
        umNoh->esq = insereAux(umNoh->esq, umDado);
    }
    else if (umDado.ano > umNoh->elemento.ano)
    {
        umNoh->dir = insereAux(umNoh->dir, umDado);
    }
    else
    {
        throw runtime_error("chave repetida na inserção");
    }

    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh *avl::arrumaBalanceamento(noh *umNoh)
{
    if (umNoh == NULL)
        return umNoh;

    atualizarAltura(umNoh);
    int fatorBal = fatorBalanceamento(umNoh);

    if ((fatorBal >= -1) and (fatorBal <= 1))
    {
        return umNoh;
    }

    else if ((fatorBal > 1) and (fatorBalanceamento(umNoh->esq) >= 0))
    {
        return rotacaoDireita(umNoh);
    }
    else if ((fatorBal > 1) and (fatorBalanceamento(umNoh->esq) < 0))
    {
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        return rotacaoDireita(umNoh);
    }
    else if ((fatorBal < -1) and (fatorBalanceamento(umNoh->dir) <= 0))
    {
        return rotacaoEsquerda(umNoh);
    }
    else if ((fatorBal < -1) and (fatorBalanceamento(umNoh->dir) > 0))
    {
        umNoh->dir = rotacaoDireita(umNoh->dir);
        return rotacaoEsquerda(umNoh);
    }
    return umNoh;
}

// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh *avl::rotacaoEsquerda(noh *umNoh)
{
    //cout << "chegou na rotação esquerda" << endl;

    noh *aux = umNoh->dir;
    umNoh->dir = aux->esq;

    aux->esq = umNoh;

    atualizarAltura(umNoh);
    atualizarAltura(aux);

    return aux;
}

// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh *avl::rotacaoDireita(noh *umNoh)
{
    // //cout << "chegou na rotação direita" << endl;
    noh *aux = umNoh->esq;
    umNoh->esq = aux->dir;

    aux->dir = umNoh;

    atualizarAltura(umNoh);
    atualizarAltura(aux);

    return aux;
}

// método de busca auxiliar (retorna o nó), iterativo
noh *avl::buscaAux(tipoChave chave)
{
    noh *atual = raiz;
    while (atual != NULL)
    {
        if (atual->elemento.ano == chave)
        {
            return atual;
        }
        else if (atual->elemento.ano > chave)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave)
{
    noh *resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh *avl::encontraMenor(noh *raizSub)
{
    while (raizSub->esq != NULL)
        raizSub = raizSub->esq;

    return raizSub;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh *avl::removeMenor(noh *raizSub)
{
    if (raizSub->esq == NULL)
    {
        return raizSub->dir;
    }
    else
    {
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave chave)
{
    raiz = removeAux(raiz, chave);
}
//Remoção
noh *avl::removeAux(noh *umNoh, tipoChave chave)
{
    if (umNoh == NULL)
        throw runtime_error("Erro na busca: elemento não encontrado!");

    noh *novaRaizSubArvore = umNoh;

    if (chave < umNoh->elemento.ano)
    {
        umNoh->esq = removeAux(umNoh->esq, chave);
    }
    else if (chave > umNoh->elemento.ano)
    {
        umNoh->dir = removeAux(umNoh->dir, chave);
    }
    else
    {
        if (umNoh->esq == NULL)
        {
            novaRaizSubArvore = umNoh->dir;
        }
        else if (umNoh->dir == NULL)
        {
            novaRaizSubArvore = umNoh->esq;
        }
        else
        {
            novaRaizSubArvore = encontraMenor(umNoh->dir);
            novaRaizSubArvore->dir = removeMenor(umNoh->dir);
            novaRaizSubArvore->esq = umNoh->esq;
        }
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaizSubArvore);
}
unsigned maior;
unsigned ano;
unsigned avl::levantamento()
{
    if (raiz == NULL)
        throw runtime_error("Erro na busca: elemento não encontrado!");
    else
    {
        maior = raiz->elemento.qtdadeFilmesApresentados;
        ano = raiz->elemento.ano;
        return percorreEmOrdemAux(raiz);
    }
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
unsigned avl::percorreEmOrdemAux(noh *atual)
{
    if (atual != NULL)
    {
        percorreEmOrdemAux(atual->esq);
        if (atual->elemento.qtdadeFilmesApresentados >= maior and atual->elemento.ano < ano)
        {
            maior = atual->elemento.qtdadeFilmesApresentados;
            ano = atual->elemento.ano;
        }
        else if (atual->elemento.qtdadeFilmesApresentados > maior)
        {
            maior = atual->elemento.qtdadeFilmesApresentados;
            ano = atual->elemento.ano;
        }
        percorreEmOrdemAux(atual->dir);
    }
    return ano;
}
ostream &
operator<<(ostream &output, avl &arvore)
{
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string &prefixo, const noh *meuNoh)
{
    if (meuNoh != nullptr)
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq(prefixo + "    ", meuNoh->esq, meuNoh->dir == nullptr);
        imprimirDir(prefixo + "    ", meuNoh->dir);
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string &prefixo, const noh *meuNoh, bool temIrmao)
{
    if (meuNoh != nullptr)
    {
        std::cout << prefixo;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─";
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.ano << "," << meuNoh->elemento.cidadeRealizacao << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq(prefixo + "│   ", meuNoh->esq, meuNoh->dir == nullptr);
        imprimirDir(prefixo + "│   ", meuNoh->dir);
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if (this->raiz != nullptr)
    {
        std::cout << "(" << this->raiz->elemento.ano << "," << this->raiz->elemento.cidadeRealizacao << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq(" ", this->raiz->esq, this->raiz->dir == nullptr);
        imprimirDir(" ", this->raiz->dir);
    }
    else
        std::cout << "*arvore vazia*" << std::endl;
}

int main()
{
    avl arvore;
    tipoChave chave;
    dado umDado;
    unsigned ano;

    char operacao;

    do
    {
        try
        {
            cin >> operacao;
            switch (operacao)
            {
            case 'i': // Inserir recursivamente
                // objeto recebe nome, cidade e quantidade de filmes apresentados
                cin >> umDado;
                arvore.insere(umDado);
                break;
            case 'r': // Remover recursivamente
                cin >> chave;
                arvore.remove(chave);
                break;
            case 'b':                         // Buscar
                cin >> chave;                 // ler a chave
                umDado = arvore.busca(chave); // escrever os dados do festival
                cout << "Elemento buscado: " << umDado << endl;
                break;
            case 'l': // Levantamento pelo ano com maior número de filmes apresentados
                ano = arvore.levantamento();
                cout << "Edição com maior quantidade de filmes apresentados: " << ano << endl;
                break;
            case 'e': // Escrever tudo (em ordem)
                cout << arvore;
                break;
            case 'f': // Finalizar execução
                break;
            default:
                cout << "Comando invalido!\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
