#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
const int n = 5;
int nr;

typedef struct {                    //structura pt thread ce contine si un identificator reprezentand indicele de creare in main
    pthread_t thr;
    int id;
} thread;

thread th[10];                      //vector de threaduri

int bariera() {
    pthread_mutex_lock( & mtx);     //blochez mutex-ul pentru contorizare
    nr++;                           //incrementez contorul de thread uri ce asteapta la bariera
    pthread_mutex_unlock( & mtx);   //deblochez mutex-ul

    if (nr < n) {
        //daca inca nu s-au adunat n thread-uri, nu permit executia (valoarea din semafor la momentul apelului sem_wait(&sem) este 0 si deci thread-ul este blocat)
        if (sem_wait(&sem)) { perror(NULL); return errno; }
    } else for (int i = 0; i < n - 1; i++) { 
        // in momentul in care s-au adunat n thread-uri, "ridic" bariera si permit executia tuturor (cand ajunge thread-ul n, nu mai face wait si face post, astfel
        // incrementand valoarea din semafor la 1 -> restul thread-urilor ce asteptau la wait vor putea acum sa isi continue executia)
        if (sem_post(&sem)) { perror(NULL); return errno; }
    }
}

void* tfun(void* v) {
    int id = *(int*)v;                            //indicele thread ului
    printf("%d reached the barrier!\n", id);
    bariera();                                    //gestionarea barierei
    printf("%d passed the barrier!\n", id);
}

// -pthread flag required again :))
// Execute me: gcc -pthread ex2.c -o ex2 && ./ex2
int main() {
    if (pthread_mutex_init(&mtx, NULL)) { perror(NULL); return errno; }
    if (sem_init( & sem, 0, 0)) { perror(NULL); return errno; }

    // creez n thread-uri, fiecare primind sa execute functia tfun, avand ca argument indicele de creere
    for (int i = 0; i < n; i++) { 
      th[i].id = i;
      pthread_create( & th[i].thr, NULL, tfun, & th[i].id);
    }

    // unesc thread-urile cu main-thread
    for (int i = 0; i < n; i++) pthread_join(th[i].thr, NULL);

    pthread_mutex_destroy( & mtx);    //distrug mutex-ul
    sem_destroy( & sem);              //distrug semaforul
}