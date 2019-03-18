#include "Button.h"

Button::Button()
{
	this->show_button = false;
	this->main_image = NULL;
	this->hover_image = NULL;
	this->click_image = NULL;
}

Button::
Button(string type, float size_x, float size_y, float centre_pos_x, float centre_pos_y, const char* main_image, const char* hover_image, const char* click_image, bool show_button)
{
	this->type = type;
	this->size_x = size_x;
	this->size_y = size_y;
	this->centre_pos_x = centre_pos_x;
	this->centre_pos_y = centre_pos_y;
	this->main_image = al_load_bitmap(main_image);
	this->hover_image = al_load_bitmap(hover_image);
	this->click_image = al_load_bitmap(click_image);
	this->show_button = show_button;
}


void Button::
showButton(void)
{
	show_button = true;
}

void Button::
hideButton(void)
{
	show_button = false;
}

bool Button::
canSeeButton(void)
{
	return show_button;
}

void Button::
setType(string type)
{
	this->type = type;
}

Button::~Button()
{

}