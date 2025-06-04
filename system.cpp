#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;
int shared_count = 0;  // 共享的計數器

class Student{
        private:
        std::string name;
        int id;
        // std::vector <CourseSection> courses;

    public:
        Student(std::string name, int id):name(name),id(id){}

        void increment(){
            std::lock_guard<std::mutex> lock(mtx);
            shared_count++;  // 所有執行緒共同增加這個數字
            std::cout << "Student " << name << " (ID: " << id << ") incremented shared_count to: " << shared_count << std::endl;
        }
        
};

class CourseSection{
    private:
        


};




int main(){
    std::vector<std::thread> threads;
    std::vector<Student> students={
        Student("Nick", 111),
        Student("Jane", 222),
        Student("Jim", 333)
    };

    for (auto& s : students) {
        threads.push_back(std::thread(&Student::increment, std::ref(s)));
    }
    for(auto& t : threads){
        t.join();
    }

    std::cout << "Final shared_count value: " << shared_count << std::endl;
    std::cout << "I am master thread and I am about to finish"<< std::endl;
    return 0;
}