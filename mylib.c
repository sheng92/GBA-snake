// Sheng Jiang
#include "mylib.h"

// video buffer
u16 *videoBuffer = (u16 *) 0x6000000;

// A function that waits for scanline blank to prevent tearing
void wait_for_vblank() {
  u16 *X = SCANLINECOUNTER;

  while (*X > 160) {;} // in vblank, wait to exit
  while (*X <= 160) {;} // wait for beginning of next vblank
}

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color){
	videoBuffer[240*r+c] = color;
}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int height, int width, u16 color){
	for (int i = 0; i < height; i++) { // loop through each row
		for (int j = 0; j < width; j++) { // each column
			setPixel(r+i, c+j, color);
		}
	}
}

// A function to draw a HOLLOW rectangle starting at (r, c)
// NOTE: It has to run in O(w+h) time.
void drawHollowRect(int r, int c, int height, int width, u16 color){
	for (int i = 0; i < height; i++) {
		setPixel(r+i, c, color);
		setPixel(r+i, c+width-1, color);
	}
	for (int i = 0; i < width; i++) {
		setPixel(r, c+i, color);
		setPixel(r+height-1, c+i, color);
	}
}

// A function to draw lines to a screen
void plotLine(int r0, int c0, int r1, int c1, u16 color){
	int dr = r1 - r0;
	int dc = c1 - c0;
	int slope = 0;
	if ((dr >= 0 && dc >= 0) || (dr <= 0 && dc <= 0)){
		if (dr < 0){
			plotLine(r1, c1, r0, c0, color);
			return;
		}
		if (dr > dc){
			slope = 1;
			int temp = r0;
			r0 = c0;
			c0 = temp;
			temp = r1;
			r1 = c1;
			c1 = temp;
			dr = r1 - r0;
			dc = c1 - c0;
			setPixel(c0, r0, color);
		}
		else{
			setPixel(r0, c0, color);
		}
	
		int d = (dr<<2)-dc;
		int r = r0;
		for (int c = c0+1; c <= c1; c++){
			if (d > 0){
				r += 1;
				if (slope>0){
					setPixel(c, r, color);
				}
				else{
					setPixel(r, c, color);
				}
				d += ((dr-dc)<<2);
			}
			else{
				if (slope>0){
					setPixel(c, r, color);
				}
				else{
					setPixel(r, c, color);
				}
				d += (dr<<2);
			}
		}
	}
	else{
		if (dc < 0){
			plotLine(r1, c1, r0, c0, color);
			return;
		}
		if (dc + dr < 0){
			slope = 1;
			int temp = r0;
			r0 = c1;
			c1 = temp;
			temp = r1;
			r1 = c0;
			c0 = temp;
			dr = r1 - r0;
			dc = c1 - c0;
			setPixel(c0, r0, color);
		}
		else{
			setPixel(r0, c0, color);
		}
		int d = 0-(dr<<2)-dc;
		int r = r0;
		for (int c = c0+1; c <= c1; c++){
			if (d > 0){
				r += -1;
				if (slope>0){
					setPixel(c, r, color);
				}
				else{
					setPixel(r, c, color);
				}
				d += ((0-dr-dc)<<2);
			}
			else{
				if (slope>0){
					setPixel(c, r, color);
				}
				else{
					setPixel(r, c, color);
				}
				d = d-(dr<<2);
			}
		}
	}
}
