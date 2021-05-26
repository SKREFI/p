package com.skrefi.main.ui;

/*
    Grupa:  241
    Author: Sandu Razvan-Alexandru
    Tema:   Catalog (student, materie, profesor)


    Deadlines:
        Etapa I  : 31 martie 2021
        Etapa II : 28 aprilie 2021
        Etapa III: 26 mai 2021
* */


import com.skrefi.main.data.models.userData.Grupa;
import com.skrefi.main.data.models.userData.users.Student;
import com.skrefi.main.data.models.userData.users.Teacher;
import com.skrefi.main.data.utils.Helper;
import com.skrefi.main.data.utils.Menu;
import com.skrefi.main.repo.DatabaseRepository;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Teacher baetica = Helper.getOneTeacher();
        Student representant = Helper.getOneStudent();
        Grupa best = Helper.getOneGrupa(representant);

        DatabaseRepository db = DatabaseRepository.getInstance();

        Helper.print(Helper.getRandomGrade());

        Menu menu = Menu.getInstance();
        menu.show();
    }

    private static <T> void print(T object) { Helper.print(object); }
}


