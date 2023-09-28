//João Vitor M Vieira - 2° Informática

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

class Palavra{
    public:
        int LetraIgualVertical(string vertical, int i){ //Seria melhor se ficasse no construtor, mas estava dando muitos erros criar um construtor de Palavra
            char letra = vertical[i];
            for(int j = 0; j < p.length(); j++){
                if(p[j] == letra){
                    posicao = j;
                    return posicao;
                }
            }
        }
        void IniciarAcertou(string vertical, int j){ //Também ficaria no construtor
            acertou = new bool[p.length()];
            for(int i = 0; i < p.length(); i++){
                if(i == LetraIgualVertical(vertical, j)){ //Coloca a letra do meio como true, para que ela apareça no começo do jogo
                    acertou[i] = true;
                }
                else{ //Coloca todo o resto como false
                    acertou[i] = false;
                }
            }
        }
        bool Descobriu(int i){ //Apenas para facilitar a escrita, não tinha necessidade
            return acertou[i];
        }
        bool VerificaAcerto(char l){ //Recebe o chute do jogador e verifica se essa letra aparece na palavra
            bool aux = false;
            for(int i = 0; i < p.length(); i++){
                if(p[i] == l){
                    acertou[i] = true;
                    aux = true;
                }
            }
            return aux;
        }

        string getp(){
            return p;
        }
        void setp(string p){
            this->p = p;
        }

        int getposicao(){
            return posicao;
        }

        void setposicao(int posicao){
            this->posicao = posicao;
        }

        bool *getacertou(){
            return acertou;
        }

        void setacertou(bool *acertou){
                this->acertou = acertou;
        }

    protected:
        string p;
        int posicao; //guarda o índice da palavra horizontal em que a letra é igual a letra da palavra na vertical
        bool *acertou; //Será um vetor de booleano; se o jogador já acertou certa letra da palavra, a respectiva posição nesse vetor = true
};

class Jogo:Palavra{ //Derivado de palavra já que usa métodos dela
    public:
        Jogo(Palavra palavras[]){ //Construtor que descobre qual será o número de colunas da matriz de char (tam), além de alocar dinamicamente essa matriz
            int maior = 0;
            for(int i = 0; i < 10; i++){
                if(palavras[i].getp().length() > maior){
                    maior = palavras[i].getp().length();
                }
            }
            tam = maior * 2;
            tabuleiro = new char*[10];
            for(int i = 0; i < 10; i++){
                tabuleiro[i] = new char[tam];
            }
        }
        char **tabuleiro; //Tem que ser dinâmico porque só descubro a qtd de colunas depois; Deixei public mesmo, para a sintaxe ficar melhor (Já usei encapsulamento na outar classe)
        void PreencherTabuleiroVertical(string vertical, Palavra palavras[]){
            char letra;
            for(int i = 0; i < 10; i++){ //Percorre as 10 letras da palavra na vertical
                letra = vertical[i];
                for(int j = 0; j < 10; j++){ //Percorre o vetor de 10 palavras
                    for(int m = 0; m < palavras[j].getp().length(); m++){ //Percorre cada char
                        if(palavras[j].getp()[m] == letra){
                            tabuleiro[i][tam/2] = letra;
                        }
                    }
                }
            }
        }
        void PreencherTabuleiroVazio(){
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < tam; j++){
                    tabuleiro[i][j] = ' ';
                }
            }
        }
        void PTH(string vertical, Palavra plvr[]){ //Preenche as palavras horizontais do tabuleiro
            int meio = tam / 2;
            for (int i = 0; i < 10; i++) {
                plvr[i].LetraIgualVertical(vertical, i);
                int pos = plvr[i].getposicao() + 1;
                for (int j = meio + 1; j < meio + plvr[i].getp().length() && pos < plvr[i].getp().length(); j++) { // Preenche do meio para a direita
                    tabuleiro[i][j] = plvr[i].getp()[pos];
                    pos++;
                }
                pos = plvr[i].getposicao() - 1;
                for (int j = meio - 1; j >= 0 && pos >= 0; j--) { // Preenche do meio para a esquerda
                    tabuleiro[i][j] = plvr[i].getp()[pos];
                    pos--;
                }
            }
        }
        void Resposta(){ //Mostra todas as palavras
            for(int i = 0; i < 10; i ++){
                for(int j = 0; j < tam; j++){
                    cout<<tabuleiro[i][j];
                }
                cout<<endl;
            }
        }
        void EscreverJogo(Palavra plvr[]){ //Mostra a palavra vertical e as letras que o jogador acertou
            for(int i = 0; i < 10; i++){
                int aux = 0;
                do{
                    for(int j = 0; j < tam; j++){
                    cout<<" ";
                        if(tabuleiro[i][j] != ' '){
                            if(plvr[i].Descobriu(aux) == true){ //Se nessa posição ele já descobriu
                                cout<<tabuleiro[i][j];
                            }else{
                                cout<<"_";
                            }
                            aux++;
                        }
                        else{
                            cout<<" ";
                        }
                        cout<<" ";
                    }
                    cout<<endl;
                }while(aux < plvr[i].getp().length());
            }
            cout<<"\n";
        }
        bool Terminou(Palavra plvr[]){ //Verifica se o jogador já acertou ou não todas as letras
            bool aux = false;
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < plvr[i].getp().length(); j++){ //Percorre cada letra de cada palavra e verifica se ele já acertou ou não
                    if(plvr[i].getacertou()[j] == true)
                        aux = true;
                    else
                        return false;
                }
            }
            return aux; //Para a função retornar true, todos os valores precisam ser true.
        }
    protected:
        int tam;

};

