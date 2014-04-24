#define USE_CONSOLE
#include <allegro.h>
#include <stdio.h>

 
#define  Maxifilas 20
#define  Maxcols   31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;

int dir =0;
int px =30*10, py =30*10;


char mapa[Maxifilas][Maxcols] = {
     "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"x          xxxxx            x",
	"x  xxx  xxxxx  xxxxx  xxx   x",
	"x  xxx  xxxxx  xxxxx  xxx   x",
	"x  xxx  xxxxx               x",
	"x  xxx  xxxxx  xxxxx   xxx  x",
	"x  xxx         xxxxx   xxx  x",
	"x  xxxxxxxxx           xxx  x",
	"x  xxxxxxxxx   xx xx   xxx  x",
	"x  xxx   xxx   xx  xx  xxx  x",
	"x  xxx   xxx   xx  xx  xxx  x",
	"x  xxx   xxx   xx  xx  xxx  x",
	"x  xxx   xxx       xx       x",
	"x        xxx   xxxxxx       x",
	"x  xxx   xxx   xxxxxx  xxx  x",
    "x  xxx   xxx   xxx          x",
	"x  xxx   xxx   xxx  xxx  xx x",
	"x  xxx         xxx          x",                         
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",

};
void dibujar_mapa(){
int row,col;

for(row = 0 ;row< Maxifilas ; row++){
    for ( col=0; col< Maxcols; col++){
		if(mapa[row][col]=='x'){
			draw_sprite(buffer,roca,col*30,row*30);
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

	while (!key[KEY_ESC]){
		if(key[KEY_RIGHT]) dir = 1;
		else if (key[KEY_LEFT]) dir = 0;
		else if(key[KEY_UP]) dir =2;
		else if(key[KEY_DOWN]) dir =3;


		if(dir == 0) px -=30;
		if(dir == 1) px +=30;
		if(dir == 2) py -=30;
		if(dir == 3) py +=30;

		clear(buffer);

		dibujar_mapa();
		dibujar_personaje();
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