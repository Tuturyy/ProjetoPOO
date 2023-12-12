#include "Casino.h"
#include "Uteis.h"
#include "Relogio.h"
#include <algorithm>

using namespace std;




Casino::Casino(string nome, int numMaquinas)
{
	nomeC = nome;
	LM = *GerarMaquinas(numMaquinas);
	DinheiroPerdido = 0;
	DinheiroRecebido = 0;
	TempoAtualCasino = 0;
}

Casino::~Casino()
{
	/*for (auto& maqPtr : LM) {
		delete maqPtr;
	}
	LM.clear();

	for (auto& pessoaPtr : LP) {
		delete pessoaPtr;
	}
	LP.clear();*/
}

void Casino::LerFicheiro()
{
	string fich = "pessoas.txt";
	ifstream file(fich);
	if (!file.is_open())
	{
		cout << "Erro ao abrir ficheiro" << endl;
		return;
	}
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		int ID;
		string Nome;
		string Localidade;
		int Idade;
		string token;
		int tokenPosition = 0;
		while (getline(iss, token, '\t'))
		{
			if (tokenPosition == 0)
			{
				ID = stoi(token);
			}
			else if (tokenPosition == 1)
			{
				Nome = token;
			}
			else if (tokenPosition == 2)
			{
				Localidade = token;
			}
			else if (tokenPosition == 3)
			{
				Idade = stoi(token);
			}
			tokenPosition++;
		}
		Pessoa* pessoa = new Pessoa(ID, Nome, Localidade, Idade);
		LPT.push_back(pessoa);

	}
	file.close();
}

void Casino::MostrarListaPessoas(list<Pessoa*> lista) {
	for (list<Pessoa*>::iterator it = lista.begin(); it != lista.end(); it++) {
		(*it)->MostrarPessoa();
	}
}
 
void Casino::MostrarPessoasFora(){
	for (list<Pessoa*>::iterator it = LPT.begin(); it != LPT.end(); it++) {
		(*it)->MostrarPessoa();
	}
}

void Casino::MostrarPessoasCasino()
{
	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); it++) {
		(*it)->MostrarPessoa();
	}
}

Pessoa* Casino::GetPessoa() {

	int index = Util::RandNumInt(0, LPT.size());

	auto it = LPT.begin();
	std::advance(it, index);

	return *it;
}


void Casino::AddPessoa(Pessoa *pessoa) {
	pessoa->PessoaParaCasino(this);
	LP.push_back(pessoa);
	LPJ.push_back(pessoa);
	LPT.remove(pessoa);
	pessoa->adicionaSaldo(Util::RandNumInt(100, 500));
}

void Casino::RmvPessoa(Pessoa* pessoa) {
	pessoa->PessoaParaFora();
	LP.remove(pessoa);
}

bool Casino::AddMaquina(Maquina* m)
{
	LM.push_back(m);
	return true;
}

Maquina* Casino::PesquisarMaquinaID(int id_maq)
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->getID() == id_maq)
		{
			return *it;
		}
	}
	return nullptr;
}

void Casino::MostrarMaquinas()
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		(*it)->MostrarMaquina();
	}
}

void Casino::MostrarListaMaquinas(list<Maquina*> lista)
{
	for (list<Maquina*>::iterator it = lista.begin(); it != lista.end(); it++) {
		(*it)->MostrarMaquina();
	}
}

void Casino::Desligar(int id_maq)
{
	Maquina* maq = PesquisarMaquinaID(id_maq);
	if (maq)
		maq->DesligarMaquina();
	else
		cout << "Erro ao desligar maquina. Nao existe uma maquina com ID=" << id_maq << endl << "\n";
}

ESTADO_MAQUINA Casino::Get_Estado(int id_maq)
{
	Maquina* M = PesquisarMaquinaID(id_maq);
	if (M)
	{
		return M->getEstado();
	}
	else
		cout << "Erro ao procurar maquina. Nao existe uma maquina com ID=" << id_maq << endl << "\n";
}

