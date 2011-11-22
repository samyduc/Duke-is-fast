#include "InputState.hpp"

#define PATH_CONTROLS "./Res/Config/"

InputState::InputState()
{
	//cursor_id = CKernel::uniqueID();
	//CKernel::addEntity(cursor_id, "cursor");
	cursor_position = new Point2d<float>(0.f, 0.f);

	m_continue = true;
}

InputState::~InputState()
{
	delete cursor_position;
}

bool InputState::update()
{
	sf::RenderWindow *window = CKernel::graphic()->getWindow();
	sf::Event Event;


	while (window->GetEvent(Event))
	{
		if (Event.Type == sf::Event::Closed)
		{
			window->Close();
			m_continue = false;
		}
		else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
		{
			window->Close();
			m_continue = false;
		}
		else if(Event.Type == sf::Event::KeyPressed)
		{
			m_keyMap_t::right_const_iterator right_it = m_keyMap.right.find(Event.Key.Code);
			if(right_it != m_keyMap.right.end())
			{
				// action to send to gameLogic !
				m_actionMap[right_it->second] = true;
				CKernel::input()->doAction(right_it->second);
			}
		}
		else if(Event.Type == sf::Event::KeyReleased)
		{
			m_keyMap_t::right_const_iterator right_it = m_keyMap.right.find(Event.Key.Code);
			if(right_it != m_keyMap.right.end())
			{
				m_actionMap[right_it->second] = false;
			}
		}
		else if(Event.Type == sf::Event::MouseButtonPressed)
		{
			m_mouseMap_t::right_const_iterator right_it = m_mouseMap.right.find(Event.MouseButton.Button);
			if(right_it != m_mouseMap.right.end())
			{
				// action to send to gameLogic !
				CKernel::input()->doAction(right_it->second);
			}
		}
		else if(Event.Type == sf::Event::MouseMoved)
		{
				float x_mouse = boost::lexical_cast<float>(Event.MouseMove.X);
				float y_mouse =  boost::lexical_cast<float>(Event.MouseMove.Y);
				//const Point2d<float> cursor_temp(x_mouse, y_mouse);
				cursor_position->setX(x_mouse);
				cursor_position->setY(y_mouse);
				CKernel::graphic()->setPosition(cursor_id, *cursor_position);
		}
	}
    return (m_continue);
}

