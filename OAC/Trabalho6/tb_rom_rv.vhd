library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_rom_rv is
end entity tb_rom_rv;

architecture sim of tb_rom_rv is
    constant ADDR_WIDTH : integer := 11;
    constant DATA_WIDTH : integer := 32;

    signal address : std_logic_vector(ADDR_WIDTH-1 downto 0) := (others => '0');
    signal dataout : std_logic_vector(DATA_WIDTH-1 downto 0);
begin

    dut: entity work.rom_rv
        port map (
            address => address,
            dataout => dataout
        );

    stim: process
    begin
        for i in 0 to 9 loop
            address <= std_logic_vector(to_unsigned(i, ADDR_WIDTH));
            wait for 10 ns;
            report "ROM[" & integer'image(i) & "] = 0x" & to_hstring(dataout);
        end loop;
        wait;
    end process;

end architecture sim;