#pragma once

#include "stdafx.h"
#include "Bat.h"
#include "Ball.h"
#include "AIBat.h"
#include "Constants.h"

class Game {
private:
    Font font;
    SoundBuffer buffer;
    Sound music;

    Text title;
    Text startMessage;

    Text _BatScore;
    Text _aiBatScore;

    Text finishMessage1;
    Text finishMessage2;

    void updateBatScore() {
        char bts[10];
        _itoa_s(batScore, bts, 10);
        _BatScore.setString(bts);
    }

    void updateAiBatScore() {
        char aibts[10];
        _itoa_s(aiBatScore, aibts, 10);
        _aiBatScore.setString(aibts);
    }

public:

    Game() {
        // Mensaje del inicio
        title.setCharacterSize(90);
        title.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        title.setFont(font);
        title.setFillColor(Color::Color(21, 182, 185));
        title.setString("     PONG");

        startMessage.setCharacterSize(30);
        startMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage.setFont(font);
        startMessage.setString("\n\n\n\n\n\n\n\n      Presiona las flechas para iniciar");

        // Mensaje de victoria
        finishMessage1.setCharacterSize(30);
        finishMessage1.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        finishMessage1.setFont(font);
        finishMessage1.setFillColor(Color::White);
        finishMessage1.setString("                 ¡Ganaste!\n\n   Presiona cualquier tecla para reiniciar");

        // Mensaje de derrota
        finishMessage2.setCharacterSize(30);
        finishMessage2.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        finishMessage2.setFont(font);
        finishMessage2.setFillColor(Color::White);
        finishMessage2.setString("                 Perdiste...\n\n   Presiona cualquier tecla para reiniciar");

        //Mostrar puntaje del jugador
        _BatScore.setCharacterSize(60);
        _BatScore.setPosition(800.0f, 100.0f);
        _BatScore.setFont(font);
        _BatScore.setFillColor(Color::White);

        //Mostrar puntaje de la IA
        _aiBatScore.setCharacterSize(60);
        _aiBatScore.setPosition(200.0f, 100.0f);
        _aiBatScore.setFont(font);
        _aiBatScore.setFillColor(Color::White);

        updateBatScore();
        updateAiBatScore();
    }

    void musicAndFont() {
        //Cargando la fuente 
        font.loadFromFile("VCR_OSD_MONO.ttf");

        //Seteando la musica
        buffer.loadFromFile("MainMusic.wav");
        music.setBuffer(buffer);
    }

    //void logic() {

    //}

    void pong() {
        RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

        //Creando los objetos
        Bat bat(20, windowHeight / 2);
        Ball ball(windowWidth / 2 + 50, windowHeight / 2);
        AIBat aibat(windowWidth - 40, windowHeight / 2);

        musicAndFont();

        while (window.isOpen()) {

            // Limpiar y dibujar fondo
            window.clear(Color(34, 34, 34, 100));

            window.setFramerateLimit(480);

            music.play();

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == event.Closed) {
                    window.close();
                }
            }

            // Controles del usuario
            if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Up)) {
                bat.moveBatUp();
            }
            else if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Down)) {
                bat.moveBatDown();
            }

             // Logica
            ball.reboundSides();
            ball.passLeft();
            ball.passRight();

            if (ball.getBallFloatRect().intersects(bat.getBatFloatRect())) {
                ball.reboundBatorAI();
            }

            if (ball.getBallFloatRect().intersects(aibat.getAIBatFloatRect())) {
                ball.reboundBatorAI();
            }

            if (ball.getBallFloatRect().top > (aibat.getAIBatFloatRect().top) + 50) {
                if (aiBatCounter % 60 == 0) {
                    aibat.moveAIBatDown();
                }
            }

            if (ball.getBallFloatRect().top < (aibat.getAIBatFloatRect().top) + 50) {
                if (aiBatCounter % 60 == 0) {
                    aibat.moveAIBatUp();
                }
            }

            if (ball.getBallPosition.x > windowWidth) {
                aibat.AIBatSpeedReverse();
            }

             // Actualizacion
            if (aiBatCounter == 1000000) {
                aiBatCounter = 0;
            }

            aiBatCounter++;
            
            ball.update();
            bat.update();
            aibat.update();

            // Textos e iniciacion //

            if (batScore == 10) {
                //En caso de victoria
                window.draw(finishMessage1);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatScore = 0;
                    batScore = 0;
                    ball.resetVelocity();
                }

            } else if (aiBatScore == 10) {
                //En caso de derrota
                window.draw(finishMessage2);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatScore = 0;
                    batScore = 0;
                    ball.resetVelocity();
                }

            } else if (batScore == -1) {
                window.draw(title);
                window.draw(startMessage);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatScore = 0;
                    batScore = 0;

                    //Mostrar puntaje de cada uno
                    window.draw(_BatScore);
                    window.draw(_aiBatScore);

                    ball.resetVelocity();
                }

            } else {
                window.draw(bat.getBatObject());
                window.draw(ball.getBallObject());
                window.draw((aibat.getAIBatObject()));
            }

            window.display();
        }
    }
};
