package com.skrefi.PAOProject.repo;

import com.opencsv.CSVWriter;
import com.opencsv.bean.StatefulBeanToCsv;
import com.opencsv.bean.StatefulBeanToCsvBuilder;
import com.opencsv.exceptions.CsvDataTypeMismatchException;
import com.opencsv.exceptions.CsvRequiredFieldEmptyException;
import com.skrefi.PAOProject.data.models.Course;
import com.skrefi.PAOProject.data.models.userData.Grade;
import com.skrefi.PAOProject.data.models.userData.Grupa;
import com.skrefi.PAOProject.data.models.userData.users.Student;
import com.skrefi.PAOProject.data.models.userData.users.Teacher;
import com.skrefi.PAOProject.data.utils.Helper;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.nio.file.Path;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static com.skrefi.PAOProject.data.utils.Constants.*;

public class CSVRepository {
    private static CSVRepository instance = null;

    public static CSVRepository getInstance() throws IOException {
        return instance == null ? new CSVRepository() : instance;
    }

    public CSVRepository() {}

    public void writeCsvGrades(List<Grade> list) throws Exception {
        Writer writer  = new FileWriter(GRADES_CSV_PATH);

        StatefulBeanToCsv sbc = new StatefulBeanToCsvBuilder(writer)
                .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
                .build();

        sbc.write(list);
        writer.close();
    }

    public void writeCsvTeachers(List<Teacher> list) throws Exception {
        Writer writer  = new FileWriter(TEACHERS_CSV_PATH);

        StatefulBeanToCsv sbc = new StatefulBeanToCsvBuilder(writer)
                .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
                .build();

        sbc.write(list);
        writer.close();
    }

    public void writeCsvStudents(List<Student> list) throws Exception {
        Writer writer  = new FileWriter(STUDENTS_CSV_PATH);

        StatefulBeanToCsv sbc = new StatefulBeanToCsvBuilder(writer)
                .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
                .build();

        sbc.write(list);
        writer.close();
    }

    public void writeCsvGrupe(List<Grupa> list) throws Exception {
        StatefulBeanToCsv sbc = new StatefulBeanToCsvBuilder(new FileWriter(GRUPE_CSV_PATH))
                .withSeparator(CSVWriter.DEFAULT_SEPARATOR)
                .build();

        sbc.write(list);
    }
}