void Casino::AtribuirMaquinaPessoa(Pessoa* pessoa)
{
	list<Maquina*> MaquinasAleatorias = LM;
	vector<Maquina*> MaquinasVector(MaquinasAleatorias.begin(), MaquinasAleatorias.end());

	std::random_shuffle(MaquinasVector.begin(), MaquinasVector.end());
	for (vector<Maquina*>::iterator it = MaquinasVector.begin(); it != MaquinasVector.end(); it++)
	{
		if ((*it)->getEstado() == ESTADO_MAQUINA::OFF)
		{
			(*it)->AddJogadorMaquina(pessoa);
			(*it)->TempoJogadaTerminada = TempoAtualCasino + (*it)->getTempoJogadaMaquina();
			//cout << "Adicionada Pessoa: " << pessoa->getNome() << " A Maquina: " << (*it)->getID() << "\n";
			return;
		}
	}
	cout << "Maquinas indisponiveis.\n";
	return;
}

int Casino::Memoria_Total()
{
	int memoriaTotal = 0;
	
	memoriaTotal += sizeof(*this);

	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); it++)
	{
		memoriaTotal += sizeof(*it);
	}
	memoriaTotal += sizeof(LP);
	for (list<Pessoa*>::iterator it = LPT.begin(); it != LPT.end(); it++)
	{
		memoriaTotal += sizeof(*it);
	}
	memoriaTotal += sizeof(LPT);
	for (list<Pessoa*>::iterator it = LPJ.begin(); it != LPJ.end(); it++)
	{
		memoriaTotal += sizeof(*it);
	}
	memoriaTotal += sizeof(LPJ);
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		memoriaTotal += sizeof(*it);
	}
	memoriaTotal += sizeof(LM);

	return memoriaTotal;
}

list<Maquina*>* Casino::GerarMaquinas(int numMaquinas)
{
	list<Maquina*>* lista = new list<Maquina*>();
	for (int i = 0; i < numMaquinas; i++)
	{
		TIPO_MAQUINA randomTipo = static_cast<TIPO_MAQUINA>(1 + (rand() % 4));//tipo de jogo na maquina aleatorio
		int randomx, randomy;
			bool posicaoOcupada;
			do
			{
				posicaoOcupada = false;
				randomx = 0 + (rand() % (X_MAX_CASINO+1));
				randomy = 0 + (rand() % (Y_MAX_CASINO + 1));
				for (list<Maquina*>::iterator it = lista->begin(); it != lista->end(); ++it)
				{
					if (((*it)->getX() == randomx) && ((*it)->getY() == randomy))//se a posicao ja estiver ocupada
					{
						posicaoOcupada = true;
						break;
					}
				}
			} while (posicaoOcupada);

			Maquina* maq = new Maquina(i + 1, randomTipo, randomx, randomy);
		lista->push_back(maq);
	}
	return lista;
}

list<Maquina*> Casino::Listar_Tipo(string Tipo, ostream& f)
{
	TIPO_MAQUINA tipoDesejado;
	list<Maquina*> maquinasdoTipo;

	if (Tipo == "Poker")
	{
		tipoDesejado = TIPO_MAQUINA::Poker;
	}
	else if (Tipo == "BlackJack")
	{
		tipoDesejado = TIPO_MAQUINA::BlackJack;
	}
	else if (Tipo == "ClassicSlots")
	{
		tipoDesejado = TIPO_MAQUINA::ClassicSlots;
	}
	else if (Tipo == "Roleta")
	{
		tipoDesejado = TIPO_MAQUINA::Roleta;
	}
	else 
	{
		f << "Tipo de maquina invalido!\n";
		return list<Maquina*>();
	}

	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->getTipo()==tipoDesejado)
		{
			maquinasdoTipo.push_back((*it));
			(*it)->MostrarMaquina();
		}
	}
	return maquinasdoTipo;
}

list<Maquina*> Casino::Ranking_Das_Mais_Trabalhadores()
{
	list<Maquina*> Ordenada = LM;
	Ordenada.sort([](const Maquina* a, const Maquina* b) {
		return a->Utilizacoes > b->Utilizacoes;
		});
	return Ordenada;
}


list<Pessoa*> Casino::Jogadores_Mais_Ganhos()
{
	list<Pessoa*> JogadoresMaisLucro = LPJ;
	JogadoresMaisLucro.sort([](const Pessoa* a, const Pessoa* b) {
		return a->Lucro > b->Lucro;
		});
	return JogadoresMaisLucro;
}

