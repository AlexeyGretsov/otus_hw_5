#include <iostream>

#include "models.h"

int main(int argc, char *argv[]) {
  ShapesModel model;

  model.addShape(std::unique_ptr<AbstractShape>(new Point()));
  model.addShape(std::unique_ptr<AbstractShape>(new Line()));
  model.addShape(std::unique_ptr<AbstractShape>(new Rect()));
  model.addShape(std::unique_ptr<AbstractShape>(new Elliple()));
  model.addShape(std::unique_ptr<AbstractShape>(new Text()));
  model.addShape(std::unique_ptr<AbstractShape>(new Image()));

  auto data = model.serialize();
  std::cout << data << std::endl;

  if (not model.parse(data)) {
    std::cerr << "Failed to parse data";
  }

  std::cout << "Data after parse" << std::endl;
  data = model.serialize();
  std::cout << data << std::endl;

  return 0;
}
