#include "Juego.h"
#include "Encabesados.h"
#include "Personaje.h"

SDL_Rect srcR,desR;

Personaje* Gio;
Uint32 frameStart , frameTiempo;

Juego::Juego(){ enEjecucion=true;}

Juego::~Juego(){}

void Juego::juegoInicializacion(){

    if( SDL_Init(SDL_INIT_EVERYTHING) == 0 ){
        std::cout << "Se inicio correctamente el SDL"<<std::endl;
        //Create window
        window = SDL_CreateWindow("Synergy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window){
            std::cout<<"Se creo la ventana"<<std::endl;
        }
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer){
            std::cout<<"Se creo el renderer"<<std::endl;
            SDL_SetRenderDrawColor(renderer,255,255,255,200);
        }

        enEjecucion=true;
    }else{
        std::cout << " Fallo al iniciar el SDL "<<std::endl;
        enEjecucion=false;
    }

    Gio = new Personaje("personaje.png",renderer);
}

void Juego::eventosManejo(){

	SDL_Event evento;

	frameStart = SDL_GetTicks();

    while(SDL_PollEvent(&evento)){
    	if(evento.type == SDL_QUIT){ enEjecucion = false ;}
    	Gio->eventos(evento);
    }

    Gio->actualizar();

    frameTiempo = SDL_GetTicks() - frameStart;
    if( 250 > frameTiempo){
            SDL_Delay( 250- frameTiempo );
    }

}

void Juego::actualizar(){

}

void Juego::renderizar(){

    //LIMPIA EL RENDER ENTERO CON EL COLOR QUE SE LE DIO
    SDL_RenderClear(renderer);
    //Copy a portion of the texture to the current rendering target.
    Gio->renderizar();
    // SDL_RenderCopy(renderer,personajeTextura,NULL,&desR);
    //ACTUALIZA LA PANTALLA CON EL RENDER REALIZADO
    SDL_RenderPresent(renderer);
}

void Juego:: limpiar(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<std::endl<<"Se cerro el juego correctamente"<<std::endl;
}
