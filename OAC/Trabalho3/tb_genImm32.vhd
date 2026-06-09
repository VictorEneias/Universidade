library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_genImm32 is
end entity tb_genImm32;

architecture sim of tb_genImm32 is

    signal instr : std_logic_vector(31 downto 0);
    signal imm32 : signed(31 downto 0);

begin

    dut: entity work.genImm32
        port map (
            instr => instr,
            imm32 => imm32
        );

    stimulus: process

        procedure check_imm(
            constant nome     : in string;
            constant codigo   : in std_logic_vector(31 downto 0);
            constant esperado : in signed(31 downto 0)
        ) is
        begin
            instr <= codigo;
            wait for 10 ns;

            assert imm32 = esperado
                report "ERRO em " & nome &
                       ". Esperado = " & integer'image(to_integer(esperado)) &
                       ", obtido = " & integer'image(to_integer(imm32))
                severity error;

            report "OK: " & nome &
                   ". Imediato = " & integer'image(to_integer(imm32))
                severity note;
        end procedure;

    begin

        -- Testes conforme a tabela do enunciado.

        check_imm(
            "add t0, zero, zero - R-type",
            x"000002B3",
            to_signed(0, 32)
        );

        check_imm(
            "lw t0, 16(zero) - I-type",
            x"01002283",
            to_signed(16, 32)
        );

        check_imm(
            "addi t1, zero, -100 - I-type",
            x"F9C00313",
            to_signed(-100, 32)
        );

        check_imm(
            "xori t0, t0, -1 - I-type",
            x"FFF2C293",
            to_signed(-1, 32)
        );

        check_imm(
            "addi t1, zero, 354 - I-type",
            x"16200313",
            to_signed(354, 32)
        );

        check_imm(
            "jalr zero, zero, 0x18 - I-type",
            x"01800067",
            to_signed(24, 32)
        );

        check_imm(
            "srai t1, t2, 10 - I-type*",
            x"40A3D313",
            to_signed(10, 32)
        );

        check_imm(
            "lui s0, 2 - U-type",
            x"00002437",
            to_signed(8192, 32)
        );

        check_imm(
            "sw t0, 60(s0) - S-type",
            x"02542E23",
            to_signed(60, 32)
        );

        check_imm(
            "bne t0, t0, main - SB-type",
            x"FE5290E3",
            to_signed(-32, 32)
        );

        check_imm(
            "jal rot - UJ-type",
            x"00C000EF",
            to_signed(12, 32)
        );

        report "Todos os testes foram executados." severity note;

        wait;

    end process;

end architecture sim;