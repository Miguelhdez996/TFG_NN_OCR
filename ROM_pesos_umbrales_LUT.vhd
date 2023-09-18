--Autor: Miguel Ángel Linares Hernández
--TFG: Implementacioón de una red neuronal en una FPGA
--Código para la implementación de una memoria ROM en VHDL
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ROM_W_U_LUT is
    Port (
        CK : in std_logic;
        Dir: in std_logic_vector(15 downto 0); -- Dirección de 16 bits
        dato_sale : out std_logic_vector(15 downto 0) -- Datos de salida de 16 bits
    );
end ROM_W_U_LUT; 

architecture Behavioral of ROM_W_U_LUT is
    type ROM_Array is array (0 to 65535) of std_logic_vector(15 downto 0); -- 64k direcciones, profundidad de 16 bits
    signal rom_data : ROM_Array;

begin
    -- Inicializa los datos de la memoria ROM con tus valores deseados
    process
    begin
        -- Se rellena rom_data con los valores de los umbrales en esta parte
        -- Por ejemplo:
        rom_data(0) <= "0000000000000001"; -- Dirección 0
        rom_data(1) <= "0000000000000010"; -- Dirección 1
        -- ...
        rom_data(65535) <= "1111111111111111"; -- Dirección 65535
    end process;

    -- Acceso a la memoria ROM
    process(CK)
    begin
        if rising_edge(CK) then
            dato_sale <= rom_data(to_integer(unsigned(Dir)));
        end if;
    end process;

end Behavioral;
