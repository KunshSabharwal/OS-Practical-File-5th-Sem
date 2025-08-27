#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex; // Semaphore for writer access
sem_t mutex;    // Semaphore for reader access
int read_count = 0;
int shared_data = 0; // Shared resource

void *reader(void *arg)
{
    int reader_id = *((int *)arg);
    while (1)
    {
        // Reader entry section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
        {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);
        sleep(1); // Simulate reading time

        // Reader exit section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
        {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
        sleep(1); // Simulate delay before next reading
    }
    return NULL;
}

void *writer(void *arg)
{
    int writer_id = *((int *)arg);
    while (1)
    {
        // Writer entry section
        sem_wait(&rw_mutex);

        // Writing section
        shared_data++;
        printf("Writer %d: Wrote shared data = %d\n", writer_id, shared_data);
        sleep(1); // Simulate writing time

        // Writer exit section
        sem_post(&rw_mutex);
        sleep(2); // Simulate delay before next writing
    }
    return NULL;
}

int main()
{
    pthread_t rtid[5], wtid[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&rtid[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&wtid[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Join all threads
    for (int i = 0; i < 5; i++)
    {
        pthread_join(rtid[i], NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(wtid[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