int ContarPalavras(){
    ifstream arq("Palavra.txt");
    string aux;
    int qtd = 0;
    if(arq.is_open()){
        while(getline(arq, aux)){
            qtd++;
        }
    }
    arq.close();
    return qtd;
};

int Sortear(){
    return rand() % (ContarPalavras() + 1);
};


string Percorrer(char letra){ //Acha 10 palavras em que uma letra seja igual a uma letra da palavra vertical
    ifstream arq("Palavra.txt");
    int linhaAtual, sorteado;
    string aux = "";
    if(arq.is_open()){
        bool achou = false;
        do{
            arq.seekg(0);
            sorteado = Sortear();
            linhaAtual = 0;
            while(getline(arq, aux)){
                if(linhaAtual == sorteado){
                    break;
                }
                linhaAtual++;
            }
            for(int i = 0; i < aux.length(); i++){
                if(aux[i] == letra){
                    achou = true;
                    break;
                }
            }
        }while(achou == false);
        arq.close();
        return aux;
    }
};

string SortearPalavraVertical(){ //Sorteia uma palavra de 10 letras
    ifstream arq("Palavra.txt");
    int linhaAtual, sorteado;
    string aux;
    if(arq.is_open()){
        do{
            arq.seekg(0); //Volta pro início
            sorteado = Sortear();
            linhaAtual = 0;
            while(getline(arq, aux)){
                if(linhaAtual == sorteado){
                    break;
                }
                linhaAtual++;
            }
        }while(aux.length() != 10);
        arq.close();
    }
    return aux;
};

