#include <stdint.h>
#include "pcd8544.h"

#include <HardwareSPI.h>
#include <libmaple.h>

HardwareSPI spi(SPI_NUM);

// LCD commands, Table 1, page 14
#define PCD8544_FUNCTION_SET (1<<5)
#define PCD8544_FUNCTION_PD  (1<<2)
#define PCD8544_FUNCTION_V   (1<<1)
#define PCD8544_FUNCTION_H   (1<<0)

// Normal instructions, H = 0
#define PCD8544_DISPLAY_CONTROL (1<<3)
#define PCD8544_DISPLAY_CONTROL_D (1<<2)
#define PCD8544_DISPLAY_CONTROL_E (1<<0)
#define PCD8544_DISPLAY_CONTROL_BLANK 0
#define PCD8544_DISPLAY_CONTROL_NORMAL_MODE  PCD8544_DISPLAY_CONTROL_D
#define PCD8544_DISPLAY_CONTROL_ALL_ON       PCD8544_DISPLAY_CONTROL_E
#define PCD8544_DISPLAY_CONTROL_INVERSE      (PCD8544_DISPLAY_CONTROL_D|PCD8544_DISPLAY_CONTROL_E)

#define PCD8544_SET_Y_ADDRESS (1<<6)
#define PCD8544_Y_ADRESS_MASK 0b111
#define PCD8544_SET_X_ADDRESS (1<<7)
#define PCD8544_X_ADRESS_MASK 0b01111111

// Extended instructions. H = 1
#define PCD8544_TEMP_CONTROL (1<<2)
#define PCD8544_TEMP_TC1     (1<<1)
#define PCD8544_TEMP_TC0     (1<<0)

#define PCD8544_BIAS     (1<<4)
#define PCD8544_BIAS_BS2 (1<<2)
#define PCD8544_BIAS_BS1 (1<<1)
#define PCD8544_BIAS_BS0 (1<<0)

#define PCD8544_VOP (1<<7)


pcd8544::pcd8544(uint8_t dc_pin, uint8_t reset_pin, uint8_t cs_pin, uint8_t hardware_spi)
{
	dc = dc_pin;
	cs = cs_pin;
	reset = reset_pin;
	hardware_spi_num = hardware_spi;
	if (hardware_spi_num > 2)
		hardware_spi_num = 2;

	sdin = 11;  // Change to maple names
	sclk = 13;
	if (hardware_spi_num  == 2) {
		sdin = 32;
		sclk = 34;
	}
}

void pcd8544::begin(void)
{
	pinMode(cs,   OUTPUT);
	pinMode(reset, OUTPUT);
	pinMode(dc,    OUTPUT);
	pinMode(sdin,  OUTPUT);
	pinMode(sclk,  OUTPUT);

	timer_set_mode(TIMER3, 2, TIMER_DISABLED);
        timer_set_mode(TIMER3, 1, TIMER_DISABLED);


	if (hardware_spi_num > 0) {
		spi.begin(SPI_4_5MHZ, MSBFIRST, 0);
		//spi_init(hardware_spi_num, SPI_PRESCALE_16, SPI_MSBFIRST, 0);
	}
	digitalWrite(reset, LOW);
	delay(1);
	digitalWrite(reset, HIGH);
  
	// Extenden instructions and !powerdown
	// and horizontal adressing (autoincrement of x-adress)
	command(PCD8544_FUNCTION_SET | PCD8544_FUNCTION_H);
	// Set Vop to 0x3F
	command(PCD8544_VOP | 0x3F);
	// Vlcd temp. coeff. 0
	command(PCD8544_TEMP_CONTROL);
	// Bias system 4, 1:48
	command(PCD8544_BIAS | PCD8544_BIAS_BS1 | PCD8544_BIAS_BS0);
	// Set H = 0 for normal instructions
	command(PCD8544_FUNCTION_SET);  
	// Normal mode
	command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_CONTROL_NORMAL_MODE);
}


void pcd8544::clear(void)
{
	int i;
	for (i = 0; i < PCD8544_WIDTH*PCD8544_LINES; i++)
		data(0);
}

void pcd8544::data(uint8_t data)
{
	send(1, data);
}

void pcd8544::command(uint8_t data)
{
	send(0, data);
}

void pcd8544::send(uint8_t data_or_command, uint8_t data)
{
	digitalWrite(dc, data_or_command);
	digitalWrite(cs, LOW);
	if (hardware_spi_num == 0) {
		shiftOut(sdin, sclk, MSBFIRST, data);
	} else {
		//spi_tx_byte(hardware_spi_num, data);
		spi.transfer(data);
	}
	digitalWrite(cs, HIGH);
	if(data_or_command)
		inc_row_column();
}


void pcd8544::setCursor(uint8_t column, uint8_t row)
{
	gotoRc(row, 6*column);
}


void pcd8544::gotoRc(uint8_t row, uint8_t column)
{
	if (row >= PCD8544_LINES)
		row %= PCD8544_LINES;
	if (column >= PCD8544_WIDTH)
		row %= PCD8544_WIDTH;
	command(PCD8544_SET_X_ADDRESS | column);
	command(PCD8544_SET_Y_ADDRESS | row);
	current_row = row;
	current_column = column;
}

void pcd8544::inc_row_column(void)
{
	if (++current_column >= PCD8544_WIDTH) {
		current_column = 0;
		if (++current_row >= PCD8544_LINES)
			    current_row = 0;
	}
}

void pcd8544::clearRestOfLine(void)
{
	while (current_column != 0)
		data(0);
}


void pcd8544::bitmap(uint8_t bdata[], uint8_t rows, uint8_t columns)
{
	uint8_t row, column;
	uint16_t i;
	uint8_t toprow = current_row;
	uint8_t startcolumn = current_column;
	for (row = 0, i = 0; row < rows; row++) {
		gotoRc(row+toprow, startcolumn);
		for (column = 0; column < columns; column++) {
			data(bdata[i++]);
		}
	}
}
