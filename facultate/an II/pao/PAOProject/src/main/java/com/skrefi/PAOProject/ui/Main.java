package com.skrefi.PAOProject.ui;

/*
    Grupa:  241
    Author: Sandu Razvan-Alexandru
    Tema:   Catalog (student, materie, profesor)


    Deadlines:
        Etapa I  : 31 martie 2021
        Etapa II : 28 aprilie 2021
        Etapa III: 26 mai 2021
**/


import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import com.skrefi.PAOProject.PaoProjectApplication;
import com.skrefi.PAOProject.data.models.userData.Grade;
import com.skrefi.PAOProject.data.models.userData.Grupa;
import com.skrefi.PAOProject.data.models.userData.users.Student;
import com.skrefi.PAOProject.data.models.userData.users.Teacher;
import com.skrefi.PAOProject.data.utils.Helper;
import com.skrefi.PAOProject.data.utils.Menu;
import com.skrefi.PAOProject.repo.CSVRepository;
import com.skrefi.PAOProject.repo.DatabaseRepository;
import org.springframework.boot.SpringApplication;

import java.io.IOException;
import java.nio.file.Paths;
import java.sql.Array;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;

import static com.skrefi.PAOProject.data.utils.Constants.GRADES_CSV_PATH;

public class Main {
    public static void main(String[] args) throws Exception {
        SpringApplication.run(PaoProjectApplication.class, args);
        DatabaseRepository db = DatabaseRepository.getInstance();
        Student student = Helper.getOneStudent();

        CSVRepository csvRepository = CSVRepository.getInstance();

        ArrayList<Grade> grades = new ArrayList();
        grades.add(Helper.getOneGrade());
        grades.add(Helper.getOneGrade());
        grades.add(Helper.getOneGrade());
        grades.add(Helper.getOneGrade());


        ArrayList<Grupa> grupe = new ArrayList();
        grupe.add(Helper.getOneGrupa(student));
        grupe.add(Helper.getOneGrupa(student));
        grupe.add(Helper.getOneGrupa(student));

        csvRepository.writeCsvGrupe(grupe);
        csvRepository.writeCsvGrades(grades);


        Menu menu = Menu.getInstance();
        menu.show();
    }

    private static <T> void print(T object) { Helper.print(object); }
}


