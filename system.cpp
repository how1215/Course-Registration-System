#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;

class Student{
        private:
        std::string name;
        int id;
        int count=0;
        // std::vector <CourseSection> courses;

    public:
        Student(std::string name, int id):name(name),id(id){}

        void increment(){
            count++;
        }
        
};

// class CourseSection{



// };




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

    std::cout << "I am master thread and I am about to finish"<< std::endl;
    return 0;
}