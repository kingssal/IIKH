#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "Recipe.h"

using namespace std;


//여러 레시피드을 그룹화해서 하나의 식사(Meal)로 관리
class Meal{

private:
    //recipe객체들을 저장하는 벡터
    vector<Recipe> recipes;
public:
    Meal(){}
    
    //저장된 레시피들의 벡터를 반환
    vector<Recipe> getRecipes() {return recipes;}
    
    //주어진 레시피를 벡터에 추가
    void addRecipes(Recipe data) {recipes.push_back(data);}

    //주어진 레시피와 일치하는 레시피를 벡터에서 삭제
    //일치하지 않으면 검색결과 없음 출력
    void deleteRecipes(Recipe target) {
        bool found = false;
        for (int i = 0; i < recipes.size(); i++){
            if(recipes[i].getName() == target.getName()){
                recipes.erase(recipes.begin() + i);
                found = true;
                //break;
            }
        }
        if (!found) {
            cout << "there is no search result" << endl;
        }
    }

    //지정된 모든 레시피의 이름을 출력
    void print(){
        cout << endl;
        for (Recipe recipe : recipes){
            cout << "-" << recipe.getName() << endl;
        }
        cout << endl;
    }
};

//하루 식사 계획을 나타냄
class Plan{
private:
    Meal breakfast, lunch, dinner;

    //이름을 name에서 date로 바꿈
    string date = "NULL";
public: 
    Plan() {};

    //아침,점심,저녁 meal정보를 인자로 받음
    Plan(string n, Meal a, Meal b, Meal c) {
        date = n;
        breakfast = a;
        lunch = b;
        dinner = c;
    }
    //식사 계획의 이름
    string getName() {
        return date;
    }
    Meal getBreakfast() {return breakfast;}
    Meal getLunch() {return lunch;}
    Meal getDinner() {return dinner;}

    void setName(string d) {date = d;}
    void setBreakfast(Meal data) {breakfast = data;}
    void setLunch(Meal data) {lunch = data;}
    void setDinner(Meal data) {dinner = data;}

    void print(){
        cout << endl;
        cout << "Plan date: "<< date << endl;
        cout << "--Breakfast--";
        breakfast.print();
        cout << "--Lunch--";
        lunch.print();
        cout << "--dinner--";
        dinner.print();
    }
};

class PlanDB{
private:
    vector<Plan> plans;
public:
    //plans에 plan 추가, 같은 이름(날짜)있으면 already exist 출력
    void addPlan(Plan d){
        if(d.getName()!= "NULL"){
            for(Plan c : plans){
            if(c.getName() == d.getName()){
                cout << "Already exist" << endl;
                return;
            }
            }
            plans.push_back(d);
            return;
        }
        cout << "\n plan does not have a name";
    }

    //planDB에서 plan 삭제, DB에 없으면 검색 결과 없다고 출력
    void deletePlan(string s){
        bool found = false;
        for (int i = 0; i < plans.size(); i++){
            if(plans[i].getName() == s){
                plans.erase(plans.begin()+i);
                found = true;
                return;
            }
        }
        if(!found){
            cout << "there is no search result";
        }
    }

    void printPlan(string s){
        bool found = false;
        for (Plan p : plans) {
            if(s == p.getName()){
                found = true;
                p.print();
                return;
            }
        }
        if(!found){
            cout << "there is no search result";
        }
    }
    Plan getPlan(string data) {
        for (Plan p : plans){
            if(data==p.getName()){
                return p;
            }
        }
    }

    vector<Plan> getPlans() {return plans;}


    //이거 이상하다 확인해봐야 함
    void searchPlan(string& s) {
        for (Plan p : plans){
            string data = p.getName();
            if(data.find(s) != string::npos){
                p.print();
                cout << "-------------------"<< endl;

            }
        }
    }

    void printAll(){
        for(Plan p: plans){
            p.print();
            cout << "--------------"<< endl;
        }
    
    }


};

class Date{
private:
    int year, month, day;
    Plan plan;
public: 
    Date(){
        year = 0;
        month = 0;
        day = 0;
    }
    Date(int y, int m, int d, Plan p){
        year = y;
        month = m;
        day = d;
        plan = p;
    }
    void setYear(int data) { year = data; }
	void setMonth(int data) { month = data; }
	void setDay(int data) { day = data; }
    void setDate(int y, int m, int d) {
        year = y; 
        month = m; 
        day = d;
    }
    int getYear(){return year; }
    int getMonth() { return month; }
	int getDay() { return day; }

    int *getDate(){
        int arr[] = {year, month, day};
        return arr;
    }

    void setPlan(Plan d) {plan = d;}
    Plan getPlan() {return plan;}
    void print(){
        cout << "---------------"<<endl;
        cout << "Date: " << year<< "-" << month << "-" << day;
        plan.print();
    }
};

bool compareDate(Date a, Date b){
    if (a.getYear() < b.getYear()) { return 1; }
	else if (a.getYear() > b.getYear()) { return 0; }
	else if (a.getMonth() < b.getMonth()) { return 1; }
	else if (a.getMonth() > b.getMonth()) { return 0; }
	else if (a.getDay() < b.getDay()) { return 1; }
	else if (a.getDay() > b.getDay()) { return 0; }
	return 1;
}

class Calendar{
private:
    vector<Date> dates;
public:
    Calendar() {}

    void addDate(Date d){
        int y = d.getYear();
        int m = d.getMonth();
        int dd = d.getDay();
        for (int i = 0; i < (int)dates.size(); i++) {
            if (dates[i].getYear() == y && dates[i].getMonth() == m && dates[i].getDay() == dd){
                cout << endl;
                cout << "Already exist";
                return;
            }
        }
        dates.push_back(d);
    }

    void deleteDate(int y, int m, int d) {
        bool found = false;
		for (int i = 0; i < (int)dates.size(); i++) {
			if (dates[i].getYear() == y && dates[i].getMonth() == m && dates[i].getDay() == d) {
				dates.erase(dates.begin() + i);
                found = true;
				return;
			}
		}
		if(!found){
            cout << "there is no search result";
        }
	}

    void sortDate() {
		sort(dates.begin(), dates.end(), compareDate);
	}

    void printAll() {
		for (Date kk : dates) {
			kk.print();
		}
	}

    void printDate(int y,int m,int d) {
		for (Date kk : dates) {
			if (kk.getYear() == y && kk.getMonth() == m && kk.getDay() == d) {
				kk.print();
			}
		}
	}

    Date getDate(int y, int m, int d) {
		for (Date kk : dates) {
			if (kk.getYear() == y && kk.getMonth() == m && kk.getDay() == d) {
				return kk;
			}
		}
	}
	
    vector<Date> getCalendar() {
		return dates;
	}


};