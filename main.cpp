#include <iostream>
#include <fstream>
#include <string>

#include "Greeter.h"
#include "FileIO.h"

using namespace std;

int main(){
    FileIO fileio = FileIO();

	RecipeDB recipedb;
	fileio.loadRecipe(recipedb);
	PlanDB plandb;
	fileio.loadPlan(plandb);
	Calendar calendar;
	fileio.loadCalendar(calendar);
	Greeter greeter(recipedb,plandb,calendar);


	while (1) {
		system("cls");
		greeter.printOption();
		greeter.selectOption();
	}

}