/*============================================================================
// Name        : Courses.cpp
// Author      : Jay Zinzuwadia
// Version     : 1.0
// Description : Program sorts courses for ABCU Advising by course number
//               and their prerequisites. User of program has a menu that they can choose from
//               loading structure, printing sample schedule and also asking details about a specific course
//============================================================================ */
#include <iostream>
#include <algorithm>
#include <fstream> //required to open txt file and manipulate
#include <vector>//required to use vector
#include <sstream> // stringstream library

using namespace std;

class Course {
public: //public variables for easy access
    int numPrereqs;
    string courseName;
    string courseNum;
    vector<string> prereqs;
};

vector<Course> v;
//userinput for case 3 in switch statement
string userInput;
void loadVector (string fileName) {

    //create a text string to read the output from the file
    string courses; //standard string to read the whole file lines

    //read  text from file
    ifstream myFile (fileName);

    if(myFile.is_open()) {

        while (getline (myFile, courses)) {
            string temp;
            // pass in the string as a stream, passed into inputStream variable
            stringstream inputStream(courses);
            Course c;
            //reject one empty line because there was a comma printing
            //before the sample schedule
            if (courses == "") {
                continue;
            }

            //gets information from the string and decodes the information into vector.
            int end = courses.find(",");
            //take substring and assign it to the number
            c.courseNum = courses.substr(0,end);
            courses = courses.substr(end+1);
            end = courses.find(",");

            //if there is no comma then c.courseName = courses
            if(end ==string::npos) {

                c.courseName = courses;
            }
                else {
                    c.courseName = courses.substr(0,end);
                    courses = courses.substr(end+1);

                    int i =0;

                    while (courses != ""){
                        end = courses.find(",");

                        if(end != string::npos) {

                            temp = courses.substr(0,end);
                            c.prereqs.push_back(temp);
                            courses = courses.substr(end+1);
                        }
                        else {
                            c.prereqs.push_back(courses);
                            break;
                        }
                    }

                }

                // finally, store the course into the courseList
                v.push_back(c);

            }

            //close file as good practice once done reading from
            myFile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }

    }

//sorts the stored array in ascending order of courseNum
    bool compareCourses(Course c1, Course c2) {

        return (c1.courseNum < c2.courseNum);
    }

//implement isEaual function to compare the courses
    bool isEqual(Course c){

        //compares if the coruse saved in vector is same as the userInput
        return (c.courseNum == userInput);
    }

    int main() {

        //declaration for user input number choice that runs the loop/cases
        int choice;
        //declaration of it within the vector
        vector<Course>:: iterator it;

        cout <<"Welcome to the course planner" << endl;
        do { // do

            cout << endl;
            cout << "1. Load Data Structure:" << endl;
            cout << "2. Print Course List:" << endl;
            cout << "3. Print Course:" << endl;
            cout << "4. Exit" << endl;
            cout << "What would you like to do?";

            cin >> choice;

            switch (choice) {
                case 1: {
                    //load the data struct
                    //call the loadVector function
                    string fileName;
                    loadVector("Advising_input.txt");
                    //sort the vector. sorting it here will remove the need for multiple sorts
                    sort(v.begin(), v.end(), compareCourses);
                    break;
                }

                case 2: {
                    cout << "Here is a sample schedule:\n" << endl;

                    //print out courses according to size of vector
                    for (int i = 0; i < v.size(); i++) {

                        cout << v[i].courseNum << "," << v[i].courseName << endl;
                    }
                    break;
                }

                case 3:{
                    //ask user what course they want to find out about
                    cout << "What course would you like to know about" << endl;

                    //take in userInput and make sure to put cin.ignore() for the C++ input issue
                    cin >> userInput;
                    cin.ignore();

                    //iterator it is a type within vector class we  will use it to sort and call isEqual
                    it = find_if(v.begin(), v.end(), isEqual);

                    //print course information

                    //use it as the type for vector reference
                    if (it != v.end()) {

                        cout << it->courseNum << "," << it->courseName << endl;
                        cout << "Prerequisites: ";

                        for (int i = 0; i < it->prereqs.size(); i++) {
                            //print the prerequisites for courses
                            cout << it->prereqs[i];

                            //removes the comma after last prerequisite
                            if (i == it->prereqs.size() - 1) {
                                cout << endl;
                            } else {
                                //comma between prerequisites
                                cout << ", ";

                            }
                        }
                    } else {
                        //error message for incorrect class choice by the user
                        cout << "Course Number: " << userInput << " is not found." << endl;
                    }
                    break;
            }
                case 4: {
                    //exit program
                    break;
                }
                    //when user enters anything but the four menu options provided
                default: {
                    cout << "Invalid option, please try again" << endl;
                }
            }

        }
        while (choice != 4); // while condition is met continue to run the program

        return 0;
    }

