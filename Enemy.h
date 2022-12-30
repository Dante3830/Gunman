#pragma once
#include "stdafx.h"

class Enemy {

private:

	Texture enemy;
	Sprite _enemy;

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

	Enemy(float x, float y) {
		srand(time(NULL));

		enemy.loadFromFile("Images/Enemy.png");
		_enemy.setTexture(enemy);
		_enemy.setScale(0.2f, 0.2f);
		_enemy.setPosition(x, y);

		_isAlive = true;
		isVisible = false;
		timeOn = 3.0f;
		timeOff = 1.0f;
	}

	bool isAlive() {
		return _isAlive;
	}

	bool isActive() {
		return _isAlive && isVisible;
	}

	bool onTop(float x, float y) {
		FloatRect bounds = _enemy.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Defeat() {
		_isAlive = false;
		isVisible = false;
	}

	void hide() {
		isVisible = false;
	}

	//Actualizar la posicion del enemigo
	void Update(RenderWindow* _wnd) {
		if (!_isAlive) {
			return;
		}

		//Tira una probabilidad para ver si se activa
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
			_wnd->draw(_enemy);
		}
	}

};
