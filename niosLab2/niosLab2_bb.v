
module niosLab2 (
	clk_clk,
	pio_1_switchs_export,
	pio_2_button_export,
	pio_3_motor_export,
	reset_reset_n,
	leds_name);	

	input		clk_clk;
	input	[3:0]	pio_1_switchs_export;
	input		pio_2_button_export;
	output	[3:0]	pio_3_motor_export;
	input		reset_reset_n;
	output	[3:0]	leds_name;
endmodule
