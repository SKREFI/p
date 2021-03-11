package com.skrefi.main.ui;

/*
    Author: Sandu Razvan-Alexandru
    Tema:   Catalog (student, materie, profesor)

    Deadlines:
        Etapa I  : 31 martie 2021
        Etapa II : 28 aprilie 2021
        Etapa III: 26 mai 2021


* */


import com.skrefi.main.data.models.Course;
import com.skrefi.main.data.models.userData.Address;
import com.skrefi.main.data.models.userData.Grade;
import com.skrefi.main.data.models.userData.Grupa;
import com.skrefi.main.data.models.userData.users.Student;
import com.skrefi.main.data.models.userData.users.Teacher;
import com.skrefi.main.data.utils.Domain;
import com.skrefi.main.data.utils.Helper;
import com.skrefi.main.data.utils.TeacherType;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        Teacher baetica = new Teacher(
                "Baetica",
                "Cornel",
                 "baetica@unibuc.ro",
                new Address("Bucuresti", "Bucuresti", "Academiei"),
                1,
                TeacherType.Professor);

        Student representant = new Student(
                "Andrei",
                "Neagu",
                "andrei@unibuc.ro",
                new Address("Bucharest", "Bucharest", "Wherever"),
                1,
                new ArrayList<Course>()
                );

        Grupa best = new Grupa(
                Domain.Info,
                2,
                4,
                1,
                30,
                representant
        );

        print(best);
    }

    private static <T> void print(T object) { Helper.print(object); }
}


