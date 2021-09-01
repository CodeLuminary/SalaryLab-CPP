#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>

using namespace std;

double f1Salary = 0.0; int f1Hours = 0; int f1employeeNum = 0;
double f2Salary = 0.0; int f2Hours = 0; int f2employeeNum = 0;
double f3Salary = 0.0; int f3Hours = 0; int f3employeeNum = 0;
double f4Salary = 0.0; int f4Hours = 0; int f4employeeNum = 0;
double fSalary = 0.0; int fHours = 0;

//This function get the length of a string separated with space
int txLength(string tx){
		string ch;int cnt = 0;
	for(int i = 0; i < tx.length(); i++){
		ch = tx.substr(i,1);
		if(strcmp(ch.c_str()," ")==0){
			cnt++;
		}
	}
	return cnt + 1;
}
//This function takes in a string, split it using space and return and array of all the string
string * splitString(string tx){
	string ch;int cnt = 0;
	
	//return cnt;
	int len = txLength(tx);
	string * newStr = new string[len];
	int cnt2 = 0; int start = 0; int sz;
	for(int i = 0; i < tx.length(); i++){
		ch = tx.substr(i,1);
		if(strcmp(ch.c_str()," ")==0){
			newStr[cnt2++] = tx.substr(start,i-(start));
			start = i + 1;
			if(cnt2 == (len-1)){
				newStr[cnt2] = tx.substr(start,(len-start));
			}
		}
	}
	return newStr;
}
//This function takes in a text and change it to all lower case
string toLower(string tx){
	transform(tx.begin(),tx.end(),tx.begin(), ::tolower);
	return tx;
}
//This function do all departmental calculations
double calculateDepartmentData(string * arr, int strLen){
	int totalHours = 0; double sal =0.0;
	if(strcmp(arr[strLen-1].c_str(),"F1")==0){ //This checks if the category is F1
		
		for(int i = 1; i < strLen -1; i++){
			totalHours += atoi(arr[i].c_str());
		}
		f1Hours += totalHours;		
		sal = (totalHours*11.25);
		f1Salary += sal;
		f1employeeNum++;
	}
	else if(strcmp(arr[strLen-1].c_str(),"F2")==0){//This checks if the category is F2
		for(int i = 1; i < strLen -1; i++){
			totalHours += atoi(arr[i].c_str());
		}
		f2Hours += totalHours;		
		sal = (totalHours-35)*18.95+400;
		f2Salary += sal;
		f2employeeNum++;
	}
	else if(strcmp(arr[strLen-1].c_str(),"F3")==0){//This checks if the category is F3
		//f3Hours += 
		if(atof(arr[2].c_str())> 0.1){
			f3Hours += 40;
		}
		else{
			f3Hours +=30;
		}
		totalHours +=f3Hours;
		sal = atoi(arr[1].c_str())*atof(arr[2].c_str());
		f3Salary += sal;
		f3employeeNum++;
	}
	if(strcmp(arr[strLen-1].c_str(),"F4")==0){ //This checks if the category is F4
		int firstFiveHours = 0; //Create a variable to hold first 5 hours
		int lastTwoHours = 0; //Create a variable that hold the last two
		for(int i = 1; i < strLen -1;i++){
			if(i <= 5){
				firstFiveHours += atoi(arr[i].c_str());
			}
			else{
				lastTwoHours += atoi(arr[i].c_str());
			}
		}
		totalHours += firstFiveHours + lastTwoHours;
		f4Hours = totalHours;
		sal = (firstFiveHours*22.55) + (lastTwoHours*48.75);
		f4Salary += sal;
		f4employeeNum++;
	}
	fHours += totalHours;
	return sal;
}
//This function is meant to check if the line is the title
bool isTitle(string * arr, int len){
	for(int i = 0; i < len; i++){
		
		if(strcmp(toLower(arr[i]).c_str(),toLower("Department").c_str())==0){
			return true;
		}
	}
	//cout << len <<'\n';
	
	return false;
}
//This function converts a double to string
string toString(double x){ 
  char* a;
  ostringstream ss;
  ss << x;
  //ss >> a;
  string ab = ss.str();
  return ab;
}
//This function is what is responsible for printing the details
void printDetail(string fileName){
	string line; //This is the variable that holds the content of each line
	int cnt = 0; //This is just a counter variable
	int employeeCount = 0; //This is the variable that holds the number of employee
	bool isFirst = true; //This is to check if the department is the first department on the list
	string employeesName = "";
	ifstream myfile(fileName.c_str());
	if(myfile.is_open()){//Open file
		while(getline(myfile,line)){//Check while there is still content
			if(isTitle(splitString(line),txLength(line))){//Check if the line is a title line
				if(!isFirst || strcmp(splitString(line)[0].c_str(),"EOF")==0){//Check if the line is not a title line or EOF line
					cout << "Total Salary: $" << fSalary << '\n';
					cout << "Total Hours: " << fHours << '\n';
					cout << "Total Number Of Employees: " << employeeCount << '\n';
					cout << "Roster: " <<employeesName.substr(0,employeesName.length()-1)<< '\n'<< '\n';
					cout << "F1:";
					for(int i = 0; i < 30; i++){
						cout << " ";
					}
					cout << "F3:" << '\n';
					cout << "Total Salary: $" << f1Salary;
					int tlen;
					    tlen = toString(f1Salary).length();
					for(int i = (tlen+12); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Salary: $" << f3Salary << '\n';	//cout << "/-" << to_string(f3Salary).length()<<"/-" << to_string(f3Salary);
					
				    cout << "Total Hours: " << f1Hours;
					for(int i = (toString(f1Hours).length()+10); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Hours: " << f3Hours << '\n';
					
					cout << "Total Number of Employees: " << f1employeeNum;
					for(int i = (toString(f1employeeNum).length()+24); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Number of Employees: " << f3employeeNum << '\n'<<'\n';
					
					cout << "F2:";
					for(int i = 0; i < 30; i++){
						cout << " ";
					}
					cout << "F4:" << '\n';
					cout << "Total Salary: $" << f2Salary;
					
					    tlen = toString(f2Salary).length();
					for(int i = (tlen+12); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Salary: $" << f4Salary << '\n';	//cout << "/-" << to_string(f3Salary).length()<<"/-" << to_string(f3Salary);
					
				    cout << "Total Hours: " << f2Hours;
					for(int i = (toString(f2Hours).length()+10); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Hours: " << f4Hours << '\n';
					
					cout << "Total Number of Employees: " << f2employeeNum;
					for(int i = (toString(f2employeeNum).length()+24); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Number of Employees: " << f4employeeNum << '\n'<<'\n';						
					
				}
				cout << line << '\n';isFirst = false;
				fSalary = 0.0; fHours = 0;employeeCount = 0;
				f1Salary = 0.0; f1Hours = 0;f1employeeNum =0;
				f2Salary = 0.0; f2Hours = 0;f2employeeNum =0;
				f3Salary = 0.0; f3Hours = 0;f3employeeNum =0;
				f4Salary = 0.0; f4Hours = 0;f4employeeNum =0;
				employeesName = "";
			}
			else if(strcmp(line.c_str(),"EOF")==0){//Check if the line is a EOF line
				cout << "Total Salary: $" << fSalary << '\n';
				cout << "Total Hours: " << fHours << '\n';
				cout << "Total Number Of Employees: " << employeeCount << '\n';
					cout << "Roster: " <<employeesName.substr(0,employeesName.length()-1)<< '\n'<< '\n';
					cout << "F1:";
					for(int i = 0; i < 30; i++){
						cout << " ";
					}
					cout << "F3:" << '\n';
					cout << "Total Salary: $" << f1Salary;
					int tlen;
						tlen = toString(f1Salary).length();
					for(int i = (tlen+12); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Salary: $" << f3Salary << '\n';	//cout << "/-" << to_string(f1Salary).length()<<"/-" << to_string(f1Salary);
					
				    cout << "Total Hours: " << f1Hours;
					for(int i = (toString(f1Hours).length()+10); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Hours: " << f3Hours << '\n';
					
					cout << "Total Number of Employees: " << f1employeeNum;
					for(int i = (toString(f1employeeNum).length()+24); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Number of Employees: " << f3employeeNum << '\n'<<'\n';
					
					cout << "F2:";
					for(int i = 0; i < 30; i++){
						cout << " ";
					}
					cout << "F4:" << '\n';
					cout << "Total Salary: $" << f2Salary;
					    tlen = toString(f2Salary).length();
					for(int i = (tlen+12); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Salary: $" << f4Salary << '\n';	
					
				    cout << "Total Hours: " << f2Hours;
					for(int i = (toString(f2Hours).length()+10); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Hours: " << f4Hours << '\n';
					
					cout << "Total Number of Employees: " << f2employeeNum;
					for(int i = (toString(f2employeeNum).length()+24); i < 30; i++){
						cout << " ";
					}
					cout <<"Total Number of Employees: " << f4employeeNum << '\n'<<'\n';
			}
			else{
				if(!isFirst){
					fSalary += calculateDepartmentData(splitString(line),txLength(line)); //Calculate salary for each department
				}
				employeeCount++; //Increment employee variable
				employeesName += splitString(line)[0] + ","; //Get employee names
			}
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file";
	}
}

int main(){
	printDetail("payrol.txt");
}



