#include "SimulationField.h"
#include "Simulation.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

using namespace std;

SDL_Surface *load_image( std::string filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );

    if (loadedImage != NULL) {
    } else {
        cout << "Error: Could not load image" << endl;
    }

    return loadedImage;
}

void visualize(Simulation s)
{
    SDL_Surface *screen,
                *empty,
                *vegetated,
                *burning,
                *burnt;
    SDL_Init(SDL_INIT_EVERYTHING);

    // load the bitmaps
    empty     = load_image("fig/empty.bmp");
    vegetated = load_image("fig/vegetated.bmp");
    burning   = load_image("fig/burning.bmp");
    burnt     = load_image("fig/burnt.bmp");

    int width = s.m_field.size.x * 32;
    int height = s.m_field.size.y * 32;

    screen = SDL_SetVideoMode( width, height, 32, SDL_SWSURFACE );

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;
    SDL_Surface *fig_to_use;

    while (s.running()) {
        // loop through each cell and blit it to the screen
        for (int x = 0; x < s.m_field.size.x; ++x) {
            for (int y = 0; y < s.m_field.size.y; ++y) {
                switch (s.m_field.get(y, x)) {
                    case EMPTY:
                        fig_to_use = empty;
                        break;
                    case VEGETATED:
                        fig_to_use = vegetated;
                        break;
                    case BURNING:
                        fig_to_use = burning;
                        break;
                    case BURNT:
                        fig_to_use = burnt;
                        break;
                    default:
                        fig_to_use = empty;
                        cout << "Using default" << endl;
                        break;
                }
                
                SDL_BlitSurface(fig_to_use, NULL, screen, &rect);
                cout << "Rect: " << rect.x << ", " << rect.y << endl;

                rect.y += 32;
            }

            rect.y = 0;

            rect.x += 32;
        }

        rect.x = 0;

        SDL_Flip( screen );
        SDL_Delay( 500 );

        s.step();
        cout << endl;
    }

    SDL_Delay(5000);

    SDL_FreeSurface(empty);
    SDL_FreeSurface(vegetated);
    SDL_FreeSurface(burning);
    SDL_FreeSurface(burnt);

    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    int size;
    double density;

    cout << "What is the field size (n x n)?" << endl << "> " << flush;
    cin >> size;

    cout << "What is the veggie density?" << endl << "> " << flush;
    cin >> density;

    Simulation s(size, size, density);
    visualize(s);

    return 0;
}
