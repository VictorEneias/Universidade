library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ula_tb is
end entity ula_tb;

architecture tb_arch of ula_tb is

    constant WSIZE : natural := 32;

    -- Sinais de estimulo e observacao.
    signal opcode : std_logic_vector(3 downto 0);
    signal A, B   : std_logic_vector(WSIZE-1 downto 0);
    signal Z      : std_logic_vector(WSIZE-1 downto 0);
    signal cond   : std_logic;

    -- Declaracao do componente ULA.
    component ulaRV is
        generic (WSIZE : natural := 32);
        port (
            opcode : in  std_logic_vector(3 downto 0);
            A, B   : in  std_logic_vector(WSIZE-1 downto 0);
            Z      : out std_logic_vector(WSIZE-1 downto 0);
            cond   : out std_logic
        );
    end component;

    -- Codigos das operacoes.
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

    -- Instanciacao da ULA (dispositivo sob teste).
    dut: ulaRV
        generic map (WSIZE => WSIZE)
        port map (
            opcode => opcode,
            A      => A,
            B      => B,
            Z      => Z,
            cond   => cond
        );

    stimulus: process

        constant PERIODO : time := 10 ns;

        -- Aplica um estimulo e confere o resultado esperado em Z e cond.
        procedure check(
            constant nome      : in string;
            constant op        : in std_logic_vector(3 downto 0);
            constant a_in      : in std_logic_vector(WSIZE-1 downto 0);
            constant b_in      : in std_logic_vector(WSIZE-1 downto 0);
            constant z_esp     : in std_logic_vector(WSIZE-1 downto 0);
            constant cond_esp  : in std_logic
        ) is
        begin
            opcode <= op;
            A      <= a_in;
            B      <= b_in;
            wait for PERIODO;

            assert Z = z_esp
                report "ERRO em " & nome & ": Z obtido = " &
                       integer'image(to_integer(signed(Z))) &
                       ", esperado = " &
                       integer'image(to_integer(signed(z_esp)))
                severity error;

            assert cond = cond_esp
                report "ERRO em " & nome & ": cond obtido = " &
                       std_logic'image(cond) & ", esperado = " &
                       std_logic'image(cond_esp)
                severity error;

            report "OK: " & nome severity note;
        end procedure;

    begin

        ------------------------------------------------------------------
        -- ADD: resultado positivo, negativo e zero.
        ------------------------------------------------------------------
        check("ADD positivo (10 + 5 = 15)",
              ADD_OP, x"0000000A", x"00000005", x"0000000F", '0');

        check("ADD negativo (-10 + 4 = -6)",
              ADD_OP, x"FFFFFFF6", x"00000004", x"FFFFFFFA", '0');

        check("ADD zero (-8 + 8 = 0)",
              ADD_OP, x"FFFFFFF8", x"00000008", x"00000000", '0');

        ------------------------------------------------------------------
        -- SUB: resultado positivo, negativo e zero.
        ------------------------------------------------------------------
        check("SUB positivo (20 - 5 = 15)",
              SUB_OP, x"00000014", x"00000005", x"0000000F", '0');

        check("SUB negativo (5 - 20 = -15)",
              SUB_OP, x"00000005", x"00000014", x"FFFFFFF1", '0');

        check("SUB zero (7 - 7 = 0)",
              SUB_OP, x"00000007", x"00000007", x"00000000", '0');

        ------------------------------------------------------------------
        -- Operacoes logicas.
        ------------------------------------------------------------------
        check("AND (0F0F & 00FF = 000F)",
              AND_OP, x"0F0F0F0F", x"00FF00FF", x"000F000F", '0');

        check("OR (0F0F | 00FF = 0FFF)",
              OR_OP,  x"0F0F0F0F", x"00FF00FF", x"0FFF0FFF", '0');

        check("XOR (0F0F ^ 00FF = 0FF0)",
              XOR_OP, x"0F0F0F0F", x"00FF00FF", x"0FF00FF0", '0');

        ------------------------------------------------------------------
        -- Deslocamentos (usa os 5 bits menos significativos de B).
        ------------------------------------------------------------------
        check("SLL (1 << 4 = 16)",
              SLL_OP, x"00000001", x"00000004", x"00000010", '0');

        check("SRL (0x80000000 >> 4 sem sinal = 0x08000000)",
              SRL_OP, x"80000000", x"00000004", x"08000000", '0');

        check("SRA (0x80000000 >> 4 com sinal = 0xF8000000)",
              SRA_OP, x"80000000", x"00000004", x"F8000000", '0');

        ------------------------------------------------------------------
        -- Comparacoes com sinal.
        ------------------------------------------------------------------
        check("SLT verdadeiro (-1 < 1)",
              SLT_OP, x"FFFFFFFF", x"00000001", x"00000001", '1');

        check("SLT falso (1 < -1)",
              SLT_OP, x"00000001", x"FFFFFFFF", x"00000000", '0');

        check("SGE verdadeiro (5 >= 5)",
              SGE_OP, x"00000005", x"00000005", x"00000001", '1');

        check("SGE falso (-1 >= 1)",
              SGE_OP, x"FFFFFFFF", x"00000001", x"00000000", '0');

        ------------------------------------------------------------------
        -- Comparacoes sem sinal.
        ------------------------------------------------------------------
        check("SLTU verdadeiro (1 < 0xFFFFFFFF)",
              SLTU_OP, x"00000001", x"FFFFFFFF", x"00000001", '1');

        check("SLTU falso (0xFFFFFFFF < 1)",
              SLTU_OP, x"FFFFFFFF", x"00000001", x"00000000", '0');

        check("SGEU verdadeiro (0xFFFFFFFF >= 1)",
              SGEU_OP, x"FFFFFFFF", x"00000001", x"00000001", '1');

        check("SGEU falso (1 >= 0xFFFFFFFF)",
              SGEU_OP, x"00000001", x"FFFFFFFF", x"00000000", '0');

        ------------------------------------------------------------------
        -- Igualdade / diferenca.
        ------------------------------------------------------------------
        check("SEQ verdadeiro (7 == 7)",
              SEQ_OP, x"00000007", x"00000007", x"00000001", '1');

        check("SEQ falso (7 == 8)",
              SEQ_OP, x"00000007", x"00000008", x"00000000", '0');

        check("SNE verdadeiro (7 != 8)",
              SNE_OP, x"00000007", x"00000008", x"00000001", '1');

        check("SNE falso (7 != 7)",
              SNE_OP, x"00000007", x"00000007", x"00000000", '0');

        report "Todos os testes da ULA foram executados." severity note;

        wait;

    end process;

end architecture tb_arch;
