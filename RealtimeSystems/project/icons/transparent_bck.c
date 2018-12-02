/**
  * This code turns white into transparent in Allegro 4 .bmp files.
  */

#include <allegro.h>
#include <stdio.h>

char imgs[][50] = {
	"arm.bmp", "artichoke.bmp", "cheese.bmp", "dough.bmp", "ham.bmp",
	"ingr_artichoke.bmp", "ingr_cheese.bmp", "ingr_ham.bmp",
	"ingr_mushroom.bmp", "ingr_olive.bmp", "ingr_tomato.bmp",
	"mushroom.bmp", "olive.bmp", "oven.bmp", "tomato.bmp", "videocam.bmp"
};

int main(void) {
	BITMAP *fish, *fishp; // pointers to bitmap
	PALETTE pal; // color palette
	int x, y, c;
	int pink, white;

	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	clear_to_color(screen, makecol(0,0,0));

	white = makecol(255, 255, 255);
	pink  = makecol(255, 0, 255);

	char str[50] = "", where[50] = "";	
	for(int i = 0; i < sizeof(imgs); i++) {
		strcpy(str, imgs[i]);

		printf("Processing %s\n", str);
		fish = load_bitmap(str, NULL);
		fishp = create_bitmap(fish->w, fish->h);
		for (x=0; x<fish->w; x++) {
			for (y=0; y<fish->h; y++) {
				c = getpixel(fish, x, y);
				if (c == white) {
					c = pink;
					printf("Found white at %d %d\n",x,y);
				}
				printf("Writing color %d\n",c);
				putpixel(fishp, x, y, c);
			}
		}
		get_palette(pal);
		strcpy(where, "new/");
		strcat(where, str);
		save_bitmap(where, fishp, pal);
		
	}

	return 0;
}