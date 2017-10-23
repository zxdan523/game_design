#include <SFML/Graphics.hpp>

class UIManager
{
public:
  void startGame(bool click);
  void pauseGame(bool click);
  void goToMainMenu(bool click);
  void goToSettingsMenu(bool click);
  
private:
  bool buttonClick;

}
