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

	float enemyX;
	float enemyY;

	Vector2f _randomPos(Vector2u maxPos) {
		Vector2f random((float)(rand() % maxPos.x), (float)(rand() % maxPos.y));
		return random;
	}

public:

	Enemy(float x, float y) {
		srand(time(NULL));

		enemyX = x;
		enemyY = y;

		enemy.loadFromFile("Images/Enemy.png");
		_enemy.setTexture(enemy);
		_enemy.setScale(0.2f, 0.2f);
		_enemy.setPosition(enemyX, enemyY);

		_isAlive = true;
		isVisible = false;
		timeOn = 1.5f;
		timeOff = 0.5f;
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
	bool Update(RenderWindow* _wnd) {
		if (!_isAlive) {
			return false;
		}

		//Tira una probabilidad para ver si se activa
		if (!isVisible) {

			if (clock.getElapsedTime().asSeconds() > timeOff) {
				clock.restart();

				if (rand() % 100 < 50) {
					isVisible = true;

					enemy.loadFromFile("Images/Enemy.png");
					_enemy.setTexture(enemy);
					_enemy.setScale(0.2f, 0.2f);
					_enemy.setPosition(enemyX, enemyY);
				}
			}

		} else {
			//Cuando pasa el tiempo, el enemigo se va o dispara
			if (clock.getElapsedTime().asSeconds() > timeOn) {

				if (rand() % 100 < 10) {
					enemy.loadFromFile("Images/EnemyB.png");
					_enemy.setTexture(enemy);
					_enemy.setScale(0.2f, 0.2f);
					_enemy.setPosition(enemyX, enemyY);

					clock.restart();
					return true;
				}
				else {
					isVisible = false;
				}

				clock.restart();
			}
		}

		return false;
	}

	void Draw(RenderWindow* _wnd) {
		if (isVisible) {
			_wnd->draw(_enemy);
		}
	}

};
