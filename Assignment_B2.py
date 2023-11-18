from threading import Semaphore, Thread
from time import sleep

# Shared Memory variables
CAPACITY = 10
# buffer max number of items that can a stored at a time -> like an inventory
buffer = [-1 for i in range(CAPACITY)]
#buffer = [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
in_index = 0
out_index = 0

# Declaring Semaphores
# 1 means semaphore is free. 0 means acquired
mutex = Semaphore()

# stores number of slots free in buffer.
empty = Semaphore(CAPACITY)

# number of slots full in buffer.
full = Semaphore(0)


class Producer(Thread):
    def run(self):

        global CAPACITY, buffer, in_index, out_index, mutex, empty, full

        items_produced = 0
        counter = 0

        while items_produced < 20:
            empty.acquire()
            mutex.acquire()

            counter += 1
            buffer[in_index] = counter
            in_index = (in_index + 1) % CAPACITY
            print("Producer produced : ", counter)

            mutex.release()
            full.release()

            sleep(1)

            items_produced += 1


class Consumer(Thread):
    def run(self):

        global CAPACITY, buffer, in_index, out_index, counter
        global mutex, empty, full

        items_consumed = 0

        while items_consumed < 20:
            full.acquire()
            mutex.acquire()

            item = buffer[out_index]
            out_index = (out_index + 1) % CAPACITY
            print("Consumer consumed item : ", item)

            mutex.release()
            empty.release()

            sleep(2)

            items_consumed += 1


# Creating Threads
producer = Producer()
consumer = Consumer()

# Starting Threads
producer.start()
consumer.start()


# Waiting for threads to complete
producer.join()
consumer.join()