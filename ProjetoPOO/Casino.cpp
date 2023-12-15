#include "Casino.h"
#include "Uteis.h"
#include "Relogio.h"
#include "menu.h"
#include <algorithm>
#include <cmath>

using namespace std;



Casino::Casino(string nome, int numMaquinas, string horarioAbertura, string horarioFecho)
{
	nomeC = nome;
	GerarMaquinas(numMaquinas);
	DinheiroPerdido = 0;
	DinheiroRecebido = 0;
	TempoAtualCasino = 0;
	HoraEncerrar = 0;
}

Casino::~Casino()
{
	for (auto it = LPT.begin(); it != LPT.end(); ++it) 
	{
		delete(*it);
	}

	for (auto it = LPJ.begin(); it != LPJ.end(); ++it)
	{
		delete(*it);
	}

	for (auto it = LM.begin(); it != LM.end(); ++it)
	{
		delete(*it);
	}
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

Pessoa* Casino::PesquisarPessoaID(int id_pessoa)
{
	for (list<Pessoa*>::iterator it = LPJ.begin(); it != LPJ.end(); ++it)
	{
		if ((*it)->getID() == id_pessoa)
		{
			return *it;
		}
	}
	return nullptr;
}


void Casino::AddPessoa(Pessoa *pessoa) {
	pessoa->PessoaParaCasino(this);
	LP.push_back(pessoa);
	LPJ.push_back(pessoa);
	LPT.remove(pessoa);
	pessoa->adicionaSaldo(Util::RandNumInt(100, 500));
}

void Casino::RmvPessoa(Pessoa* pessoa) {
	pessoa->PessoaParaForaCasino();
	LP.remove(pessoa);
}

list<Pessoa*> Casino::getListaJogadores()
{
	return LPJ;
}

list<Pessoa*> Casino::getListaPessoasCasino()
{
	return LP;
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
			cout << "Adicionada Pessoa: " << pessoa->getNome() << " A Maquina: " << (*it)->getID() << "\n";
			return;
		}
	}
	cout << "Maquinas indisponiveis.\n";
	return;
}

list<Maquina*> Casino::Ranking_Das_Mais_Avariadas()
{
	list<Maquina*> Ordenada = LM;
	Ordenada.sort([](const Maquina* a, const Maquina* b) {
		return a->Avarias > b->Avarias;
		});
	return Ordenada;
}


//int Casino::Memoria_Total()
//{
//	int memoriaTotal = 0;
//
//	// Tamanho dos membros da classe Casino
//	memoriaTotal += sizeof(*this); // Tamanho da instância de Casino
//
//	// Tamanho das listas (somente dos contêineres)
//	memoriaTotal += LP.size() * sizeof(Pessoa*); // Tamanho da lista de ponteiros
//	memoriaTotal += LPT.size() * sizeof(Pessoa*);
//	memoriaTotal += LPJ.size() * sizeof(Pessoa*);
//	memoriaTotal += LM.size() * sizeof(Maquina*);
//
//	// Itera pelas listas e adiciona o tamanho dos objetos apontados (estimativa)
//	for (const auto& pessoaPtr : LP) {
//		if (pessoaPtr) {
//			memoriaTotal += sizeof(*pessoaPtr); // Tamanho estimado de cada Pessoa
//			// Adicione mais ao totalMemoryUsage se a Pessoa tiver dados dinâmicos
//		}
//	}
//	for (const auto& pessoaPtr : LPT) {
//		if (pessoaPtr) {
//			memoriaTotal += sizeof(*pessoaPtr); // Tamanho estimado de cada Pessoa
//			// Adicione mais ao totalMemoryUsage se a Pessoa tiver dados dinâmicos
//		}
//	}
//	for (const auto& pessoaPtr : LPJ) {
//		if (pessoaPtr) {
//			memoriaTotal += sizeof(*pessoaPtr); // Tamanho estimado de cada Pessoa
//			// Adicione mais ao totalMemoryUsage se a Pessoa tiver dados dinâmicos
//		}
//	}
//	for (const auto& maquinaPtr : LM) {
//		if (maquinaPtr) {
//			memoriaTotal += sizeof(*maquinaPtr); // Tamanho estimado de cada Maquina
//			// Adicione mais ao totalMemoryUsage se a Maquina tiver dados dinâmicos
//		}
//	}
//
//	return memoriaTotal;
//}


