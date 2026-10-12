#include <iostream>

// Node structure for circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Circular linked list class
class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList(int n) {
        head = nullptr;
        size = 0;
        
        // Create n nodes with values 1 to n
        for (int i = 1; i <= n; i++) {
            append(i);
        }
    }
    
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Traverse the circular list and delete all nodes
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
        
        head = nullptr;
        size = 0;
    }
    
    void append(int val) {
        Node* newNode = new Node(val);
        
        if (head == nullptr) {
            head = newNode;
            head->next = head; // Point to itself for circularity
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        
        size++;
    }
    
    // Delete the m-th node starting from start, and return the node after the deleted one
    Node* deleteMth(Node* start, int m) {
        if (head == nullptr || size == 0) return nullptr;
        
        // If only one node remains
        if (size == 1) {
            std::cout << head->data << std::endl;
            Node* result = head->next; // This will be head itself
            delete head;
            head = nullptr;
            size--;
            return result;
        }
        
        // Special case: if m == 1, we delete the start node
        if (m == 1) {
            Node* nodeToDelete = start;
            Node* nextStart = start->next;
            
            // Find the node before start (the predecessor)
            Node* prev = start;
            while (prev->next != start) {
                prev = prev->next;
            }
            
            // Remove the node from the list
            prev->next = nextStart;
            
            // If we're deleting the head, update head pointer
            if (nodeToDelete == head) {
                head = nextStart;
            }
            
            std::cout << nodeToDelete->data << std::endl;
            delete nodeToDelete;
            size--;
            
            return nextStart;
        }
        
        // Find the node before the one to delete (m-1 steps from start)
        Node* current = start;
        for (int i = 0; i < m - 2; i++) {
            current = current->next;
        }
        
        // Now current points to the node before the one to delete
        Node* nodeToDelete = current->next;
        Node* nextStart = nodeToDelete->next; // The node after deleted one becomes the new start
        
        // Remove the node from the list
        current->next = nextStart;
        
        // If we're deleting the head, update head pointer
        if (nodeToDelete == head) {
            head = nextStart;
        }
        
        std::cout << nodeToDelete->data << std::endl;
        delete nodeToDelete;
        size--;
        
        return nextStart;
    }
    
    Node* getHead() const {
        return head;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    
    CircularLinkedList list(n);
    
    // Simulate Josephus problem
    Node* current = list.getHead();
    while (!list.isEmpty()) {
        current = list.deleteMth(current, m);
    }
    
    return 0;
}