#include "database.h"

Database::Database(const std::string& path) : dbPath(path), db(nullptr) {}

Database::~Database() {
    close();
}

bool Database::open() {
    close(); // Fecha a conexão antes de abrir uma nova
    
    std::cout << "Tentando abrir banco de dados em: " << dbPath << std::endl;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX;
    int rc = sqlite3_open_v2(dbPath.c_str(), &db, flags, nullptr);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << " (Código: " << rc << ")" << std::endl;
        return false;
    }
    std::cout << "Banco de dados aberto com sucesso." << std::endl;
    
    // Ativar suporte a chaves estrangeiras (foreign keys)
    std::cout << "Ativando suporte a chaves estrangeiras..." << std::endl;
    if (!execute("PRAGMA foreign_keys = ON;")) {
        std::cerr << "Erro: Não foi possível ativar PRAGMA foreign_keys." << std::endl;
        return false;
    }
    
    std::cout << "Chaves estrangeiras ativadas com sucesso." << std::endl;
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::execute(const std::string& query) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erro ao executar a query: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::executeScript(const std::string& scriptPath) {
    std::ifstream scriptFile(scriptPath);
    if (!scriptFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de script: " << scriptPath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << scriptFile.rdbuf();
    std::string sql = buffer.str();

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erro ao executar o script: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

sqlite3_stmt* Database::prepare(const std::string& query) {
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar a query: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    return stmt;
}

bool Database::tabelaExiste(const std::string& nomeTabela) {
    std::string query = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + nomeTabela + "';";
    sqlite3_stmt* stmt = prepare(query);

    if (!stmt) {
        return false; // Erro ao preparar a query
    }

    bool existe = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);

    return existe;
}