int Casino::Memoria_Total()
{
	int MemoriaTotal = sizeof(*this);

	for (auto it = LPT.begin(); it != LPT.end(); it++)
	{
		MemoriaTotal += (*it)->MemoriadaClass();
	}
	MemoriaTotal += sizeof(LPT);

	for (auto it = LPJ.begin(); it != LPJ.end(); it++)
	{
		MemoriaTotal += (*it)->MemoriadaClass();
	}
	MemoriaTotal += sizeof(LPJ);

	for (auto it = LM.begin(); it != LM.end(); it++)
	{
		MemoriaTotal += (*it)->MemoriaClass();
	}
	MemoriaTotal += sizeof(LM);


	return MemoriaTotal;
}


void Casino::ListarEstadoCasino(ostream& f)
{
	f << "Nome do Casino: " << nomeC << "\n";

	int horaAbertura = 15;
	int horaFecho = 3;

	f << "Hora de abertura: " << horaAbertura << "h\n";
	f << "Hora de fecho: " << horaFecho << "h\n";

	f << "Lista de Maquinas do Casino:\n";
	MostrarMaquinas();
	
}

void Casino::GerarMaquinas(int numMaquinas)
{
	if (numMaquinas > ((X_MAX_CASINO + 1) * (Y_MAX_CASINO + 1)))
	{
		cout << "ERRO. NUMERO DE MAQUINAS MUITO ELEVADO PARA A AREA DO CASINO\n\n";
		return;
	}
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
				for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
				{
					if (((*it)->getX() == randomx) && ((*it)->getY() == randomy))//se a posicao ja estiver ocupada
					{
						posicaoOcupada = true;
						break;
					}
				}
			} while (posicaoOcupada);

			Maquina* maq = new Maquina(i + 1, randomTipo, randomx, randomy);
		LM.push_back(maq);
	}

}

list<Maquina*> Casino::Listar_TipoMaquina(string Tipo, ostream& f)
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

list<Maquina*> Casino::Maquinas_Mais_Avarias()
{
	list<Maquina*> Ordenada = LM;
	Ordenada.sort([](Maquina* a, Maquina* b) {
		return a->Avarias > b->Avarias;
		});

	if (Ordenada.size() > 5) {
		auto it = Ordenada.begin();
		advance(it, 5);
		Ordenada.erase(it, Ordenada.end());
	}

	return Ordenada;
}

list<Maquina*> Casino::Ranking_Das_Mais_Trabalhadores()
{
	list<Maquina*> Ordenada = LM;
	Ordenada.sort([](const Maquina* a, const Maquina* b) {
		return a->Utilizacoes > b->Utilizacoes;
		});

	if (Ordenada.size() > 10) {
		auto it = Ordenada.begin();
		advance(it, 10);
		Ordenada.erase(it, Ordenada.end());
	}

	return Ordenada;
}

void Casino::SubirProbabilidadeVizinhas(Maquina* M_ganhou, float R, list<Maquina*>& lmvizinhas)
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		float distancia = CalcularDistanciaEntreMaquinas(M_ganhou, (*it));
		if (distancia > 0 && distancia <= R)
		{

			lmvizinhas.push_back(*it);
		}
	}
}

float Casino::CalcularDistanciaEntreMaquinas(Maquina* M1, Maquina* M2)
{
	int x1 = M1->getX();
	int y1 = M1->getY();
	int x2 = M2->getX();
	int y2 = M2->getY();

	float distancia = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return distancia;
}


list<Pessoa*> Casino::Jogadores_Mais_Ganhos()
{
	cout << "\nTOP 10 Jogadores com mais Lucro:\n\n";
	list<Pessoa*> JogadoresMaisLucro = LPJ;
	JogadoresMaisLucro.sort([](Pessoa* a, Pessoa* b) {
		return a->getLucro() > b->getLucro();
	});

	if (JogadoresMaisLucro.size() > 10) {
		auto it = JogadoresMaisLucro.begin();
		advance(it, 10);
		JogadoresMaisLucro.erase(it, JogadoresMaisLucro.end());
	}

	return JogadoresMaisLucro;
}

