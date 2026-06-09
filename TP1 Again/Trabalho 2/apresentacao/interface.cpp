#include <iostream>
#include <string>
#include "../entidade.h"
#include "../servico.h"
#include "../database.h"
#include "../dominio.h"
#include "interface.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void START_SCREEN::run(Database db){

        std::string command;
        bool logged = false;
        ServicoConta Conta = ServicoConta(db);
        ServicoAtividade Atividade = ServicoAtividade(db);
        ServicoDestino Destino = ServicoDestino(db);
        ServicoHospedagem Hospedagem = ServicoHospedagem(db);
        ServicoViagem viagem = ServicoViagem(db);
        while (true)
        {
            std::cout << ">" << std::endl;
            std::cin >> command;
            clearScreen();
            if(command=="sair"){
                break;
            }
            else if (command == "criar_conta")
            {
                std::string codigo, senha;
                CONTA conta;
                CODIGO _codigo;
                SENHA _senha;
                std::cout << "nome" << std::endl;
                std::cin >> codigo;
                std::cout << "senha" << std::endl;
                std::cin >> senha;
                try
                {
                    _codigo.SetCodigo(codigo);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                try
                {
                    _senha.SetSenha(std::stoi(senha));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                loggedAcount.SetCodigo(_codigo);
                loggedAcount.SetSenha(_senha);
                Conta.criarConta(_codigo, _senha);
                logged = true;
            }
            else if (command == "login")
            {
                std::string codigo, senha;
                CONTA conta;
                CODIGO _codigo;
                SENHA _senha;
                std::cout << "nome" << std::endl;
                std::cin >> codigo;
                std::cout << "senha" << std::endl;
                std::cin >> senha;
                try
                {
                    _codigo.SetCodigo(codigo);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                try
                {
                    _senha.SetSenha(std::stoi(senha));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                if (Conta.autenticarConta(_codigo, _senha) == true)
                {
                    loggedAcount.SetCodigo(_codigo);
                    loggedAcount.SetSenha(_senha);
                    logged=true;
                }
            }
            else if (command == "ajuda")
            {
                std::cout << "\nComandos disponíveis:\n";
                std::cout << "----------------------------------------\n";
                std::cout << "  ajuda - Mostra esta lista de comandos.\n";
                std::cout << "  sair - Encerra o programa.\n";
                std::cout << "\n  criar_conta - Cria uma nova conta.\n";
                std::cout << "  ler_conta - Lê os detalhes de uma conta.\n";
                std::cout << "  atualizar_conta - Atualiza a senha de uma conta.\n";
                std::cout << "  excluir_conta - Exclui uma conta.\n";
                std::cout << "\n  criar_viagem - Cria uma nova viagem.\n";
                std::cout << "  ler_viagem - Lê os detalhes de uma viagem.\n";
                std::cout << "  atualizar_viagem - Atualiza os detalhes de uma viagem.\n";
                std::cout << "  excluir_viagem - Exclui uma viagem.\n";
                std::cout << "\n  criar_destino - Cria um novo destino.\n";
                std::cout << "  ler_destino - Lê os detalhes de um destino.\n";
                std::cout << "  atualizar_destino - Atualiza o nome de um destino.\n";
                std::cout << "  excluir_destino - Exclui um destino.\n";
                std::cout << "\n  criar_atividade - Cria uma nova atividade.\n";
                std::cout << "  ler_atividade - Lê os detalhes de uma atividade.\n";
                std::cout << "  atualizar_atividade - Atualiza a descrição de uma atividade.\n";
                std::cout << "  excluir_atividade - Exclui uma atividade.\n";
                std::cout << "\n  criar_hospedagem - Cria uma nova hospedagem.\n";
                std::cout << "  ler_hospedagem - Lê os detalhes de uma hospedagem.\n";
                std::cout << "  atualizar_hospedagem - Atualiza os detalhes de uma hospedagem.\n";
                std::cout << "  excluir_hospedagem - Exclui uma hospedagem.\n";
                std::cout << "----------------------------------------\n\n";
            }
            else
            {
                // Handle Conta commands
                if (command == "excluir_conta")
                {
                    Conta.deletarConta(loggedAcount.GetCodigo());
                }

                // Handle Viagem commands
                else if (command == "criar_viagem")
                {
                    std::string _id, _avaliacao;
                    std::cout << "Digite o nome da viagem: ";
                    std::cin >> _id;
                    std::cout << "Digite os detalhes da viagem: ";
                    std::cin>>_avaliacao;
                    CODIGO id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    viagem.criarViagem(id,nome , avaliacao, loggedAcount.GetCodigo());
                }

                else if (command == "ler_viagem")
                {
                    std::string id;
                    std::cout << "Digite o ID da viagem: ";
                    std::cin >> id;
                    CODIGO _id;
                    try
                    {
                        _id.SetCodigo(id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    viagem.listarViagens(id);
                }

                else if (command == "atualizar_viagem")
                {
                    std::string _id, _avaliacao;
                    std::cout << "Digite o nome da viagem: ";
                    std::cin >> _id;
                    std::cout << "Digite os detalhes da viagem: ";
                    std::cin>>_avaliacao;
                    CODIGO id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    viagem.atualizarViagem(id,nome , avaliacao);
                }

                else if (command == "excluir_viagem")
                {
                    std::string _id, _avaliacao;
                    std::cout << "Digite o nome da viagem: ";
                    std::cin >> _id;
                    CODIGO id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    viagem.deletarViagem(id);
                }

                // Handle Destino commands
                else if (command == "criar_destino")
                {
                    std::string _id, _avaliacao,_id_viagem,_di,_df;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> _id;
                    std::cout << "Digite o nome da viagem: ";
                    std::cin >> _id_viagem;
                    std::cout << "Digite a data de inicio: ";
                    std::cin >> _di;
                    std::cout << "Digite data de volta: ";
                    std::cin >> _df;
                    std::cout << "Digite a avaliacao do destino: ";
                    std::cin>> _avaliacao;
                    DATA di,df;
                    CODIGO id_viagem,id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        id_viagem.SetCodigo(_id_viagem);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        di.SetData(_di);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        df.SetData(_df);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Destino.criarDestino(id,nome,di,df,avaliacao,id_viagem);
                }

                else if (command == "ler_destino")
                {
                    std::string id;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> id;
                    CODIGO _id;
                    try
                    {
                        _id.SetCodigo(id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Destino.listarDestinos(_id);
                }

                else if (command == "atualizar_destino")
                {
                    std::string _id, _avaliacao,_id_viagem,_di,_df;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> _id;
                    std::cout << "Digite a data de inicio: ";
                    std::cin >> _di;
                    std::cout << "Digite data de volta: ";
                    std::cin >> _df;
                    std::cout << "Digite a avaliacao do destino: ";
                    std::cin>> _avaliacao;
                    DATA di,df;
                    CODIGO id_viagem,id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        id_viagem.SetCodigo(_id_viagem);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        di.SetData(_di);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        df.SetData(_df);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Destino.atualizarDestino(id,nome,di,df,avaliacao);
                }

                else if (command == "excluir_destino")
                {
                    std::string id;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> id;
                    CODIGO _id;
                    try
                    {
                        _id.SetCodigo(id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Destino.deletarDestino(_id);
                }

                // Handle Atividade commands
                else if (command == "criar_atividade")
                {
                    std::string _id, _avaliacao,_id_destino,_data,_horario,_valor,_duracao;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> _id;
                    std::cout << "Digite o nome do destino: ";
                    std::cin >> _id_destino;
                    std::cout << "Digite a data de inicio: ";
                    std::cin >> _data;
                    std::cout << "Digite o horario: ";
                    std::cin >> _horario;
                    std::cout << "Digite a duracao:";
                    std::cin >> _duracao;
                    std::cout << "Digite o valor:";
                    std::cin >> _valor;
                    std::cout << "Digite a avaliacao da atividade: ";
                    std::cin>> _avaliacao;
                    DATA data;
                    CODIGO id_destino,id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    HORARIO horario;
                    DURACAO duracao;
                    DINHEIRO valor;
                    try
                    {
                        horario.SetHorario(_horario);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    try {
                        id.SetCodigo(_id);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir CODIGO (id): " << e.what() << '\n';
                    }

                    try {
                        id_destino.SetCodigo(_id_destino);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir CODIGO (id_viagem): " << e.what() << '\n';
                    }

                    try {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir AVALIACAO: " << e.what() << '\n';
                    }

                    try {
                        nome.SetNome(_id); // Assuming _nome is the correct variable for the name
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir NOME: " << e.what() << '\n';
                    }

                    try {
                        data.SetData(_data);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DATA: " << e.what() << '\n';
                    }

                    try {
                        duracao.SetDuracao(std::stoi(_duracao)); // Assuming _duracao is a string representing duration
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DURACAO: " << e.what() << '\n';
                    }

                    try {
                        valor.SetDinheiro(std::stof(_valor)); // Assuming _valor is a string representing money
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DINHEIRO: " << e.what() << '\n';
                    }
                    
                    Atividade.criarAtividade(id,nome,data,horario,duracao,valor,avaliacao,id_destino);
                }

                else if (command == "ler_atividade")
                {
                    std::string _id;
                    std::cout << "Digite o ID da atividade: ";
                    std::cin >> _id;
                    CODIGO id;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Atividade.listarAtividades(id);
                }

                else if (command == "atualizar_atividade")
                {
                    std::string _id, _avaliacao,_id_destino,_data,_horario,_valor,_duracao;
                    std::cout << "Digite o ID do destino: ";
                    std::cin >> _id;
                    std::cout << "Digite o nome do destino: ";
                    std::cin >> _id_destino;
                    std::cout << "Digite a data de inicio: ";
                    std::cin >> _data;
                    std::cout << "Digite o horario: ";
                    std::cin >> _horario;
                    std::cout << "Digite a duracao:";
                    std::cin >> _duracao;
                    std::cout << "Digite o valor:";
                    std::cin >> _valor;
                    std::cout << "Digite a avaliacao da atividade: ";
                    std::cin>> _avaliacao;
                    DATA data;
                    CODIGO id_destino,id;
                    NOME nome;
                    AVALIACAO avaliacao;
                    HORARIO horario;
                    DURACAO duracao;
                    DINHEIRO valor;
                    try
                    {
                        horario.SetHorario(_horario);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    try {
                        id.SetCodigo(_id);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir CODIGO (id): " << e.what() << '\n';
                    }

                    try {
                        id_destino.SetCodigo(_id_destino);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir CODIGO (id_viagem): " << e.what() << '\n';
                    }

                    try {
                        avaliacao.SetAvaliacao(std::stoi(_avaliacao));
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir AVALIACAO: " << e.what() << '\n';
                    }

                    try {
                        nome.SetNome(_id); // Assuming _nome is the correct variable for the name
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir NOME: " << e.what() << '\n';
                    }

                    try {
                        data.SetData(_data);
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DATA: " << e.what() << '\n';
                    }

                    try {
                        duracao.SetDuracao(std::stoi(_duracao)); // Assuming _duracao is a string representing duration
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DURACAO: " << e.what() << '\n';
                    }

                    try {
                        valor.SetDinheiro(std::stof(_valor)); // Assuming _valor is a string representing money
                    } catch (const std::exception& e) {
                        std::cerr << "Erro ao definir DINHEIRO: " << e.what() << '\n';
                    }
                    
                    Atividade.atualizarAtividade(id,nome,data,horario,duracao,valor,avaliacao);
                }
                
                else if (command == "excluir_atividade")
                {
                    std::string _id;
                    std::cout << "Digite o ID da atividade: ";
                    std::cin >> _id;
                    CODIGO id;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Atividade.deletarAtividade(id);
                }

                // Handle Hospedagem commands
                else if (command == "criar_Hospedagem")
                {
                    std::string _id, _avaliacao,_data,_valor,_id_destino;
                    std::cout << "Digite o nome: ";
                    std::cin >> _id;
                    std::cout << "Digite a avalicao: ";
                    std::cin >> _avaliacao;
                    std::cout << "Digite o valor: ";
                    std::cin >> _valor;
                    std::cout << "Digite o valor: ";
                    std::cin >> _id_destino;
                    CODIGO id,id_destino;
                    AVALIACAO avalicao;
                    DINHEIRO valor;
                    NOME nome;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }try
                    {
                        avalicao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        valor.SetDinheiro(std::stoi(_valor));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        id_destino.SetCodigo(_id_destino);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    Hospedagem.criarHospedagem(id, nome,avalicao,valor,id_destino);
                }

                else if (command == "ler_Hospedagem")
                {
                    std::string id;
                    std::cout << "Digite o ID da Hospedagem: ";
                    std::cin >> id;
                    Hospedagem.listarHospedagens(id);
                }

                else if (command == "atualizar_Hospedagem")
                {
                    std::string _id, _avaliacao,_data,_valor,_id_destino;
                    std::cout << "Digite o nome: ";
                    std::cin >> _id;
                    std::cout << "Digite a avalicao: ";
                    std::cin >> _avaliacao;
                    std::cout << "Digite o valor: ";
                    std::cin >> _valor;
                    std::cout << "Digite o valor: ";
                    std::cin >> _id_destino;
                    CODIGO id,id_destino;
                    AVALIACAO avalicao;
                    DINHEIRO valor;
                    NOME nome;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }try
                    {
                        avalicao.SetAvaliacao(std::stoi(_avaliacao));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        valor.SetDinheiro(std::stoi(_valor));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        nome.SetNome(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    try
                    {
                        id_destino.SetCodigo(_id_destino);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    Hospedagem.atualizarHospedagem(id, nome,avalicao,valor);
                }

                else if (command == "excluir_Hospedagem")
                {
                    std::string _id;
                    std::cout << "Digite o ID da Hospedagem: ";
                    std::cin >> _id;
                    CODIGO id;
                    try
                    {
                        id.SetCodigo(_id);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    Hospedagem.deletarHospedagem(id);
                }
                else
                {
                    std::cout << "Comando inválido!" << std::endl;
                }
            }
        }
};
START_SCREEN::START_SCREEN(){};