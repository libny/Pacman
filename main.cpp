#define USE_CONSOLE
#include <allegro.h>
#include<cstdlib>
#define MAXFILAS 20
#define MAXCOLS 31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *comida;
BITMAP *muertebmp;
SAMPLE *musica;
SAMPLE *bolita;
SAMPLE *caminando;
SAMPLE *muerte;

int dir=4;
int px=30*14,py=30*17;
int anteriorpx,anteriorpy;

char mapa[MAXFILAS][MAXCOLS]={
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"Xo o |o o o   XX o o |o o oX",
	"X XXX XXXXX XX    XXX X XXX X",
	"X XXX XXXXX XX  X XXX X XXX X",
	"X     o |o o o o o o |o o   X",
	"X XXX XX XX XXXXX XX XX XXX X",
	"X     XX     XXX     XX     X",
	"X XXX XX X X XXX XXXXXX XXX X",
	"X XXX XX ooo ooo ooooXX XXX X",
	"     |XX X XX X X XX XX|     ",
	"X XXX XX X XX X X XX XX XXX X",
	"X XXX XX o         o XX XXX X",
	"X XXX XXX XX XXX XXXXXX XXX X",
	"X     XX     XXX     XX     X",
	"X XXX XX XXXXXXXXXXX XX XXX X",
	"X XXX  oo |ooo ooo|o oo|XXX X",
	"X XXX XXXX XXXXXXX XXXX XXX X",
	"X XXX XXXX         XXXX XXX X",
	"X o  |     XXXXXXX     | o  X",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};
void dibujar_mapa()
{
     int row,col;
     for(row=0;row<MAXFILAS;row++)
     {
      for(col=0;col<MAXCOLS;col++)
      {
         if(mapa[row][col]=='X')
         {
             draw_sprite(buffer,roca,col*30,row*30);
         }
         else if(mapa[row][col]=='o')
         {
               draw_sprite(buffer,comida,col*30,row*30);
               if(py/30==row && px/30==col)
               {
				//play_sample(muerte,300,150,1000,0);              
				mapa[row][col]=' ';
               }
          }
      }
     }
}

void pantalla()
{
     blit(buffer, screen,0,0,0,0,880,600);
} 

void dibujar_personaje()
{
     blit(pacbmp,pacman,dir*33,0,0,0,33,33); 
     draw_sprite(buffer,pacman,px,py);                 
}                                

bool game_over()
{
      int row,col;
     for(row=0;row<MAXFILAS;row++)
     {
      for(col=0;col<MAXCOLS;col++)
      {
         if(mapa[row][col]=='o')return true;
       }
      }
      return false;
 }

class fantasma
{
   BITMAP *enemigobmp;
   BITMAP *enemigo;
   int fdir;
   int _x,_y;
public:
       fantasma(int x,int y);//constructor
       void dibujar_fantasma() const;
       void mover_fantasma();
       void choque_pacman();        
};    
fantasma::fantasma(int x,int y)
{
      _x=x;
      _y=y;
      fdir=rand()%4;
      enemigo=create_bitmap(30,30);
      enemigobmp=load_bitmap("enemigo.bmp",NULL);
}
void fantasma::dibujar_fantasma() const
{
     blit(enemigobmp,enemigo,0,0,0,0,30,30); 
     draw_sprite(buffer,enemigo,_x,_y); 
 }    
 void fantasma::choque_pacman()
 {
     if(py==_y && px==_x || _y==anteriorpy && _x==anteriorpx)
     {
          play_sample(muerte,100,150,1000,0);
         for(int j=0;j<=5;j++)
         {
              clear(pacman);
              clear(buffer);
              dibujar_mapa();
              
              blit(muertebmp,pacman,j*33,0,0,0,33,33);
              draw_sprite(buffer,pacman,px,py);
              
              pantalla();
              rest(80);   
         }      
         px=30*14;
         py=30*17;
         dir=4;
     }  
}
void fantasma::mover_fantasma()
{
     dibujar_fantasma();
     choque_pacman();
     if(mapa[_y/30][_x/30]=='|')
     {
          fdir=rand()%4;
     }
     if(fdir==0)
     {
          if(mapa[_y/30][(_x-30)/30]!='X')_x-=30;
          else fdir=rand()%4;
     }
     else if(fdir==1)
     {
          if(mapa[_y/30][(_x+30)/30]!='X')_x+=30;
          else fdir=rand()%4;
     }
     else if(fdir==2)
     {
          if(mapa[(_y-30)/30][_x/30]!='X')_y-=30;
          else fdir=rand()%4;
     }
     else if(fdir==3)
     {
          if(mapa[(_y+30)/30][_x/30]!='X')_y+=30;
          else fdir=rand()%4;
     }
//rutina atajo
    if(_x<=-30)_x=870;
    else if(_x>=870)_x=-30;
 }
 
int main() {
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
	//inicializa el audio en allegro
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
     { allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error); 
     return 1; 
      }
    set_volume(70, 70);
    musica=load_wav("pacman_beginning.wav");
	bolita=load_wav("pacman_eatghost.wav");
	caminando=load_wav("pacman_intermission.wav");
	muerte=load_wav("pacman_death.wav");
	
	buffer=create_bitmap(880,600);
	roca=load_bitmap("roca.bmp",NULL);
	pacbmp=load_bitmap("pacman.bmp",NULL);
	pacman=create_bitmap(33,33);
	comida= load_bitmap("Comida.bmp",NULL);
	muertebmp=load_bitmap("muerte.bmp",NULL);
	
    fantasma A(30*2,30*3);
    fantasma B(30*15,30*15);
    fantasma C(30*16,30*6);
    fantasma D(30*8,30*8);
    fantasma E(30*12,30*2);
    
    play_sample(musica,100,150,1000,1); 
	while(!key[KEY_ESC] && game_over())
	{    
    anteriorpx=px;
    anteriorpy=py;
     
    if(key[KEY_RIGHT]) dir=1;
    else if(key[KEY_LEFT]) dir=0;
    else if(key[KEY_UP]) dir=2;
    else if(key[KEY_DOWN]) dir=3;
    
    if(dir==0)
    {     if(mapa[py/30][(px-30)/30]!='X')
          px -=30;
          else
          dir=4;
    }
    if(dir==1)
     {     if(mapa[py/30][(px+30)/30]!='X')
          px +=30;
          else
          dir=4;
    }
    if(dir==2)
     {     if(mapa[(py-30)/30][(px)/30]!='X')
          py -=30;
          else
          dir=4;
    }
    if(dir==3)
     {     if(mapa[(py+30)/30][px/30]!='X')
          py +=30;
          else
          dir=4;
    }
    
    //rutina para atajo
    if(px<=-30)px=870;
    else if(px>=870)px=-30;
    
    clear(buffer);
	dibujar_mapa();
	dibujar_personaje();
	A.mover_fantasma();
	B.mover_fantasma();
	C.mover_fantasma();
	D.mover_fantasma();
	E.mover_fantasma();
	pantalla();
	rest(70);
	
	clear(pacman);
	blit(pacbmp,pacman,4*33,0,0,0,33,33); 
    draw_sprite(buffer,pacman,px,py);
    pantalla();
    rest(90);
    }
}
END_OF_MAIN()

