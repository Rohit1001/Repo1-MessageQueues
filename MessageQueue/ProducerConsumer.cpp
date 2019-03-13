#include "MyQueue.h"
#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

const int nbConsumers = 4;
const int nbToConsume = 3;
const int nbToProduce = nbToConsume * nbConsumers;

void print(string x) {
  static mutex mutex1;
  unique_lock<mutex> locker(mutex1);
  cout << x << "\n";
}

void produce(MyQueue<int>& q) {
  for (int i = 1; i <= nbToProduce; ++i) {
    ostringstream tmp;
    tmp << "P --> " << i;
    print(tmp.str());
    q.push(i);
  }
}

void consume(MyQueue<int>& q, unsigned int id) {
  for (int i = 0; i < nbToConsume; ++i) {
    auto item = q.pop();
    ostringstream tmp;
    tmp << "C        " << item << " --> C" << id;
    print(tmp.str());
  }
}

int main()
{
  MyQueue<int> q;

  // Start the producer thread.
  thread prod(bind(produce, ref(q)));

  // Start the consumer threads.
  vector<thread> consumers;
  for (int i = 0 ; i < nbConsumers ; ++i) {
    thread consumer(bind(&consume, ref(q), i + 1));
    consumers.push_back(move(consumer));
  }

  // Joining threads to main process to avoid exception
  prod.join();

  // Joining threads to main process to avoid exception
  for (auto& consumer : consumers) {
    consumer.join();
  }
}
