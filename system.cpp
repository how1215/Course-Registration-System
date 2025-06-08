#include <iostream>
#include <thread>
#include <vector>
#include <string>


class Course{   
    private:
        //課程名稱
        std::string name;
        //課程編號
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
            if(prerequisite != nullptr){
                std::cout<<"前修課程: "<<prerequisite->getName()<<std::endl;
            }else{
                std::cout<<"前修課程: 無"<<std::endl;
            }
            std::cout<<"--------------------------------"<<std::endl;
        }

};

class Student{  
        private:
        //學生名稱
        std::string name;
        //學生學號
        int id;
        //已修過課程
        std::vector<Course> passedCourses;
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

        //比對學生是否修過前修課程
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
        //註冊課程
        Course course_registration;
        //已註冊成功學生
        std::vector<Student> registrationList;
        //特殊允許免修過前修之學生(用學號紀錄)
        std::vector<int> special_permission_students_id;
    public:       
        CourseSection(const Course& course_registration):course_registration(course_registration),registrationList({}),special_permission_students_id({}){}


        //紀錄不需要修過前修課程的學生
        void addSpecialPermissionStudents(const int student_id){
            this->special_permission_students_id.push_back(student_id);
        }


        //學生註冊課程（
        void requestToRegist(const Student& student){
            std::cout<<"--------------------------------"<<std::endl;
            std::cout<<"學生( "<<student.getName()<<" )正在註冊課程: "<<course_registration.getName()<<std::endl;

            //用2個thread分別判斷是否符合前修課程和課程人數是否已滿
            std::thread prerequisite_thread(&CourseSection::check_prerequisite, this, student);
            std::thread capacity_thread(&CourseSection::check_course_capacity, this);

            //等待所有thread完成才完成註冊
            prerequisite_thread.join();
            capacity_thread.join();

            //2個條件都符合，則註冊成功
            registrationList.push_back(student);

            std::cout<<"學生( "<<student.getName()<<" )註冊課程: "<<course_registration.getName()<<" 成功！！！"<<std::endl;
            std::cout<<"--------------------------------"<<std::endl;            
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
                std::cout<<"課程人數已滿，註冊失敗！！！"<<std::endl;
                //如果課程人數已滿，則退出程式
                exit(1);
            }
        }
        
        //確認學生學號是否在特殊允許名單中
        bool hasSpecialPermission(const Student& student){
            if(special_permission_students_id.empty()){
                return false;
            }
            for(const auto& id : special_permission_students_id){
                if(id == student.getId()){
                    return true;
                }
            }
            return false;
        }

        //判斷欲註冊學生是否符合前修課程
        void check_prerequisite(const Student& student){
            Course* preReq = course_registration.getPrerequisite();
            
            // 檢查是否有前修課程
            if(preReq == nullptr){
                // 若此課程沒有前修課程，直接允許註冊
                std::cout<<"此課程無前修課程要求！！！"<<std::endl;
            }
            else if(student.hasPassedCourse(*preReq)){
                //若修過前修課程，則允許註冊
                std::cout<<"已通過所有前修課程！！！"<<std::endl;
            }else{
                //若沒修過前修課程，查看學生是否有特殊允許不需前修課程
                if(hasSpecialPermission(student)){
                    std::cout<<"教授已給予特殊允許！！！"<<std::endl;
                }else{
                    //若也沒有特殊允許，則註冊失敗並退出程式
                    std::cout<<student.getName()<<"\n未修過以下先修課程，註冊失敗:"<<preReq->getName()<<std::endl;
                    exit(1);
                }
            }
        }

};

int main(){

        //Course(課堂名稱,課程編號,課程人數上限,前修課程)
        //基礎課程(無任何前修課程)  
        Course c1("C++", 101, 2, nullptr);
        Course c2("Data Structure", 102, 2, nullptr);
        Course c3("Algorithm", 103, 3, nullptr);
        //進階課程(有前修課程)
        Course c4("OOP", 201, 3, &c1);
        Course c5("Advanced Data Structure", 202, 2, &c2);
        Course c6("Algorithm 2", 203, 3, &c3);

        //Student(學生名稱,學生編號,已修過課程)
        //新生(無修過任何課程)
        Student s1("Lebron", 1,{});
        //大二(已修過某些基礎課程) 
        Student s2("John", 4,{c1,c2,c3});
        Student s3("Minji", 5,{c1});
        //壞學生(之前全被當，沒有修過任何課程)
        Student s4("Nick", 6,{});
        //將課程放上課程網站開放註冊
        CourseSection c1_section(c1);
        CourseSection c2_section(c2);
        CourseSection c3_section(c3);
        CourseSection c4_section(c4);
        CourseSection c5_section(c5);
        CourseSection c6_section(c6);        
                
        // c1.printCourseInfo();
        // c1_section.requestToRegist(s1);
        // c1_section.requestToRegist(s2);
        // c1_section.requestToRegist(s3);

        // c5.printCourseInfo();
        // c5_section.addSpecialPermissionStudents(6);
        // c5_section.requestToRegist(s2);
        // c5_section.requestToRegist(s4);
        // c5_section.printRegistrationList();

    return 0;
}


        
