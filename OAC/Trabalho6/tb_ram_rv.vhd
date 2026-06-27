library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_ram_rv is
end entity tb_ram_rv;

architecture sim of tb_ram_rv is
    constant ADDR_WIDTH : integer := 13;
    constant DATA_WIDTH : integer := 32;
    constant clk_period : time    := 10 ns;

    signal clck    : std_logic := '0';
    signal we      : std_logic := '0';
    signal byte_en : std_logic := '0';
    signal sgn_en  : std_logic := '0';
    signal address : std_logic_vector(ADDR_WIDTH-1 downto 0) := (others => '0');
    signal datain  : std_logic_vector(DATA_WIDTH-1 downto 0) := (others => '0');
    signal dataout : std_logic_vector(DATA_WIDTH-1 downto 0);

    signal sim_done : boolean := false;
begin

    dut: entity work.ram_rv
        port map (
            clck => clck, we => we, byte_en => byte_en, sgn_en => sgn_en,
            address => address, datain => datain, dataout => dataout
        );

    clk_gen: process
    begin
        while not sim_done loop
            clck <= '0';
            wait for clk_period / 2;
            clck <= '1';
            wait for clk_period / 2;
        end loop;
        wait;
    end process;

    stim: process

        procedure escreve_word(addr : integer; dado : std_logic_vector) is
        begin
            address <= std_logic_vector(to_unsigned(addr, ADDR_WIDTH));
            datain  <= dado;
            byte_en <= '0';
            we      <= '1';
            wait until rising_edge(clck);
            we      <= '0';
        end procedure;

        procedure escreve_byte(addr : integer; dado : std_logic_vector) is
        begin
            address <= std_logic_vector(to_unsigned(addr, ADDR_WIDTH));
            datain  <= dado;
            byte_en <= '1';
            we      <= '1';
            wait until rising_edge(clck);
            we      <= '0';
        end procedure;

        procedure le_word(addr : integer) is
        begin
            we      <= '0';
            byte_en <= '0';
            address <= std_logic_vector(to_unsigned(addr, ADDR_WIDTH));
            wait for clk_period;
            report "le_word ["  & integer'image(addr) & "] = 0x" & to_hstring(dataout);
        end procedure;

        procedure le_byte(addr : integer; com_sinal : std_logic) is
        begin
            we      <= '0';
            byte_en <= '1';
            sgn_en  <= com_sinal;
            address <= std_logic_vector(to_unsigned(addr, ADDR_WIDTH));
            wait for clk_period;
            report "le_byte ["  & integer'image(addr) & "] sgn=" &
                   std_logic'image(com_sinal) & " = 0x" & to_hstring(dataout);
        end procedure;

    begin
        wait for clk_period;

        escreve_word(0, x"DEADBEEF");
        escreve_word(4, x"12345678");
        le_word(0);
        le_word(4);

        le_byte(0, '0');
        le_byte(0, '1');
        le_byte(3, '0');
        le_byte(3, '1');

        le_byte(4, '0');
        le_byte(4, '1');

        escreve_byte(8, x"000000AB");
        le_byte(8, '0');
        le_byte(8, '1');

        wait for clk_period;
        sim_done <= true;
        wait;
    end process;

end architecture sim;