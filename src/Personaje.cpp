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
	rebote = true;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x= 0;
	srcRect.y = 0;

	desRect.h = 64;
	desRect.w = 64 ;
	desRect.x = 200 ;
	desRect.y = 200 ;

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
					if(rebote){
						saltando();
						rebote = false;
						break;
					}

					rebote = true ;
					break;

	        case SDLK_LEFT:

	            personajeTextura = TexturaGenerador::cargarTextura("1.png",renderer);
	            desRect.x = desRect.x-3;
	            break;
	        case SDLK_RIGHT:
	        	if(rebote){
	        			caminando();
	        			rebote = false;
	        				break;
	        		}

	        		rebote = true ;
	        		break;
		        /* personajeTextura = TexturaGenerador::cargarTextura("1.png",renderer);
		         desRect.x = desRect.x+3;
	            break;*/
	        case SDLK_DOWN:
	        	personajeTextura = TexturaGenerador::cargarTextura("2.png",renderer);
	            //desRect.y = desRect.y + 4;
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

void Personaje::saltando(){
	for(int i=0 ; i < 15 ; i++){
		desRect.y = desRect.y -5 ;
		SDL_RenderClear(renderer);
		personajeTextura = TexturaGenerador::cargarTextura("7.png",renderer);
		renderizar();
		SDL_RenderPresent(renderer);
		SDL_Delay(15);
	}
	for(int i=0 ; i < 14 ; i++){
		 desRect.y = desRect.y +5 ;
		 SDL_RenderClear(renderer);
		 personajeTextura = TexturaGenerador::cargarTextura("8.png",renderer);
		 renderizar();
	     SDL_RenderPresent(renderer);
		 SDL_Delay(15);
	}
	desRect.y = desRect.y +5 ;
	SDL_RenderClear(renderer);
	personajeTextura = TexturaGenerador::cargarTextura("1.png",renderer);
	renderizar();
	SDL_RenderPresent(renderer);
	SDL_Delay(30);
}

void Personaje::caminando(){
	for(int i=0 ; i < 3 ; i++){
			desRect.x = desRect.x +1  ;
			SDL_RenderClear(renderer);
			personajeTextura = TexturaGenerador::cargarTextura(spriteNames[i],renderer);
			renderizar();
			SDL_RenderPresent(renderer);
			SDL_Delay(15);
	}

}
