#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "models.h"
#include "views.h"

/** @struct Action
 *  @brief User action
 */
struct Action {
  enum class Type : uint8_t {
    UNDEFINED,
    DRAW_POINT,
    DRAW_LINE,
    DRAW_RECT,
    DRAW_ELLIPSE,
    DRAW_TEXT,
    DRAW_IMAGE,
    REMOVE_LAST_SHAPE,
    NEW_DOCUMENT,
    SAVE_TO_FILE,
    RESTORE_FROM_FILE,
    INVALID_COMMAND,
    QUIT
  };

  Action() {}
  Action(Action::Type type, std::string_view data) : type(type), data(data) {}

  Type type{Type::UNDEFINED};
  std::string data;
};

/** @struct AbstractController
 *  @brief Controllers interface class
 */
struct AbstractController {
  virtual ~AbstractController() = default;

  virtual void start() = 0;
  virtual Action waitAction() = 0;

  virtual void saveFoFile(const std::string &fileName,
                          const std::string &data) = 0;
  virtual std::string readFromFile(const std::string &fileName) = 0;
};

/** @class KeyboardController
 *  @brief Keyboard controller class
 */
class KeyboardController : public AbstractController {
public:
  KeyboardController(std::unique_ptr<AbstractModel> model,
                     std::unique_ptr<AbstractView> view)
      : model(std::move(model)), view(std::move(view)) {}

  void start() override {
    bool isActive{true};
    while (isActive) {
      Action action = waitAction();
      std::unique_ptr<AbstractShape> shape;

      switch (action.type) {
      case Action::Type::QUIT:
        isActive = false;
        std::cout << "Quit\n";
        break;
      case Action::Type::DRAW_POINT:
        std::cout << "Create point required\n";
        shape.reset(new Point());
        break;
      case Action::Type::DRAW_LINE:
        std::cout << "Create line required\n";
        shape.reset(new Line());
        break;
      case Action::Type::DRAW_RECT:
        std::cout << "Create rect required\n";
        shape.reset(new Rect());
        break;
      case Action::Type::DRAW_ELLIPSE:
        std::cout << "Create ellipse required\n";
        shape.reset(new Elliple());
        break;
      case Action::Type::DRAW_TEXT:
        std::cout << "Create text required\n";
        shape.reset(new Text(action.data));
        break;
      case Action::Type::DRAW_IMAGE:
        std::cout << "Create image required\n";
        shape.reset(new Image());
        break;
      case Action::Type::REMOVE_LAST_SHAPE:
        std::cout << "Remove last shape\n";
        model->removeLastShape();
        view->draw(model->getShapes());
        break;
      case Action::Type::NEW_DOCUMENT:
        std::cout << "New document required\n";
        model->reset();
        view->draw(model->getShapes());
        break;
      case Action::Type::SAVE_TO_FILE:
        std::cout << "Save to file " << action.data << " required\n";
        saveFoFile(action.data, model->serialize());
        break;
      case Action::Type::RESTORE_FROM_FILE:
        std::cout << "Restore from file " << action.data << " required\n";
        model->parse(readFromFile(action.data));
        view->draw(model->getShapes());
        break;
      case Action::Type::INVALID_COMMAND:
        std::cerr << "Invalid command format\n";
        break;
      default:
        std::cerr << "Ignore unsupported command. Use 'q' for quit\n";
        break;
      }
      if (shape) {
        model->addShape(std::move(shape));
        view->draw(model->getShapes());
      }
    }
  }
  Action waitAction() override {
    std::string line;
    std::getline(std::cin, line);

    std::stringstream stream(line);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(stream, segment, ' ')) {
      seglist.push_back(segment);
    }

    if (seglist.empty()) {
      return Action{};
    }

    Action action;
    std::string_view command = seglist.at(0);
    if (command == "p") {
      action.type = Action::Type::DRAW_POINT;
    } else if (command == "l") {
      action.type = Action::Type::DRAW_LINE;
    } else if (command == "r") {
      action.type = Action::Type::DRAW_RECT;
    } else if (command == "e") {
      action.type = Action::Type::DRAW_ELLIPSE;
    } else if (command == "t") {
      action.type = Action::Type::DRAW_TEXT;
      if (seglist.size() > 1) {
        action.data = seglist.at(1);
      }
    } else if (command == "i") {
      action.type = Action::Type::DRAW_IMAGE;
    } else if (command == "rem") {
      action.type = Action::Type::REMOVE_LAST_SHAPE;
    } else if (command == "n") {
      action.type = Action::Type::NEW_DOCUMENT;
    } else if (command == "q") {
      action.type = Action::Type::QUIT;
    } else if (command == "save") {
      action.type = Action::Type::SAVE_TO_FILE;
      if (seglist.size() > 1) {
        action.data = seglist.at(1);
      } else {
        action.type = Action::Type::INVALID_COMMAND;
      }
    } else if (command == "restore") {
      action.type = Action::Type::RESTORE_FROM_FILE;
      if (seglist.size() > 1) {
        action.data = seglist.at(1);
      } else {
        action.type = Action::Type::INVALID_COMMAND;
      }
    }

    return action;
  }
  void saveFoFile(const std::string &fileName,
                  const std::string &data) override {
    std::ofstream out(fileName);
    out << data;
    out.close();
  }
  std::string readFromFile(const std::string &fileName) override {
    std::string result, line;
    std::ifstream in(fileName);
    while (std::getline(in, line)) {
      result.append(line).append("\n");
    }
    in.close();

    return result;
  }

private:
  std::unique_ptr<AbstractModel> model;
  std::unique_ptr<AbstractView> view;
};