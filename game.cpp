#include "game.h"
#include <iostream>
#include "logger.h"
bool Game::Init() 
{
	try
	{
		m_pConsole = std::make_unique < Console>();
	}
	catch (std::exception& e)
	{
		std::string error = e.what();
		TBV_ERROR(error);
		return false;
	}

	return true;
}

void Game::ProcessInputs() 
{
	
}

void Game::Update() 
{
	
}

void Game::Draw() 
{
	m_pConsole->Write(10, 10, L"The Broken Veil - Chapter 0: Initial Testing");
	m_pConsole->Draw();
}

Game::Game()
	: m_bIsRunning(true)
{

}

Game::~Game() 
{

}

void Game::Run()
{
	if (!Init())
	{
		m_bIsRunning = false;
	}

	while (m_bIsRunning)
	{
		ProcessInputs();
		Update();
		Draw();
	}
	std::cout << "Bye Bye" << std::endl;
}