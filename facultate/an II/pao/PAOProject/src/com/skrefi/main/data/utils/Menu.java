package com.skrefi.main.data.utils;

import com.skrefi.main.repo.DatabaseRepository;

import java.util.Scanner;

public class Menu {
    private static Menu instance = null;
    private static Scanner scanner;

    public int promptMenu() {
        Helper.print("============== MENU ==============");
        Helper.print("=========== 0. Print All Students  ===========");
        Helper.print("=========== 1. Print All Teachers  ===========");
        Helper.print("=========== 2. Print All Courses  ===========");
        Helper.print("=========== 3. Add a new Student  ===========");
        Helper.print("=========== 4. Add a new Teacher  ===========");
        Helper.print("=========== 5. Add a new Course  ===========");
        Helper.print("=========== 6. TODO  ===========");

        int option = scanner.nextInt();

        switch (option) {
            case 0:
                printAllStudents();
                break;
            case 1:
                printAllTeachers();
                break;
            case 2:
                printAllCourses();
                break;
            case 3:
                addNewStudent();
                break;
            case 4:
                addNewTeacher();
                break;
            case 5:
                addNewCourse();
                break;

            default:
                Helper.print("No such option in my menu :)");
        }

        return option;
    }

    private void printAllStudents() {

    }

    private void printAllTeachers() {

    }

    private void printAllCourses() {

    }

    private void addNewStudent() {

    }

    private void addNewTeacher() {

    }

    private void addNewCourse() {
        
    }



    private Menu() {
        scanner = new Scanner(System.in);
    }
    public static Menu getInstance() { return instance == null ? new Menu(): instance; }
}
