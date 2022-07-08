#include <iostream>
#include <vector>
#include <string>
#include <nanogui/screen.h>

using namespace std;

int main()
{
  cout << "Hello YAS!\n";

  nanogui::init();
  nanogui::Screen s = nanogui::Screen(nanogui::Vector2i(300, 300), "Caption", true);
  s.performLayout();
  s.setVisible(true);
  nanogui::mainloop(16);

  nanogui::shutdown();
}