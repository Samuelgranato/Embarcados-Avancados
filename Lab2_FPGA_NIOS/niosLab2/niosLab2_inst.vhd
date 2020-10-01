	component niosLab2 is
		port (
			clk_clk              : in  std_logic                    := 'X';             -- clk
			pio_1_switchs_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			pio_2_button_export  : in  std_logic                    := 'X';             -- export
			pio_3_motor_export   : out std_logic_vector(3 downto 0);                    -- export
			reset_reset_n        : in  std_logic                    := 'X';             -- reset_n
			leds_name            : out std_logic_vector(3 downto 0)                     -- name
		);
	end component niosLab2;

	u0 : component niosLab2
		port map (
			clk_clk              => CONNECTED_TO_clk_clk,              --           clk.clk
			pio_1_switchs_export => CONNECTED_TO_pio_1_switchs_export, -- pio_1_switchs.export
			pio_2_button_export  => CONNECTED_TO_pio_2_button_export,  --  pio_2_button.export
			pio_3_motor_export   => CONNECTED_TO_pio_3_motor_export,   --   pio_3_motor.export
			reset_reset_n        => CONNECTED_TO_reset_reset_n,        --         reset.reset_n
			leds_name            => CONNECTED_TO_leds_name             --          leds.name
		);

