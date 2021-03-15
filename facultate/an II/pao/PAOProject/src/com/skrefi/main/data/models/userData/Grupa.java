package com.skrefi.main.data.models.userData;

import com.skrefi.main.data.models.userData.users.Student;
import com.skrefi.main.data.utils.Domain;

import java.util.Objects;

public class Grupa {
    private Integer id;
    private Domain domain;

    private Integer studyYear;
    private Integer yearSeries;
    private Integer groupId;

    private Integer numberOfStudents;
    private Student representant;

    public Integer getGrupa() {
        return 100 * studyYear + 10 * yearSeries + groupId;
    }

    public Grupa(Domain domain, Integer studyYear, Integer yearSeries, Integer groupId, Integer numberOfStudents, Student representant) {
        this.domain = domain;
        this.studyYear = studyYear;
        this.yearSeries = yearSeries;
        this.groupId = groupId;
        this.numberOfStudents = numberOfStudents;
        this.representant = representant;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Grupa)) return false;
        Grupa grupa = (Grupa) o;
        return getDomain() == grupa.getDomain() && getStudyYear().equals(grupa.getStudyYear()) && getYearSeries().equals(grupa.getYearSeries()) && getGroupId().equals(grupa.getGroupId()) && getRepresentant().equals(grupa.getRepresentant());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getDomain(), getStudyYear(), getYearSeries(), getGroupId());
    }

    @Override
    public String toString() {
        return "Grupa{" +
                "domain=" + domain +
                "grupa: " + this.getGrupa().toString() +
                ", numberOfStudents=" + numberOfStudents +
                ", representant=" + representant +
                '}';
    }

    public Domain getDomain() {
        return domain;
    }

    public void setDomain(Domain domain) {
        this.domain = domain;
    }

    public Integer getStudyYear() {
        return studyYear;
    }

    public void setStudyYear(Integer studyYear) {
        this.studyYear = studyYear;
    }

    public Integer getYearSeries() {
        return yearSeries;
    }

    public void setYearSeries(Integer yearSeries) {
        this.yearSeries = yearSeries;
    }

    public Integer getGroupId() {
        return groupId;
    }

    public void setGroupId(Integer groupId) {
        this.groupId = groupId;
    }

    public Student getRepresentant() {
        return representant;
    }

    public void setRepresentant(Student representant) {
        this.representant = representant;
    }

    public Integer getNumberOfStudents() {
        return numberOfStudents;
    }

    public void setNumberOfStudents(Integer numberOfStudents) {
        this.numberOfStudents = numberOfStudents;
    }
}
