package com.skrefi.main.data.models.userData.users;

import com.skrefi.main.data.models.userData.Address;
import com.skrefi.main.data.utils.TeacherType;

import java.util.Objects;


public class Teacher extends Person {
    private Integer courseId;
    private TeacherType teacherType;

    public Teacher(String firstName, String lastName, String emailAddress, Address address, Integer courseId, TeacherType teacherType) {
        super(firstName, lastName, emailAddress, address);
        this.courseId = courseId;
        this.teacherType = teacherType;
    }

    @Override
    public String toString() {
        return "Teacher{" +
                "Details=" + super.toString() +
                "courseId=" + courseId +
                ", teacherType=" + teacherType +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Teacher)) return false;
        if (!super.equals(o)) return false;
        Teacher that = (Teacher) o;
        return getCourseId().equals(that.getCourseId()) && getTeacherType() == that.getTeacherType();
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getCourseId(), getTeacherType());
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public TeacherType getTeacherType() {
        return teacherType;
    }

    public void setTeacherType(TeacherType teacherType) {
        this.teacherType = teacherType;
    }
}
