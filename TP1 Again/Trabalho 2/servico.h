/**
 * @file servico.h
 * @brief Declaração das classes de serviço para contas, viagens, destinos, atividades e hospedagens.
 */

#ifndef SERVICO_H
#define SERVICO_H

#include "database.h"
#include "dominio.h"
#include "entidade.h"

/**
 * @class ServicoConta
 * @brief Serviço responsável por operações de conta.
 */
class ServicoConta {
private:
    Database& db; /**< Referência para o banco de dados. */

public:
    /** @brief Construtor padrão. */
    ServicoConta();
    /** @brief Construtor com referência ao banco de dados. */
    ServicoConta(Database& database);
    /** @brief Cria uma nova conta. */
    bool criarConta(const CODIGO& codigo, const SENHA& senha);
    /** @brief Autentica uma conta existente. */
    bool autenticarConta(const CODIGO& codigo, const SENHA& senha);
    /** @brief Deleta uma conta. */
    bool deletarConta(const CODIGO& codigo);
    /** @brief Obtém informações de uma conta. */
    CONTA getConta(const CODIGO& nome);
};

/**
 * @class ServicoViagem
 * @brief Serviço responsável por operações relacionadas a viagens.
 */
class ServicoViagem {
private:
    Database& db;

public:
    /** @brief Construtor com referência ao banco de dados. */
    ServicoViagem(Database& database);
    /** @brief Cria uma nova viagem. */
    bool criarViagem(const CODIGO& codigo, const NOME& nome, const AVALIACAO& avaliacao, const CODIGO& codigoConta);
    /** @brief Lista viagens associadas a uma conta. */
    bool listarViagens(const CODIGO& codigoConta);
    /** @brief Deleta uma viagem. */
    bool deletarViagem(const CODIGO& codigo);
    /** @brief Atualiza os dados de uma viagem. */
    bool atualizarViagem(const CODIGO& codigo, const NOME& novoNome, const AVALIACAO& novaAvaliacao);
};

/**
 * @class ServicoDestino
 * @brief Serviço responsável por operações relacionadas a destinos.
 */
class ServicoDestino {
private:
    Database& db;

public:
    /** @brief Construtor com referência ao banco de dados. */
    ServicoDestino(Database& database);
    /** @brief Cria um novo destino. */
    bool criarDestino(const CODIGO& codigo, const NOME& nome, const DATA& dataInicio, const DATA& dataFim, const AVALIACAO& avaliacao, const CODIGO& codigoViagem);
    /** @brief Lista destinos de uma viagem. */
    bool listarDestinos(const CODIGO& codigoViagem);
    /** @brief Deleta um destino. */
    bool deletarDestino(const CODIGO& codigo);
    /** @brief Atualiza os dados de um destino. */
    bool atualizarDestino(const CODIGO& codigo, const NOME& novoNome, const DATA& novaDataInicio, const DATA& novaDataFim, const AVALIACAO& novaAvaliacao);
};

/**
 * @class ServicoAtividade
 * @brief Serviço responsável por operações relacionadas a atividades.
 */
class ServicoAtividade {
private:
    Database& db;

public:
    /** @brief Construtor com referência ao banco de dados. */
    ServicoAtividade(Database& database);
    /** @brief Cria uma nova atividade. */
    bool criarAtividade(const CODIGO& codigo, const NOME& nome, const DATA& data, const HORARIO& horario, const DURACAO& duracao, const DINHEIRO& preco, const AVALIACAO& avaliacao, const CODIGO& codigoDestino);
    /** @brief Lista atividades de um destino. */
    bool listarAtividades(const CODIGO& codigoDestino);
    /** @brief Deleta uma atividade. */
    bool deletarAtividade(const CODIGO& codigo);
    /** @brief Atualiza os dados de uma atividade. */
    bool atualizarAtividade(const CODIGO& codigo, const NOME& novoNome, const DATA& novaData, const HORARIO& novoHorario, const DURACAO& novaDuracao, const DINHEIRO& novoPreco, const AVALIACAO& novaAvaliacao);
};

/**
 * @class ServicoHospedagem
 * @brief Serviço responsável por operações relacionadas a hospedagens.
 */
class ServicoHospedagem {
private:
    Database& db;

public:
    /** @brief Construtor com referência ao banco de dados. */
    ServicoHospedagem(Database& database);
    /** @brief Cria uma nova hospedagem. */
    bool criarHospedagem(const CODIGO& codigo, const NOME& nome, const AVALIACAO& avaliacao, const DINHEIRO& diaria, const CODIGO& codigoDestino);
    /** @brief Lista hospedagens de um destino. */
    bool listarHospedagens(const CODIGO& codigoDestino);
    /** @brief Deleta uma hospedagem. */
    bool deletarHospedagem(const CODIGO& codigo);
    /** @brief Atualiza os dados de uma hospedagem. */
    bool atualizarHospedagem(const CODIGO& codigo, const NOME& novoNome, const AVALIACAO& novaAvaliacao, const DINHEIRO& novaDiaria);
};

#endif // SERVICO_H
