#include "Hardware.h"

Hardware::Hardware(int numId, int numQuantity, float numCost, const std::string& name)
	: id(numId), quantity(numQuantity), cost(numCost) {
	setName(name);
}

void Hardware::setId(int num) { id = num; }
int Hardware::getID() const { return id; }

void Hardware::setQuantity(int num) { quantity = num; }
int Hardware::getQuantity()const { return quantity; }

void Hardware::setCost(float num) { cost = num; }
float Hardware::getCost() const { return cost; }

void Hardware::setName(const std::string& nameStr) {
	int length = nameStr.size();
	length = (length < 30 ? length : 29);
	nameStr.copy(toolName, length);
	toolName[length] = '\0';
}
std::string Hardware::getName() const { return toolName; }
