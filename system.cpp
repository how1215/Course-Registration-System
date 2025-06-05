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

        
};

class CourseSection{
    private:



};

void check_prerequisite(){}
void check_course_capacity(){}

int main(){
    std::vector<std::thread> threads;
    std::vector<Student> students={
        Student("Nick", 111),
        Student("Jane", 222),
        Student("Jim", 333)
    };


    return 0;
}