#ifndef PCD8544_H
#define PCD8544_H

#include <stdint.h>

#include <WProgram.h> // Arduino 0022

#ifndef SPI_NUM
#define SPI_NUM 1
#endif

class pcd8544 {
public:
	// Constructor for harware SPI
	pcd8544(uint8_t dc_pin, uint8_t reset_pin, uint8_t cs_pin, uint8_t hardware_spi = 1);

	// Call this first
	void begin(void);

	// Clear lcd without changing location
	void clear(void);

	// Change current position to (character) column and row
	void setCursor(uint8_t column, uint8_t row);

	// Change current location to 0 <= row <= 5,
	// 0 <= pixel_column <= 83
	void gotoRc(uint8_t row, uint8_t pixel_column);

	// Send data to lcd. Will draw data as one pixel wide, 8 pixel high.
	// LSB up.
	void data(uint8_t data);

	void clearRestOfLine(void);
	void bitmap(uint8_t *data, uint8_t rows, uint8_t columns);

private:
	void send(uint8_t dc, uint8_t data);
	void command(uint8_t data);
	void inc_row_column(void);
	uint8_t dc;
	uint8_t cs;
	uint8_t reset;
	uint8_t hardware_spi_num;
	uint8_t sdin;
	uint8_t sclk;
	uint8_t current_row, current_column;
};

#define PCD8544_LINES 6
#define PCD8544_COLS  14
#define PCD8544_WIDTH  84
#define PCD8544_HEIGHT 48


#endif
