package com.skrefi.PAOProject.repo;

import com.opencsv.CSVWriter;
import com.opencsv.bean.StatefulBeanToCsv;
import com.opencsv.bean.StatefulBeanToCsvBuilder;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import com.skrefi.PAOProject.data.models.Course;
import com.skrefi.PAOProject.data.models.userData.Grade;
import com.skrefi.PAOProject.data.models.userData.users.Student;
import com.skrefi.PAOProject.data.models.userData.users.Teacher;
import com.skrefi.PAOProject.data.utils.Helper;

import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.Random;

import static com.skrefi.PAOProject.data.utils.Constants.*;

public class DatabaseRepository {
    private static DatabaseRepository instance = null;
    private final Random random = new Random();

    Connection connection;

    private final ArrayList<Student> students = new ArrayList<>();
    private final ArrayList<Teacher> teachers = new ArrayList<>();
    private final ArrayList<Course> courses = new ArrayList<>();
    private final ArrayList<Grade> grades = new ArrayList<>();

    public void insertStudent(Student student) throws SQLException {
        Statement statement =  connection.createStatement();
        statement.execute("" +
                "INSERT INTO Students (id, firstName, lastName, emailAddress, addressId, grupaId) " +
                "VALUES (" + random.nextInt(1000) +  ", " +
                "\""+ student.getFirstName() +"\"," +
                "\""+ student.getLastName() +"\"," +
                "\""+ student.getEmailAddress() +"\"," +
                "\""+ random.nextInt(1000) +"\"," +
                " " + student.getGrupa() +")");
    }

    public void insertStudent(String firstName, String lastName, String email, Integer grupa) throws SQLException {
        Statement statement =  connection.createStatement();
        // Arata groaznic, stiu, dar JAVA nu are string interpolation, in afara de .format care nu vrea sa mearga impreuna cu metoda execute
        statement.execute("" +
                "INSERT INTO Students (id, firstName, lastName, emailAddress, addressId, grupaId) " +
                "VALUES (" + random.nextInt(1000) +  ", " +
                "\""+ firstName +"\"," +
                "\""+ lastName +"\"," +
                "\""+ email +"\"," +
                "\""+ random.nextInt(1000) +"\"," +
                " " + grupa +")");
    }


    public void deleteStudent(Integer id) throws SQLException {
        Statement statement =  connection.createStatement();
        statement.execute(String.format("DELETE FROM Students where id = %d", id));
    }

    public void printAllStudents() throws SQLException {
        Statement statement =  connection.createStatement();
        ResultSet rs = statement.executeQuery("SELECT * FROM Students");
        while (rs.next()) {
            Integer id = rs.getInt("id");
            String firstName = rs.getString("firstName");
            String lastName = rs.getString("lastName");
            String emailAddress = rs.getString("emailAddress");
            Integer addressId = rs.getInt("addressId");
            Integer grupaId = rs.getInt("grupaId");

            Helper.print(String.format("Id %d: %s %s %s AddressId: %d IdGrupa: %d", id, firstName, lastName, emailAddress, addressId, grupaId));
        }
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

    private DatabaseRepository() throws SQLException, ClassNotFoundException, IOException {
        Class.forName("com.mysql.jdbc.Driver");
        connection = DriverManager.getConnection(DATABASE_URL, DATABASE_USERNAME, DATABASE_PASSWORD);
    }

    public static DatabaseRepository getInstance() throws SQLException, ClassNotFoundException, IOException {
        return instance == null ? new DatabaseRepository(): instance;
    }
}
