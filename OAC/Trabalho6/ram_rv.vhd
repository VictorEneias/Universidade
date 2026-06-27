library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ram_rv is
    port (
        clck    : in  std_logic;         
        we      : in  std_logic;         
        byte_en : in  std_logic;         
        sgn_en  : in  std_logic;         
        address : in  std_logic_vector;  
        datain  : in  std_logic_vector;  
        dataout : out std_logic_vector   
    );
end entity ram_rv;

architecture RTL of ram_rv is
    type mem_type is array (0 to (2**address'length)-1)
                     of std_logic_vector(7 downto 0);

    signal mem : mem_type := (others => (others => '0'));
begin

    process(clck)
        variable a : integer;
    begin
        if rising_edge(clck) then
            if we = '1' then
                a := to_integer(unsigned(address));
                if byte_en = '1' then
                    mem(a) <= datain(7 downto 0);
                else
                    mem(a)     <= datain(7  downto 0);
                    mem(a + 1) <= datain(15 downto 8);
                    mem(a + 2) <= datain(23 downto 16);
                    mem(a + 3) <= datain(31 downto 24);
                end if;
            end if;
        end if;
    end process;

    process(all)
        variable a    : integer;
        variable byte : std_logic_vector(7 downto 0);
        variable word : std_logic_vector(31 downto 0);
    begin
        a := to_integer(unsigned(address));
        if byte_en = '1' then
            byte := mem(a);
            if sgn_en = '1' then
                dataout <= std_logic_vector(resize(signed(byte), dataout'length));
            else
                dataout <= std_logic_vector(resize(unsigned(byte), dataout'length));
            end if;
        else
            word := mem(a + 3) & mem(a + 2) & mem(a + 1) & mem(a);
            dataout <= word;
        end if;
    end process;

end architecture RTL;