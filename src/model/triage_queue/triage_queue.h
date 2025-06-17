#ifndef TRIAGE_QUEUE_H
#define TRIAGE_QUEUE_H

#include "../triage/triage.h"

class TriageQueueNode {
public:
    Triage* triage;
    TriageQueueNode* next;

    TriageQueueNode(Triage* triageData);
};

class TriageQueue {
private:
    TriageQueueNode* head;

public:
    TriageQueue();
    ~TriageQueue();

    void enqueue(Triage* triage);
    void print();
    TriageQueueNode* getHead();  // Para a GUI acessar
};

#endif
