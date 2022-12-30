#pragma once
#include "stdafx.h"

class PlayerCrossHair {

private:

	Texture Player;
	Sprite _player;

public:

	PlayerCrossHair() {
		Player.loadFromFile("Images/crosshair.png");
		_player.setTexture(Player);
		_player.setScale(0.15f, 0.15f);

		Vector2u size = Player.getSize();

		_player.setOrigin(size.x / 2.0f, size.y / 2.0f);
	}

	void Draw(RenderWindow* wnd) {
		wnd->draw(_player);
	}

	//Posiciona la mira (crosshair) segun lo que recibe
	void Positionate(float x, float y) {
		_player.setPosition(x, y);
	}

	//Recibe la posicion de la mira y se lo da al void Positionate
	Vector2f gettingPosition() {
		return _player.getPosition();
	}

};
