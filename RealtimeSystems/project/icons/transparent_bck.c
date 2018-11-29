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

	white = makecol(255, 255, 255);
	pink = makecol(255, 0, 255);

	for(int i = 0; i < sizeof(imgs); i++) {
		char str[50] = "";
		strcpy(str, imgs[i]);

printf("%s\n", str);

		fish = load_bitmap("icons/dough.bmp", NULL);printf("sa\n");
		fishp = create_bitmap(fish->w, fish->h);
		for (x=0; x<fish->w; x++)
			for (y=0; y<fish->h; y++) {
				c = getpixel(fish, x, y);
				if (c == white) c = pink;
					putpixel(fishp, x, y, c);
			}
		get_palette(pal);
		save_bitmap(str, fishp, pal);
	}
}