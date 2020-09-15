library IEEE;
use IEEE.std_logic_1164.all;

entity LAB2_FPGA_NIOS is
    port (
        -- Gloabals
        fpga_clk_50        : in  std_logic;             -- clock.clk

        -- I/Os
        fpga_led_pio       : out std_logic_vector(5 downto 0);
		stepmotor_quarter	: in  std_logic;
		stepmotor_switch 	: in  std_logic_vector(3 downto 0);
        stepmotor_pio 		: out std_logic_vector(3 downto 0)
  );
end entity LAB2_FPGA_NIOS;

architecture rtl of LAB2_FPGA_NIOS is

    component niosLab2 is
        port (
            clk_clk              : in  std_logic                    := 'X';             -- clk
            pio_0_leds_export    : out std_logic_vector(5 downto 0);                    -- export
            pio_1_switchs_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
            pio_2_button_export  : in  std_logic                    := 'X';             -- export
            reset_reset_n        : in  std_logic                    := 'X';             -- reset_n
			pio_3_motor_export   : out std_logic_vector(3 downto 0)
        );
    end component niosLab2;

begin

    u0 : component niosLab2
        port map (
            clk_clk              => fpga_clk_50,        				--  clk.clk
            pio_0_leds_export    => fpga_led_pio,    					--  pio_0_leds.export
            pio_1_switchs_export => stepmotor_switch, 					--  pio_1_switchs.export
            pio_2_button_export  => not stepmotor_quarter,  				--  pio_2_button.export
			reset_reset_n 		 => '1',            					--  reset.reset_n
			pio_3_motor_export   => stepmotor_pio     --   pio_3_motor.export
        );

end rtl;