#define USE_CONSOLE
#include <allegro.h>
 #include <stdio.h>
#include <allegro.h>
 
#define  Maxifilas 20
#define  Maxcols   31
BITMAP *buffer;
BITMAP *roca;
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


int main()
{
	allegro_init();
	install_keyboard();
 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
 
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 860, 600, 0, 0);

	buffer = create_bitmap(880, 600);
	roca = load_bitmap("roca.bmp", NULL);

	while (!key[KEY_ESC]){
		dibujar_mapa();
		pantalla();
	}
 
	return 0;
}
 
END_OF_MAIN();