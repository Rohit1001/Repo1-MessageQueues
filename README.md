# Repo1-MessageQueues
Queue container adapter as we know is not thread safe.
We have created a wrapper class to have a queue object as a datamember. And have added a thread safe behavior to the push and pop methods on a our new queue class object.
Here is a C++ implementaion for how it can be made thread safe.
Thanks to below blog for understanding message queue using producer consumer example.
https://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/
