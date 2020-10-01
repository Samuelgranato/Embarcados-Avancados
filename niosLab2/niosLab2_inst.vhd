	component niosLab2 is
		port (
			clk_clk              : in  std_logic                    := 'X';             -- clk
			leds_name            : out std_logic_vector(3 downto 0);                    -- name
			motor_name           : out std_logic_vector(3 downto 0);                    -- name
			pio_1_switchs_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			pio_2_button_export  : in  std_logic                    := 'X';             -- export
			reset_reset_n        : in  std_logic                    := 'X'              -- reset_n
		);
	end component niosLab2;

	u0 : component niosLab2
		port map (
			clk_clk              => CONNECTED_TO_clk_clk,              --           clk.clk
			leds_name            => CONNECTED_TO_leds_name,            --          leds.name
			motor_name           => CONNECTED_TO_motor_name,           --         motor.name
			pio_1_switchs_export => CONNECTED_TO_pio_1_switchs_export, -- pio_1_switchs.export
			pio_2_button_export  => CONNECTED_TO_pio_2_button_export,  --  pio_2_button.export
			reset_reset_n        => CONNECTED_TO_reset_reset_n         --         reset.reset_n
		);

