#pragma once

#include <string>
#include <memory>

#include "models.h"
#include "views.h"

/** @struct Action
 *  @brief User action
 */
struct Action
{
	enum class Type : uint8_t
	{
		UNDEFINED,
		DRAW_POINT,
		DRAW_LINE,
		DRAW_RECT,
		DRAW_ELLIPSE,
		DRAW_TEXT,
		DTAW_IMAGE
	};

	Action(){}
	Action(Action::Type type, std::string_view data) : type(type), data(data){}

	Type type{Type::UNDEFINED};
	std::string data;
};

/** @struct AbstractController
 *  @brief Controllers interface class
 */
struct AbstractController
{
	virtual ~AbstractController() = default;

	virtual void start() = 0;
	virtual Action waitAction() = 0;
};

/** @class KeyboardController
 *  @brief Keyboard controller class
 */
class KeyboardController : public AbstractController
{
	public:
		KeyboardController(std::unique_ptr<AbstractModel> model,
				std::unique_ptr<AbstractView> view) :
			model(std::move(model)), view(std::move(view)) {}
			
		void start() override
		{

		}
		Action waitAction() override
		{
			return Action{};
		}

	private:
		std::unique_ptr<AbstractModel> model;
		std::unique_ptr<AbstractView> view;
};