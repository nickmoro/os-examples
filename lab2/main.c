#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct messageToThread {
    int* arr;
    int left;
    int right;
} messageToThread;

messageToThread newMessage(int* arr, int left, int right) {
    messageToThread msg;
    msg.arr = arr;
    msg.left = left;
    msg.right = right;
    return msg;
}

void* threadFunction(void* arg) {
    messageToThread* msg = (messageToThread*)arg;

    for (int i = msg->left; i < msg->right; ++i) {
        for (int j = msg->left; j < msg->right; ++j) {
            msg->arr[i] += 1;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int threadsN = 2, n;
    if (argc == 2) {
        threadsN = atoi(argv[1]);
    }
    printf("Will calculate on %d threads\n", threadsN);

    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    pthread_t* threads = malloc(threadsN * sizeof(pthread_t));
    messageToThread* msg = malloc(threadsN * sizeof(messageToThread));

    clock_t begin = clock();

    int left = 0;
    for (int i = 0; i < threadsN; ++i) {
        int right = left + (n + threadsN - 1) / threadsN;
        msg[i] = newMessage(arr, left, right);
        left = right;
        if (pthread_create(&threads[i], NULL, threadFunction, (void*)&msg[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < threadsN; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    printf("elapsed %3.6f ms\n", ((double)(end - begin) / CLOCKS_PER_SEC) * 1000);

    // printf("%d\n", n);
    // for (int i = 0; i < n; i += n / 10) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    free(threads);
    free(msg);
    free(arr);
}
