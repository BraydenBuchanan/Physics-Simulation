#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include <MainMenu.hpp>
#include <Engine.hpp>
#include <RigidBodies.hpp>
#include <Objects.hpp>
#include <Pendulum.hpp>
#include <DoublePendulum.hpp>
#include <SoftBody.hpp>
#include <Assets.hpp>

const uint32_t FRAMERATE = 120;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Physics Simulation", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	sf::Clock clock;

	window.setFramerateLimit(FRAMERATE);

	MainMenu menu("Play", "Exit", "Physics Simulation");
	menu.setPos({ 450.f, 350.f });

	Engine engine;

	Rigid rigid;

	Assets assets;

	SoftBody softBody(0.5f, 0.5f, 15000.f);
    bool enable = false, reset = true, isSpawn = false;

	Pendulum pendulum(100, 200, window.getSize().x / 2.f, 0.f);
	pendulum.setScale({ 0.f, 0.f });

	DoublePendulum doublePendulum(100, 200, window.getSize().x / 2.f, 0.f);
	DoublePendulum doublePendulum2(100, 200, &doublePendulum);
	doublePendulum2.setScale({ 0.f, 0.f });

	std::vector<Objects> objects;
	objects.push_back({ Objects({450.f, 75.f}, {450.f, 450.f}, sf::Color::Black) });

	objects.push_back({ Objects({10.f, 800.f}, {-5.f, 400.f}, sf::Color::Black) });
	objects.push_back({ Objects({1000.f, 10.f}, {500.f, -5.f}, sf::Color::Black) });

	engine.setPosRBUI({ 760.f, 30.f });
	engine.setPosPENUI({ 880.f, 30.f });

	engine.setPosRBUI({ 760.f, 30.f });
	engine.setPosPENUI({ 880.f, 30.f });
	engine.setPosSBUI({ 760.f, 100.f });

	bool isPlay = false;

	// MUSIC

	sf::Music musicForMainMenu;
	sf::Music musicForGamePlay;

	musicForMainMenu.openFromFile(assets.musicForMainMenu);
	musicForGamePlay.openFromFile(assets.musicForGamePlay);

	musicForMainMenu.play();
	musicForMainMenu.setLoop(true);

	/****************************************************/

	assets.printPaths();

	while (window.isOpen())
	{
		window.clear(sf::Color(150, 150, 150));

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		while (window.pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				window.close();
			}

			else if (enable)
			{
				if (event.type == event.MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left && !engine.isMouseOverSBpanel(pos) && !engine.isMouseOverSelectBar(pos))
						softBody.addPoint({ (float)pos.x, (float)pos.y });
				}

				if (event.type == event.MouseButtonPressed)
					if (event.mouseButton.button == sf::Mouse::Right)
					{
						reset = false;
						enable = false;
					}
			}

			// MENU:

			if (!isPlay)
			{
				menu.isMouseOverPlayButton(pos);

				if (menu.isMouseOverPlayButton(pos)) { menu.setBGColorPlayButton(sf::Color(150, 150, 150)); }
				else { menu.setBGColorPlayButton(sf::Color(128, 128, 128)); }

				if (menu.isMouseClickedPlayButton(pos))
				{
					isPlay = true;

					musicForMainMenu.stop();

					musicForGamePlay.play();
					musicForGamePlay.setLoop(true);
				}

				menu.isMouseOverExitButton(pos);

				if (menu.isMouseOverExitButton(pos)) { menu.setBGColorExitButton(sf::Color(255, 87, 51)); }
				else { menu.setBGColorExitButton(sf::Color::Red); }

				if (menu.isMouseClickedExitButton(pos))
					window.close();
			}

			/****************************************************/

			// RIGID BODIES:

			if (isPlay)
			{
				engine.isMouseOverRBUI(pos);

				if (engine.isMouseOverRBUI(pos)) { engine.setBGColorRBUI(sf::Color(185, 185, 185)); }
				else { engine.setBGColorRBUI(sf::Color(205, 205, 205)); }
			}

			if (isPlay)
			{
				engine.isMouseOverRBsquare(pos);

				if (engine.isMouseOverRBsquare(pos)) { engine.setBGColorRBsquare(sf::Color(185, 185, 185)); }
				else { engine.setBGColorRBsquare(sf::Color(205, 205, 205)); }

				if (engine.isMouseClickedRBsquare(pos))
					engine.setRBstatus(pos);

				engine.isMouseOverRBcircle(pos);

				if (engine.isMouseOverRBcircle(pos)) { engine.setBGColorRBcircle(sf::Color(185, 185, 185)); }
				else { engine.setBGColorRBcircle(sf::Color(205, 205, 205)); }

				if (engine.isMouseClickedRBcircle(pos))
					engine.setRBstatus(pos);
			}

			if (isPlay)
			{
				engine.isMouseOverRBreset(pos);

				if (engine.isMouseOverRBreset(pos)) { engine.setBGColorRBreset(sf::Color(255, 87, 51)); }
				else { engine.setBGColorRBreset(sf::Color::Red); }

				if (engine.isMouseClickedRBreset(pos))
				{
					engine.setRBstatus(pos);

					rigid.setScaleCircle({ 0.f, 0.f });
					rigid.setScaleSquare({ 0.f, 0.f });
				}
			}

			if (isPlay)
			{
				engine.isSpawnRBsquare(pos);

				if (engine.isSpawnRBsquare(pos))
				{
					rigid.spawnSquare(pos);
					rigid.setScaleSquare({ 1.f, 1.f });
				}

				engine.isSpawnRBcircle(pos);

				if (engine.isSpawnRBcircle(pos))
				{
					rigid.spawnCircle(pos);
					rigid.setScaleCircle({ 1.f, 1.f });
				}
			}

			/****************************************************/

			// PENDULUM:

			if (isPlay)
			{
				engine.isMouseOverPENUI(pos);

				if (engine.isMouseOverPENUI(pos)) { engine.setBGColorPENUI(sf::Color(185, 185, 185)); }
				else { engine.setBGColorPENUI(sf::Color(205, 205, 205)); }
			}

			if (isPlay)
			{
				engine.isMouseOverDPB(pos);

				if (engine.isMouseOverDPB(pos)) { engine.setBGColorDPB(sf::Color(185, 185, 185)); }
				else { engine.setBGColorDPB(sf::Color(205, 205, 205)); }

				if (engine.isMouseClickedDPB(pos))
				{
					objects[0].setScale({ 0.f, 0.f });

					pendulum.setScale({ 0.f, 0.f });
					engine.setPENstatus(pos);
				}

				engine.isMouseOverPB(pos);

				if (engine.isMouseOverPB(pos)) { engine.setBGColorPB(sf::Color(185, 185, 185)); }
				else { engine.setBGColorPB(sf::Color(205, 205, 205)); }

				if (engine.isMouseClickedPB(pos))
				{
					objects[0].setScale({0.f, 0.f});

					doublePendulum2.setScale({ 0.f, 0.f });
					engine.setPENstatus(pos);
				}
			}

			if (isPlay)
			{
				engine.isMouseOverPENreset(pos);

				if (engine.isMouseOverPENreset(pos)) { engine.setBGColorPENreset(sf::Color(255, 87, 51)); }
				else { engine.setBGColorPENreset(sf::Color::Red); }
				
				if (engine.isMouseClickedPENreset(pos))
				{
					objects[0].setScale({ 1.f, 1.f });

					doublePendulum2.setScale({ 0.f, 0.f });
					pendulum.setScale({ 0.f, 0.f });
					engine.setPENstatus(pos);
				}
			}

			if (isPlay)
			{
				engine.isSpawnPendulum(pos);

				if (engine.isSpawnPendulum(pos))
					pendulum.setScale({ 1.f, 1.f });

				engine.isSpawnDPendulum(pos);

				if (engine.isSpawnDPendulum(pos))
					doublePendulum2.setScale({ 1.f, 1.f });
			}

			/****************************************************/

			// SOFTBODY:

			if (isPlay)
			{
				engine.isMouseOverSBUI(pos);

				if (engine.isMouseOverSBUI(pos)) { engine.setBGColorSBUI(sf::Color(185, 185, 185)); }
				else { engine.setBGColorSBUI(sf::Color(205, 205, 205)); }
			}

			if (isPlay)
			{
				engine.isMouseOverSBAB(pos);

				if (engine.isMouseOverSBAB(pos)) { engine.setBGColorSBAB(sf::Color(185, 185, 185)); }
				else { engine.setBGColorSBAB(sf::Color(205, 205, 205)); }
		
				engine.isMouseClickedSBAB(pos);

				if (engine.isMouseClickedSBAB(pos))
					engine.setSBstatus(pos);
			}

			if (isPlay)
			{
				engine.isMouseOverSBreset(pos);

				if (engine.isMouseOverSBreset(pos)) { engine.setBGColorSBreset(sf::Color(255, 87, 51)); }
				else { engine.setBGColorSBreset(sf::Color::Red); }

				engine.isMouseClickedSBreset(pos);

				if (engine.isMouseClickedSBreset(pos))
				{
					softBody.clear();
					engine.setSBstatus(pos);

					reset = true;
					enable = true;
					isSpawn = false;
				}
			}

			if (isPlay)
			{
				engine.isSpawnSoftBody(pos);

				if (engine.isSpawnSoftBody(pos))
					isSpawn = true;

				if (isSpawn)
				{
					if (reset)
						enable = true;
				}

				else
					softBody.clear();
			}

			/****************************************************/
		}

		doublePendulum.dragPendulum(pos);
		doublePendulum2.dragPendulum(pos);

		pendulum.dragPendulum(pos);

		doublePendulum.Update(pos);
		doublePendulum2.Update(pos);

		pendulum.Update(pos);

		rigid.UpdateSquare();
		rigid.checkCollisionWithSquareToWindow(window);

		rigid.UpdateCircle();
		rigid.checkCollisionWithCircleToWindow(window);

		if (!enable)
		{
			softBody.Move(0.25f);

			for (auto& object : objects)
			{
				if (object)
					softBody.checkCollisionWithObjects(object, 0.f);
			}

			if (rigid.checkScaleSquare())
				softBody.checkCollisionWithSquare(rigid, 0.f);

			if (rigid.checkScaleCircle())
				softBody.checkCollisionWithCircle(rigid, 0.f);

			softBody.checkCollisionWithWindow(window);
			softBody.acceleratePoints();
		}

		for (auto& object : objects)
		{
			if (object)
			{
				rigid.checkCollisionWithSquareToObjects(object, 0.f);
				rigid.checkCollisionWithCircleToObjects(object, 0.f);
			}
		}

		if (!isPlay)
			menu.Draw(window);

		if (isPlay)
		{
			if (rigid.checkScaleSquare() && rigid.checkScaleCircle())
				rigid.checkCollisionWithCircleToSquare();

			for (auto& object : objects)
				object.Draw(window);

			rigid.Draw(window);
			pendulum.Draw(window);

			doublePendulum.Draw(window);
			doublePendulum2.Draw(window);

			softBody.Draw(window, sf::Color::Black);

			engine.createRigidBodyPanel(pos);
			engine.createPendulumPanel(pos);
			engine.createSoftbodyPanel(pos);

			engine.Draw(window, { pos.x, pos.y });
		}

		window.display();
	}
}
