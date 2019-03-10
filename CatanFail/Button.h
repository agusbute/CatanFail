#pragma once

#include <iostream>
#include <string>

using namespace std;

class Button
{
	public:
		Button();	//por defecto show_button = false y las imagenes NULL
		/*por lo que entend� necesito las coordenadas del cetro del bot�n y el tama�o, hay que hacerlo con porcentajes*/
		Button(string type, float size_x, float size_y, float centre_pos_x, float centre_pos_y, const char* main_image, const char* hover_image, const char* click_image, bool show_button = 0); //faltan las imagenes
		void showButton(void);	// show_button = true
		void hideButton(void);	//show_button = false
		bool canSeeButton(void);	// devuelve el valor de show_button
		void setType(string type);	//settea el tipo de boton que es

		~Button();

	private:
		string type;
		bool show_button;	//false si el boton no deber�a visualizarse en el display
		float size_x;	//tama�o del bot�n
		float size_y;
		float centre_pos_x;	//posicion del centro del bot�n
		float centre_pos_y;
		ALLEGRO_BITMAP* main_image;
		ALLEGRO_BITMAP* hover_image;
		ALLEGRO_BITMAP* click_image;

		// despu�s las imagenes originales y la que se pone cuando el mouse est� sobre la zona

};