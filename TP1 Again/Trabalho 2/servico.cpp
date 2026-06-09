#include "servico.h"
#include <iostream>

// Implementação do ServicoConta
ServicoConta::ServicoConta(Database& database) : db(database) {}

bool ServicoConta::criarConta(const CODIGO& codigo, const SENHA& senha) {
    std::string query = "INSERT INTO Conta (codigo, senha) VALUES ('" + codigo.GetCodigo() + "', '" + std::to_string(senha.GetSenha()) + "');";
    return db.execute(query);
}

bool ServicoConta::autenticarConta(const CODIGO& codigo, const SENHA& senha) {
    std::string query = "SELECT senha FROM Conta WHERE codigo = '" + codigo.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);
    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        int senhaDB = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return senhaDB == senha.GetSenha();
    }
    return false;
}
CONTA ServicoConta::getConta(const CODIGO& codigo) {
    std::string query = "SELECT codigo, senha FROM Conta WHERE codigo = '" + codigo.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);

    if (stmt && sqlite3_step(stmt) == SQLITE_ROW) {
        // Retrieve the codigo and senha from the database
        std::string codigoDB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int senhaDB = sqlite3_column_int(stmt, 1);

        // Create a CONTA object
        CONTA conta;
        conta.SetCodigo(CODIGO(codigoDB));
        conta.SetSenha(SENHA(senhaDB));

        // Clean up the statement
        sqlite3_finalize(stmt);

        // Return the CONTA object
        return conta;
    }

    // If no rows are returned, clean up and throw an exception
    sqlite3_finalize(stmt);
    throw std::runtime_error("Conta não encontrada para o código fornecido.");
}


