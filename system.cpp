#include <thread>
#include <iostream>
#include <vector>

class Student{
        private:
        std::string name;
        int id;
        std::vector <CourseSection> courses;

    public:
        Student(std::string name, int id):name(name),id(id){}
        
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
        threads.emplace_back(std::thread(std::ref(s)));
    }
    for(auto& t : threads){
        t.join();
    }

    std::cout << "I am dick thread and I am about to finish"<< std::endl;
    return 0;
}