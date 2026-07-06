library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- ULA do RISC-V de 32 bits.
--
-- Entradas de dados: A e B (WSIZE bits).
-- Saida de dados:    Z     (WSIZE bits).
-- Selecao:           opcode (4 bits) - escolhe a operacao.
-- Saida de condicao: cond  - vale '1' quando a comparacao testada e
--                            verdadeira e '0' caso contrario. Para as
--                            operacoes que nao sao de comparacao cond fica
--                            inativo ('0').
entity ulaRV is
    generic (WSIZE : natural := 32);
    port (
        opcode : in  std_logic_vector(3 downto 0);
        A, B   : in  std_logic_vector(WSIZE-1 downto 0);
        Z      : out std_logic_vector(WSIZE-1 downto 0);
        cond   : out std_logic
    );
end entity ulaRV;

architecture behavioral of ulaRV is

    -- Codigos das operacoes (opcode).
    constant ADD_OP  : std_logic_vector(3 downto 0) := "0000";
    constant SUB_OP  : std_logic_vector(3 downto 0) := "0001";
    constant AND_OP  : std_logic_vector(3 downto 0) := "0010";
    constant OR_OP   : std_logic_vector(3 downto 0) := "0011";
    constant XOR_OP  : std_logic_vector(3 downto 0) := "0100";
    constant SLL_OP  : std_logic_vector(3 downto 0) := "0101";
    constant SRL_OP  : std_logic_vector(3 downto 0) := "0110";
    constant SRA_OP  : std_logic_vector(3 downto 0) := "0111";
    constant SLT_OP  : std_logic_vector(3 downto 0) := "1000";
    constant SLTU_OP : std_logic_vector(3 downto 0) := "1001";
    constant SGE_OP  : std_logic_vector(3 downto 0) := "1010";
    constant SGEU_OP : std_logic_vector(3 downto 0) := "1011";
    constant SEQ_OP  : std_logic_vector(3 downto 0) := "1100";
    constant SNE_OP  : std_logic_vector(3 downto 0) := "1101";

begin

    process (opcode, A, B)
        -- Quantidade de bits de deslocamento: apenas os bits menos
        -- significativos de B sao usados (5 bits para 32 bits).
        variable shamt : natural;
    begin
        -- Valores padrao: evitam a inferencia de latch.
        Z    <= (others => '0');
        cond <= '0';

        shamt := to_integer(unsigned(B(4 downto 0)));

        case opcode is

            when ADD_OP =>
                Z <= std_logic_vector(signed(A) + signed(B));

            when SUB_OP =>
                Z <= std_logic_vector(signed(A) - signed(B));

            when AND_OP =>
                Z <= A and B;

            when OR_OP =>
                Z <= A or B;

            when XOR_OP =>
                Z <= A xor B;

            when SLL_OP =>
                Z <= std_logic_vector(shift_left(unsigned(A), shamt));

            when SRL_OP =>
                Z <= std_logic_vector(shift_right(unsigned(A), shamt));

            when SRA_OP =>
                Z <= std_logic_vector(shift_right(signed(A), shamt));

            -- Set less than (com sinal): Z = 1 se A < B.
            when SLT_OP =>
                if signed(A) < signed(B) then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            -- Set less than (sem sinal): Z = 1 se A < B.
            when SLTU_OP =>
                if unsigned(A) < unsigned(B) then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            -- Set greater or equal (com sinal): Z = 1 se A >= B.
            when SGE_OP =>
                if signed(A) >= signed(B) then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            -- Set greater or equal (sem sinal): Z = 1 se A >= B.
            when SGEU_OP =>
                if unsigned(A) >= unsigned(B) then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            -- Set equal: Z = 1 se A == B.
            when SEQ_OP =>
                if A = B then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            -- Set not equal: Z = 1 se A != B.
            when SNE_OP =>
                if A /= B then
                    Z    <= std_logic_vector(to_unsigned(1, WSIZE));
                    cond <= '1';
                else
                    Z    <= (others => '0');
                    cond <= '0';
                end if;

            when others =>
                Z    <= (others => '0');
                cond <= '0';

        end case;
    end process;

end architecture behavioral;
