#include <stdio.h>
//Allegro Libraries
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
//Own h files
#include "InputManager.h"
#include "Elevator.h"


int main(int argc, char **argv)
{
	// set diaplay parameters
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	// set Framerate
	int FPS = 60;
	// Game loop & rendering variables
	bool game_done = false;				// used for game loop
	bool redraw = false;				// used for rendering

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;			//Pointer to display.
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//Pointer to event queue
	ALLEGRO_TIMER *timer = NULL;				//Pointer to timers

	//Elevator variables
	int numFloors = 10;
	Elevator myElevator(numFloors);

	//Initialise allegro, if unsuccesful, show error.
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize allegro",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; //exit program
	}

	// create display & check if succesful.
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Could not initatialize the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1; // exit program
	}

	//Create Timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Event Queue
	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the event queue",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	


	//Intitialize addons
	al_install_keyboard();		//Keyboard
	al_install_mouse();			//Mouse
	al_init_primitives_addon(); //Primitives (shapes)
	al_init_image_addon();		//Images

	//Register Event Sources
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display events
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer events
	al_register_event_source(event_queue, al_get_keyboard_event_source()); // keyboard events
	al_register_event_source(event_queue, al_get_mouse_event_source()); // mouse events

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_timer(timer); //Start the timer

	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); // wait for event


		//Capture key input
		InputManager::getInstance().getInput(ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			// update
			if (InputManager::getInstance().isMouseButtonPressed(0))
			{
				if (InputManager::getInstance().getMouseX() < DISPLAY_WIDTH/2)
				{
					myElevator.checkButtons();
					InputManager::getInstance().clearInput();
				}
			}
			myElevator.update();
		}


		//Escape key pressed? exit game
		if (InputManager::getInstance().isKeyPressed(ESCAPE))
		{
			game_done = true;
		}

		// Capture close windows event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		//Rendering
		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty before redrawing.
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			//Elevator shaft
			al_draw_line(DISPLAY_WIDTH / 2 - 5, 0, DISPLAY_WIDTH / 2 - 5, DISPLAY_HEIGHT, al_map_rgb(255, 0, 0), 10);
			al_draw_line(490, 0,490, DISPLAY_HEIGHT, al_map_rgb(255, 0, 0), 10);

			// Floor lines
			for (int i = 0; i < DISPLAY_HEIGHT; i += 60)
			{
				al_draw_line(DISPLAY_WIDTH / 2, i, DISPLAY_WIDTH, i, al_map_rgb(255, 0, 0), 10);
			}
			
			myElevator.draw();
			// draw
			al_flip_display();
		}
	}

	// Cleanup
	// Destroy everything that you create that doesnt do its own cleanup
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}