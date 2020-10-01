library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;
use work.all;

entity peripheral_motor is
    generic (
        LEN  : natural := 4
    );
    port (
        -- Gloabals
        clk                : in  std_logic                     := '0';             
        reset              : in  std_logic                     := '0';             

        -- I/Os
        motor_phases               : out std_logic_vector(LEN - 1 downto 0) := (others => '0');

        -- Avalion Memmory Mapped Slave
        avs_address     : in  std_logic_vector(3 downto 0)  := (others => '0'); 
        avs_read        : in  std_logic                     := '0';             
        avs_readdata    : out std_logic_vector(31 downto 0) := (others => '0'); 
        avs_write       : in  std_logic                     := '0';             
        avs_writedata   : in  std_logic_vector(31 downto 0) := (others => '0')
    );
end entity peripheral_motor;

architecture rtl of peripheral_motor is

component stepmotor IS
    PORT (
        -- Gloabals
        clk : IN std_logic;
        en : IN std_logic; -- 1 on/ 0 of
        dir : IN std_logic; -- 1 clock wise
        vel : IN std_logic_vector(1 DOWNTO 0); -- 00: low / 11: fast
        quarter : IN std_logic;
        phases : OUT std_logic_vector(3 DOWNTO 0)  );
END component;

signal en, dir, quarter : std_logic := '0';
signal vel : std_logic_vector(1 downto 0) := (others => '0');

signal config  : std_logic_vector(31 downto 0) := (others => '0');


begin

  u1: stepmotor port map (
	clk => clk,
	en  => en,
	dir => dir,
	vel => vel,
	quarter => quarter,
	phases => motor_phases );
	
	en  <= config(0);
	dir <= config(1);

  process(clk)
  begin
    if(rising_edge(clk)) then
        if(avs_address = "0000") then                  -- REG_DATA
            if(avs_write = '1') then
             config  <= avs_writedata;
            end if;
				if(avs_read = '1') then
					avs_readdata <= config;
				end if;
        end if;
    end if;
  end process;

end rtl;