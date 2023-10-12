#pragma once
#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "Plan.h"


using namespace std;

class Greeter{
    RecipeDB recipedb;
    PlanDB plandb;
    Calendar calendar;

public:    
    Greeter(RecipeDB r, PlanDB p, Calendar c){ recipedb = r; plandb = p; calendar = c;}
    void printOption();
    void selectOption();

    void searchRecipe(){

        string name;

        cout << "Enter Recipe Name of Ingredient to Search: ";
        cin.ignore();
        getline(cin, name);
        cout << "-----Result-----" << endl;
        recipedb.searchRecipe(name);

    }

    void addRecipe(){
        string name, description;
        vector<string> ingredients;
        int time;

        cout << "Enter Recipe Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Ingredients (enter a blank line to finish) \n";
        string ingredient;
        while (true) {
            cout << "Ingredient: ";
            getline(cin, ingredient);

            if(ingredient.empty()){
                break;
            }

            ingredients.push_back(ingredient);
        }

        cout << "Enter Recipe Cooking Time (in minutes): ";
        cin >> time;
        cin.ignore();

        cout << "Enter Recipe Description: ";
        getline(cin, description);

        Recipe recipe(name, description, time, ingredients);
        recipedb.addRecipe(recipe);

        // system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();

    }

    void deleteRecipe(){
        string name;

        cout << "Enter Recipe Name to Delete: ";
        cin.ignore();
        getline(cin, name);

        recipedb.deleteRecipe(name);

        // system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }   

    void showRecipe() {
		cout << "All Recipes:\n";
		recipedb.printAll();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	}

    void searchPlan() {
		string name;

		cout << "Enter Plan Name to Search: ";
		cin.ignore();
		getline(cin, name);
		cout << "-----Result-----" << endl;
		plandb.searchPlan(name);

	}

    void addPlan(){
        string name;
        Meal breakfast, lunch, dinner;
        cout << "Enter Plan Date: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Recipe name for BREAKFAST(enter a blank line to finish)\n";
        string recipe;
        while(true){
            cout << "Recipe Name: ";
            getline(cin, recipe);

            if(recipe.empty()){
                break;
            }
            Recipe data = recipedb.getRecipe(recipe);
            if(data.getName()!= "NULL"){
                breakfast.addRecipes(data);
            }
            else{
                cout << "there is no search result" << endl;
            }
        }
        cout << "Enter Recipe name for LUNCH(enter a blank line to finish)\n";
        while(true){
            cout << "Recipe Name: ";
            getline(cin, recipe);

            if(recipe.empty()){
                break;
            }
            Recipe data = recipedb.getRecipe(recipe);
            if(data.getName()!= "NULL"){
                lunch.addRecipes(data);
            }
            else{
                cout << "there is no search result" << endl;
            }
        }
        cout << "Enter Recipe name for DINNER(enter a blank line to finish)\n";
        while(true){
            cout << "Recipe Name: ";
            getline(cin, recipe);

            if(recipe.empty()){
                break;
            }
            Recipe data = recipedb.getRecipe(recipe);
            if(data.getName()!= "NULL"){
                dinner.addRecipes(data);
            }
            else{
                cout << "there is no search result" << endl;
            }
        }
        Plan plan(name, breakfast, lunch, dinner);
        plandb.addPlan(plan);
        // system("pause");
        cout << "Press Enter to continue...";
        cin.get();
    }

    void deletePlan(){
        string name;

        cout << "Enter Plan Name to delete: " ;
        cin.ignore();
        getline(cin,name);

        plandb.deletePlan(name);

        // system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }

	void showPlan() {
		cout << "All Plans:\n";
		plandb.printAll();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	};

    void searchDate(){
        string date;
        bool validFormat = false;
        while(!validFormat){
            cout << "Enter Date to Search (yyyy-mm-dd): ";
            cin.ignore();
            getline(cin,date);

            if (date.size() == 10 && date[4] == '-' && date[7] == '-' && isdigit(date[0]) && isdigit(date[1]) && isdigit(date[2]) && isdigit(date[3]) && isdigit(date[5]) && isdigit(date[6]) && isdigit(date[8]) && isdigit(date[9])) {
            validFormat = true;
            } 
            else {
            cout << "Invalid format! Please enter the date in the format yyyy-mm-dd." << endl;
            }
        }
        int y = stoi(date.substr(0, 4));
		int m = stoi(date.substr(5, 2));
		int d = stoi(date.substr(8, 2));
		cout << "-----Result-----" << endl;
		calendar.printDate(y,m,d);
    }

    void addDate(){
        string planname;
        string date;

        cout << "Enter Date (yyyy-mm-dd) to add: ";
        cin.ignore();
        getline(cin, date);

        int y = stoi(date.substr(0, 4));
		int m = stoi(date.substr(5, 2));
		int d = stoi(date.substr(8, 2));

        //수정대상
        cout << "Enter Plan name:\n";
		cout << "Plan name: ";
		getline(cin, planname);

        Plan p = plandb.getPlan(planname);
		if (p.getName() != "NULL") {
			Date dd(y, m, d, plandb.getPlan(planname));
			calendar.addDate(dd);
			calendar.sortDate();
			// system("pause");
            cout << "Press Enter to continue...";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
		}
    }

    //형식 맞지 않으면 경고 표시 뜨게 수정할 것
    void deleteDate() {
		string date;

		cout << "Enter Date (yyyy-mm-dd) to delete: ";
		cin.ignore();
		getline(cin, date);

		int y = stoi(date.substr(0, 4));
		int m = stoi(date.substr(5, 2));
		int d = stoi(date.substr(8, 2));

		calendar.deleteDate(y, m, d);
		// system("pause");
        cout << "Press Enter to continue...";
        cin.get();
	}

    void showCalender() {
		cout << "All Dates:\n";
		calendar.sortDate();
		calendar.printAll();
        // system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
};

void Greeter::printOption() {

	cout << " -------------------------------------------\n";
	cout << "��  ######   ######    ##  ###   ###  ###  ��\n";
	cout << "��    ##       ##      ## ##      ##  ##   ��\n";
	cout << "��    ##       ##      ###        ######   ��\n";
	cout << "��    ##       ##      ## ##      ##  ##   ��\n";
	cout << "��  ######   ######    ##  ###   ###  ###  ��\n";
	cout << " -------------------------------------------\n";
	cout << endl;
	cout << "         1.Search recipe\n";
	cout << "         2.Add recipe\n";
	cout << "         3.Delete recipe\n";
	cout << "         4.Show all recipe\n";
	cout << "         5.Search plan\n";
	cout << "         6.Add plan\n";
	cout << "         7.Delete plan\n";
	cout << "         8.Show all plan\n";
	cout << "         9.Search Date\n";
	cout << "         10.Add Date\n";
	cout << "         11.Delete Date\n";
	cout << "         12.Show Calender\n";
	cout << "         13.Save\n";
	cout << "         14.Load\n";
	cout << "         15.Exit & Save\n";
}

void Greeter::selectOption(){
    int selectedOption;
    cin >> selectedOption;

    //system("CLS");
    system("clear");
    switch (selectedOption) {
	case 1: {
		cout << " Search recipe " << endl;
		searchRecipe();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 2:
	{
		cout << " Add recipe" << endl;
		addRecipe();
		break;
	}
	case 3:
	{
		cout << " Delete recipe" << endl;
		deleteRecipe();
		break;

	}
	case 4: {
		showRecipe();
		break;
	}
	case 5: {
		cout << " Search Plan" << endl;
		searchPlan();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 6: {
		cout << " Add Plan" << endl;
		addPlan();
		break;
	}
	case 7:
	{
		cout << " Delete Plan" << endl;
		deletePlan();
		break;
	}
	case 8: {
		showPlan();
		break;
	}
	case 9: { //search Date
		cout << " Search Date" << endl;
		searchDate();
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
		break;
	}
	case 10: { //add Date
		cout << " Add Date" << endl;
		addDate();
		break;
	}
	case 11: { // delete Date
		cout << " Delete Date" << endl;
		deleteDate();
		break;
	}
	case 12: { // Show Calender
		showCalender();
		break;
	}
	case 13: { // Save
		FileIO fileio = FileIO();
		fileio.saveRecipe(recipedb);
		fileio.savePlan(plandb);
		fileio.saveCalendar(calendar);
		break;
	}
	case 14: { // Load
		FileIO fileio = FileIO();
		fileio.loadRecipe(recipedb);
		fileio.loadPlan(plandb);
		fileio.loadCalendar(calendar);
		break;
	}
	case 15:
	{
		cout << "Exit the program.\n";
		exit(0);
		break;
	}
	default:
		cout << "Entered it incorrectly. Enter a number between 1 and 15.\n";
		// system("pause");
        cout << "Press Enter to continue...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
	}

}