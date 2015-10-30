#include <stdio.h>
#include <stdlib.h>
#include <sys/types.>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "reader.h"
#include "writer.h"
#include "common.h"

sem_t mutex, wrt;
