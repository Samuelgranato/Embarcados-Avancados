--
-- Rafael C.
-- ref:
--   - https://www.intel.com/content/www/us/en/programmable/quartushelp/13.0/mergedProjects/hdl/vhdl/vhdl_pro_state_machines.htm
--   - https://www.allaboutcircuits.com/technical-articles/implementing-a-finite-state-machine-in-vhdl/
--   - https://www.digikey.com/eewiki/pages/viewpage.action?pageId=4096117

LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;

ENTITY stepmotor IS
    PORT (
        -- Gloabals
        clk : IN std_logic;

        -- controls
        en : IN std_logic; -- 1 on/ 0 of
        dir : IN std_logic; -- 1 clock wise
        vel : IN std_logic_vector(1 DOWNTO 0); -- 00: low / 11: fast
        quarter : IN std_logic;

        -- I/Os
        phases : OUT std_logic_vector(3 DOWNTO 0)
    );
END ENTITY stepmotor;

ARCHITECTURE rtl OF stepmotor IS

    TYPE STATE_TYPE IS (s0, s1, s2, s3);
    SIGNAL state : STATE_TYPE := s0;
    SIGNAL enable : std_logic := '0';
    SIGNAL topCounter : INTEGER RANGE 0 TO 50000000;

BEGIN

    PROCESS (clk)
    BEGIN
        IF (rising_edge(clk)) THEN
            CASE state IS
                WHEN s0 =>
                    IF (enable = '1') THEN
                        state <= s1;
                    END IF;
                WHEN s1 =>
                    IF (enable = '1') THEN
                        state <= s2;
                    END IF;
                WHEN s2 =>
                    IF (enable = '1') THEN
                        state <= s3;
                    END IF;
                WHEN s3 =>
                    IF (enable = '1') THEN
                        state <= s0;
                    END IF;
                WHEN OTHERS =>
                    state <= s0;
            END CASE;
        END IF;
    END PROCESS;

    PROCESS (state)

    BEGIN
        IF (dir = '1') THEN
            CASE state IS
                WHEN s0 =>
                    phases <= "0001";
                WHEN s1 =>
                    phases <= "0010";
                WHEN s2 =>
                    phases <= "0100";
                WHEN s3 =>
                    phases <= "1000";
                WHEN OTHERS =>
                    phases <= "0000";
            END CASE;
        ELSE
            CASE state IS
                WHEN s0 =>
                    phases <= "1000";
                WHEN s1 =>
                    phases <= "0100";
                WHEN s2 =>
                    phases <= "0010";
                WHEN s3 =>
                    phases <= "0001";
                WHEN OTHERS =>
                    phases <= "0000";
            END CASE;
        END IF;
    END PROCESS;

    PROCESS (clk)
        VARIABLE counter : INTEGER RANGE 0 TO 50000000 := 0;
        VARIABLE counter_enables : INTEGER RANGE 0 TO 50000000 := 0;
        VARIABLE speed_on : std_logic := '0';
        VARIABLE rising_topCounter : INTEGER RANGE 0 TO 50000000 := 0;
        VARIABLE target_topCounter : INTEGER RANGE 0 TO 50000000 := 0;
    BEGIN
        IF (rising_edge(clk)) THEN
			IF (speed_on = '1') THEN
				target_topCounter := 100000;

            ELSE 
				IF (vel = "00") THEN
					target_topCounter := 10000000;
				ELSE

					IF (vel = "01") THEN
						target_topCounter := 5000000;
					ELSE
						IF (vel = "10") THEN
							target_topCounter := 1000000;
						ELSE
							target_topCounter := 100000;
						END IF;
					END IF;
				END IF;
			END IF;
			
            IF (topCounter > target_topCounter) THEN
                rising_topCounter := rising_topCounter + 1;
                IF (rising_topCounter > 50) THEN
                    topCounter <= topCounter - 1;
                    rising_topCounter := 0;
                END IF;

            ELSE
                IF (topCounter < target_topCounter) THEN
                    rising_topCounter := rising_topCounter + 1;

                    IF (rising_topCounter > 50) THEN
                        topCounter <= topCounter + 1;
                        rising_topCounter := 0;
                    END IF;

                END IF;
            END IF;
            IF (quarter = '0' AND speed_on = '0') THEN
                speed_on := '1';
            END IF;

            IF (speed_on = '1') THEN
                IF (counter_enables > 2038) THEN
                    speed_on := '0';
                    counter_enables := 0;
                ELSE
                    IF (counter < topCounter OR en = '0') THEN
                        counter := counter + 1;
                        enable <= '0';
                    ELSE
                        counter := 0;
                        counter_enables := counter_enables + 1;
                        enable <= '1';
                    END IF;
                END IF;

            ELSE
                IF (counter < topCounter OR en = '0') THEN
                    counter := counter + 1;
                    enable <= '0';
                ELSE
                    counter := 0;
                    counter_enables := counter_enables + 1;
                    enable <= '1';
                END IF;

            END IF;

        END IF;
    END PROCESS;

END rtl;