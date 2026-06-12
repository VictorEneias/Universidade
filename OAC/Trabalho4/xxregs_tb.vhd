library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
 
entity tb_XREGS is
end tb_XREGS;
 
architecture test of tb_XREGS is
 
    constant WSIZE : natural := 32;
    constant CLK_PERIOD : time := 10 ns;
 
    signal clk  : std_logic := '0';
    signal wren : std_logic := '0';
    signal rs1, rs2, rd : std_logic_vector(4 downto 0) := (others => '0');
    signal data : std_logic_vector(WSIZE-1 downto 0) := (others => '0');
    signal ro1, ro2 : std_logic_vector(WSIZE-1 downto 0);
 
    signal fim : boolean := false;  -- sinaliza fim da simulacao
 
begin
 
    -- Instancia do DUT (Device Under Test)
    DUT: entity work.XREGS
        generic map (WSIZE => WSIZE)
        port map (
            clk  => clk,
            wren => wren,
            rs1  => rs1,
            rs2  => rs2,
            rd   => rd,
            data => data,
            ro1  => ro1,
            ro2  => ro2
        );
 
    -- Geracao do clock (para quando fim = true)
    clk_gen: process
    begin
        while not fim loop
            clk <= '0';
            wait for CLK_PERIOD / 2;
            clk <= '1';
            wait for CLK_PERIOD / 2;
        end loop;
        wait;
    end process;
 
    -- Processo de estimulo e verificacao
    stim: process
        variable valor_esperado : std_logic_vector(WSIZE-1 downto 0);
    begin


        wren <= '1';
        for i in 0 to 31 loop
            rd   <= std_logic_vector(to_unsigned(i, 5));
            data <= std_logic_vector(to_unsigned(i * 10, WSIZE));
            wait until rising_edge(clk);
            wait for 1 ns;  -- pequena folga apos a borda
        end loop;
        wren <= '0';
 
        for i in 0 to 31 loop
            rs1 <= std_logic_vector(to_unsigned(i, 5));
            rs2 <= std_logic_vector(to_unsigned(i, 5));
            wait for 2 ns;  -- tempo para a leitura combinacional
 
            if i = 0 then
                -- registrador 0 deve ser sempre zero
                valor_esperado := (others => '0');
            else
                valor_esperado := std_logic_vector(to_unsigned(i * 10, WSIZE));
            end if;
 
            assert ro1 = valor_esperado
                report "ERRO em ro1: registrador " & integer'image(i) &
                       " leu valor incorreto"
                severity error;
 
            assert ro2 = valor_esperado
                report "ERRO em ro2: registrador " & integer'image(i) &
                       " leu valor incorreto"
                severity error;
        end loop;


        wren <= '1';
        rd   <= "00000";
        data <= x"DEADBEEF";
        wait until rising_edge(clk);
        wait for 1 ns;
        wren <= '0';
 
        rs1 <= "00000";
        rs2 <= "00000";
        wait for 2 ns;
 
        assert ro1 = std_logic_vector(to_unsigned(0, WSIZE))
            report "ERRO: registrador 0 foi alterado (ro1)!"
            severity error;
 
        assert ro2 = std_logic_vector(to_unsigned(0, WSIZE))
            report "ERRO: registrador 0 foi alterado (ro2)!"
            severity error;
 
        report "Fim da simulacao: todos os testes executados."
            severity note;
 
        fim <= true;
        wait;
    end process;
 
end test;
