package com.skrefi.PAOProject.data.utils;


import com.skrefi.PAOProject.data.models.Course;
import com.skrefi.PAOProject.data.models.userData.Address;
import com.skrefi.PAOProject.data.models.userData.Grade;
import com.skrefi.PAOProject.data.models.userData.Grupa;
import com.skrefi.PAOProject.data.models.userData.users.Student;
import com.skrefi.PAOProject.data.models.userData.users.Teacher;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Helper {
    private static Random random = null;
    public static Random getRandomInstance() { return random == null ? new Random() : random; }

    public static <T> void print(ArrayList<T> o) {
        o.forEach(Helper::print);
    }

    public static <T> void print(T o) {
        System.out.println(o);
    }

    public static Student getOneStudent() {
        return new Student(
                "Andrei",
                "Neagu",
                "andrei@unibuc.ro",
                new Address("Bucharest", "Bucharest", "Wherever"),
                1,
                new ArrayList<Course>()
        );
    }

    public static Teacher getOneTeacher() {
        return new Teacher(
                "Baetica",
                "Cornel",
                "baetica@unibuc.ro",
                new Address("Bucuresti", "Bucuresti", "Academiei"),
                1,
                TeacherType.Professor
        );
    }

    public static Course getOneCourse() {
        return new Course(

        );
    }

    public static Grade getOneGrade() {
        return new Grade(5.0, 6d);
    }

    public static Grupa getOneGrupa(Student representant) {
        return new Grupa(
                Domain.Info,
                2,
                4,
                1,
                30,
                representant
        );
    }

    public static ArrayList<Student> getSomeStudents() {
        ArrayList<Student> students = new ArrayList<>();

        students.add(
            new Student(
                    "Ethan",
                    "Evelyn",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Liam",
                    "Olivia",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Olivia",
                    "Emma",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Noah",
                    "Ava",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Oliver",
                    "Sophia",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "William",
                    "Isabella",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Elijah",
                    "Mia",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "James",
                    "Lucas",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        students.add(
            new Student(
                    "Ethan",
                    "Harper",
                    "mail@unibuc.ro",
                    new Address("Bucharest", "Bucharest", "Wherever"),
                    1,
                    new ArrayList<Course>()
            )
        );

        return students;
    }
    public static ArrayList<Teacher> getSomeTeachers() {
        ArrayList<Teacher> teachers = new ArrayList<>();

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        teachers.add(
                new Teacher(
                        getRandomName(),
                        getRandomName(),
                        "mail@unibuc.ro",
                        new Address("Bucuresti", "Bucuresti", "Academiei"),
                        1,
                        Arrays.asList(TeacherType.Professor, TeacherType.Assistent).get(getRandomInstance().nextInt(1))
                )
        );

        return teachers;
    }
    public static ArrayList<Course> getSomeCourses() {
        ArrayList<Course> courses = new ArrayList<>();



        return courses;
    }

    public static Grade getRandomGrade() {
        return new Grade(
                round(1 + getRandomInstance().nextDouble() * 9, 2),
                round(1 + getRandomInstance().nextDouble() * 9, 2)
        );
    }

    public static String getRandomName() {
        final ArrayList<String> names = new ArrayList<>();
        names.add("James");
        names.add("Mary");
        names.add("John");
        names.add("Patricia");
        names.add("Robert");
        names.add("Jennifer");
        names.add("Michael");
        names.add("Linda");
        names.add("William");
        names.add("Elizabeth");
        names.add("David");
        names.add("Barbara");
        names.add("Richard");
        names.add("Susan");
        names.add("Joseph");
        names.add("Jessica");
        names.add("Thomas");
        names.add("Sarah");
        names.add("Charles");
        names.add("Karen");
        names.add("Christopher");
        names.add("Nancy");
        names.add("Daniel");
        names.add("Lisa");
        names.add("Matthew");
        names.add("Margaret");
        names.add("Anthony");
        names.add("Betty");
        names.add("Donald");
        names.add("Sandra");
        names.add("Mark");
        names.add("Ashley");
        names.add("Paul");
        names.add("Dorothy");
        return names.get((getRandomInstance()).nextInt(names.size()));
    }

    public static double round(double value, int places) {
        if (places < 0) throw new IllegalArgumentException();

        BigDecimal bd = BigDecimal.valueOf(value);
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }
}
