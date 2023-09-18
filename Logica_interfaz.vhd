--Autor: Miguel Ángel Linares Hernández
--TFG: Implementacioón de una red neuronal en una FPGA
--Código para la implementación del bloque de interfaz lógica
--entre las distintas capas en VHDL
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Forward_Ent is
    Port (
        clk : in std_logic;
        reset : in std_logic;
        input_ram_data : in std_logic_vector(15 downto 0); -- Datos de entrada desde la RAM
        weights_rom_data : in std_logic_vector(15 downto 0); -- Datos de pesos desde la ROM
        biases_rom_data : in std_logic_vector(15 downto 0); -- Datos de umbrales desde la ROM
        lut_rom_data : in std_logic_vector(15 downto 0); -- Datos de la LUT desde la ROM
        output_ram_data : out std_logic_vector(15 downto 0) -- Datos de salida hacia la RAM
    );
end Forward_Ent;

architecture Forward_Beh of Forward_Ent is
    signal Sum_pond : std_logic_vector(15 downto 0);
    signal Sal_Act : std_logic_vector(15 downto 0);
begin
    process (clk, reset)
        variable acc : integer := 0; -- Acumulador para sumar ponderadas
        variable addr : integer := 0; -- Dirección de acceso a RAM y ROM
    begin
        if reset = '1' then
            -- Reiniciar el acumulador y la dirección al detectar un reset
            acc := 0;
            addr := 0;
        elsif rising_edge(clk) then
            -- Acceder a los datos de entrada desde la RAM y los pesos desde la ROM
            input_ram_data <= ram_read(addr);
            weights_rom_data <= rom_read(addr);

            -- Realizar la multiplicación y suma ponderada
            acc := acc + (to_integer(unsigned(input_ram_data)) * to_integer(unsigned(weights_rom_data)));

            -- Avanzar a la siguiente dirección
            addr := addr + 1;

            -- Comprobar si se ha completado una capa de neuronas
            if addr = NEURONS_PER_LAYER then
                -- Acceder a los datos de umbrales desde la ROM
                biases_rom_data <= rom_read(addr);
                -- Aplicar el umbral y la función de activación
                activation_output <= apply_threshold(acc, biases_rom_data);
                -- Escribir la salida en la RAM
                output_ram_data <= activation_output;

                -- Reiniciar el acumulador y la dirección para la siguiente capa
                acc := 0;
                addr := 0;
            end if;
        end if;
    end process;
