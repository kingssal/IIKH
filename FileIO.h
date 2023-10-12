#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <sstream>

#include "Greeter.h"
#include "Plan.h"
#include "Recipe.h"

using namespace std;

class FileIO {
private:

public:

    FileIO(){};
    
    void savePlan(PlanDB pdb) {
        vector<Plan> plans = pdb.getPlans();
        ofstream ofs;
        ofs.open("plan.txt", ios::out);
        if (ofs.fail())
        {
            cerr << "Error!" << endl;
            return;
        }
        vector<Recipe> recipes;
        for(Plan p : plans) {
            ofs << p.getName() << "|";
            recipes= p.getBreakfast().getRecipes();
            for(Recipe r : recipes) {
                ofs << r.getName() << ",";
            }
            ofs << "|";
            recipes = p.getLunch().getRecipes();
			for (Recipe r : recipes) {
				ofs << r.getName() << ",";
			}
			ofs << "|";
			recipes = p.getDinner().getRecipes();
			for (Recipe r : recipes) {
				ofs << r.getName() << ",";
			}
			ofs << endl;
        }
        ofs.close();
    }
    void loadPlan(PlanDB& planDB) {
        ifstream file("plan.txt");
        if(!file.is_open()){
            cout<< "cannot open the file" << endl;
            return;
        }
        string line;
        while (getline(file,line))
        {
            if (!line.empty())
            {
                istringstream iss(line);
                string token;
                vector<string> Field;
                RecipeDB recipedb;
                loadRecipe(recipedb);

                while(getline(iss, token, '|')){
                    Field.push_back(token);
                }
                if (Field.size()>=4){
                    string name = Field[0];
                    Meal breakfast, lunch ,dinner;
                    string a = "";
                    string breakfastRecipeNames = Field[1];

                    istringstream breakfastRecipeStream(breakfastRecipeNames);
                    string breakfastRecipeName;

                    while(getline(breakfastRecipeStream, breakfastRecipeName, ',')){
                        Recipe breakfastRecipe = recipedb.getRecipe(breakfastRecipeName);

                        breakfast.addRecipes(breakfastRecipe);
                    }

                    string lunchRecipeNames = Field[2];
					istringstream lunchRecipeStream(lunchRecipeNames);
					string lunchRecipeName;
					while (getline(lunchRecipeStream, lunchRecipeName, ',')) {
						Recipe lunchRecipe = recipedb.getRecipe(lunchRecipeName);
						lunch.addRecipes(lunchRecipe);
					}

                    string dinnerRecipeNames = Field[3];
					istringstream dinnerRecipeStream(dinnerRecipeNames);
					string dinnerRecipeName;
					while (getline(dinnerRecipeStream, dinnerRecipeName, ',')) {
						Recipe dinnerRecipe = recipedb.getRecipe(dinnerRecipeName);
						dinner.addRecipes(dinnerRecipe);
					}

                    Plan plan(name, breakfast, lunch, dinner);
					planDB.addPlan(plan);
                }
            }
            
        }
        file.close();       
    }
    void saveRecipe(RecipeDB rdb){
        vector<Recipe>  recipes = rdb.getRecipes();
        ofstream ofs;
        ofs.open("recipe.txt", ios::out);
        if(ofs.fail()){
            cerr << "Error!" << endl;
            return;
        }
        for (Recipe r: recipes) {
            ofs << r.getName() << "|";
            ofs << r.getDescription() << "|" << r.getTime() << "|";
            for(string s : r.getIngredients()){
                ofs << s << ",";
            }
            ofs << endl;
        }
        ofs.close();
    }
    void loadRecipe(RecipeDB& recipeDB){
        ifstream inputFile("recipe.txt");  

		if (!inputFile.is_open()) {
			cout << "cannot open recipe.txt " << endl;
			return;
		}

        string line;

        while (getline(inputFile, line)) {
			if (!line.empty()) {
				istringstream iss(line);
				string token;
				vector<string> recipeFields;

				while (getline(iss, token, '|')) {
					recipeFields.push_back(token);
				}

				if (recipeFields.size() >= 4) {
					string name = recipeFields[0];
					string description = recipeFields[1];
					int time = stoi(recipeFields[2]);
					vector<string> ingredients;

					
					istringstream ingredientsStream(recipeFields[3]);
					while (getline(ingredientsStream, token, ',')) {
						ingredients.push_back(token);
					}

					
					recipeDB.addRecipe(Recipe(name, description, time, ingredients));
				}
			}
		}
		inputFile.close();  
    }

    void saveCalendar(Calendar cdb) {
        vector<Date> dates = cdb.getCalendar();
        ofstream ofs;
        ofs.open("calendar.txt", ios::out);
        if (ofs.fail()) {
			cerr << "Error!" << endl;
			return;
		}
        for (Date c : dates) {
			ofs << c.getYear() << "|" << c.getMonth() << "|" << c.getDay() << "|" << c.getPlan().getName() << endl;
		}
		ofs.close();
    }
    void loadCalendar(Calendar& calendar) {
        ifstream file("calendar.txt");
        if(!file.is_open()){
            cout << "cannot open the file" << endl;
			return;
        }
        string line;
		while (getline(file, line)) {
			if (!line.empty()) {
				istringstream iss(line);
				string token;
				vector<string> Field;
				PlanDB plandb;
				loadPlan(plandb);
				while (getline(iss, token, '|')) {
					Field.push_back(token);
				}
				if (Field.size() >= 4) {
					string y = Field[0];
					int year = stoi(y);
					string m = Field[1];
					int month = stoi(m);
					string d = Field[2];
					int day = stoi(d);
					string planName = Field[3];
					Plan plan = plandb.getPlan(planName);
					Date date(year, month, day, plan);
					calendar.addDate(date);
				}

			}

		}
		file.close();

    }


};