package com.skrefi.PAOProject.data.models.userData.users;

import com.opencsv.bean.CsvBindByName;
import com.skrefi.PAOProject.data.models.Course;
import com.skrefi.PAOProject.data.models.userData.Address;
import com.skrefi.PAOProject.data.models.userData.Grupa;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Objects;

public class Student extends Person {
    @CsvBindByName
    private Integer grupaId;

    private ArrayList<Course> courses;

    public Student(String firstName, String lastName, String emailAddress, Address address, Integer grupaId, ArrayList<Course> courses) {
        super(firstName, lastName, emailAddress, address);
        this.grupaId = grupaId;
        this.courses = courses;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student)) return false;
        if (!super.equals(o)) return false;
        Student that = (Student) o;
        return getGrupa().equals(that.getGrupa()) && getCourses().equals(that.getCourses());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getGrupa(), getCourses());
    }

    public Integer getGrupa() {
        return grupaId;
    }

    public void setGrupa(Integer grupaId) {
        this.grupaId = grupaId;
    }

    public ArrayList<Course> getCourses() {
        return courses;
    }

    public void setCourses(ArrayList<Course> courses) {
        this.courses = courses;
    }
}
