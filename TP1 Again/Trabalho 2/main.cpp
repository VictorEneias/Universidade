#include "database.h"
#include "servico.h"
#include"apresentacao/interface.h"
#include <iostream>

int main() {
    Database db("banco.db");

    // Abre a conexão com o banco de dados
    if (!db.open()) {
        std::cerr << "Erro ao abrir o banco de dados." << std::endl;
        return 1;
    }
    START_SCREEN screen;
    screen.run(db);

    return 0;
}