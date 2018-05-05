/*  simple Hello World, for cc65, for NES
 *  doug fraker 2015
 *  feel free to reuse any code here
 *  Ajustado y comentado por 
 *  carloskl12 ( abril de 2018)
 */

#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS  *((unsigned char*)0x2002)
#define SCROLL      *((unsigned char*)0x2005)
#define PPU_ADDRESS *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)

//  Globals
unsigned char NMI_flag;
unsigned char Frame_Count;
unsigned char index;
unsigned char Text_Position;
const unsigned char TEXT[]={
"Hola mundo!"};
//No se cuenta el número cero al final del string
unsigned char Text_dim= sizeof(TEXT)-1; 

// Paleta de colores
const unsigned char PALETTE[]={
0x0f, 0x17, 0x28, 0x39
}; // negro, naranja, amarillo, verde crema 

//  Prototipos
void Load_Text(void);
void All_Off(void);
void All_On(void);
void Reset_Scroll (void);
void Load_Palette(void);



void main (void) {
  //  apaga la pantalla
  All_Off();
  Load_Palette();
  Reset_Scroll();

  //  Enciende la pantalla
  All_On();
  
  while (1){ //  loop infinito
    while (NMI_flag == 0);  //  esperar hasta NMI
    NMI_flag = 0;
    
    if (Frame_Count == 10){ //  espera 30 frames = 0.5 seconds
      Load_Text();
      Reset_Scroll();
      Frame_Count = 0;
    }
  }
}
  

// En cada V-blank, dentro del codigo de inicio, la rutina de NMI tendrá 
// ++NMI_flag y ++Frame_Count

void Load_Text(void) {
  if (Text_Position < Text_dim){
    // Agrega el tile a la posición actual del texto
    PPU_ADDRESS = 0x20;
    PPU_ADDRESS = 0xca + Text_Position; 
    PPU_DATA = TEXT[Text_Position];
    ++Text_Position;  
  }
  else {
    //De exceder la longitud, reinicia la posición del texto
    Text_Position = 0;
    PPU_ADDRESS = 0x20;
    PPU_ADDRESS = 0xca;
    for ( index = 0; index < Text_dim; ++index ){
      PPU_DATA = 32;  //  borra el texto con el tile #32 
    }
  }
}


void All_Off(void) {
  PPU_CTRL = 0;
  PPU_MASK = 0; 
}

  
void All_On(void) {
  PPU_CTRL = 0x90; //  screen is on, NMI on
  PPU_MASK = 0x1e; 
}

  
void Reset_Scroll (void) {
  PPU_ADDRESS = 0;
  PPU_ADDRESS = 0;
  SCROLL = 0;
  SCROLL = 0;
}

void Load_Palette(void) {
  PPU_ADDRESS = 0x3f;
  PPU_ADDRESS = 0x00;
  for( index = 0; index < sizeof(PALETTE); ++index ){
    PPU_DATA = PALETTE[index];
  }
}
