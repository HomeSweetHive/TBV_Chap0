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

	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	m_pKeyboard = std::make_unique<Keyboard>();
	return true;
}

void Game::ProcessEvents()
{
	// Get the number of Console Inputs
	if (!GetNumberOfConsoleInputEvents(m_hConsoleIn, &m_NumRead))
	{
		DWORD error = GetLastError();
		TBV_ERROR("Failed to get number of console input events." + error);
		return;
	}

	if (m_NumRead <= 0)
	{
		return;
	}

	if (!PeekConsoleInput(m_hConsoleIn, m_InRecBuff, 128, &m_NumRead))
	{
		DWORD error = GetLastError();
		TBV_ERROR("Failed to Peek Events." + error);
		return;
	}

	for (int i = 0; i < m_NumRead; i++)
	{
		switch (m_InRecBuff[i].EventType)
		{
		case KEY_EVENT:
			// TODO: Create function to process key events
			KeyEventProcess(m_InRecBuff[i].Event.KeyEvent);
			break;
		default:
			break;
		}
	}

	// Clear or flush other input events
	FlushConsoleInputBuffer(m_hConsoleIn);
}

void Game::ProcessInputs()
{
	if (m_pKeyboard->IsKeyJustPressed(KEY_ESCAPE))
	{
		m_bIsRunning = false;
	}
}

void Game::Update() 
{
	m_pKeyboard->Update();
}

void Game::Draw() 
{
	m_pConsole->Write(10, 10, L"The Broken Veil - Chapter 0: Initial Testing");
	m_pConsole->Draw();
}

void Game::KeyEventProcess(KEY_EVENT_RECORD keyEvent)
{
	if (keyEvent.bKeyDown)
	{
		m_pKeyboard->OnKeyDown(keyEvent.wVirtualKeyCode);
	}
	else
	{
		m_pKeyboard->OnKeyUp(keyEvent.wVirtualKeyCode);
	}
}

Game::Game()
	: m_bIsRunning(true)
	, m_pConsole{ nullptr }
	, m_pKeyboard{ nullptr }
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
		ProcessEvents();
		ProcessInputs();
		Update();
		Draw();
	}
	std::cout << "Bye Bye" << std::endl;
}