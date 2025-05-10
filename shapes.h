#pragma once

#include <iostream>
#include <memory>
#include <string>

/** @class AbstractShape
 *  @brief Shapes interface class
 */
struct AbstractShape {
  virtual ~AbstractShape() = default;

  virtual void draw() = 0;

  virtual std::string getKey() const = 0;
  virtual std::string serialize() const = 0;
  virtual bool parse(std::string_view source) = 0;
};

/** @class Point
 *  @brief Point shape class
 */
struct Point : public AbstractShape {
  void draw() override { std::cout << "Draw point\n"; }
  std::string getKey() const override { return "[Point]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

/** @class Line
 *  @brief Line shape class
 */
struct Line : public AbstractShape {
  void draw() override { std::cout << "Draw line\n"; }
  std::string getKey() const override { return "[Line]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

/** @class Rect
 *  @brief Rect shape class
 */
struct Rect : public AbstractShape {
  void draw() override { std::cout << "Draw rect\n"; }
  std::string getKey() const override { return "[Rect]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

/** @class Elliple
 *  @brief Elliple shape class
 */
struct Elliple : public AbstractShape {
  void draw() override { std::cout << "Draw ellipse\n"; }
  std::string getKey() const override { return "[Elliple]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

/** @class Text
 *  @brief Text shape class
 */
struct Text : public AbstractShape {
  void draw() override { std::cout << "Draw text\n"; }
  std::string getKey() const override { return "[Text]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

/** @class Image
 *  @brief Image shape class
 */
struct Image : public AbstractShape {
  void draw() override { std::cout << "Draw image\n"; }
  std::string getKey() const override { return "[Image]"; }
  std::string serialize() const override { return getKey(); }
  bool parse(std::string_view source) override {
    if (source.find(getKey(), 0) == 0) {
      // Parce other parameters
      return true;
    }

    return false;
  }
};

std::unique_ptr<AbstractShape> createShape(std::string_view source) {
  auto isShape = [=](std::string_view key) -> bool {
    return source.find(key, 0) == 0;
  };

  std::unique_ptr<AbstractShape> result;
  if (isShape(Point{}.getKey())) {
    result.reset(new Point{});
    result->parse(source);
  } else if (isShape(Line{}.getKey())) {
    result.reset(new Line{});
    result->parse(source);
  } else if (isShape(Rect{}.getKey())) {
    result.reset(new Rect{});
    result->parse(source);
  } else if (isShape(Elliple{}.getKey())) {
    result.reset(new Elliple{});
    result->parse(source);
  } else if (isShape(Text{}.getKey())) {
    result.reset(new Text{});
    result->parse(source);
  } else if (isShape(Image{}.getKey())) {
    result.reset(new Image{});
    result->parse(source);
  }

  return std::move(result);
}
