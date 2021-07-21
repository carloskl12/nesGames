/*  simple Hello World, for cc65, for NES
 *  examples of attribute tables and pragmas and include
 *  doug fraker 2015
 *  feel free to reuse any code here
 *  Ajustado y comentado por 
 *  carloskl12 ( abril de 2018)
 */

#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS    *((unsigned char*)0x2002)
#define SCROLL      *((unsigned char*)0x2005)
#define PPU_ADDRESS    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

//  Globals
#pragma bss-name(push, "ZEROPAGE")
/*  forces these variables to be in the zeropage of the RAM
 *  note, in reset.s, I also changed the .import to .importzp
 *  zeropage code runs slightly faster than anything outside the zeropage
 */

unsigned char NMI_flag;
unsigned char Frame_Count;
unsigned char index;
unsigned char Text_Position;

#pragma bss-name(push, "BSS")
//  these variables to be in the BSS of the RAM, set as 0x300 in the cfg file
unsigned char test;
unsigned char nPalette;
unsigned char state;

const unsigned char TEXT[]={
"0011001100110011"};
const unsigned char TEXT2[]={
"2233223322332233"};
// La dimensión de solo texto corresponde a 
// el tamaño del array menos uno que es el byte 
// 0 ubicado al final de la cadena.
unsigned char Text_dim= sizeof(TEXT)-1;
//  Una forma facil de tener codigo limpio es ubicar 
//  el codigo de funciones en diferentes archivos
#include "PALETTE.c"
#include "CODE.c"

// Prototipos
void Load_Text (void);
void Change_Atrib_table(void);
void Ajusta_Pantalla(void);
void main (void) {
  All_Off();     // Apaga la pantalla
  Load_Palette();
  Ajusta_Pantalla();
  Reset_Scroll();
  state=0;
  test=0;
  nPalette=0;
  All_On();//  Enciende la pantalla
  while (1){     //  loop infinito
    while (NMI_flag == 0);  //  esperar hasta la interrupción NMI
    NMI_flag = 0;
    
    if (Frame_Count == 10){ //  30 frames = 0.5 seconds
      if (state == 0){
        Load_Text();
        
      } else{
        Change_Atrib_table();
        ++state;
      }
      ++test;  //  dummy, just making sure this compiles into the BSS section 0x300
      if (  Text_Position == Text_dim && state == 0)//& test>= 
        state=1;
      if (state>= 12){
          state=0;
          nPalette=0;
          Change_Atrib_table();
      }
      Reset_Scroll();
      Frame_Count = 0;
    }
    
  } 
}
  
// En cada V-blank, dentro del codigo de inicio, la rutina de NMI tendrá 
// ++NMI_flag y ++Frame_Count
void Load_Text (void) {
  if (Text_Position < Text_dim){

    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0x88 + Text_Position; //  one line down = add 0x20 to the low bit
    PPU_DATA = TEXT[Text_Position];

    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xa8 + Text_Position; //  one line down = add 0x20 to the low bit
    PPU_DATA = TEXT[Text_Position];
  
    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xc8 + Text_Position; //  about the middle of the screen 21d0
    PPU_DATA = TEXT2[Text_Position];
    
    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xe8 + Text_Position; //  one line down = add 0x20 to the low bit
    PPU_DATA = TEXT2[Text_Position];
    
    ++Text_Position;  
  }
  else {
    Text_Position = 0;
    
    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0x88; //  una linea abajo = sumar 0x20 a los bits mas bajos
    for ( index = 0; index < Text_dim; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
    }

    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xa8; //  una linea abajo = sumar 0x20 a los bits mas bajos
    for ( index = 0; index < Text_dim; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
    }
    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xc8;
    for ( index = 0; index < Text_dim; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
    }
    PPU_ADDRESS = 0x21;
    PPU_ADDRESS = 0xe8;
    for ( index = 0; index < Text_dim; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
    }
  }
}

void Change_Atrib_table(void){
  PPU_ADDRESS = 0x23;
  PPU_ADDRESS = 0xda;
  PPU_DATA =  Attrib_Table[nPalette];
  ++nPalette;
  if (nPalette>= sizeof(Attrib_Table))
    nPalette=0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void Ajusta_Pantalla(void){
  /*
  Agrega una franja con el color de fondo para mejorar
  el aspecto de la zona donde estarán los cambios
  
  name table 0 desde 0x2000 hasta 0x23ff
  */
  PPU_ADDRESS = 0x21;
  PPU_ADDRESS = 0x40;
  for ( index = 0; index < 255; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
  }
  //No se puede llegar a 255, por tanto
  //se agrega el ultimo tile.
  PPU_DATA = 32;
}