sf::Key::Code InputState::getApiKey(std::string input)
{
	sf::Key::Code toReturn;
	if(input == "Escape") toReturn = sf::Key::Escape;
	else if(input == "LControl") toReturn = sf::Key::LControl;
	else if(input == "LAlt") toReturn = sf::Key::LAlt;
	else if(input == "LSystem") toReturn = sf::Key::LSystem;
	else if(input == "RControl") toReturn = sf::Key::RControl;
	else if(input == "RShift") toReturn = sf::Key::RShift;
	else if(input == "RAlt") toReturn = sf::Key::RAlt;
	else if(input == "RSystem") toReturn = sf::Key::RSystem;
	else if(input == "Menu") toReturn = sf::Key::Menu;
	else if(input == "LBracket") toReturn = sf::Key::LBracket;
	else if(input == "RBracket") toReturn = sf::Key::RBracket;
	else if(input == "SemiColon") toReturn = sf::Key::SemiColon;
	else if(input == "Comma") toReturn = sf::Key::Comma;
	else if(input == "Period") toReturn = sf::Key::Period;
	else if(input == "Quote") toReturn = sf::Key::Quote;
	else if(input == "Slash") toReturn = sf::Key::Slash;
	else if(input == "BackSlash") toReturn = sf::Key::BackSlash;
	else if(input == "Tilde") toReturn = sf::Key::Tilde;
	else if(input == "Equal") toReturn = sf::Key::Equal;
	else if(input == "Dash") toReturn = sf::Key::Dash;
	else if(input == "Space") toReturn = sf::Key::Space;
	else if(input == "Return") toReturn = sf::Key::Return;
	else if(input == "Back") toReturn = sf::Key::Back;
	else if(input == "Tab") toReturn = sf::Key::Tab;
	else if(input == "PageUp") toReturn = sf::Key::PageUp;
	else if(input == "PageDown") toReturn = sf::Key::PageDown;
	else if(input == "End") toReturn = sf::Key::End;
	else if(input == "Home") toReturn = sf::Key::Home;
	else if(input == "Insert") toReturn = sf::Key::Insert;
	else if(input == "Delete") toReturn = sf::Key::Delete;
	else if(input == "Add") toReturn = sf::Key::Add;
	else if(input == "Subtract") toReturn = sf::Key::Subtract;
	else if(input == "Multiply") toReturn = sf::Key::Multiply;
	else if(input == "Divide") toReturn = sf::Key::Divide;
	else if(input == "Left") toReturn = sf::Key::Left;
	else if(input == "Right") toReturn = sf::Key::Right;
	else if(input == "Up") toReturn = sf::Key::Up;
	else if(input == "Down") toReturn = sf::Key::Down;
	else if(input == "Numpad0") toReturn = sf::Key::Numpad0;
	else if(input == "Numpad1") toReturn = sf::Key::Numpad1;
	else if(input == "Numpad2") toReturn = sf::Key::Numpad2;
	else if(input == "Numpad3") toReturn = sf::Key::Numpad3;
	else if(input == "Numpad4") toReturn = sf::Key::Numpad4;
	else if(input == "Numpad5") toReturn = sf::Key::Numpad5;
	else if(input == "Numpad6") toReturn = sf::Key::Numpad6;
	else if(input == "Numpad7") toReturn = sf::Key::Numpad7;
	else if(input == "Numpad8") toReturn = sf::Key::Numpad8;
	else if(input == "Numpad9") toReturn = sf::Key::Numpad9;
	else if(input == "F1") toReturn = sf::Key::F1;
	else if(input == "F2") toReturn = sf::Key::F2;
	else if(input == "F3") toReturn = sf::Key::F3;
	else if(input == "F4") toReturn = sf::Key::F4;
	else if(input == "F5") toReturn = sf::Key::F5;
	else if(input == "F6") toReturn = sf::Key::F6;
	else if(input == "F7") toReturn = sf::Key::F7;
	else if(input == "F8") toReturn = sf::Key::F8;
	else if(input == "F9") toReturn = sf::Key::F9;
	else if(input == "F10") toReturn = sf::Key::F10;
	else if(input == "F11") toReturn = sf::Key::F11;
	else if(input == "F12") toReturn = sf::Key::F12;
	else if(input == "F13") toReturn = sf::Key::F13;
	else if(input == "F14") toReturn = sf::Key::F14;
	else if(input == "F15") toReturn = sf::Key::F15;
	else if(input == "Pause") toReturn = sf::Key::Pause;
	else
	{
		// API give ascii code as id
		toReturn = static_cast<sf::Key::Code>(input.c_str()[0]);
	}
	return toReturn;
}

sf::Mouse::Button InputState::getApiMouse(std::string input)
{
	sf::Mouse::Button toReturn;
	if(input == "Left") toReturn = sf::Mouse::Left;
	else if(input == "Right") toReturn = sf::Mouse::Right;
	else if(input == "Middle") toReturn = sf::Mouse::Middle;
	else if(input == "XButton1") toReturn = sf::Mouse::XButton1;
	else if(input == "XButton2") toReturn = sf::Mouse::XButton2;
	else
	{
		toReturn = sf::Mouse::Left;
	}	
	return toReturn;
}

Point2d<float> *InputState::getCursorPosition()
{
	return cursor_position;
}

// is action active or not
bool InputState::isAction(std::string action)
{
	bool toReturn = false;
	std::map<std::string, bool>::iterator it = m_actionMap.find(action);
	if(it != m_actionMap.end())
	{
		toReturn = it->second;
	}
	return toReturn;
}

void InputState::setCursor(int id)
{
	CKernel::removeEntity(cursor_id);
	cursor_id = id;
}

void InputState::parseFile(std::string state)
{
	TiXmlDocument doc(std::string(PATH_CONTROLS) + std::string("Controls.cfg"));

	if(doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		// constant string must be replaced with module name
		TiXmlElement *element = hdl.FirstChildElement().FirstChildElement(state).Element();
		if(element)
		{
			TiXmlElement *elem_key = element->FirstChildElement("action");
			while(elem_key)
			{
				std::string id = elem_key->Attribute("id");
				std::string key = elem_key->Attribute("keyboard");
				std::string mouse = elem_key->Attribute("mouse");

				if(id != "")
				{
					if(key != "") m_keyMap.insert(m_keyMap_t::value_type(id, getApiKey(key)));
					if(mouse != "") m_mouseMap.insert(m_mouseMap_t::value_type(id, getApiMouse(mouse)));
				}
				elem_key = elem_key->NextSiblingElement();
			}
		}
	}
}