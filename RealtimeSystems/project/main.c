#define RADIUS 50

int main() {
	int x = 100, y = 100, col = 4;

	allegro_init();
	install_keyboard();

	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT, 640, 48, 0,0);
	clear_to_color(screen, x, y, RADIUS, col);


	circlefill(screen, x, y, RADIUS, col);

	readkey();
	allegro_exit();
	return 0;

}