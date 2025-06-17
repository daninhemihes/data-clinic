#include "triage_queue.h"
#include <iostream>

TriageQueueNode::TriageQueueNode(Triage* triageData) {
    triage = triageData;
    next = nullptr;
}

TriageQueue::TriageQueue() {
    head = nullptr;
}

TriageQueue::~TriageQueue() {
    TriageQueueNode* current = head;
    while (current != nullptr) {
        TriageQueueNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void TriageQueue::enqueue(Triage* triage) {
    TriageQueueNode* newNode = new TriageQueueNode(triage);

    if (!head || head->triage->priority > triage->priority) {
        newNode->next = head;
        head = newNode;
        return;
    }

    TriageQueueNode* current = head;
    while (current->next && current->next->triage->priority <= triage->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void TriageQueue::print() {
    TriageQueueNode* current = head;
    std::cout << "\n--- Fila de Triagem (Manchester) ---\n";
    while (current) {
        std::cout << "ID: " << current->triage->id
                  << " | Prioridade: " << current->triage->priority << std::endl;
        current = current->next;
    }
}

TriageQueueNode* TriageQueue::getHead() {
    return head;
}