list<Pessoa*> Casino::Jogadores_Mais_Frequentes()
{
	list<Pessoa*> JogadoresMaisFrequentes = LPJ;
	JogadoresMaisFrequentes.sort([](Pessoa* a, Pessoa* b) {
		return a->getTempoAJogar() > b->getTempoAJogar();
		});

	/*if (JogadoresMaisFrequentes.size() > 10) {
		auto it = JogadoresMaisFrequentes.begin();
		advance(it, 10);
		JogadoresMaisFrequentes.erase(it, JogadoresMaisFrequentes.end());
	}*/

	return JogadoresMaisFrequentes;
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
		arquivo_xml << "\t\t\t<PROB_G>" << (*it)->getPorcentWin() << "</PROB_G>\n";
		arquivo_xml << "\t\t\t<X>" << (*it)->getX() << "</X>\n";
		arquivo_xml << "\t\t\t<Y>" << (*it)->getY() << "</Y>\n";

		arquivo_xml << "\t\t</MAQUINA>\n";
	}
	arquivo_xml << "\t</LISTA_MAQ>\n";


	arquivo_xml << "</DADOS>";
	arquivo_xml.close();
}

void Casino::EstatisticasCasino()
{
	int numPessoasLucro = 0;
	int numPessoasPrejuizo = 0;
	int numPessoasMantem = 0;
	for (list<Pessoa*>::iterator it = LPJ.begin(); it != LPJ.end(); it++)
	{
		if ((*it)->getLucro() > 0)
		{
			numPessoasLucro++;
		}
		else if ((*it)->getLucro() < 0)
		{
			numPessoasPrejuizo++;
		}
		else {
			numPessoasMantem++;
		}
	}
	cout << "\n\n***********************************************************\n";
	cout << "Casino " << nomeC << "\n";
	cout << "***********************************************************\n\n";

	cout << "	O Casino teve um lucro de: " << (DinheiroRecebido - DinheiroPerdido) << "EUR\n\n";
	cout << "	Os jogadores apostaram um total de: " << DinheiroRecebido << "EUR\n";
	cout << "	O casino em apostas perdeu um total de: " << DinheiroPerdido << "EUR\n\n";
	cout << "***********************************************************\n\n";
	cout << "	Jogaram um total de " << LPJ.size() << " pessoas.\n\n";
	cout << "	Destas ficaram "<< numPessoasLucro << " no lucro :)\n";
	cout << "	E "<< numPessoasPrejuizo << " ficaram no prejuizo :(\n";
	if (numPessoasMantem != 0)
	{
		cout << "	" << numPessoasMantem << " ficaram na mesma :|\n";
	}
	cout << "\n***********************************************************\n\n";

	
}

void Casino::ListarMaquinasProbabilidadeMaiorQueX(float X, ostream& f)
{
	bool maquinaEncontrada = false;
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); it++)
	{
		if ((*it)->getPorcentWin() >= X)
		{
			(*it)->MostrarMaquina();
			f << "Porcentagem de ganhar: " << (*it)->getPorcentWin() << "\n";
			maquinaEncontrada = true;
		}
	}

	if (!maquinaEncontrada)
		f << "Nenhuma maquina com probilidade maior ou igual a " << X << "\n";
}

void Casino::PessoasVaoParaMaquinas()
{
	if ((TempoAtualCasino + 10 * 60) <= HoraEncerrar) //Pessoas nao entram nem jogam qnd faltar 10min para fechar o casino
	{
		int numPessoasEntrar = Util::RandNumInt(1, 1);
		if (numPessoasEntrar + LP.size() <= PESSOAS_MAX_CASINO)
		{
			for (int i = 0; i < numPessoasEntrar; i++)
			{
				Pessoa* jogador = GetPessoa();
				int DuracaoNoCasino = Util::RandNumInt(30 * 60, 3 * 60 * 60);//de 30min a 2horas
				jogador->setHoraEntradaCasino(TempoAtualCasino);
				jogador->SetHoraSaidaCasino(TempoAtualCasino + DuracaoNoCasino);
				AddPessoa(jogador);
			}
		}

		list<Pessoa*> PessoaAleatoria = LP;
		vector<Pessoa*> PessoasCasinoVetor(PessoaAleatoria.begin(), PessoaAleatoria.end());
		std::random_shuffle(PessoasCasinoVetor.begin(), PessoasCasinoVetor.end());
		for (vector<Pessoa*>::iterator it = PessoasCasinoVetor.begin(); it != PessoasCasinoVetor.end(); ++it)
		{

			if ((*it)->getMaquina() == nullptr)
			{
				AtribuirMaquinaPessoa((*it));
			}
		}
		
	}
	else
		cout << "JA NINGUEM ENTRA\n";
}


