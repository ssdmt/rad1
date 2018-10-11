@cls
@set INC=-I"C:\Users\ssdmt\YandexDisk\DMT\datakam\D6 DUO\prg\rad1\src\inc"
@set CC= -lstm8 -mstm8 --out-fmt-ihx --std-sdcc99

sdcc %CC% %INC% -c src/stm8l15x_tim1.c
sdcc %CC% %INC% -c src/stm8l15x_clk.c
sdcc %CC% %INC% -c src/stm8l15x_gpio.c
sdcc %CC% %INC% -c src/stm8l15x_syscfg.c
sdcc %CC% %INC% -c src/main.c 

sdcc %CC% main.rel stm8l15x_gpio.rel stm8l15x_clk.rel ^
			stm8l15x_syscfg.rel stm8l15x_tim1.rel

packihx main.ihx > main.hex


:: SDCC_INCLUDE, 36