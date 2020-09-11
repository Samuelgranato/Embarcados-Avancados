
module niosLab2 (
	clk_clk,
	pio_0_leds_export,
	pio_1_switchs_export,
	pio_2_button_export,
	pio_3_motor_export,
	reset_reset_n);	

	input		clk_clk;
	output	[5:0]	pio_0_leds_export;
	input	[3:0]	pio_1_switchs_export;
	input		pio_2_button_export;
	output	[3:0]	pio_3_motor_export;
	input		reset_reset_n;
endmodule
