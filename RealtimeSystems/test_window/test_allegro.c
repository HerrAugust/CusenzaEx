#define RADIUS 50

#include <allegro.h>

int main() {
	int x = 100, y = 100, col = 4;

	allegro_init();
	install_keyboard();

	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0,0);
	clear_to_color(screen, 0);


	circlefill(screen, x, y, RADIUS, col);

	readkey();
	allegro_exit();
	return 0;
}