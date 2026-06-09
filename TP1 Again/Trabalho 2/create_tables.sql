CREATE TABLE IF NOT EXISTS Conta (
    codigo TEXT PRIMARY KEY,
    senha INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS Viagem (
    codigo TEXT PRIMARY KEY,
    nome TEXT NOT NULL,
    avaliacao INTEGER,
    codigo_conta TEXT,
    FOREIGN KEY (codigo_conta) REFERENCES Conta(codigo) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Destino (
    codigo TEXT PRIMARY KEY,
    nome TEXT NOT NULL,
    data_inicio TEXT NOT NULL,
    data_fim TEXT NOT NULL,
    avaliacao INTEGER,
    codigo_viagem TEXT,
    FOREIGN KEY (codigo_viagem) REFERENCES Viagem(codigo) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Atividade (
    codigo TEXT PRIMARY KEY,
    nome TEXT NOT NULL,
    data TEXT NOT NULL,
    horario TEXT NOT NULL,
    duracao INTEGER NOT NULL,
    preco REAL NOT NULL,
    avaliacao INTEGER,
    codigo_destino TEXT,
    FOREIGN KEY (codigo_destino) REFERENCES Destino(codigo) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Hospedagem (
    codigo TEXT PRIMARY KEY,
    nome TEXT NOT NULL,
    avaliacao INTEGER,
    diaria REAL NOT NULL,
    codigo_destino TEXT,
    FOREIGN KEY (codigo_destino) REFERENCES Destino(codigo) ON DELETE CASCADE
);