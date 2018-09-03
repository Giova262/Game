/*
 * Personaje.cpp
 *
 *  Created on: 02/09/2018
 *      Author: gio
 */

#include "Personaje.h"
#include "TexturaGenerador.h"

Personaje::Personaje(const char* nombre,SDL_Renderer* ren) {

	renderer = ren ;
	personajeTextura = TexturaGenerador::cargarTextura(nombre,renderer);

	pos =0;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x= 0;
	srcRect.y = 0;

	desRect.h = 64;
	desRect.w = 64 ;
	desRect.x = 150 ;
	desRect.y = 150 ;

	spriteNames[0]= "4.png";
	spriteNames[1]= "5.png";
	spriteNames[2]= "6.png";
	spriteNames[3]= "5.png";

}

Personaje::~Personaje() {

}

void Personaje::eventos(SDL_Event evento){

	 switch(evento.key.keysym.sym){

	        case SDLK_SPACE:
	        	personajeTextura = TexturaGenerador::cargarTextura("7.png",renderer);

	        	desRect.y = desRect.y -4 ;
	            break;
	        case SDLK_LEFT:

	            personajeTextura = TexturaGenerador::cargarTextura("1.png",renderer);
	            desRect.x = desRect.x-3;
	            break;
	        case SDLK_RIGHT:

		         personajeTextura = TexturaGenerador::cargarTextura("1.png",renderer);
		         desRect.x = desRect.x+3;
	            break;
	        case SDLK_DOWN:
	        	personajeTextura = TexturaGenerador::cargarTextura("2.png",renderer);
	            desRect.y = desRect.y + 4;
	            break;
	        default:
	            break;
	    }
}

void Personaje:: actualizar(){
	personajeTextura = TexturaGenerador::cargarTextura(spriteNames[pos],renderer);
	pos++;
	if(pos == 4) pos =0 ;
}

void Personaje::renderizar(){
	SDL_RenderCopy(renderer,personajeTextura,NULL,&desRect);
}

void Personaje::limpiar(){

	spriteNames[0] = NULL;
	spriteNames[1] = NULL;
	spriteNames[2] = NULL;
	spriteNames[3] = NULL;
	SDL_DestroyTexture(personajeTextura);

}
