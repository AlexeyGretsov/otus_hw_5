#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "shapes.h"

/** @class AbstractModel
 *  @brief Models interface class
 */
struct AbstractModel {
  virtual ~AbstractModel() = default;

  virtual void addShape(std::unique_ptr<AbstractShape> shape) = 0;
  virtual void removeLastShape() = 0;
  virtual void reset() = 0;
  virtual const std::vector<std::unique_ptr<AbstractShape>> &
  getShapes() const = 0;

  virtual bool parse(const std::string &source) = 0;
  virtual std::string serialize() const = 0;
};

class ShapesModel : public AbstractModel {
public:
  void addShape(std::unique_ptr<AbstractShape> shape) override {
    for (const auto &tmp : shapes) {
      if (tmp.get() == shape.get()) {
        return;
      }
    }

    shapes.push_back(std::move(shape));
  }
  void removeLastShape() override {
    if (not shapes.empty()) {
      shapes.pop_back();
    }
  }
  void reset() override { shapes.clear(); }

  const std::vector<std::unique_ptr<AbstractShape>> &
  getShapes() const override {
    return shapes;
  }
  bool parse(const std::string &source) override {
    shapes.clear();
    std::istringstream stream(source);
    std::string line;

    while (std::getline(stream, line)) {
      auto shape = createShape(line);
      if (not shape) {
        std::cerr << "ERROR! Unsupported shape " << line << "\n";

        return false;
      }

      shapes.push_back(std::move(shape));
    }

    return true;
  }
  std::string serialize() const override {
    std::string result;

    for (const auto &shape : shapes) {
      result.append(shape->serialize()).append("\n");
    }

    return result;
  }

private:
  std::vector<std::unique_ptr<AbstractShape>> shapes;
};