void Casino::PessoasJogam()
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->getEstado() == ESTADO_MAQUINA::ON)
		{

			if (TempoAtualCasino >= (*it)->TempoJogadaTerminada) //verificar se o jogador ja teve o tempo para jogar
			{
				int numJogadas = 1;

				int TempoDiferenca = TempoAtualCasino - (*it)->TempoJogadaTerminada;
				int MaxJogadas = (TempoDiferenca) / ((*it)->getTempoCadaJogada());
				if (MaxJogadas >1)
				{
					numJogadas = Util::RandNumInt(1, MaxJogadas);
				}
				cout << "VOU JOGAR " << numJogadas << " VEZES\n";
				for (int i=0; i<numJogadas;i++)
				{
					(*it)->JogadorJoga((*it)->CalcularBet(), this);
				}
				(*it)->RemoverJogadorMaquina();
			}
		}
	}
}

void Casino::VerificarSaidaPessoas()
{
	list<Pessoa*> PessoasaRemover;
	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); ++it)
	{
		if (((*it)->getSaldo() <= 0) || (TempoAtualCasino >= (*it)->getHoraSaidaCasino()))
		{
			PessoasaRemover.push_back((*it));
		}
	}


	for (list<Pessoa*>::iterator it = PessoasaRemover.begin(); it != PessoasaRemover.end(); it++)
	{
		RmvPessoa((*it));
	}
}

void Casino::Run(bool Debug) {
	int x = 0;
	Relogio relogio;
	relogio.StartRelogio(360, horarioAbertura.c_str()); // Inicia o relógio com velocidade 1 e tempo 0

	// Adiciona 12 horas em segundos (12 horas * 60 minutos * 60 segundos)
	const int duracao_casino_segundos = 43200;
	time_t tempoTermino = relogio.VerTimeRelogio() + duracao_casino_segundos;
	HoraEncerrar = tempoTermino;

	bool loopAtivo = true;
	bool pausado = false;

	while (loopAtivo) {
		time_t tempoAtual = relogio.VerTimeRelogio();
		TempoAtualCasino = tempoAtual;

		if (!pausado) {
			relogio.MostrarTempo(tempoAtual); // Mostra o tempo apenas se não estiver pausado
		}

		// Verificar se já se passaram as 12 horas
		if (tempoAtual >= tempoTermino) {
			loopAtivo = false;
		}
		else {
			// Verifica se a tecla "m" foi pressionada
			if (_kbhit()) {
				char tecla = _getch();
				if (tecla == 'M' || tecla == 'm'){
					relogio.PararRelogio();
					menuGeral(relogio, this);
				}
			}

			VerificarSaidaPessoas();
			PessoasVaoParaMaquinas();
			PessoasJogam();

			relogio.Wait(1);
			
		}
	}
}

bool Casino::LoadCasino(const string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Erro ao abrir o arquivo XML." << endl;
		return false;
	}

	stringstream buffer;
	buffer << file.rdbuf();
	string content = buffer.str();

	size_t pos = content.find("<Nome>");
	if (pos != string::npos) {
		size_t endPos = content.find("</Nome>", pos);
		nomeC = content.substr(pos + 6, endPos - pos - 6);
	}

	pos = content.find("<NumeroMaquinas>");
	if (pos != string::npos) {
		size_t endPos = content.find("</NumeroMaquinas>", pos);
		numeroMaquinas = stoi(content.substr(pos + 16, endPos - pos - 16));
	}

	pos = content.find("<Abertura>");
	if (pos != string::npos) {
		size_t endPos = content.find("</Abertura>", pos);
		horarioAbertura = content.substr(pos + 10, endPos - pos - 10);
	}

	pos = content.find("<Fecho>");
	if (pos != string::npos) {
		size_t endPos = content.find("</Fecho>", pos);
		horarioFecho = content.substr(pos + 8, endPos - pos - 8);
	}

	return true;
}

int Casino::getNumeroMaquinas() const {
	return numeroMaquinas;
}

string Casino::getHorarioAbertura() const {
	return horarioAbertura;
}

string Casino::getHorarioFecho() const {
	return horarioFecho;
}