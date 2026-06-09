"""
Trabalho 1 - Cifra de Vigenere
Parte I: cifrador e decifrador.
Parte II: ataque de recuperacao de senha por analise de frequencia.

Regras adotadas:
- Apenas letras A-Z participam da cifra.
- Minusculas e maiusculas sao preservadas na saida.
- Caracteres que nao sao letras (espacos, pontuacao, numeros, acentos etc.)
  sao mantidos sem alteracao.
"""

ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
TAMANHO_ALFABETO = len(ALFABETO)

# Frequencias aproximadas de letras (A-Z) para analise de frequencia.
FREQ_INGLES = [
    0.08167,
    0.01492,
    0.02782,
    0.04253,
    0.12702,
    0.02228,
    0.02015,
    0.06094,
    0.06966,
    0.00153,
    0.00772,
    0.04025,
    0.02406,
    0.06749,
    0.07507,
    0.01929,
    0.00095,
    0.05987,
    0.06327,
    0.09056,
    0.02758,
    0.00978,
    0.02360,
    0.00150,
    0.01974,
    0.00074,
]

FREQ_PORTUGUES = [
    0.1463,
    0.0104,
    0.0388,
    0.0499,
    0.1257,
    0.0102,
    0.0130,
    0.0078,
    0.0618,
    0.0040,
    0.0002,
    0.0278,
    0.0474,
    0.0505,
    0.1073,
    0.0252,
    0.0120,
    0.0653,
    0.0781,
    0.0434,
    0.0463,
    0.0167,
    0.0001,
    0.0021,
    0.0001,
    0.0047,
]

MAPA_FREQ_IDIOMA = {
    "en": FREQ_INGLES,
    "pt": FREQ_PORTUGUES,
}


def validar_senha(senha: str) -> str:
    """Valida e normaliza a senha para uso na cifra."""
    if not senha:
        raise ValueError("A senha nao pode ser vazia.")

    senha_filtrada = "".join(ch for ch in senha.upper() if ch in ALFABETO)
    if not senha_filtrada:
        raise ValueError("A senha deve conter ao menos uma letra de A-Z.")

    return senha_filtrada


def _deslocamento_da_letra(letra_senha: str) -> int:
    """Converte a letra da senha em deslocamento numerico (A=0, B=1, ...)."""
    return ord(letra_senha) - ord("A")


def _transformar_texto(texto: str, senha: str, cifrar: bool) -> str:
    """Aplica cifragem ou decifragem de Vigenere sobre o texto."""
    senha_normalizada = validar_senha(senha)
    resultado = []
    indice_senha = 0

    for ch in texto:
        ch_maiusculo = ch.upper()

        if ch_maiusculo in ALFABETO:
            deslocamento = _deslocamento_da_letra(
                senha_normalizada[indice_senha % len(senha_normalizada)]
            )

            base = ord("A") if ch.isupper() else ord("a")
            posicao_atual = ord(ch) - base

            if cifrar:
                nova_posicao = (posicao_atual + deslocamento) % TAMANHO_ALFABETO
            else:
                nova_posicao = (posicao_atual - deslocamento) % TAMANHO_ALFABETO

            resultado.append(chr(base + nova_posicao))
            indice_senha += 1
        else:
            resultado.append(ch)

    return "".join(resultado)


def cifrar_vigenere(mensagem: str, senha: str) -> str:
    """Cifra uma mensagem usando a cifra de Vigenere."""
    return _transformar_texto(mensagem, senha, cifrar=True)


def decifrar_vigenere(criptograma: str, senha: str) -> str:
    """Decifra um criptograma usando a cifra de Vigenere."""
    return _transformar_texto(criptograma, senha, cifrar=False)


def _somente_letras_maiusculas(texto: str) -> str:
    """Extrai apenas letras A-Z em maiusculas."""
    return "".join(ch for ch in texto.upper() if ch in ALFABETO)


def _indice_coincidencia(texto: str) -> float:
    """Calcula o indice de coincidencia para um texto com A-Z."""
    n = len(texto)
    if n <= 1:
        return 0.0

    contagens = [0] * TAMANHO_ALFABETO
    for ch in texto:
        contagens[ord(ch) - ord("A")] += 1

    numerador = sum(c * (c - 1) for c in contagens)
    denominador = n * (n - 1)
    return numerador / denominador


def estimar_tamanho_senha(criptograma: str, max_tamanho: int = 20) -> int:
    """Estima o tamanho da senha usando media do indice de coincidencia."""
    texto = _somente_letras_maiusculas(criptograma)
    if not texto:
        raise ValueError("O criptograma precisa ter letras A-Z para analise.")

    limite = max(1, min(max_tamanho, len(texto)))
    melhor_tamanho = 1
    melhor_ic = -1.0

    for tamanho in range(1, limite + 1):
        fatias = [texto[i::tamanho] for i in range(tamanho)]
        ics_validos = [_indice_coincidencia(fatia) for fatia in fatias if len(fatia) > 1]
        if not ics_validos:
            continue

        ic_medio = sum(ics_validos) / len(ics_validos)
        if ic_medio > melhor_ic:
            melhor_ic = ic_medio
            melhor_tamanho = tamanho

    return melhor_tamanho


