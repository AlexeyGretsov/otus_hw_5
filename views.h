#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "shapes.h"

/** @class struct AbstractView
 *  @brief Views interface class
 */
struct AbstractView {
  virtual ~AbstractView() = default;

  virtual void
  draw(const std::vector<std::unique_ptr<AbstractShape>> &shapes) const = 0;
};

class PrintView : public AbstractView {
public:
  void draw(const std::vector<std::unique_ptr<AbstractShape>> &shapes)
      const override {
    std::cout << "[Draw shapes start]\n";
    for (const auto &shape : shapes) {
      std::cout << " > ";
      shape->draw();
    }
    std::cout << "[Draw shapes finish]\n";
  }
};
