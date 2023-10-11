#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <iostream>
using namespace std;

class GameWindow : public Gosu::Window
{
public:

	Gosu::Image Hintergrund;

	GameWindow()
		: Window (Gosu :: available_width(),Gosu :: available_height(), true)
		, Hintergrund ("Hintergrund.png")
	{
		set_caption("Gosu Tutorial mit Git");
	}

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		Hintergrund.draw(Gosu :: available_height()-(3556* double(Gosu::available_height()) / double(3556)), 0, -100, double(Gosu::available_width()) / double(7111), double(Gosu::available_height()) / double(3556));

		graphics().draw_line(
			0, Gosu::available_height(), Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
	}
};

// C++ Hauptprogramm
int main()
{
	cout<< Gosu::available_height() - (3550 * double(Gosu::available_height()) / double(3550));
	GameWindow window;
	window.show();
	return 1;
}