def _chi_quadrado_deslocamento(coluna: str, deslocamento: int, freq_esperada: list[float]) -> float:
    """Mede quao bem um deslocamento explica a distribuicao da coluna."""
    n = len(coluna)
    if n == 0:
        return float("inf")

    observados = [0] * TAMANHO_ALFABETO
    for ch in coluna:
        pos = ord(ch) - ord("A")
        # Para decifrar: P = C - k. Fazemos isso para testar k.
        pos_decifrada = (pos - deslocamento) % TAMANHO_ALFABETO
        observados[pos_decifrada] += 1

    chi = 0.0
    for i in range(TAMANHO_ALFABETO):
        esperado = n * freq_esperada[i]
        if esperado > 0:
            diferenca = observados[i] - esperado
            chi += (diferenca * diferenca) / esperado
    return chi


def recuperar_senha_por_frequencia(
    criptograma: str,
    idioma: str,
    tamanho_senha: int | None = None,
    max_tamanho: int = 20,
) -> str:
    """Recupera a senha estimada por analise de frequencia."""
    idioma_normalizado = idioma.strip().lower()
    if idioma_normalizado not in MAPA_FREQ_IDIOMA:
        raise ValueError("Idioma invalido. Use 'pt' para portugues ou 'en' para ingles.")

    texto = _somente_letras_maiusculas(criptograma)
    if not texto:
        raise ValueError("O criptograma precisa ter letras A-Z para analise.")

    if tamanho_senha is None:
        tamanho_senha = estimar_tamanho_senha(texto, max_tamanho=max_tamanho)
    elif tamanho_senha <= 0:
        raise ValueError("O tamanho da senha deve ser maior que zero.")

    freq = MAPA_FREQ_IDIOMA[idioma_normalizado]
    senha = []

    for i in range(tamanho_senha):
        coluna = texto[i::tamanho_senha]
        melhor_deslocamento = 0
        melhor_chi = float("inf")

        for deslocamento in range(TAMANHO_ALFABETO):
            chi = _chi_quadrado_deslocamento(coluna, deslocamento, freq)
            if chi < melhor_chi:
                melhor_chi = chi
                melhor_deslocamento = deslocamento

        senha.append(chr(ord("A") + melhor_deslocamento))

    return "".join(senha)


def atacar_e_decifrar(
    criptograma: str,
    idioma: str,
    tamanho_senha: int | None = None,
    max_tamanho: int = 20,
) -> tuple[str, str]:
    """Recupera senha estimada e retorna mensagem decifrada."""
    senha_estimada = recuperar_senha_por_frequencia(
        criptograma=criptograma,
        idioma=idioma,
        tamanho_senha=tamanho_senha,
        max_tamanho=max_tamanho,
    )
    mensagem = decifrar_vigenere(criptograma, senha_estimada)
    return senha_estimada, mensagem


def menu_interativo() -> None:
    """Interface simples para uso no terminal."""
    print("Trabalho 1 - Cifra de Vigenere")
    print("1) Cifrar mensagem")
    print("2) Decifrar criptograma")
    print("3) Ataque por analise de frequencia (Parte II)")

    opcao = input("Escolha uma opcao (1, 2 ou 3): ").strip()

    try:
        if opcao == "1":
            senha = input("Digite a senha: ")
            mensagem = input("Digite a mensagem: ")
            criptograma = cifrar_vigenere(mensagem, senha)
            print("\nCriptograma:")
            print(criptograma)
        elif opcao == "2":
            senha = input("Digite a senha: ")
            criptograma = input("Digite o criptograma: ")
            mensagem = decifrar_vigenere(criptograma, senha)
            print("\nMensagem decifrada:")
            print(mensagem)
        elif opcao == "3":
            idioma = input("Idioma do texto original (pt/en): ").strip().lower()
            criptograma = input("Digite o criptograma: ")

            tamanho_digitado = input(
                "Tamanho da senha (Enter para estimar automaticamente): "
            ).strip()

            if tamanho_digitado:
                tamanho_senha = int(tamanho_digitado)
            else:
                tamanho_senha = None

            senha_estimada, mensagem = atacar_e_decifrar(
                criptograma=criptograma,
                idioma=idioma,
                tamanho_senha=tamanho_senha,
            )

            print("\nSenha estimada:")
            print(senha_estimada)
            print("\nMensagem decifrada:")
            print(mensagem)
        else:
            print("Opcao invalida. Execute novamente e escolha 1, 2 ou 3.")
    except ValueError as erro:
        print(f"Erro: {erro}")


if __name__ == "__main__":
    menu_interativo()
