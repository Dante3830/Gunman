#pragma once
#include "stdafx.h"
#include "Position.h"
#include "Player.h"

class Game {

private:
	//El fondo
	Texture background;
	Sprite West;

	//Los objetos que necesita el juego
	RenderWindow* _wnd;
	PlayerCrossHair* _player;
	Position* _positions;

	//La fuente y textos
	Font font;
	Text Score;
	Text _score;
	Text Lives;
	Text _lives;
	Text GameOver;

	//Puntuacion y vidas
	int points;
	int lives;

	//Transformar el entero de puntuacion a string
	void updateScore() {
		char pts[100];
		_itoa_s(points, pts, 10);
		_score.setString(pts);
	}

	//Transformar el entero de vidas a string
	void updateLives() {
		char pts[10];
		_itoa_s(lives, pts, 10);
		_lives.setString(pts);
	}

public:

	Game() {
		_wnd = new RenderWindow(VideoMode(800, 600), "Crosshair");
		_player = new PlayerCrossHair();
		_positions = new Position[5];

		for (int i = 0; i < 5; i++) {
			_positions[i].setCoordenates(i);
		}
		
		points = 0;
		lives = 3;

		background.loadFromFile("Images/West.png");
		West.setTexture(background);

		font.loadFromFile("Retro_Gaming.ttf");

		//Mostrar el puntaje
		Score.setFont(font);
		Score.setPosition(0.0f, 0.0f);
		Score.setCharacterSize(30.0f);
		Score.setFillColor(Color::Color(115, 55, 8));
		Score.setString("Score");

		_score.setFont(font);
		_score.setPosition(0.0f, 30.0f);
		_score.setCharacterSize(30.0f);
		_score.setFillColor(Color::Black);

		//Mostrar las vidas
		Lives.setFont(font);
		Lives.setPosition(698.0f, 0.0f);
		Lives.setCharacterSize(30.0f);
		Lives.setFillColor(Color::Color(115, 55, 8));
		Lives.setString("Lives");

		_lives.setFont(font);
		_lives.setPosition(700.0f, 30.0f);
		_lives.setCharacterSize(30.0f);
		_lives.setFillColor(Color::Black);

		//Mostrar "Game Over" cuando el jugador pierda
		GameOver.setFont(font);
		GameOver.setPosition(230.0f, 250.0f);
		GameOver.setCharacterSize(50.0f);
		GameOver.setFillColor(Color::Red);
		GameOver.setString("GAME OVER");

		updateScore();
		updateLives();

	}

	//Procesamos los eventos que ocurran
	void process() {
		Event evt;

		while (_wnd->pollEvent(evt)) {
			switch (evt.type) {
			case Event::Closed:
				_wnd->close();
				break;
			case Event::MouseMoved:
				_player->Positionate(evt.mouseMove.x, evt.mouseMove.y);
				break;
			case Event::MouseButtonPressed:
				if (evt.mouseButton.button == Mouse::Button::Left)
					shoot();
				break;
			}
		}

	}
	
	//Actualizamos la posicion de los enemigos y aliados
	void update() {
		//Llamamos
		for (int i = 0; i < 5; i++) {
			_positions[i].update(_wnd);
		}
	}

	//Chequeamos colisiones con el disparo en enemigos y aliados
	void shoot() {
		Vector2f playerPos = _player->gettingPosition();

		for (int i = 0; i < 5; i++) {
			if (_positions[i].onTop(playerPos.x, playerPos.y)) {
				if (_positions[i].hasEnemy()) {
					_positions[i].defeatEnemy();
					points += 10;
				}
				else if (_positions[i].hasAlly()) {
					_positions[i].hurtAlly();
					points -= 10;
					lives--;
				}
			}
		}

		updateScore();
		updateLives();
	}

	//Dibujar los elementos de juego
	void drawing() {
		_wnd->clear();

		//El fondo del oeste
		_wnd->draw(West);

		//Se dibujan los enemigos y aliados segun la posicion
		for (int i = 0; i < 5; i++) { 
			_positions[i].Draw(_wnd);
		}

		//Texto "Score" y la puntuacion
		_wnd->draw(Score);
		_wnd->draw(_score);
		
		//Texto "Lives" y las vidas
		_wnd->draw(Lives);
		_wnd->draw(_lives);
		
		//La mira
		_player->Draw(_wnd);
		
		//Si el jugador se queda sin vidas, se termina el juego
		if (lives <= 0) {
			lives = 0;
			_wnd->draw(GameOver);
			
			delete _player;
		}

		_wnd->display();
	}

	//El juego que se cargara en el main.cpp
	void Gunman() {
		while (_wnd->isOpen()) {
			srand(time(NULL));

			process();
			update();
			drawing();
		}
	}

	~Game() {
		delete _player;
		delete[] _positions;
		delete _wnd;
	}
};
