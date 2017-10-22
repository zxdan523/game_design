#include "TextManager.h"

TextManager::TextManager()
{

}

// have to keep font object alive?
/*void TextManager::addBlank(std::string id, std::string path)
{

	sf::Font font;
	if (!font.loadFromFile("../data/Roboto-Regular.ttf"))
		throw std::runtime_error("error");

	std::shared_ptr<sf::Text> text=std::make_shared<sf::Text>();
	text->setFont(font);

	textMap.insert(std::make_pair(id, std::move(text)));
}*/

void TextManager::addFont(std::string id, std::string path)
{
	std::shared_ptr<sf::Font> font=std::make_shared<sf::Font>();
	if (!font->loadFromFile(path))
		throw std::runtime_error("error");

	fontMap.insert(std::make_pair(id, std::move(font)));
}


std::shared_ptr<sf::Font> TextManager::getFont(std::string id)
{
	auto found = fontMap.find(id);
	assert(found != fontMap.end());
	return found->second;
}