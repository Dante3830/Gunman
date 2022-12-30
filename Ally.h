#pragma once
#include "stdafx.h"

class Ally {

private:

	Texture ally;
	Sprite _ally;

	bool _isAlive;
	bool isVisible;
	Clock clock;
	float timeOn;
	float timeOff;

	Vector2f _randomPos(Vector2u maxPos) {
		Vector2f random((float)(rand() % maxPos.x), (float)(rand() % maxPos.y));
		return random;
	}

public:

	Ally(float x, float y) {
		srand(time(NULL));

		ally.loadFromFile("Images/Ally.png");
		_ally.setTexture(ally);
		_ally.setScale(0.2f, 0.2f);
		_ally.setPosition(x, y);

		_isAlive = true;
		isVisible = false;
		timeOn = 3.0f;
		timeOff = 3.0f;
	}

	bool isAlive() {
		return _isAlive;
	}

	bool isActive() {
		return _isAlive && isVisible;
	}

	bool onTop(float x, float y) {
		FloatRect bounds = _ally.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Hurt() {
		_isAlive = false;
		isVisible = false;
	}

	void hide() {
		isVisible = false;
	}

	//Actualizar la posicion del aliado
	void Update(RenderWindow* _wnd) {
		if (!_isAlive) {
			return;
		}

		//Tira una posibilidad para ver si se activa
		if (!isVisible) {

			if (clock.getElapsedTime().asSeconds() > timeOff) {
				clock.restart();

				if (rand() % 100 < 50) {
					isVisible = true;
				}
			}

		} else {
			//Cuando pasa el tiempo, el enemigo se va
			if (clock.getElapsedTime().asSeconds() > timeOn) {
				isVisible = false;
				clock.restart();
			}
		}
	}

	void Draw(RenderWindow* _wnd) {
		if (isVisible) {
			_wnd->draw(_ally);
		}
	}
	
};
