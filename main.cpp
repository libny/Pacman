#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>
#include <cstdlib>
 
#define  Maxifilas 20
#define  Maxcols   31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *comida;
BITMAP *enemigobmp;
BITMAP *enemigo;
int dir =0;                       
int px =30*10, py =30*10;
int fdir=0;
int _x=30*14, _y=30*14;

char mapa[Maxifilas][Maxcols] = {
     "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"x    0  0  xxxxx            x",
	"x x xx&  xxxxx  xxxxx  xxx  x",
	"x x    xxxxx  xxxxx  xxx    x",
	"x0xxxx  xxxxx               x",
	"x x     xxxxx  xxxxx   xxx  x",
	"x0x xx         &xxxxx0 0xxx x",
	"x x xxxxxxxx x 0 0 0  xxx   x",
	"x0  xxxxxxxx x0xx xx   xxx  x",
	"x xxxx   xxx x xx  xx  xxx  x",
	"x0  xx x     x0xx  xx  xxx  x",
	"x x xx   xxx x xx  xx  xxx  x",
	"x0x xx x xxx x0    xx       x",
	"x        xxx x xxxxxx       x",
	"x0xxxx x xxx x0xxxxxx  xxx  x",
    "x      x xxx x xxx          x",
	"x0xxxx x xxx x xxx  xxx  xx x",
	"x  0   0  0 0 0xxx          x",                         
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",

};
void dibujar_mapa(){
int row,col;

for(row = 0 ;row< Maxifilas ; row++){
    for ( col=0; col< Maxcols; col++){
		if(mapa[row][col]=='x'){
			draw_sprite(buffer,roca,col*30,row*30);
		}
		if(mapa[row][col]=='0'){
			draw_sprite(buffer,comida,col*30,row*30);
			if(py/30 == row && px/30 ==col )
				mapa[row][col]=' ';
		}
	}
}
}

void pantalla(){
	blit (buffer ,screen , 0,0,0,0,870,600);
}

void dibujar_personaje(){
	blit(pacbmp,pacman,dir *33,0,0,0,33,33);
	draw_sprite(buffer, pacman,px,py);
}

bool game_over(){

	int row,col;

	for(row = 0 ;row< Maxifilas ; row++){
		for ( col=0; col< Maxcols; col++){		
			if(mapa[row][col]=='0') return true;
		}
	}
	return false;
}

void dibujar_fantasma(){
blit(enemigobmp,enemigo,0,0,0,0,30,30);
	draw_sprite(buffer, enemigo,_x,_y);
}
void fantasmas (){
	dibujar_fantasma();
	if(mapa[_y/30][_x/30]=='&'){
		fdir =rand()%4;
	}
	if(fdir==0){
		if(mapa[_y/30][(_x-30)/30]!='x') _x-=30;
		else fdir=rand()%3;
	}
	 if(fdir==1){
		if(mapa[_y/30][(_x+30)/30]!='x') _x+=30;
		else fdir=rand()%3;
	 }

	 if(fdir==2){
		if(mapa[(_y-30)/30][_x/30]!='x') _y-=30;
		else fdir=rand()%3;
	 }

	 if(fdir==3){
		if(mapa[(_y+30)/30][_x/30]!='x') _y+=30;
		else fdir=rand()%3;
	 }

}
int main()
{
	allegro_init();
	install_keyboard();
 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
 
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 860, 600, 0, 0);

	buffer = create_bitmap(880, 600);
	roca = load_bitmap("roca.bmp", NULL);
	pacbmp = load_bitmap("pacman.bmp", NULL);
	pacman = create_bitmap(33,33);
	comida = load_bitmap("comida.bmp",NULL);
	enemigo =create_bitmap(30,30);
	enemigobmp = load_bitmap("enemigo.bmp",NULL);
	
	
	while (!key[KEY_ESC]  && game_over()){
		if(key[KEY_RIGHT]) dir = 1;
		else if (key[KEY_LEFT]) dir = 0;
		else if(key[KEY_UP]) dir =2;
		else if(key[KEY_DOWN]) dir =3;


		if(dir == 0){
			if(mapa[py/30][(px -30)/30] !='x')
				px -=30;
			else
			{
				dir =4;
			}
		}
		if(dir == 1){ 
			if(mapa[py/30][(px +30)/30] !='x')
				px +=30;
			else
			{
				dir =4;
			}
			
		}
		if(dir == 2) {
			if(mapa[(py-30)/30][px/30] !='x')
			 py -=30;
			else	
			dir =4;
		}
		if(dir == 3) {
			if(mapa[(py+30)/30][px/30] !='x')
				py +=30;
			else	
				dir =4;
		
		}
				
		clear(buffer);              

		dibujar_mapa();
		dibujar_personaje();
		fantasmas();
		pantalla();
		rest(70);

		clear(pacman);
		blit(pacbmp,pacman,4 *33,0,0,0,33,33);
		draw_sprite(buffer, pacman,px,py);
		
		pantalla();
		rest(90);

	}
 
	return 0;
}
 
END_OF_MAIN();