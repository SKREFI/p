package com.skrefi.main.data.models.userData;

import java.util.Objects;

public class Grade {
    private Double labScore;
    private Double examScore;

    public Grade(Double labScore, Double examScore) {
        this.labScore = labScore;
        this.examScore = examScore;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Grade)) return false;
        Grade grade = (Grade) o;
        return labScore.equals(grade.labScore) && examScore.equals(grade.examScore);
    }

    @Override
    public int hashCode() {
        return Objects.hash(labScore, examScore);
    }

    @Override
    public String toString() {
        return "Grade{" + "labGrade=" + labScore + ", examGrade=" + examScore + '}';
    }

    public Double getLabScore() {
        return labScore;
    }

    public void setLabScore(Double labScore) {
        this.labScore = labScore;
    }

    public Double getExamScore() {
        return examScore;
    }

    public void setExamScore(Double examScore) {
        this.examScore = examScore;
    }
}
