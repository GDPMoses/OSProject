#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>
#include <chrono>
#include <vector>

#define BUFFER_SIZE 10

std::queue<int> buffer;
pthread_mutex_t mutexBuffer;
pthread_cond_t condFull;
pthread_cond_t condEmpty;

int num_items = 100;
int producer_sleep = 1;
int consumer_sleep = 1;
int num_producers = 1;
int num_consumers = 1;

void* producer(void* arg) {
    int id = *((int*)arg);
    int items = num_items / num_producers;
    for (int i = 0; i < items; ++i) {
        usleep(producer_sleep * 100000);
        pthread_mutex_lock(&mutexBuffer);
        while (buffer.size() == BUFFER_SIZE) {
            pthread_cond_wait(&condFull, &mutexBuffer);
        }
        buffer.push(id * 1000 + i);
        std::cout << "Producer " << id << " produced item " << id * 1000 + i << std::endl;
        pthread_cond_signal(&condEmpty);
        pthread_mutex_unlock(&mutexBuffer);
    }
    return nullptr;
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    int items = num_items / num_consumers;
    for (int i = 0; i < items; ++i) {
        usleep(consumer_sleep * 100000);
        pthread_mutex_lock(&mutexBuffer);
        while (buffer.empty()) {
            pthread_cond_wait(&condEmpty, &mutexBuffer);
        }
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed item " << item << std::endl;
        pthread_cond_signal(&condFull);
        pthread_mutex_unlock(&mutexBuffer);
    }
    return nullptr;
}

int main() {
    std::cout << "Enter number of items to produce/consume: ";
    std::cin >> num_items;
    std::cout << "Enter producer sleep time (deciseconds): ";
    std::cin >> producer_sleep;
    std::cout << "Enter consumer sleep time (deciseconds): ";
    std::cin >> consumer_sleep;
    std::cout << "Enter number of producers: ";
    std::cin >> num_producers;
    std::cout << "Enter number of consumers: ";
    std::cin >> num_consumers;

    pthread_mutex_init(&mutexBuffer, nullptr);
    pthread_cond_init(&condFull, nullptr);
    pthread_cond_init(&condEmpty, nullptr);

    std::vector<pthread_t> producers(num_producers);
    std::vector<pthread_t> consumers(num_consumers);
    std::vector<int> producer_ids(num_producers);
    std::vector<int> consumer_ids(num_consumers);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_producers; ++i) {
        producer_ids[i] = i;
        pthread_create(&producers[i], nullptr, producer, &producer_ids[i]);
    }
    for (int i = 0; i < num_consumers; ++i) {
        consumer_ids[i] = i;
        pthread_create(&consumers[i], nullptr, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < num_producers; ++i) {
        pthread_join(producers[i], nullptr);
    }
    for (int i = 0; i < num_consumers; ++i) {
        pthread_join(consumers[i], nullptr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTotal Turnaround Time: " << elapsed.count() << " seconds\n";

    pthread_mutex_destroy(&mutexBuffer);
    pthread_cond_destroy(&condFull);
    pthread_cond_destroy(&condEmpty);

    return 0;
}