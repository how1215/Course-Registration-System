#include <thread>
#include <iostream>
#include <vector>
#include <mutex>


class Course{   
    private:
        std::string name;
        int id;
        //課程人數上限
        int max_capacity;
        //前修課程
        std::vector<Course> prerequisite;
    public:
        Course(std::string name, int id, int max_capacity, std::vector<Course> prerequisite):name(name),id(id),max_capacity(max_capacity),prerequisite(prerequisite){}

        std::string getName() const { return name; }
        void setName(std::string name) { this->name=name; }

        int getId() const { return id; }
        void setId(int id) { this->id=id; }

        int getMaxCapacity() const { return max_capacity; }
        void setMaxCapacity(int max_capacity) { this->max_capacity=max_capacity; }

        std::vector<Course> getPrerequisite() const { return prerequisite; }
        void setPrerequisite(std::vector<Course> prerequisite) { this->prerequisite=prerequisite; }
        //印出課程資訊
        void printCourseInfo(){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"課程名稱: "<<name<<std::endl;
            std::cout<<"課程編號: "<<id<<std::endl;
            std::cout<<"課程人數上限: "<<max_capacity<<std::endl;
            std::cout<<"前修課程: "<<prerequisite.size()<<std::endl;
            std::cout<<"--------------------------------"<<std::endl;
        }

};

class Student{  
        private:
        std::string name;
        int id;
        //已修過課程
        std::vector<Course> passedCourses;
        //已選課程
        std::vector<Course> schedule;
    public:
        Student(std::string name, int id, std::vector<Course> passedCourses):name(name),id(id),passedCourses(passedCourses){}
        
        std::string getName() const { return name; }
        void setName(std::string name) { this->name=name; }

        int getId() const { return id; }
        void setId(int id) { this->id=id; }

        std::vector<Course> getPassedCourses() const { return passedCourses; }
        void setPassedCourses(std::vector<Course> passedCourses)  { this->passedCourses=passedCourses; }

        //印出學生資訊
        void printStudentInfo(){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"學生名稱: "<<name<<std::endl;
            std::cout<<"學生編號: "<<id<<std::endl;
            std::cout<<"已修過課程: "<<passedCourses.size()<<std::endl;
            std::cout<<"--------------------------------"<<std::endl;
        }


};

class CourseSection{
    private:

        bool open=false;
        bool closedOrCancelled=false;
        //
        std::vector<Student> registrationList;
    public:       
        //學生註冊課程
        void registerCourse(Student student, Course course){
            //確認有無符合前修課程

        }

};

//確認有無符合前修課程
void check_prerequisite(){}
//確認課程人數是否已滿
void check_course_capacity(){}


int main(){

        //基礎課程(無前修課程)  
        Course c1("C++", 101, 3, {});
        Course c2("Data Structure", 102, 2, {});
        Course c3("Algorithm", 103, 3, {});
        //進階課程(有前修課程)
        Course c4("OOP", 201, 3, {c1});
        Course c5("Advanced Data Structure", 202, 3, {c2});
        Course c6("Algorithm 2", 203, 3, {c3});

        //新生(無修過任何課程)
        Student s1("Lebron", 001,{});
        Student s2("Hanni", 002,{});
        Student s3("Jake", 003,{});
        //大二(已修過某些基礎課程) 
        Student s4("John", 004,{c1,c2,c3});
        Student s5("Minji", 005,{c1,c2});
        //壞學生(之前全被當)
        Student s6("Nick", 006,{});
        
        s4.printStudentInfo();

    
    return 0;
}