#include <iostream>
#include <string>
#include "../entidade.h"
#include "../servico.h"
#include "../database.h"
#include "../dominio.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

class START_SCREEN
{
public:
    void run(Database);
    START_SCREEN();

private:
    CONTA loggedAcount;
    void clearScreen()
    {
#ifdef _WIN32
        // Windows
        system("cls");
#else
        // Linux and macOS
        system("clear");
#endif
    }
};