#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
// Making name global
string name;
//subFunction
double calculateOvertimeHours(double hoursWorked, double hourlyPayRate) {
    int maxovertimeHours = 60;
    double overtimeHours = 0.0;
    double overtimePay = 0.0;
    if( hoursWorked > 40)
    {
        overtimeHours = maxovertimeHours - 40.0;

    } else {
        overtimeHours = 0.0;
    }

    overtimePay = overtimeHours * (hourlyPayRate * 1.5);


    return overtimePay;
}
// Function 1
double calculatePay(double hoursWorked,double hourlyPayRate) {
    const double regularPayRate = 1.0;
    const double overtimePayRate = 1.5;
    const double doublePayRate = 2.0;

    const int max_regular_hours = 40;
    const int max_overtime_hours = 60;
    const int max_double_hours = 80;

    double totalPay = 0.0;

    double regularPay = 0.0;
    double overtimePay = calculateOvertimeHours(hoursWorked,hourlyPayRate);
    double doublePay = 0.0;

    if (hoursWorked <= max_regular_hours)
        {
            regularPay = hoursWorked * hourlyPayRate * regularPayRate;
        }
        else if (hoursWorked <= max_overtime_hours)
        {
            regularPay = max_regular_hours * hourlyPayRate * regularPayRate;
            doublePay = (hoursWorked - max_regular_hours) * hourlyPayRate * overtimePayRate;
        }
        else if (hoursWorked <= max_double_hours)
        {
            regularPay = max_regular_hours * hourlyPayRate * regularPayRate;
            doublePay = (hoursWorked - max_overtime_hours) * hourlyPayRate * doublePayRate;
        }
        else
        {
            regularPay = max_regular_hours * hourlyPayRate * regularPayRate;
            doublePay = (max_double_hours - max_overtime_hours) * hourlyPayRate * doublePayRate;
        }

        totalPay = regularPay + overtimePay + doublePay;



    return totalPay; // the gross
}
// Function 3
void printPayrollToFile(string filename, string initials, double hoursWorked, double hourlyPayRate, double federalWithholding, double stateWithholding, double unionDues, double grossPay, double netPay) {
    ofstream outputFile(filename,ios::app);
    outputFile << "Employee Initials,Total Hours Worked,Pay Rate,Federal Withholding,State Withholding,Union Dues,Gross Pay,Net Pay" << endl;


    outputFile << "Initials: " << initials << ","
    << "Total Hours Worked: " << hoursWorked << ","
    << "Pay Rate: $" << hourlyPayRate << ","
    << "Gross Pay: $" << grossPay << ","
    << "Federal Withholding " << federalWithholding<< ","
    << "State Withholding" << stateWithholding << ","
    << "Union Dues (2%): $" << unionDues << ","
    << "Net Pay: $" << netPay << endl;

    outputFile.close();
}

// Function 2
void calculateDeductions(double hours, double hourlyPayRate){
    double grossPay = calculatePay(hours,hourlyPayRate);
    double federalWithholding = 0.0;
    double stateWithholding = 0.0;
    double unionDues = 0.0;
    double netPay = 0.0;
    double netpay2 = 0.0;



    federalWithholding = grossPay * 0.18;
    stateWithholding = grossPay * 0.045;
    unionDues = grossPay * 0.02;
    netPay = grossPay - federalWithholding - stateWithholding - unionDues;


    cout << "Gross Pay: $" << grossPay << endl;
    cout << "Federal Withholding: $" << federalWithholding << endl;
    cout << "State Withholding: $" << stateWithholding << endl;
    cout << "Union Dues: $" << unionDues << endl;
    cout << "Net Pay: $" << netPay << endl;

    printPayrollToFile("Output.txt",name,hours,hourlyPayRate, federalWithholding,stateWithholding, unionDues, grossPay, netPay);// printing the valid data to txt
}


//Error file.
void printToErrorFile(string filename,string error){
    ofstream errorFile(filename,ios::app);
    errorFile << "Employee Initials,Error" << endl;


    errorFile << "Initials: " << name << ","
    << "Error: " << error << endl;

    errorFile.close();

}


//Extra credit function
void RaedData(){// reads and displays data from the txt file.
     fstream newfile;
   newfile.open("employees.txt",ios::in); //open a file to perform read operation using file object
   if (newfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
         cout << tp << "\n"; //print the data of the string
      }
      newfile.close(); //close the file object.
}
}

int main()
{
    cout << "----------------------------------DISPLAYING THE DATA -------------------------------------------------\n"<< endl;
    RaedData();

    const int numberOfEmployees = 10;
    const int numberofDays = 8;
    string employeeInitials[numberOfEmployees];
    double hoursWorked[numberOfEmployees];
    double hourlyPayRate[numberOfEmployees];
     cout << "\n-------------------------DISPLAYING THE EMPLOYEES -------------------------------------------------\n"<< endl;
    fstream newfile;
    newfile.open("employees.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) //checking whether the file is open
    {
        string line;
        for(int i = 0; i < numberOfEmployees; i++)
        {
            if (getline(newfile, line))
            {
                stringstream ss(line);
                ss >> employeeInitials[i];
                double totalHours = 0.0;
                for (int j = 0; j < numberofDays - 1; j++)
                {
                    double hours;
                    ss >> hours;
                    if (hours < 0){
                         string error = "Error Message:Negative value encounted for hours on day " + to_string(j+1) + " For employee " + employeeInitials[i] + ", Skipping calculation for this day.\n";
                            cout << error << endl;
                        printToErrorFile("Errorfile.txt",error);// adding the error to the error file
                        continue;
                    }
                    totalHours += hours;
                }
                hoursWorked[i] = totalHours;
                ss >> hourlyPayRate[i];
            }
            else
            {
                break; // Stop reading if there are fewer than numberOfEmployees rows
            }
        }
        newfile.close(); //close the file object.
    }

    // Print the values for each employee
    for (int i = 0; i < numberOfEmployees; i++)
    {
        cout <<"-------------------------------EMPLOYEE "<< i+1 <<"-------------------------\n"<< endl;
        cout << "Employee " << employeeInitials[i] << " worked " << hoursWorked[i] << " hours and has an hourly pay rate of " << hourlyPayRate[i] << endl;
        name = employeeInitials[i];
        calculateDeductions(hoursWorked[i],hoursWorked[i]);

    }

    return 0;
}
