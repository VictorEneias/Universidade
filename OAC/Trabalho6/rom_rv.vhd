library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;

entity rom_rv is
    port (
        address : in  std_logic_vector;
        dataout : out std_logic_vector    
    );
end entity rom_rv;

architecture RTL of rom_rv is

    type rom_type is array (0 to (2**address'length)-1)
                     of std_logic_vector(dataout'range);

    impure function carrega_rom(nome_arquivo : string) return rom_type is
        file     arq      : text open read_mode is nome_arquivo;
        variable linha    : line;
        variable palavra  : std_logic_vector(dataout'range);
        variable conteudo : rom_type := (others => (others => '0'));
        variable i        : integer := 0;
    begin
        while (not endfile(arq)) and (i < conteudo'length) loop
            readline(arq, linha);
            hread(linha, palavra);
            conteudo(i) := palavra;
            i := i + 1;
        end loop;
    end function;

    signal ROM : rom_type := carrega_rom("instrucoes.txt");

begin
    dataout <= ROM(to_integer(unsigned(address)));
end architecture RTL;