void Casino::Relatorio(string fich_xml)
{
	std::ofstream arquivo_xml(fich_xml); // Abre o arquivo XML para escrita
	if (!arquivo_xml.is_open()) 
	{
		cout << "Erro ao abrir o arquivo XML.\n";
		return;
	}

	arquivo_xml << "<DADOS>\n";
	arquivo_xml << "\t<DEFINICOES>\n";
	arquivo_xml << "\t\t<NOME>" << nomeC << "</NOME>\n";
	arquivo_xml << "\t\t<HORA_INICIO>" << "15" << "</HORA_INICIO>\n";
	arquivo_xml << "\t\t<HORA_FIM>" << "03" << "</HORA_FIM>\n";
	arquivo_xml << "\t</DEFINICOES>\n";
	arquivo_xml << "\t<LISTA_MAQ>\n";
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		arquivo_xml << "\t\t<MAQUINA>\n";
		arquivo_xml << "\t\t\t<ID>" << (*it)->getID() << "</ID>\n";
		arquivo_xml << "\t\t\t<TIPO>" << (*it)->TipoMaquinaString() << "</TIPO>\n";
		arquivo_xml << "\t\t\t<PROB_G>" << (*it)->porcentWin << "</PROB_G>\n";
		arquivo_xml << "\t\t\t<X>" << (*it)->getX() << "</X>\n";
		arquivo_xml << "\t\t\t<Y>" << (*it)->getY() << "</Y>\n";

		arquivo_xml << "\t\t</MAQUINA>\n";
	}
	arquivo_xml << "\t</LISTA_MAQ>\n";


	arquivo_xml << "</DADOS>";
	arquivo_xml.close();
}

void Casino::Listar(float X, ostream& f)
{
	bool maquinaEncontrada = false;
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		if ((*it)->porcentWin >= X)
		{
			(*it)->MostrarMaquina();
			f << "Porcentagem de ganhar: " << (*it)->porcentWin << "\n";
			maquinaEncontrada = true;
		}
	}

	if (!maquinaEncontrada)
		f << "Nenhuma maquina com probilidade maior ou igual a " << X << "\n";
}

void Casino::PessoasVaoParaMaquinas()
{
	int numPessoasEntrar = Util::RandNumInt(0, 5);
	if (numPessoasEntrar + LP.size() <= PESSOAS_MAX_CASINO)
	{
		for (int i = 0; i < numPessoasEntrar; i++)
		{
			Pessoa* jogador = GetPessoa();
			AddPessoa(jogador);
		}
	}
	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); ++it)
	{
		if ((*it)->getMaquina() == nullptr)
		{
			AtribuirMaquinaPessoa((*it));
		}
	}
}


void Casino::PessoasJogam()
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->getEstado() == ESTADO_MAQUINA::ON)
		{
			if (TempoAtualCasino >= (*it)->TempoJogadaTerminada) //verificar se o jogador ja teve o tempo para jogar
			{
				(*it)->JogadorJoga((*it)->CalcularBet(), this);
				(*it)->RemoverJogadorMaquina();
			}
		}
	}
}

void Casino::VerificarSaidaPessoas()
{
	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); ++it)
	{
		if (((*it)->getSaldo() <= 0) || (TempoAtualCasino >= (*it)->getHoraSaidaCasino()))
		{
			RmvPessoa((*it));
		}
	}
}

void Casino::Run(bool Debug) {
	int x = 0;
	Relogio relogio;
	relogio.StartRelogio(10, 0); // Inicia o relógio com velocidade 1 e tempo 0

	// Adiciona 12 horas em segundos (12 horas * 60 minutos * 60 segundos)
	const int duracao_casino_segundos = 43200;
	time_t tempoTermino = relogio.VerTimeRelogio() + duracao_casino_segundos;

	bool loopAtivo = true;

	while (loopAtivo) {
		time_t tempoAtual = relogio.VerTimeRelogio();
		int tempo = tempoAtual;
		TempoAtualCasino = tempo;

		relogio.MostrarTempoSegundos(tempoAtual, tempoTermino, duracao_casino_segundos);

		// Verificar se já se passaram as 12 horas
		if (tempoAtual >= tempoTermino) {
			loopAtivo = false;
		}
		else {
			// Adicione sua lógica para o período do loop aqui
			PessoasVaoParaMaquinas();
			PessoasJogam();
			cout << "Numero de Pessoas: " << LP.size() << "\n";
			relogio.Wait(1);
		}
	}
}
