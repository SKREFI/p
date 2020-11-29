#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
 
// gcc ex2.c -pthread
typedef struct {
    int i; // i
    int j; // j
    int dim; // Col A / Row B
    int* c; // Referinta la c[i][j]
    int** a; // Referinta la A
    int** b; // Referinta la B
} elem_matrice;

void*    suma(void* v)
{
    elem_matrice* el = (elem_matrice*)v;
    *(el -> c) = 0;

 

    for (size_t i = 0; i < (el -> dim); i++)
        *(el -> c) += (el -> a)[el -> i][i] * (el -> b)[i][el -> j];

 

    return (void*) (el -> c);
}

int    main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf ("Utilizare: ./mult <nr. linii A> <nr. col A, nr. linii B> <nr. col B>");
        return (-1);
    }

    int** a;
    int** b;
    int rowA = atoi (argv[1]);
    int colA = atoi (argv[2]);
    int rowB = atoi (argv[2]);
    int colB = atoi (argv[3]);

    a = (int**)malloc(sizeof(int*) * rowA);    
    for (size_t i = 0; i < rowA; i++)
        a[i] = (int*)malloc(sizeof(int) * colA);

    b = (int**)malloc(sizeof(int*) * rowB);
    for (size_t i = 0; i < rowB; i++)
        b[i] = (int*)malloc(sizeof(int) * colB);

    for (int i = 0; i < rowA; i++)
        for (int j = 0; j < colA; j++)
            a[i][j] = i + j;

    for (int i = 0; i < rowB; i++)
        for (int j = 0; j < colB; j++)
            b[i][j] = i + j;

    int** c = (int**)malloc(sizeof(int*) * rowA); // Va avea linii cate are A
    for (size_t i = 0; i < rowA; i++)
        c[i] = (int*)malloc(sizeof(int) * colB); // Va avea coloane cate are B
    
    if (colA != rowB)
    {
        perror ("Numarul de coloane ale lui A diferit de numarul de linii ale lui B\n");
        return (-1);
    }

    pthread_t p [rowA * colB];
    for (size_t i = 0; i < rowA; i++)
        for (size_t j = 0; j < colB; j++)
        {
            elem_matrice* el = (elem_matrice*)malloc(sizeof(elem_matrice));
            el -> dim = rowA;
            el -> i = i;
            el -> j = j;
            el -> c = &c[i][j];
            el -> a = a;
            el -> b = b;
            el -> dim = colA; 
            if (pthread_create (&p[i * colB + j], NULL, suma, (void*) el))
            {
                perror ("Problema la initializarea thread-ului!\n");
                return errno;
            }
        }

    for (int i = 0; i < rowA; i++)
        for (int j = 0; j < colB; j++)
            if (pthread_join(p[i * colB + j], NULL))
            {
                printf ("Eroare la join-ul thread-ului");
                return errno;
            }

    printf ("===A===\n");
    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colA; j++)
            printf ("%d ", a[i][j]);
        printf ("\n");
    }

    printf ("===B===\n");
    for (int i = 0; i < rowB; i++)
    {
        for (int j = 0; j < colB; j++)
            printf ("%d ", b[i][j]);
        printf ("\n");
    }

    printf ("===C===\n");
    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colB; j++)
            printf ("%d ", c[i][j]);
        printf ("\n");
    }

    for (int i = 0; i < rowA; i++)
        free (a[i]);
    free (a);

    for (int i = 0; i < rowB; i++)
        free (b[i]);
    free (b);

    for (int i = 0; i < rowA; i++)
        free (c[i]);
    free (c);

    return 0;
}