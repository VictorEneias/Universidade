#ifndef DOMINIO_H_INCLUDED
#define DOMINIO_H_INCLUDED

#include <stdexcept>
#include <algorithm>
#include <string>

using namespace std;

/**
 * @brief Classe responsável por representar uma avaliação.
 */
class AVALIACAO {
private:
    int avaliacao; /**< Valor da avaliação (0 a 5). */
    void verifica(int); /**< Verifica se a avaliação está no intervalo válido. */

public:
    AVALIACAO() {} // Construtor padrão
    AVALIACAO(int avaliacao) { // Construtor com parâmetro
        SetAvaliacao(avaliacao);
    }
    int GetAvaliacao() const; // Método Get marcado como const
    void SetAvaliacao(int);
};

/**
 * @brief Classe responsável por representar um código.
 */
class CODIGO {
private:
    string codigo; /**< Código alfanumérico de 6 caracteres. */
    void verifica(string); /**< Verifica se o código é válido. */

public:
    CODIGO() {} // Construtor padrão
    CODIGO(const string& codigo) { // Construtor com parâmetro
        SetCodigo(codigo);
    }
    string GetCodigo() const; // Método Get marcado como const
    void SetCodigo(string);
};

/**
 * @brief Classe responsável por representar uma data.
 */
class DATA {
private:
    string data; /**< Data no formato DD-MM-AA. */
    void verifica(string); /**< Verifica se a data é válida. */

public:
    DATA() {} // Construtor padrão
    DATA(const string& data) { // Construtor com parâmetro
        SetData(data);
    }
    string GetData() const; // Método Get marcado como const
    void SetData(string);
};

/**
 * @brief Classe responsável por representar um valor monetário.
 */
class DINHEIRO {
private:
    float dinheiro; /**< Valor monetário (0 a 200000). */
    void verifica(float); /**< Verifica se o valor é válido. */

public:
    DINHEIRO() {} // Construtor padrão
    DINHEIRO(float dinheiro) { // Construtor com parâmetro
        SetDinheiro(dinheiro);
    }
    float GetDinheiro() const; // Método Get marcado como const
    void SetDinheiro(float);
};

/**
 * @brief Classe responsável por representar a duração em minutos.
 */
class DURACAO {
private:
    int duracao; /**< Duração em minutos (0 a 360). */
    void verifica(int); /**< Verifica se a duração é válida. */

public:
    DURACAO() {} // Construtor padrão
    DURACAO(int duracao) { // Construtor com parâmetro
        SetDuracao(duracao);
    }
    int GetDuracao() const; // Método Get marcado como const
    void SetDuracao(int);
};

/**
 * @brief Classe responsável por representar um horário.
 */
class HORARIO {
private:
    string horario; /**< Horário no formato HH:MM. */
    void verifica(string); /**< Verifica se o horário é válido. */

public:
    HORARIO() {} // Construtor padrão
    HORARIO(const string& horario) { // Construtor com parâmetro
        SetHorario(horario);
    }
    string GetHorario() const; // Método Get marcado como const
    void SetHorario(string);
};

/**
 * @brief Classe responsável por representar um nome.
 */
class NOME {
private:
    string nome; /**< Nome com até 30 caracteres. */
    void verifica(string); /**< Verifica se o nome é válido. */

public:
    NOME() {} // Construtor padrão
    NOME(const string& nome) { // Construtor com parâmetro
        SetNome(nome);
    }
    string GetNome() const; // Método Get marcado como const
    void SetNome(string);
};

/**
 * @brief Classe responsável por representar uma senha.
 */
class SENHA {
private:
    int senha; /**< Senha numérica de 5 dígitos. */
    void verifica(int); /**< Verifica se a senha é válida. */

public:
    SENHA() {} // Construtor padrão
    SENHA(int senha) { // Construtor com parâmetro
        SetSenha(senha);
    }
    int GetSenha() const; // Método Get marcado como const
    void SetSenha(int);
};

// Implementações inline

inline void AVALIACAO::SetAvaliacao(int avaliacao) {
    verifica(avaliacao);
    this->avaliacao = avaliacao;
}

inline int AVALIACAO::GetAvaliacao() const {
    return avaliacao;
}

inline void CODIGO::SetCodigo(string codigo) {
    verifica(codigo);
    this->codigo = codigo;
}

inline string CODIGO::GetCodigo() const {
    return codigo;
}

inline void DATA::SetData(string data) {
    verifica(data);
    this->data = data;
}

inline string DATA::GetData() const {
    return data;
}

inline void DINHEIRO::SetDinheiro(float dinheiro) {
    verifica(dinheiro);
    this->dinheiro = dinheiro;
}

inline float DINHEIRO::GetDinheiro() const {
    return dinheiro;
}

inline void DURACAO::SetDuracao(int duracao) {
    verifica(duracao);
    this->duracao = duracao;
}

inline int DURACAO::GetDuracao() const {
    return duracao;
}

inline void HORARIO::SetHorario(string horario) {
    verifica(horario);
    this->horario = horario;
}

inline string HORARIO::GetHorario() const {
    return horario;
}

inline void NOME::SetNome(string nome) {
    verifica(nome);
    this->nome = nome;
}

inline string NOME::GetNome() const {
    return nome;
}

inline void SENHA::SetSenha(int senha) {
    verifica(senha);
    this->senha = senha;
}

inline int SENHA::GetSenha() const {
    return senha;
}

#endif // DOMINIO_H_INCLUDED