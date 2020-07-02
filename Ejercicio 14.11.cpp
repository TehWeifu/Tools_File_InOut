#include <iostream>
#include <fstream>
#include <iomanip>

#include "Hardware.h"

enum class Menu {INPUT = 1, LIST, DELETE, UPTADE, END};

Menu enterMenuOption();
void initialitazeFile100(const Hardware&, std::fstream&);
void inputData(std::fstream&);
void listTools(std::fstream&);
void deleteRecord(std::fstream&);
void updateRecord(std::fstream&);

int main()
{
	std::fstream inOutHW{ "hwRecords.dat", std::ios::out | std::ios::in | std::ios::binary };
	Hardware emptyHW;
	Menu menuOption;

	if (!inOutHW)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(EXIT_FAILURE);	}


	initialitazeFile100(emptyHW, inOutHW);
	std::cout << "File initializated with 100 empty records succesfully" << std::endl;

	while ((menuOption = enterMenuOption()) != Menu::END)
	{
		switch (menuOption)
		{
		case Menu::INPUT:
			inputData(inOutHW);
			break;
		case Menu::LIST:
			listTools(inOutHW);
			break;
		case Menu::DELETE:
			deleteRecord(inOutHW);
			break;
		case Menu::UPTADE:
			updateRecord(inOutHW);
			break;
		default:
			std::cerr << "Error. Wrong input.";
			break;
		}
		inOutHW.clear();
	}
	return 0;
}

Menu enterMenuOption() {
	int choice;

	std::cout << "\nInput a menu option and press enter:" << std::endl;
	std::cout << "1 -> Input a new record" << std::endl;
	std::cout << "2 -> Prints on screen all current records" << std::endl;
	std::cout << "3 -> Delete records" << std::endl;
	std::cout << "4 -> Update records" << std::endl;
	std::cout << "5 -> Exit programn" << std::endl;

	std::cin >> choice;
	return static_cast<Menu>(choice);
}

void initialitazeFile100(const Hardware& object, std::fstream& file) {
	file.clear();
	file.seekp(0);

	for (int i = 0; i < 100; i++)
	{
		file.write(reinterpret_cast<const char*>(&object), sizeof(Hardware));
	}
}

void inputData(std::fstream& file) {
	int toolId;
	Hardware tool;

	std::cout << "\nCreating new records: " << std::endl;
	std::cout << "Input an account number (0 to go back to the main menu): ";
	std::cin >> toolId;


	while (toolId != 0)
	{
		file.seekg((toolId - 1) * sizeof(Hardware));
		file.read(reinterpret_cast<char*>(&tool), sizeof(Hardware));

		if (tool.getID() == 0)
		{
			int quantity;
			float cost;
			std::string name;

			std::cout << "Enter name within quotes: ";
			std::cin >> std::quoted(name);
			std::cout << "Enter quantity: ";
			std::cin >> quantity;
			std::cout << "Enter cost: ";
			std::cin >> cost;

			tool.setCost(cost);
			tool.setId(toolId);
			tool.setQuantity(quantity);
			tool.setName(name);

			file.seekp((toolId - 1) * sizeof(Hardware));
			file.write(reinterpret_cast<const char*>(&tool), sizeof(Hardware));

			std::cout << "Record with ID " << toolId << " succefully updated." << std::endl;
		}
		else
		{
			std::cerr << "This record already has information. Consider using the update function." << std::endl;
		}

		std::cout << "\nInput an account number (0 to go back to the main menu): ";
		std::cin >> toolId;
	}
}


void listTools(std::fstream& file) {
	Hardware tool;

	std::cout << std::left << std::setw(10) << "Tool ID" << std::setw(25) << "Tool Name"
		<< std::setw(10) << "Quantity" << std::right << std::setw(10) << "Cost" << std::endl;

	file.seekg(0);

	file.read(reinterpret_cast<char*>(&tool), sizeof(Hardware));

	while (!file.eof())
	{
		if (tool.getID() != 0)
		{
			std::cout << std::left << std::setw(10) << tool.getID() << std::setw(25) << tool.getName()
				<< std::setw(10) << tool.getQuantity() << std::right << std::setw(10) << tool.getCost() << std::endl;

		}
		file.read(reinterpret_cast<char*>(&tool), sizeof(Hardware));
	}
}

void deleteRecord(std::fstream& file) {
	int toolId;
	Hardware tool;

	std::cout << "\nDeleting records" << std::endl << std::endl;
	std::cout << "Input an account number (0 to go back to the main menu): ";
	std::cin >> toolId;

	while (toolId != 0)
	{
		file.seekg((toolId - 1) * sizeof(Hardware));
		file.read(reinterpret_cast<char*>(&tool), sizeof(Hardware));

		if (tool.getID() !=0)
		{
			Hardware blankTool;

			file.seekp((toolId - 1) * sizeof(Hardware));
			file.write(reinterpret_cast<const char*>(&blankTool), sizeof(Hardware));

			std::cout << "Tool with ID " << toolId << " deleted" << std::endl;
		}
		else {
			std::cerr << "Tool with ID " << toolId << " does not exist" << std::endl;
		}
		std::cout << "\nInput an account number (0 to go back to the main menu): ";
		std::cin >> toolId;
	}
}

void updateRecord(std::fstream& file) {
	int toolId;
	Hardware tool;

	int quantity;
	float cost;
	std::string name;

	std::cout << "\nUpdating records" << std::endl;
	std::cout << "Input an accout number (0 to go back to the main menu): ";
	std::cin >> toolId;

	while (toolId != 0)
	{
		file.seekg((toolId - 1) * sizeof(Hardware));
		file.read(reinterpret_cast<char*>(&tool), sizeof(Hardware));

		if (tool.getID() != 0)
		{
			std::cout << "Enter name within quotes: ";
			std::cin >> std::quoted(name);
			std::cin.ignore(1024, '\n');
			std::cout << "Enter quantity: ";
			std::cin >> quantity;
			std::cout << "Enter cost: ";
			std::cin >> cost;

			tool.setCost(cost);
			tool.setQuantity(quantity);
			tool.setName(name);

			file.seekp((toolId - 1) * sizeof(Hardware));
			file.write(reinterpret_cast<const char*>(&tool), sizeof(Hardware));

			std::cout << "Tool with ID " << toolId << " uptaded succesfully" << std::endl;

		}
		else {
			std::cerr << "Tool with ID " << toolId << " does not exist" << std::endl;
		}
		std::cout << "\nInput an accout number (0 to go back to the main menu): ";
		std::cin >> toolId;
	}
}