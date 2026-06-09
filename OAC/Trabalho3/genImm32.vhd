library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity genImm32 is
    port (
        instr : in  std_logic_vector(31 downto 0);
        imm32 : out signed(31 downto 0)
    );
end entity genImm32;

architecture rtl of genImm32 is
begin

    process(instr)
        variable opcode : std_logic_vector(6 downto 0);
        variable funct3 : std_logic_vector(2 downto 0);
    begin
        opcode := instr(6 downto 0);
        funct3 := instr(14 downto 12);

        case opcode is

            -- R-type
            -- opcode = 0x33 = "0110011"
            -- Não possui imediato.
            when "0110011" =>
                imm32 <= to_signed(0, 32);

            -- I-type: loads
            -- opcode = 0x03 = "0000011"
            -- imm(11:0) = instr(31:20), com extensão de sinal.
            when "0000011" =>
                imm32 <= resize(signed(instr(31 downto 20)), 32);

            -- I-type: operações imediatas
            -- opcode = 0x13 = "0010011"
            --
            -- Caso especial I-type*:
            -- instruções de deslocamento usam shamt:
            -- imm(4:0) = instr(24:20), com zeros nos bits superiores.
            --
            -- Para as demais instruções I-type:
            -- imm(11:0) = instr(31:20), com extensão de sinal.
            when "0010011" =>
                if (funct3 = "001") or (funct3 = "101") then
                    -- slli, srli, srai: imediato é o campo shamt
                    imm32 <= to_signed(to_integer(unsigned(instr(24 downto 20))), 32);
                else
                    -- addi, xori, ori, andi, slti, etc.
                    imm32 <= resize(signed(instr(31 downto 20)), 32);
                end if;

            -- I-type: jalr
            -- opcode = 0x67 = "1100111"
            -- imm(11:0) = instr(31:20), com extensão de sinal.
            when "1100111" =>
                imm32 <= resize(signed(instr(31 downto 20)), 32);

            -- S-type
            -- opcode = 0x23 = "0100011"
            -- imm(11:0) = instr(31:25) & instr(11:7), com extensão de sinal.
            when "0100011" =>
                imm32 <= resize(signed(instr(31 downto 25) & instr(11 downto 7)), 32);

            -- SB-type
            -- opcode = 0x63 = "1100011"
            -- imm(12:1) = instr(31) & instr(7) & instr(30:25) & instr(11:8)
            -- imm(0) = 0
            -- com extensão de sinal.
            when "1100011" =>
                imm32 <= resize(
                    signed(instr(31) & instr(7) & instr(30 downto 25) & instr(11 downto 8) & '0'),
                    32
                );

            -- U-type
            -- opcode = 0x37 = "0110111"
            -- imm(31:12) = instr(31:12)
            -- imm(11:0) = 0
            when "0110111" =>
                imm32 <= signed(instr(31 downto 12) & "000000000000");

            -- UJ-type
            -- opcode = 0x6F = "1101111"
            -- imm(20:1) = instr(31) & instr(19:12) & instr(20) & instr(30:21)
            -- imm(0) = 0
            -- com extensão de sinal.
            when "1101111" =>
                imm32 <= resize(
                    signed(instr(31) & instr(19 downto 12) & instr(20) & instr(30 downto 21) & '0'),
                    32
                );

            -- Caso opcode não reconhecido.
            when others =>
                imm32 <= to_signed(0, 32);

        end case;
    end process;

end architecture rtl;