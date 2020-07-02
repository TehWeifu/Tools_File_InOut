#pragma once

#include <string>

class Hardware
{
public:
	Hardware(int = 0, int = 0, float = 0.0, const std::string& = "");

	void setId(int);
	int getID() const;

	void setQuantity(int);
	int getQuantity()const;

	void setCost(float);
	float getCost() const;

	void setName(const std::string&);
	std::string getName() const;

private:
	int id;
	int quantity;
	float cost;
	char toolName[30];
};

