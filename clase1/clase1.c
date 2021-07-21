/*  simple Hello World, for cc65, for NES
 *  doug fraker 2015
 *  feel free to reuse any code here
 *  Ajustado y comentado por 
 *  carloskl12 ( abril de 2018)
 */
 
/*
 * PPU_CTRL dirección byte de control
 */

#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS    *((unsigned char*)0x2002)
#define SCROLL      *((unsigned char*)0x2005)
#define PPU_ADDRESS    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

//  Globals
unsigned char index;

const unsigned char TEXT[]={
"Hola mundo!"};

// Paleta de colores
const unsigned char PALETTE[]={
0x0f, 0x17, 0x28, 0x39
}; // negro, naranja, amarillo, verde crema 


void main (void) {
  // apaga la pantalla para poder modificar la PPU
  PPU_CTRL = 0;
  PPU_MASK = 0;
  //***********************************************
  //Carga la paleta
  PPU_ADDRESS = 0x3f;   //Se posiciona en la PPU en la dirección 0x3f00
  PPU_ADDRESS = 0x00;

  for(index = 0; index < sizeof(PALETTE); ++index){
    PPU_DATA = PALETTE[index];
  }
  //***********************************************
  //Cargan los diferentes tiles en la pantalla
  // Los tiles visibles empiezan a partir de 0x2000 (0,0)
  // 0x2001 (1,0)   0x2020= (0,1)
  // posx= dir & 0x1f   toma los 5 bits menos significativos
  // posy= (dir >> 5)& 0x1f desplaza 5 bits a la derecha y toma 5 bits
  PPU_ADDRESS = 0x20;    //  Se posiciona el inicio donde se inicia a escribir
  PPU_ADDRESS = 0x00;    //  sobre la pantalla con indices de tiles

  for (index = 0; index < 255; ++index){ //No se puede usar el número 256 
    PPU_DATA= index;
  }
  PPU_DATA= 0xff;//Se agrega manualmente el último tile (255)

  //***********************************************
  //Carga el texto, dando un offset, 0x1c/2= fila
  //posx= 0x21ca & 0x1f = a = 10
  //posy= (0x21ca >> 5) & 0x1f= d =14
  PPU_ADDRESS = 0x22;  // establece una dirección en el PPU de 0x21ca
  PPU_ADDRESS = 0x1f;
  for( index = 0; index < sizeof(TEXT); ++index ){
    PPU_DATA = TEXT[index];
  }
  
  //***********************************************
  //  reset de la posición de scroll, pues modificar
  // los tiles de pantalla cambia el scroll.
  PPU_ADDRESS = 0;
  PPU_ADDRESS = 0;
  SCROLL = 0;
  SCROLL = 0;
  
  //Prende la pantalla
  PPU_CTRL = 0x90;   //Pantalla prendida,  (non-maskable interrupt) NMI on 
  PPU_MASK = 0x1e;
  
  //iteración infinita
  while (1);
};

