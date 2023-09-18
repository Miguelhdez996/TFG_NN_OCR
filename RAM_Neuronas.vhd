--Autor: Miguel Ángel Linares Hernández
--TFG: Implementacioón de una red neuronal en una FPGA
--Código para la implementación de una memoria RAM en VHDL
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity RAM_Neuronas is
    Port (
        CK : in std_logic;               -- Señal de reloj
        Dir : in std_logic_vector(9 downto 0); -- Dirección de 10 bits
        WR_EN : in std_logic;      -- Habilitación de escritura
        dato_entra : in std_logic_vector(15 downto 0); -- Datos de entrada de 16 bits
        dato_sale : out std_logic_vector(15 downto 0) -- Datos de salida de 16 bits
    );
end RAM_Neuronas;

architecture Behavioral of RAM_Neuronas is
    type ram_array is array (0 to 1023) of std_logic_vector(15 downto 0); -- Memoria RAM de 1024 direcciones x 16 bits
    signal ram_data : ram_array;

begin
    process (CK)
    begin
        if rising_edge(CK) then
            if WR_EN = '1' then
                -- Escritura: Escribe los datos de entrada en la dirección especificada
                ram_data(to_integer(unsigned(address))) <= data_in;
            else
                -- Lectura: Lee los datos en la dirección especificada y los coloca en data_out
                dato_sale <= ram_data(to_integer(unsigned(Dir)));
            end if;
        end if;
    end process;

end Behavioral;
