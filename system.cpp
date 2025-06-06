#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>


class Course{   
    private:
        std::string name;
        int id;
        //課程人數上限
        int max_capacity;
        //前修課程
        Course* prerequisite;
    public:
        Course(const std::string& name, int id, int max_capacity, Course* prerequisite):name(name),id(id),max_capacity(max_capacity),prerequisite(prerequisite){}

        std::string getName() const { return name; }
        void setName(const std::string& name) { this->name=name; }

        int getId() const { return id; }
        void setId(int id) { this->id=id; }

        int getMaxCapacity() const { return max_capacity; }
        void setMaxCapacity(int max_capacity) { this->max_capacity=max_capacity; }

        Course* getPrerequisite() const { return prerequisite; }
        void setPrerequisite(Course* prerequisite) { this->prerequisite=prerequisite; }
        //印出課程資訊
        void printCourseInfo(){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"課程名稱: "<<name<<std::endl;
            std::cout<<"課程編號: "<<id<<std::endl;
            std::cout<<"課程人數上限: "<<max_capacity<<std::endl;
            std::cout<<"前修課程: "<<prerequisite->getName()<<std::endl;
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
        Student(const std::string& name, int id, const std::vector<Course>& passedCourses):name(name),id(id),passedCourses(passedCourses){}
        
        std::string getName() const { return name; }
        void setName(const std::string& name) { this->name=name; }

        int getId() const { return id; }
        void setId(int id) { this->id=id; }

        std::vector<Course> getPassedCourses() const { return passedCourses; }
        void setPassedCourses(const std::vector<Course>& passedCourses)  { this->passedCourses=passedCourses; }

        //印出學生資訊
        void printStudentInfo(){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"學生名稱: "<<name<<std::endl;
            std::cout<<"學生編號: "<<id<<std::endl;
            std::cout<<"已修過課程: "<<passedCourses.size()<<std::endl;
            std::cout<<"--------------------------------"<<std::endl;
        }

        //比對學生是否修過某前修課程
        bool hasPassedCourse(const Course& pre_req) const {
            for(const auto& passed : passedCourses){
                if(passed.getId() == pre_req.getId()){
                    return true;
                }
            }
            return false;
        }

};

class CourseSection{
    private:

        bool open;
        bool closedOrCancelled;
        //註冊課程
        Course course_registration;
        //已註冊學生(預設為空)
        std::vector<Student> registrationList;
    public:       
        CourseSection(const Course& course_registration):open(false),closedOrCancelled(false),course_registration(course_registration),registrationList({}){}
        
        //學生註冊課程（修改為將判斷是分開）
        void requestToRegist(const Student& student){
            //確認有無符合前修課程
            Course* preReq = course_registration.getPrerequisite();
            
            if(student.hasPassedCourse(*preReq)){
                std::cout<<"已通過所有前修課程，成功註冊此課程！！！"<<std::endl;
                registrationList.push_back(student);
            }else{
                std::cout<<student.getName()<<"\n請回去重修以下先修課程!!!"<<preReq->getName()<<std::endl;
            }
            
        }
        //輸出該堂註冊課的註冊學生
        void printRegistrationList(){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"註冊學生數量: "<<registrationList.size()<<std::endl;
            for(const auto& student : registrationList){
                std::cout<<"學生: "<<student.getName()<<std::endl;
            }
            std::cout<<"--------------------------------"<<std::endl;
        }
        //確認課程人數是否已滿
        void check_course_capacity(){
            if(registrationList.size() >= course_registration.getMaxCapacity()){
                std::cout<<"課程人數已滿，無法註冊！！！"<<std::endl;
            }
        }

};

//確認有無符合前修課程
void check_prerequisite(){}



int main(){

        //基礎課程(無前修課程)  
        Course c1("C++", 101, 3, nullptr);
        Course c2("Data Structure", 102, 2, nullptr);
        Course c3("Algorithm", 103, 3, nullptr);
        //進階課程(有前修課程)
        Course c4("OOP", 201, 3, &c1);
        Course c5("Advanced Data Structure", 202, 3, &c2);
        Course c6("Algorithm 2", 203, 3, &c3);

        //新生(無修過任何課程)
        Student s1("Lebron", 001,{});
        Student s2("Hanni", 002,{});
        Student s3("Jake", 003,{});
        //大二(已修過某些基礎課程) 
        Student s4("John", 004,{c1,c2,c3});
        Student s5("Minji", 005,{c1,c2});
        //壞學生(之前全被當)
        Student s6("Nick", 006,{});
        //將課程放上課程網站開放註冊
        CourseSection c1_section(c1);

        c1.printCourseInfo();
        c1_section.requestToRegist(s4);
        c1_section.requestToRegist(s5);
        c1_section.requestToRegist(s6);
        c1_section.printRegistrationList();
    
    return 0;
}