# Simulador.py

from CamadaFisica import (
    texto_para_bits,
    bits_para_texto,
    # Modulações banda-base
    codificar_nrz_polar,
    decodificar_nrz_polar,
    codificar_manchester,
    decodificar_manchester,
    codificar_bipolar,
    decodificar_bipolar,
    # Modulações por portadora
    codificar_ask,
    decodificar_ask,
    codificar_fsk,
    decodificar_fsk,
    codificar_qpsk,
    decodificar_qpsk,
    codificar_16qam,
    decodificar_16qam,
    # Meio de comunicação
    adicionar_ruido_gaussiano,
)


def testar_modulacao(nome, bits, codificador, decodificador, desvio_ruido=0.0):
    print("=" * 60)
    print(f"Modulação: {nome}")

    sinal = codificador(bits)

    if desvio_ruido > 0:
        sinal = adicionar_ruido_gaussiano(sinal, media=0.0, desvio_padrao=desvio_ruido)

    bits_recebidos = decodificador(sinal)
    texto_recebido = bits_para_texto(bits_recebidos)

    erros = sum(a != b for a, b in zip(bits, bits_recebidos[:len(bits)]))
    print(f"  Ruído σ={desvio_ruido} | Bits com erro: {erros}/{len(bits)}")
    print(f"  Texto recebido: {texto_recebido!r}")
    print("=" * 60)
    print()


def main():
    texto = "Oi TR1"
    print(f"Texto original: {texto!r}\n")
    bits = texto_para_bits(texto)

    # Testa sem ruído e com ruído leve
    for desvio in [0.0, 0.1]:
        print(f"{'─'*60}")
        print(f"  TESTE COM RUÍDO σ = {desvio}")
        print(f"{'─'*60}\n")

        testar_modulacao("NRZ-Polar",  bits, codificar_nrz_polar,  decodificar_nrz_polar,  desvio)
        testar_modulacao("Manchester", bits, codificar_manchester,  decodificar_manchester, desvio)
        testar_modulacao("Bipolar",    bits, codificar_bipolar,     decodificar_bipolar,    desvio)
        testar_modulacao("ASK",        bits, codificar_ask,         decodificar_ask,        desvio)
        testar_modulacao("FSK",        bits, codificar_fsk,         decodificar_fsk,        desvio)
        testar_modulacao("QPSK",       bits, codificar_qpsk,        decodificar_qpsk,       desvio)
        testar_modulacao("16-QAM",     bits, codificar_16qam,       decodificar_16qam,      desvio)


if __name__ == "__main__":
    main()
