.eqv DISPLAY_BASE 0x10040000
.eqv COR_MORTA    0x00000000
.eqv COR_VIVA     0x00FFFF00

.data
mat1: .byte
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 1 1 0 0 0 1 0 0 0 0 0 0 0 0 0
	 0 1 1 0 0 0 0 1 0 0 0 0 0 0 0 0
	 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 1 1 0 0 0 0 0 1 1 1 0 0 0
	 0 0 1 1 0 0 0 0 0 0 0 1 0 0 0 0
	 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
	 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

mat2: .byte 0:256

.text
.globl main

main:
	# desenha a matriz inicial
	la	a0, mat1
	jal	ra, plotm

	# espera 1 segundo
	li	a0, 1000
	li	a7, 32
	ecall

main_loop:
	# mat2 = próxima geração de mat1
	la	a0, mat1
	la	a1, mat2
	jal	ra, proxima_geracao

	# desenha mat2
	la	a0, mat2
	jal	ra, plotm

	# espera
	li	a0, 500
	li	a7, 32
	ecall

	# verifica se mat1 == mat2
	la	a0, mat1
	la	a1, mat2
	jal	ra, compara_matrizes

	# se forem iguais, chegou ao equilíbrio
	bne	a0, zero, main_fim

	# mat1 = próxima geração de mat2
	la	a0, mat2
	la	a1, mat1
	jal	ra, proxima_geracao

	# desenha mat1
	la	a0, mat1
	jal	ra, plotm

	# espera
	li	a0, 500
	li	a7, 32
	ecall

	# verifica se mat2 == mat1
	la	a0, mat2
	la	a1, mat1
	jal	ra, compara_matrizes

	# se forem iguais, chegou ao equilíbrio
	bne	a0, zero, main_fim

	j	main_loop

main_fim:
	# espera um pouco antes de terminar
	li	a0, 3000
	li	a7, 32
	ecall

	# final do programa
	li	a7, 10
	ecall

#função int readm(int i(a0), int j(a1), int endereço_mat(a2)) -> le o valor da matriz[i][j] e retorna em a0
readm:
	#verificação de possibilidade
	blt	a0, zero, readm_fim
	blt	a1, zero, readm_fim
	li	t0, 16
	bge	a0, t0, readm_fim
	bge	a1, t0, readm_fim
	
	#logica da função
	slli	t0, a0, 4
	add	t0, t0, a1
	add	t0, t0, a2
	lb 	a0, 0(t0)
	ret
	
readm_fim:
	li 	a0, 0
	ret

#função void write(int i(a0), int j(a1), int endereço_mat(a2)) -> le o valor da matriz[i][j] e o inverte
write:
	#verificação de possibilidade
	blt	a0, zero, write_fim
	blt	a1, zero, write_fim
	li	t0, 16
	bge	a0, t0, write_fim
	bge	a1, t0, write_fim
	
	#logica da função
	slli	t0, a0, 4
	add	t0, t0, a1
	add	t0, t0, a2
	lb 	t1, 0(t0)
	xori	t1, t1, 1
	sb	t1, 0(t0)

write_fim:
	ret

#função void plotm(int endereço_mat(a0)) -> desenha uma matriz no bitmap
plotm:
	li 	t5, 16			#ponto de parada dos laços(loops) t5 = 16
	li 	t0, 0			#contador i=0
	
plotm_loop_i:
	bge	t0, t5, plotm_fim	#condição de parada i -> acabou a matriz
	li 	t1, 0			#contador j=0
	
plotm_loop_j:
	bge	t1, t5, plotm_pxm_linha	#condição de parada j -> acabou a linha
	
	#calculo do deslocamento d
	slli	t2, t0, 4		
	add	t2, t1, t2		#deslocamento t2 = d = i * 16 + j
	
	#calculo do endereço 'e' da celula [i][j] na matriz
	add	t3, t2, a0		#t3 = e = d + endereço base da mat
	
	lb	t4, 0(t3)		#t4 = conteudo da celula mat[i][j]
	
	#calculo do endereço 'E' da celula [i][j] do bit map
	slli	t2, t2, 2		#t2 = D = d * 4. Diferentemente da matriz que cada endereço ocupa 1 byte, no bitmap cada um ocupa 4 bytes
	li	t3, DISPLAY_BASE
	add	t3, t3, t2	#t3 = E = D + endereço base do bitmap
	
	#logica da função
	beq	t4, zero, plotm_cel_morta #if a celula mat[i][j] pula
	
	#else
	li	t4, COR_VIVA		#t4 = cor viva
	j	plotm_desenha

plotm_cel_morta:
	li	t4, COR_MORTA		#t4 = cor morta
	
plotm_desenha:
	sw	t4, 0(t3)		#desenha a cor que estiver em t4 no endereço 'E' do bitmap
	
	addi	t1, t1, 1		#j++
	j	plotm_loop_j
	
plotm_pxm_linha:
	addi	t0, t0, 1		#i++
	j	plotm_loop_i
	
plotm_fim:
	ret

