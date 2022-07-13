#pragma once
#include <Core/Core.hpp>

static bool wakeup { false };
static bool init { false };

class Framework
{
private:
	EventType MenuEvent;
	Vector2 NextItemPos;
	Vector2 WindowPos { 60, 60 };
	Vector2 WindowSize;
	Vector2 MousePos, OldMousePos;
	Vector2 WidgetMousePos, OldWidgetMousePos;
	bool MouseState, OldMouseState;
	bool InsertState, OldInsertState;
	bool WidgetState, OldWidgetState;
	bool Interacting;
	bool MenuOpen { false };
	auto ContainsMouse( const Vector2& Pos1, const Vector2& Pos2 ) -> bool
	{

	}
public:
	auto Begin( const std::string& Text, const Vector2& WindowPos, const Vector2& WindowSize ) -> bool
	{
		auto TextW = std::wstring( Text.begin( ), Text.end( ) );

		if ( !init )
		{
			this->WindowPos = WindowPos;
			init = true;
		}

		auto keyCode = Event::current( )->keyCode( );
		this->WindowSize = WindowSize;
		this->MenuEvent = Event::current( )->type( );
		this->InsertState = MenuEvent == EventType::KeyDown && keyCode == KeyCode::Insert;
		this->MousePos.x = Input::mousePosition( ).x;
		this->MousePos.y = Screen::height( ) - Input::mousePosition( ).y;

		if ( this->InsertState && !OldInsertState )
			this->MenuOpen = !this->MenuOpen;

		if ( !this->MenuOpen )
			return false;

		//if ( ContainsMouse( Vector2( WindowPos.x, WindowPos.y ), Vector2( WindowPos.x + WindowSize.x, WindowPos.y + 20 ) ) && this->MouseState && g_ctx.GUIOpen )
		{
			this->WindowPos.x += MousePos.y - OldMousePos.y;
			this->WindowPos.y += MousePos.y - OldMousePos.y;
		}

		if ( MenuEvent == EventType::Repaint )
		{
			Rendering::GetInstance( )->add_rect_filled( WindowPos.x, WindowPos.y, WindowSize.x + 1, WindowSize.y + 1, Color( 24, 24, 24 ) );
			Rendering::GetInstance( )->add_rect_filled( WindowPos.x, WindowPos.y, WindowSize.x + 1, 15, Color( 28, 28, 28 ) );
			Rendering::GetInstance( )->add_rect_filled( WindowPos.x, WindowPos.y + 16, WindowSize.x + 1, 10, Color( 17, 17, 17 ) );
			Rendering::GetInstance( )->add_rect( WindowPos.x, WindowPos.y, WindowSize.x + 1, WindowSize.y + 1, { 0, 0, 0 } );
			Rendering::GetInstance( )->add_text( WindowPos.x + 6, WindowPos.y, TextW.c_str( ), Color( 255, 255, 255 ) );
		}

		return true;
	}
	auto Text( const std::string& Text, const Vector2& Pos, const Vector2& Size ) -> void;
	auto DrawTabs( const std::vector<std::string> names ) -> void;
	auto Slider( const std::string Text, int min, int max, const std::string& Format ) -> void;
	auto End( ) -> void;

};