#include <iostream>

#include "controllers.h"
#include "models.h"
#include "views.h"

int main(int argc, char *argv[]) {
  std::cout << "Commands:\n";
  std::cout << " - 'p' – draw point\n";
  std::cout << " - 'l' – draw line\n";
  std::cout << " - 'r' – draw rect\n";
  std::cout << " - 'e' – draw ellipse\n";
  std::cout << " - 't'[<space><any text>] – draw text\n";
  std::cout << " - 'i' – draw image\n";
  std::cout << " - 'rem' – remove last shape\n";
  std::cout << " - 'n' – create new document\n";
  std::cout << " - 'save'<space>'filename' - save to file\n";
  std::cout << " - 'restore'<space>'filename' - restore from file\n";
  std::cout << " - 'q' for quit\n";

  std::unique_ptr<AbstractModel> model(new ShapesModel);
  std::unique_ptr<AbstractView> view(new PrintView);

  std::unique_ptr<AbstractController> controller(
      new KeyboardController(std::move(model), std::move(view)));

  controller->start();

  return 0;
}
