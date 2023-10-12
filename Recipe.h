#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

class Recipe {
private:
    string name ="NULL";
    string description;
    set<string> ingredients;
    int time;
    int ct = 0;
public:
    Recipe() {}
    Recipe(string& n, string& d, int t, vector<string> i) :
        name(n), description(d), time(t), ingredients() {
            for(string s : i){
                ingredients.insert(s);
            }
        }

    const string& getName() const {return name;}
    const string& getDescription() const {return description;}
    const set<string>& getIngredients() const {return ingredients;}
    int getTime() const { return time; }

    void setName(string& n) {name = n ;}
    void setDescription(string& d) {description = d;}
    void setTime(int t) {time = t;}

    bool addIngredient(string& n) { return ingredients.insert(n).second;}
    bool removeIngredient(string& n) {return ingredients.erase(n) == 1;}
    bool searchIngredient(string& n) {return ingredients.find(n) != ingredients.end();}

    void print() {
        cout << ">> Recipe Name : " << name << endl;
        cout << ">> Ingredients : " << endl ;
        for (string s : ingredients){
            cout << "  " << ++ct << ". "<< s << endl;
        }
        cout << ">> Time : " << time << "minutes"<< endl;
        cout << ">> Direction" << endl << " -> " << description <<endl;
        cout << "-----------------------------------------" << endl;
    }
};
class RecipeDB {
private:
    vector<Recipe> Recipes;
public: 
    RecipeDB(){};

    //주어진 r를 받아서 입력된 이름이 동일한 레시피가 이미 존재하면 Already exist출력
    void addRecipe(Recipe r){
        for (Recipe s : Recipes) {
            if (s.getName() == r.getName()){
                cout<< "Already exist" << endl;
                return;
            }
        }
        Recipes.push_back(r);
    }

    //주어진 s를 받아서 특정 레시피의 이름 과 일치하는 레시피를 찾아서 삭제한다
    //모든 레시피 검사하고 일치하는 레시피 없으면 there is no search result
    void deleteRecipe(string& s ){ 
        for (int i = 0; i < Recipes.size(); i++){
            if (s == Recipes[i].getName()){
                Recipes.erase(Recipes.begin() + i);
                return;
            }
        }
        cout << "there is no search result" << endl;
    }

    Recipe getRecipe(string& s) {
        for (Recipe r : Recipes) {
            if (s==r.getName()){
                return r;
            }
        }
        Recipe n = Recipe();
        return n;
    }

    //RecipeDB 클래스 내의 모든 레시피들의 리스트를 반환한다.
    vector<Recipe> getRecipes(){
        return Recipes;
    }

    //레시피 DB내에서 레시피를 검색한다
    //현재 레시피 이름을 data변수에 저장, 현재 레시피 재료 목록을 inge변수에 저장
    //만약 data(레시피 이름)에 검색문자열 s가 레시피 이름이나 재료 목록에 포함되어 있다면 해당 레시피 정보 출력
    // void searchRecipe(string& s) {
    //     for(Recipe r : Recipes){
    //         string data = r.getName();
    //         set<string> inge = r.getIngredients();
    //         if (data.find(s) != string::npos){
    //             r.print();
    //         }
    //         else if (inge.find(s) != inge.end()){
    //             r.print();
    //         }

    //     }
    // }

    //found라는 bool타입 추가해서 만약 검색 결과 없을 때, 결과 없음 출력
    void searchRecipe(string& s) {
        bool found = false;
        for(Recipe r : Recipes){
            string data = r.getName();
            set<string> inge = r.getIngredients();
            if (data.find(s) != string::npos){
                r.print();
                found = true;
            }
            else if (inge.find(s) != inge.end()){
                r.print();
                found = true;
            }
        }
        if(!found) {
            cout << "there is no search result" << endl;
        }
    }

    // 레시피 DB내에서 특정 레시피 이름과 일치하는 레시피를 찾아 출력
    //일치하는 레시피가 없다면 "No search recipe found"
    void printRecipe(string& s) {
        bool found = false;
        for (Recipe r : Recipes){
            if(s == r.getName()){
                r.print();
                found = true;
                return;
            }
        }
        if(!found){
            cout << "there is no search result"<< endl;
        }
    }

    void printAll(){
        for(Recipe r : Recipes) {
            r.print();
        }
    }
    
};