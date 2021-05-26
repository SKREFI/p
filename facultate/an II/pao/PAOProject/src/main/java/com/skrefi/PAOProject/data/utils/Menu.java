package com.skrefi.PAOProject.data.utils;

import com.skrefi.PAOProject.repo.DatabaseRepository;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Scanner;

public class Menu {
    private static Menu instance = null;
    private static Scanner scanner;
    private DatabaseRepository db;

    private Menu() throws SQLException, IOException, ClassNotFoundException {
        db = DatabaseRepository.getInstance();
        scanner = new Scanner(System.in);
    }
    public static Menu getInstance() throws SQLException, IOException, ClassNotFoundException { return instance == null ? new Menu(): instance; }

    public int show() throws SQLException {
        Helper.print("============== MENU ==============");
        Helper.print("=========== 0. Print All Students  ===========");
        Helper.print("=========== 1. Insert Student      ===========");
        Helper.print("=========== 2. Delete student      ===========");

        Helper.print("=========== 3. TODO                ===========");
        Helper.print("Option: ");

        int option = scanner.nextInt();

        switch (option) {
            case 0:
                printAllStudents();
                break;
            case 1:
                insertStudent();
                break;
            case 2:
                deleteStudent();
                break;

            default:
                Helper.print("No such option in my menu :)");
        }

        this.show();
        return option;
    }


    private void printAllStudents() throws SQLException {
        db.printAllStudents();
    }

    private void insertStudent() throws SQLException {
        Helper.print("First name: ");
        String firstName = scanner.nextLine();
        Helper.print("Last name: ");
        String lastName = scanner.nextLine();
        Helper.print("Email: ");
        String email = scanner.nextLine();
        Helper.print("Grupa (int): ");
        Integer grupa = scanner.nextInt();

        db.insertStudent(firstName, lastName, email, grupa);
        Helper.print("Student successfully added.");
    }

    private void deleteStudent() throws SQLException {
        Helper.print("Student's id you want to delete:");
        db.deleteStudent(scanner.nextInt());
        Helper.print("Student successfully deleted.");
    }
}