int main()
{
    srand(time(NULL));
    int i = 0;
    Palavra PV; //A palavra vertical
    PV.setp(SortearPalavraVertical());
    Palavra P[10]; //As 10 palavras horizontais
    bool achei = false;
    for(i = 0; i < 10; i++){
        P[i].setp(Percorrer(PV.getp()[i]));
        P[i].IniciarAcertou(PV.getp(), i);
    }
    Jogo J(P);
    J.PreencherTabuleiroVazio();
    J.PreencherTabuleiroVertical(PV.getp(), P);
    J.PTH(PV.getp(), P);

    //AGORA SIM O JOGO COMEÇA
    int op;
    do{
        cout<<"Selecione sua dificuldade:\n";
        cout<<"1 - Fácil\n";
        cout<<"2 - Médio\n";
        cout<<"3 - Difícil\n";
        cin>>op;
        switch(op){
            int chutes; //Quantas tentativas o usuário já usou
            char chute;
            bool terminou;
            case 1:
                chutes = 0;
                terminou = false;
                cout<<"\nVocê tem "<<11-chutes<<" tentativas. Chute uma letra, chutes corretos não diminuirão as tentativas restantes.\n";
                do{
                    J.EscreverJogo(P);
                    cout<<"Erros: "<<chutes<<"\n";
                    cout<<"Tentativas restantes: "<<11-chutes<<"\n";
                    bool acertou = false;
                    cout<<"Chute uma letra: ";
                    cin>>chute;
                    for(i = 0; i < 10; i++){
                        if(P[i].VerificaAcerto(chute) == true)
                            acertou = true;
                    }
                    if(!acertou)
                        chutes++;
                    terminou = J.Terminou(P);
                    if(!terminou)
                        system("clear");
                }while(chutes < 11 && !terminou);
                if(terminou){
                    cout<<"PARABÉNS!! Você descobriu todas as 10 palavras! Tu é brabo\n";
                    J.EscreverJogo(P);
                }else{
                    cout<<"PERDEU!! NO nível fácil ainda :(";
                    J.EscreverJogo(P);
                    cout<<endl;
                    J.Resposta();
                }
            break;
            case 2:
                chutes = 0;
                terminou = false;
                cout<<"\nVocê tem "<<8-chutes<<" tentativas. Chute uma letra, chutes corretos não diminuirão as tentativas restantes.\n";
                do{
                    J.EscreverJogo(P);
                    cout<<"Erros: "<<chutes<<"\n";
                    cout<<"Tentativas restantes: "<<8-chutes<<"\n";
                    bool acertou = false;
                    cout<<"Chute uma letra: ";
                    cin>>chute;
                    for(i = 0; i < 10; i++){
                        if(P[i].VerificaAcerto(chute) == true)
                            acertou = true;
                    }
                    if(!acertou)
                        chutes++;
                    terminou = J.Terminou(P);
                    if(!terminou)
                        system("clear");
                }while(chutes < 8 && !terminou);
                if(terminou){
                    cout<<"PARABÉNS!! Você descobriu todas as 10 palavras! Tu é brabo\n";
                    J.EscreverJogo(P);
                }else{
                    cout<<"PERDEU!!";
                    J.EscreverJogo(P);
                    cout<<endl;
                    J.Resposta();
                }
            break;
            case 3:
                chutes = 0;
                chute;
                terminou = false;
                cout<<"\nVocê tem "<<5-chutes<<" tentativas. Chute uma letra, chutes corretos não diminuirão as tentativas restantes.\n";
                do{
                    J.EscreverJogo(P);
                    cout<<"Erros: "<<chutes<<"\n";
                    cout<<"Tentativas restantes: "<<5-chutes<<"\n";
                    bool acertou = false;
                    cout<<"Chute uma letra: ";
                    cin>>chute;
                    for(i = 0; i < 10; i++){
                        if(P[i].VerificaAcerto(chute) == true)
                            acertou = true;
                    }
                    if(!acertou)
                        chutes++;
                    terminou = J.Terminou(P);
                    if(!terminou)
                        system("clear");
                }while(chutes < 5 && !terminou);
                if(terminou){
                    cout<<"PARABÉNS!! Você descobriu todas as 10 palavras! Tu é brabo\n";
                    J.EscreverJogo(P);
                }else{
                    J.EscreverJogo(P);
                    cout<<endl;
                    J.Resposta();
                    cout<<"PERDEU!! Mas no hard é complicado mesmo.\n";
                }
            break;
            default:
                cout<<"Opção Inválida!!\n";
                cin.ignore().get();
            break;
        }
    }while(op < 1 || op > 3);
    return 0;
}
