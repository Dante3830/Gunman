#pragma once
#include "stdafx.h"
#include "Enemy.h"
#include "Ally.h"

class Position {
private:
	Enemy* _enemy = NULL;
	Ally* _ally = NULL;

	float coordX;
	float coordY;

public:

	Position() {
		
	}

	bool onTop(float x, float y) {
		if (_enemy) {
			if (_enemy->onTop(x, y)) {
				_enemy->Defeat();
				return true;
			}
		}
		else if (_ally) {
			if (_ally->onTop(x, y)) {
				_ally->Hurt();
				return true;
			}
		}

		return false;
	}

	bool hasEnemy() {
		if (_enemy) {
			return true;
		}
		else {
			return false;
		}
	}
	
	bool hasAlly() {
		if (_ally) {
			return true;
		}
		else {
			return false;
		}
	}

	void defeatEnemy() {
		delete _enemy;
		_enemy = NULL;
	}

	void hurtAlly() {
		delete _ally;
		_ally = NULL;
	}

	void Draw(RenderWindow* _wnd) {
		if (_enemy) {
			_enemy->Draw(_wnd);
		}

		if (_ally) {
			_ally->Draw(_wnd);
		}
	}

	void setCoordenates(int position) {
		switch (position) {
		case 0:
			//Ventana superior izquierda
			coordX = 150.0f;
			coordY = 150.0f;
			break;
		case 1:
			//Ventana superior derecha
			coordX = 550.0f;
			coordY = 150.0f;
			break;
		case 2:
			//Ventana inferior izquierda
			coordX = 150.0f;
			coordY = 370.0f;
			break;
		case 3:
			//Puerta de entrada
			coordX = 330.0f;
			coordY = 370.0f;
			break;
		case 4:
			//Ventana inferior derecha
			coordX = 550.0f;
			coordY = 370.0f;
			break;
		}
	}

	void update(RenderWindow* _wnd) {
		if (_enemy) {
			_enemy->Update(_wnd);
		} else if (_ally) {
			_ally->Update(_wnd);
		} else {
			if (rand() % 100 < 50) {
				_enemy = new Enemy(coordX, coordY);
			} else if (rand() % 100 < 50) {
				_ally = new Ally(coordX, coordY);
			}
		}
	}

};
