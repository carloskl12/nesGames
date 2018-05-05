const unsigned char PALETTE[]={
0x11, 0x02, 0x00, 0x02, // blues
0x00, 0x16, 0x00, 0x16, // red
0x00, 0x27, 0x00, 0x27, // yellow
0x00, 0x1a, 0x00, 0x1a, // green
}; 
// note, 11 is the default background color = blue

/*const unsigned char Attrib_Table[]={*/
/*0xe4, // 0100 0100, */
/*0x44, // 1011 1011, */
/*0xFA, // 0100 0100, */
/*0x77}; // 1011 1011*/

const unsigned char Attrib_Table[]={
0xe4, // 0100 0100, 
0x72, // 1011 1011, 
0x1B, // 0100 0100, 
0x8D}; // 1011 1011

// 33221100 = 2 bits per attribute area
// 0 1		= their relative position on the screen
// 2 3
// each box is 16x16 pixels