bool ServicoConta::deletarConta(const CODIGO& codigo) {
    std::string query = "DELETE FROM Conta WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoViagem
ServicoViagem::ServicoViagem(Database& database) : db(database) {}

bool ServicoViagem::criarViagem(const CODIGO& codigo, const NOME& nome, const AVALIACAO& avaliacao, const CODIGO& codigoConta) {
    std::string query = "INSERT INTO Viagem (codigo, nome, avaliacao, codigo_conta) VALUES ('" + codigo.GetCodigo() + "', '" + nome.GetNome() + "', " + std::to_string(avaliacao.GetAvaliacao()) + ", '" + codigoConta.GetCodigo() + "');";
    return db.execute(query);
}

bool ServicoViagem::listarViagens(const CODIGO& codigoConta) {
    std::string query = "SELECT codigo, nome FROM Viagem WHERE codigo_conta = '" + codigoConta.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Código: " << sqlite3_column_text(stmt, 0) << ", Nome: " << sqlite3_column_text(stmt, 1) << std::endl;
        }
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool ServicoViagem::deletarViagem(const CODIGO& codigo) {
    std::string query = "DELETE FROM Viagem WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoDestino
ServicoDestino::ServicoDestino(Database& database) : db(database) {}

bool ServicoDestino::criarDestino(const CODIGO& codigo, const NOME& nome, const DATA& dataInicio, const DATA& dataFim, const AVALIACAO& avaliacao, const CODIGO& codigoViagem) {
    std::string query = "INSERT INTO Destino (codigo, nome, data_inicio, data_fim, avaliacao, codigo_viagem) VALUES ('" + codigo.GetCodigo() + "', '" + nome.GetNome() + "', '" + dataInicio.GetData() + "', '" + dataFim.GetData() + "', " + std::to_string(avaliacao.GetAvaliacao()) + ", '" + codigoViagem.GetCodigo() + "');";
    return db.execute(query);
}

bool ServicoDestino::listarDestinos(const CODIGO& codigoViagem) {
    std::string query = "SELECT codigo, nome FROM Destino WHERE codigo_viagem = '" + codigoViagem.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Código: " << sqlite3_column_text(stmt, 0) << ", Nome: " << sqlite3_column_text(stmt, 1) << std::endl;
        }
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool ServicoDestino::deletarDestino(const CODIGO& codigo) {
    std::string query = "DELETE FROM Destino WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoAtividade
ServicoAtividade::ServicoAtividade(Database& database) : db(database) {}

bool ServicoAtividade::criarAtividade(const CODIGO& codigo, const NOME& nome, const DATA& data, const HORARIO& horario, const DURACAO& duracao, const DINHEIRO& preco, const AVALIACAO& avaliacao, const CODIGO& codigoDestino) {
    std::string query = "INSERT INTO Atividade (codigo, nome, data, horario, duracao, preco, avaliacao, codigo_destino) VALUES ('" + codigo.GetCodigo() + "', '" + nome.GetNome() + "', '" + data.GetData() + "', '" + horario.GetHorario() + "', " + std::to_string(duracao.GetDuracao()) + ", " + std::to_string(preco.GetDinheiro()) + ", " + std::to_string(avaliacao.GetAvaliacao()) + ", '" + codigoDestino.GetCodigo() + "');";
    return db.execute(query);
}

bool ServicoAtividade::listarAtividades(const CODIGO& codigoDestino) {
    std::string query = "SELECT codigo, nome FROM Atividade WHERE codigo_destino = '" + codigoDestino.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Código: " << sqlite3_column_text(stmt, 0) << ", Nome: " << sqlite3_column_text(stmt, 1) << std::endl;
        }
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool ServicoAtividade::deletarAtividade(const CODIGO& codigo) {
    std::string query = "DELETE FROM Atividade WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoHospedagem
ServicoHospedagem::ServicoHospedagem(Database& database) : db(database) {}

bool ServicoHospedagem::criarHospedagem(const CODIGO& codigo, const NOME& nome, const AVALIACAO& avaliacao, const DINHEIRO& diaria, const CODIGO& codigoDestino) {
    std::string query = "INSERT INTO Hospedagem (codigo, nome, avaliacao, diaria, codigo_destino) VALUES ('" + codigo.GetCodigo() + "', '" + nome.GetNome() + "', " + std::to_string(avaliacao.GetAvaliacao()) + ", " + std::to_string(diaria.GetDinheiro()) + ", '" + codigoDestino.GetCodigo() + "');";
    return db.execute(query);
}

bool ServicoHospedagem::listarHospedagens(const CODIGO& codigoDestino) {
    std::string query = "SELECT codigo, nome FROM Hospedagem WHERE codigo_destino = '" + codigoDestino.GetCodigo() + "';";
    sqlite3_stmt* stmt = db.prepare(query);
    if (stmt) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "Código: " << sqlite3_column_text(stmt, 0) << ", Nome: " << sqlite3_column_text(stmt, 1) << std::endl;
        }
        sqlite3_finalize(stmt);
        return true;
    }
    return false;
}

bool ServicoHospedagem::deletarHospedagem(const CODIGO& codigo) {
    std::string query = "DELETE FROM Hospedagem WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoViagem
bool ServicoViagem::atualizarViagem(const CODIGO& codigo, const NOME& novoNome, const AVALIACAO& novaAvaliacao) {
    std::string query = "UPDATE Viagem SET nome = '" + novoNome.GetNome() + "', avaliacao = " + std::to_string(novaAvaliacao.GetAvaliacao()) + " WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoDestino
bool ServicoDestino::atualizarDestino(const CODIGO& codigo, const NOME& novoNome, const DATA& novaDataInicio, const DATA& novaDataFim, const AVALIACAO& novaAvaliacao) {
    std::string query = "UPDATE Destino SET nome = '" + novoNome.GetNome() + "', data_inicio = '" + novaDataInicio.GetData() + "', data_fim = '" + novaDataFim.GetData() + "', avaliacao = " + std::to_string(novaAvaliacao.GetAvaliacao()) + " WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoAtividade
bool ServicoAtividade::atualizarAtividade(const CODIGO& codigo, const NOME& novoNome, const DATA& novaData, const HORARIO& novoHorario, const DURACAO& novaDuracao, const DINHEIRO& novoPreco, const AVALIACAO& novaAvaliacao) {
    std::string query = "UPDATE Atividade SET nome = '" + novoNome.GetNome() + "', data = '" + novaData.GetData() + "', horario = '" + novoHorario.GetHorario() + "', duracao = " + std::to_string(novaDuracao.GetDuracao()) + ", preco = " + std::to_string(novoPreco.GetDinheiro()) + ", avaliacao = " + std::to_string(novaAvaliacao.GetAvaliacao()) + " WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}

// Implementação do ServicoHospedagem
bool ServicoHospedagem::atualizarHospedagem(const CODIGO& codigo, const NOME& novoNome, const AVALIACAO& novaAvaliacao, const DINHEIRO& novaDiaria) {
    std::string query = "UPDATE Hospedagem SET nome = '" + novoNome.GetNome() + "', avaliacao = " + std::to_string(novaAvaliacao.GetAvaliacao()) + ", diaria = " + std::to_string(novaDiaria.GetDinheiro()) + " WHERE codigo = '" + codigo.GetCodigo() + "';";
    return db.execute(query);
}