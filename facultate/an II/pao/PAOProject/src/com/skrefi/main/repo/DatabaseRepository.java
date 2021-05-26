package com.skrefi.main.repo;

import com.skrefi.main.data.models.Course;
import com.skrefi.main.data.models.userData.Grade;
import com.skrefi.main.data.models.userData.users.Student;
import com.skrefi.main.data.models.userData.users.Teacher;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class DatabaseRepository {
    private static DatabaseRepository instance = null;

    private final ArrayList<Student> students = new ArrayList<>();
    private final ArrayList<Teacher> teachers = new ArrayList<>();
    private final ArrayList<Course> courses = new ArrayList<>();
    private final ArrayList<Grade> grades = new ArrayList<>();

    StatefulBeanToCsv<Course> coursesSbc = new StatefulBeanToCsvBuilder<Course>(new FileWriter(COURSES_CSV_PATH))
            .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
            .build();

    StatefulBeanToCsv<Teacher> teachersSbc = new StatefulBeanToCsvBuilder<Teacher>(new FileWriter(TEACHERS_CSV_PATH))
            .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
            .build();

    StatefulBeanToCsv<Student> studentsSbc = new StatefulBeanToCsvBuilder<Student>(new FileWriter(STUDENTS_CSV_PATH))
            .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
            .build();

    public void writeToCsv(Student student) {
        studentsSbc.write(student);
    }

    public void writeToCsv(Teacher teacher) {
        teachersSbc.write(teacher);
    }

    public void writeToCsv(Course course) {
        coursesSbc.write(course);
    }


    public boolean read() {
//        TODO: Implement
        return true;
    }

    public void addStudents(ArrayList<Student> e) { e.forEach(this::add); }
    public void addTeachers(ArrayList<Teacher> e) { e.forEach(this::add); }
    public void addCourses(ArrayList<Course> e) { e.forEach(this::add); }
    public void addGrades(ArrayList<Grade> e) { e.forEach(this::add); }

    public void add(Student e) { students.add(e); }
    public void add(Teacher e) { teachers.add(e); }
    public void add(Course e) { courses.add(e); }
    public void add(Grade e) { grades.add(e); }

    public ArrayList<Student> getStudents() { return students; }
    public ArrayList<Teacher> getTeachers() { return teachers; }
    public ArrayList<Course> getCourses() { return courses; }
    public ArrayList<Grade> getGrades() { return grades; }

    private DatabaseRepository() throws IOException {}
    public static DatabaseRepository getInstance() throws IOException {


        return instance == null ? new DatabaseRepository(): instance;
    }
}