#função int conta_vizinhos(int i(a0), int j(a1), int endereço_mat(a2)) -> retorna em a0 a quantidade de vizinhos vivos da célula mat[i][j]
conta_vizinhos:
	#salva registradores que por convenção devem ser salvos e restaurados depois caso eu vá usa-los na função
	addi	sp, sp, -20
	sw	ra, 16(sp)
	sw	s0, 12(sp)
	sw	s1, 8(sp)
	sw	s2, 4(sp)
	sw	s3, 0(sp)

	#guarda os argumentos originais
	mv	s0, a0			# s0 = i
	mv	s1, a1			# s1 = j
	mv	s2, a2			# s2 = endereço da matriz
	li	s3, 0			# s3 = contador de vizinhos vivos
	
	# vizinho [i-1][j-1]
	addi	a0, s0, -1
	addi	a1, s1, -1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i-1][j]
	addi	a0, s0, -1
	mv	a1, s1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i-1][j+1]
	addi	a0, s0, -1
	addi	a1, s1, 1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i][j-1]
	mv	a0, s0
	addi	a1, s1, -1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i][j+1]
	mv	a0, s0
	addi	a1, s1, 1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i+1][j-1]
	addi	a0, s0, 1
	addi	a1, s1, -1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i+1][j]
	addi	a0, s0, 1
	mv	a1, s1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# vizinho [i+1][j+1]
	addi	a0, s0, 1
	addi	a1, s1, 1
	mv	a2, s2
	jal	ra, readm
	add	s3, s3, a0

	# retorno
	mv	a0, s3

	# restaura registradores
	lw	s3, 0(sp)
	lw	s2, 4(sp)
	lw	s1, 8(sp)
	lw	s0, 12(sp)
	lw	ra, 16(sp)
	addi	sp, sp, 20

	ret

#função void limpa_matriz(int endereço_mat(a0)) -> zera todas as 256 posições da matriz
limpa_matriz:
	li	t0, 0			# contador = 0
	li	t1, 256			# total de células

limpa_matriz_loop:
	bge	t0, t1, limpa_matriz_fim

	add	t2, a0, t0		# endereço da célula atual
	sb	zero, 0(t2)		# escreve 0 na célula

	addi	t0, t0, 1		# contador++
	j	limpa_matriz_loop

limpa_matriz_fim:
	ret

#função void proxima_geracao(int origem(a0), int destino(a1))
#calcula a próxima geração da matriz origem e salva na matriz destino
proxima_geracao:
	# salva registradores importantes
	addi	sp, sp, -32
	sw	ra, 28(sp)
	sw	s0, 24(sp)
	sw	s1, 20(sp)
	sw	s2, 16(sp)
	sw	s3, 12(sp)
	sw	s4, 8(sp)
	sw	s5, 4(sp)

	# guarda argumentos
	mv	s0, a0			# s0 = matriz origem
	mv	s1, a1			# s1 = matriz destino

	# primeiro limpa a matriz destino
	mv	a0, s1
	jal	ra, limpa_matriz

	li	s2, 0			# s2 = i

proxima_loop_i:
	li	t0, 16
	bge	s2, t0, proxima_fim

	li	s3, 0			# s3 = j

proxima_loop_j:
	li	t0, 16
	bge	s3, t0, proxima_pxm_linha

	# conta vizinhos da célula origem[i][j]
	mv	a0, s2
	mv	a1, s3
	mv	a2, s0
	jal	ra, conta_vizinhos
	mv	s4, a0			# s4 = quantidade de vizinhos vivos

	# lê estado atual da célula origem[i][j]
	mv	a0, s2
	mv	a1, s3
	mv	a2, s0
	jal	ra, readm
	mv	s5, a0			# s5 = estado atual da célula

	# aplica regras do Jogo da Vida
	beq	s5, zero, proxima_celula_morta

	# caso célula esteja viva:
	# sobrevive se tiver 2 ou 3 vizinhos
	li	t0, 2
	beq	s4, t0, proxima_celula_viva_destino

	li	t0, 3
	beq	s4, t0, proxima_celula_viva_destino

	# caso contrário morre
	j	proxima_pxm_coluna

proxima_celula_morta:
	# caso célula esteja morta:
	# nasce se tiver exatamente 3 vizinhos
	li	t0, 3
	beq	s4, t0, proxima_celula_viva_destino

	# caso contrário continua morta
	j	proxima_pxm_coluna

proxima_celula_viva_destino:
	# como a matriz destino foi limpa, write transforma 0 em 1
	mv	a0, s2
	mv	a1, s3
	mv	a2, s1
	jal	ra, write

proxima_pxm_coluna:
	addi	s3, s3, 1		# j++
	j	proxima_loop_j

proxima_pxm_linha:
	addi	s2, s2, 1		# i++
	j	proxima_loop_i

proxima_fim:
	# restaura registradores
	lw	s5, 4(sp)
	lw	s4, 8(sp)
	lw	s3, 12(sp)
	lw	s2, 16(sp)
	lw	s1, 20(sp)
	lw	s0, 24(sp)
	lw	ra, 28(sp)
	addi	sp, sp, 32

	ret
	
#função int compara_matrizes(int matA(a0), int matB(a1)) -> retorna 1 em a0 se as matrizes forem iguais ou retorna 0 em a0 se forem diferentes
compara_matrizes:
	li	t0, 0			# contador = 0
	li	t1, 256			# total de células

compara_loop:
	bge	t0, t1, compara_iguais

	# lê matA[posição]
	add	t2, a0, t0
	lb	t3, 0(t2)

	# lê matB[posição]
	add	t2, a1, t0
	lb	t4, 0(t2)

	# se forem diferentes, não há equilíbrio
	bne	t3, t4, compara_diferentes

	addi	t0, t0, 1
	j	compara_loop

compara_iguais:
	li	a0, 1
	ret

compara_diferentes:
	li	a0, 0
	ret