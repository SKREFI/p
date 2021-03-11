package com.skrefi.main.repo;

import com.skrefi.main.data.models.Course;
import com.skrefi.main.data.models.userData.Grade;
import com.skrefi.main.data.models.userData.users.Student;
import com.skrefi.main.data.models.userData.users.Teacher;

import java.util.ArrayList;

public class DatabaseRepository {
    private static DatabaseRepository instance = null;

    private static ArrayList<Student> students;
    private static ArrayList<Teacher> teachers;
    private static ArrayList<Course> courses;
    private static ArrayList<Grade> grades;

    public boolean write() {
//        TODO: Implement
        return true;
    }

    public boolean read() {
//        TODO: Implement
        return true;
    }

    private DatabaseRepository() {}

    public static DatabaseRepository getInstance() { return instance == null ? new DatabaseRepository(): instance; }
}
