#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rectangle.h"

int main() {
    // Declarations
    ALLEGRO_DISPLAY * game_display = NULL;
    ALLEGRO_COLOR red = {0};
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_TIMER * game_timer = NULL;
    RECTANGLE personnage = {0,0,50,30,10, 20};
    bool fini = false;
    bool flag_left = false;
    ALLEGRO_EVENT event;

    // Initialisation
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    personnage.x = (WDISPLAY - personnage.l)/2;
    personnage.y = (HDISPLAY - personnage.h)/2;

    // Creation des éléments
    game_display = al_create_display(WDISPLAY, HDISPLAY);
    game_timer = al_create_timer(1.0/30.0);
    fifo = al_create_event_queue();
    red = al_map_rgb(255, 0,0);

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
                if(flag_left){
                    if(personnage.x>0){
                        personnage.x = personnage.x - personnage.vx;
                    }
                }
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_filled_rectangle(personnage.x, personnage.y, personnage.x + personnage.l, personnage.y+ personnage.h, red);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        // on modifie la position suivant x
                        flag_left = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if(personnage.x < (WDISPLAY-personnage.l)) {
                            personnage.x = personnage.x + personnage.vx;
                        }
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        flag_left = false;
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
