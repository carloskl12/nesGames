// El color en el indice cero es el fondo
// los otros en la misma columna no importan porque
// no se tienen en cuenta
const unsigned char PALETTE[]={
0x0F, 0x02, 0x00, 0x02, // blues
0x00, 0x16, 0x00, 0x16, // red
0x00, 0x28, 0x00, 0x27, // yellow
0x00, 0x1a, 0x00, 0x1a, // green
}; 


/*
Se crean atributos de forma que se rota
la tabla de colores, cada byte indica 
que grupo de colores de la paleta se usa en 
los 4x4 tiles, divididos en grupos de 2x2

0 0 1 1  |
0 0 1 1  |Grupos de 
2 2 3 3  |tiles
2 2 3 3  |

De forma tal que cada dos bits del byte representan
la paleta a usarse 33221100 en los respectivos 
grupos de 4 tiles.
*/
const unsigned char Attrib_Table[]={
0xe4, // 1110 0100, 
0x72, // 0111 0010
0x1B, // 0001 1011 
0x8D}; // 1000 1101

// 33221100 = 2 bits per attribute area
// 0 1		= their relative position on the screen
// 2 3
// each box is 16x16 pixels
