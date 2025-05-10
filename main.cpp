#include <iostream>

#include "models.h"
#include "views.h"

int main(int argc, char *argv[]) {
  ShapesModel model;
  PrintView view;

  model.addShape(std::unique_ptr<AbstractShape>(new Point()));
  model.addShape(std::unique_ptr<AbstractShape>(new Line()));
  model.addShape(std::unique_ptr<AbstractShape>(new Rect()));
  model.addShape(std::unique_ptr<AbstractShape>(new Elliple()));
  model.addShape(std::unique_ptr<AbstractShape>(new Text("Hello!")));
  model.addShape(std::unique_ptr<AbstractShape>(new Image()));

  view.draw(model.getShapes());

  auto data = model.serialize();
  std::cout << data << std::endl;

  if (not model.parse(data)) {
    std::cerr << "Failed to parse data";
  }

  model.addShape(std::unique_ptr<AbstractShape>(new Text("OTUS")));
  model.addShape(std::unique_ptr<AbstractShape>(new Text("C++")));
  model.addShape(std::unique_ptr<AbstractShape>(new Text("Professional")));

  view.draw(model.getShapes());

  std::cout << "Data after parse" << std::endl;
  data = model.serialize();
  std::cout << data << std::endl;

  return 0;
}
