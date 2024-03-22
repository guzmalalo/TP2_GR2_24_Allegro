#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rectangle.h"

enum {LEFT, UP, DOWN, RIGHT, Q, NUMFLAGS};

int main() {
    // Declarations
    ALLEGRO_DISPLAY * game_display = NULL;
    ALLEGRO_COLOR red = {0};
    ALLEGRO_COLOR blue = {0};
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_TIMER * game_timer = NULL;
    RECTANGLE p1 = {0, 0, 50, 30, 10, 10};
    RECTANGLE p2 = {0, 0, 50, 30, 5, 5};
    bool fini = false;
    ALLEGRO_EVENT event;
    bool flags[NUMFLAGS] = {false};

    // Initialisation
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    p1.x = (WDISPLAY - p1.l) / 2;
    p1.y = (HDISPLAY - p1.h) / 2;

    p2.x = (WDISPLAY - p1.l) / 2;
    p2.y = (HDISPLAY - p1.h) / 2;

    // Creation des éléments
    game_display = al_create_display(WDISPLAY, HDISPLAY);
    game_timer = al_create_timer(1.0/30.0);
    fifo = al_create_event_queue();
    red = al_map_rgb(255, 0,0);
    blue = al_map_rgb(0,0,255);

    // Sources
    al_register_event_source(fifo, al_get_display_event_source(game_display)); // on surveille le display
    al_register_event_source(fifo, al_get_timer_event_source(game_timer)); // on surveille le timer
    al_register_event_source(fifo,al_get_keyboard_event_source());

    // Premier affichage
    al_flip_display();

    // boucle d'événements
    al_start_timer(game_timer);
    while (!fini){
        // piocher un événement
        al_wait_for_event(fifo, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;

            case ALLEGRO_EVENT_TIMER:
                // mise à jour position
                if(flags[LEFT]==true){
                    p1.x = p1.x - p1.vx;
                }
                if(flags[RIGHT]==true){
                    p1.x = p1.x + p1.vx;
                }

                if(flags[UP]==true){
                    p1.y = p1.y - p1.vy;
                }
                if(flags[DOWN]==true){
                    p1.y = p1.y + p1.vy;
                }

                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_filled_rectangle(p1.x, p1.y, p1.x + p1.l, p1.y + p1.h, red);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flags[LEFT] = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        flags[RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_UP:
                        flags[UP] = true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        flags[DOWN] = true;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flags[LEFT] = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        flags[RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_UP:
                        flags[UP] = false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        flags[DOWN] = false;
                        break;
                }
                break;
            default:
                printf("Evenement non géré %d\n", event.type);

        }

    }


    // Liberation
    al_destroy_display(game_display);
    al_destroy_timer(game_timer);
    al_destroy_event_queue(fifo);
    return 0;
}
