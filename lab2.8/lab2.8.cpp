#include <iostream>

template <typename T>
class Stack {
private:
    T* stackArray;  // указатель на массив стека
    int maxSize;   
    int topIndex;   // индекс верхнего элемента стека

public:
    Stack(int size) : maxSize(size), topIndex(-1) {
        stackArray = new (std::nothrow) T[maxSize];  // выделение памяти под стек
        if (stackArray == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~Stack() {
        delete[] stackArray;  
    }

    int size() const {
        return topIndex + 1;
    }

    bool empty() const {
        return (topIndex == -1);
    }

    void push(const T& element) {
        if (size() == maxSize) {
            throw std::overflow_error("Stack is full.");
        }

        stackArray[++topIndex] = element;
    }

    // Last in, first out

    T pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty.");
        }

        return stackArray[topIndex--];
    }

    T top() const {
        if (empty()) {
            throw std::logic_error("Stack is empty.");      
        }

        return stackArray[topIndex];
    }
};

int main() {
    try {
        Stack<int> stack1(5);
        stack1.push(1);
        stack1.push(2);
        stack1.push(3);
        stack1.push(4);
        stack1.push(5);

        // Examples for errors:
        
        // Overflow 
        // myStack.push(60);
        
        // Bad allocation           
        // Stack<int> stack2(std::numeric_limits<int>::max());

        // Underflow
        // Stack<int> stack3(3);
        // stack3.pop();

        // Logic error
        // Stack<int> stack4(6);
        // stack4.top();

        std::cout << "Stack size: " << stack1.size() << std::endl;
        std::cout << "Top element: " << stack1.top() << std::endl;

        while (!stack1.empty()) {
            std::cout << "Popped element: " << stack1.pop() << std::endl;
        }
    }
    catch (const std::bad_alloc&) {
        std::cerr << "Memory allocation failed: Unable to create the stack." << std::endl;
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Stack overflow: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Stack underflow: " << e.what() << std::endl;
    }
    catch (const std::logic_error& e) {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }

    return 0;
}