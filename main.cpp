#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;
class Student{
public:
    bool isValuable{};
    string studentId;//学号
    string name;
    string sex;
    int age{};
    string type;//系别
    string className;//班级
    string phoneNumber;//电话号码
    vector<string> courses;

//    Student(const Student &Student) {
//        *this = Student;
//        courses.insert(courses.begin(),Student.courses.begin(),Student.courses.end());
//    }

    bool hasCourse(const string& courseId){
        cout<<"正在查找课程"<<courseId<<"  "<<courses.size()<<endl;

        for(auto i = courses.begin();i<courses.end();i++){
            cout<<"课程有"+*i<<endl;
            if(courseId==*i){
                return true;
            }
        }
        return false;
    }

    Student() = default;

    static Student create(){
        Student student;
        student.isValuable= true;
        cout<<"请输入学号"<<endl;
        cin>>student.studentId;
        cout<<"请输入姓名"<<endl;
        cin>>student.name;
        cout<<"请输入性别"<<endl;
        cin>>student.sex;
        cout<<"请输入年龄"<<endl;
        cin>>student.age;
        cout<<"请输入系别"<<endl;
        cin>>student.type;
        cout<<"请输入班级"<<endl;
        cin>>student.className;
        cout<<"请输入电话号码"<<endl;
        cin>>student.phoneNumber;

        return student;
    }

    void addCourses(const string& id){
        courses.push_back(id);
    }
    bool deleteCourses(const string& id){
        for(auto i = courses.begin();i<courses.end();i++){
            if(id==*i){}
            courses.erase(i);
            return true;
        }
        return false;
    }
    bool operator==(const Student &rhs) const {
        return studentId == rhs.studentId &&
               name == rhs.name &&
               sex == rhs.sex &&
               age == rhs.age &&
               type == rhs.type &&
               className == rhs.className &&
               phoneNumber == rhs.phoneNumber;
    }
    friend ifstream &operator>>(ifstream &is,  Student &student) {
        is>>student.studentId >> student.name >>  student.sex
                >> student.age  >> student.type  >> student.className
                >> student.phoneNumber;
        return is;
    }
    friend ostream &operator<<(ostream &os, const Student &student) {
        os << student.studentId << " " << student.name << " " << student.sex << " "
           << student.age << " " << student.type << " " << student.className << " "
           << student.phoneNumber;
        return os;
    }

    friend ofstream &operator<<(ofstream &os, const Student &student) {
        os << student.studentId << " " << student.name << " " << student.sex << " "
           << student.age << " " << student.type << " " << student.className << " "
           << student.phoneNumber;
        return os;
    }
};
class Course{
public:
    Course() = default;

    bool isValuable{};
    string id;//课程代码
    string name;//课程名称
    string type;//课程性质
    int studyTime{};//学时
    int mark{};//学分
    string startTime;//开课学期
    int chosenStudentNumber{};//选课人数
    vector<string> chosenStudents;

//    Course(const Course &Course) {
//        *this = Course;
//        chosenStudents.insert(chosenStudents.begin(),Course.chosenStudents.begin(),Course.chosenStudents.end());
//    }

    bool hasChosenStudents(const string& studentId){
        for(auto i = chosenStudents.begin();i<chosenStudents.end();i++){
            if(studentId==*i){
                return true;
            }
        }
        return false;
    }

    static Course create(){
        Course course;
        course.isValuable= true;
        cout<<"请输入课程代码"<<endl;
        cin>>course.id;
        cout<<"请输入课程名称"<<endl;
        cin>>course.name;
        cout<<"请输入课程性质"<<endl;
        cin>>course.type;
        cout<<"请输入课程学时"<<endl;
        cin>>course.studyTime;
        cout<<"请输入课程学分"<<endl;
        cin>>course.mark;
        cout<<"请输入开课学期"<<endl;
        cin>>course.startTime;
        return course;


    }
    void addStudent(const string& target){
        chosenStudents.push_back(target);
        chosenStudentNumber++;
    }

    bool deleteStudent(const string& target){
        for(auto i = chosenStudents.begin();i<chosenStudents.end();i++){
            if(target==*i){
                chosenStudents.erase(i);
                chosenStudentNumber--;
                return true;
            }
        }
        return false;
    }
    friend ifstream &operator>>(ifstream &is, Course &course) {
        is  >> course.id >> course.name >>  course.type >>
            course.studyTime >> course.mark >> course.startTime
                >> course.chosenStudentNumber;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Course &course) {
        os  << course.id << "  " << course.name << "  " << course.type << " "
           << course.studyTime << " " << course.mark << " " << course.startTime
           << " " << course.chosenStudentNumber;
        return os;
    }
    friend ofstream &operator<<(ofstream &os, const Course &course) {
        os  << course.id << "  " << course.name << "  " << course.type << " "
            << course.studyTime << " " << course.mark << " " << course.startTime
            << " " << course.chosenStudentNumber;
        return os;
    }
    bool operator==(const Course &rhs) const {
        return id == rhs.id &&
               name == rhs.name &&
               type == rhs.type &&
               studyTime == rhs.studyTime &&
               mark == rhs.mark &&
               startTime == rhs.startTime &&
               chosenStudentNumber == rhs.chosenStudentNumber;
    }

    bool operator!=(const Course &rhs) const {
        return !(rhs == *this);
    }
};
class System{
public:
    System() {
        load();
    }
    ~System() {
        save();
    }
    vector<Course> courses;
    vector<Student> students;

    void save(){
        ofstream of("courses.txt");
        for(auto i = courses.begin();i<courses.end();i++){
            of<<*i<<endl;
        }
        ofstream of2("students.txt");
        for(auto i = students.begin();i<students.end();i++){
            of2<<*i<<endl;
        }
        ofstream of3("chosen.txt");
        for(auto i = students.begin();i<students.end();i++){
            of3<<i->studentId<<endl;
            for (auto j = i->courses.begin();j<i->courses.end();j++) {
                of3<<*j<<endl;
            }
            of3<<"///"<<endl;
        }
        of.flush();
        of2.flush();
        of3.flush();
        of.close();
        of2.close();
        of3.close();
    }
    void load(){
        ifstream f1("courses.txt");
        if(!f1.is_open()){
            cout<<"文件加载失败"<<endl;
            return;
        }
        Course course;

        while(f1>>course){
            course.isValuable= true;
            courses.push_back(course);
        }
        ifstream f2("students.txt");
        if(!f2.is_open()){
            cout<<"文件加载失败"<<endl;
            return;
        }
        Student student;

        while(f2>>student){
            student.isValuable= true;
            students.push_back(student);
        }

        ifstream f3("chosen.txt");
        if(!f3.is_open()){
            cout<<"文件加载失败"<<endl;
            return;
        }
        string str;
        while(f3>>str){
            Student *targetStudent = selectStudentByStudentId(str);
            if(targetStudent== nullptr){
                cout<<"加载到了不存在的学生数据!"<<endl;
                return;
            }

            while(f3>>str){//用于建立学生和课程的关系
                if(str=="///"){
                    break;
                }
                Course *targetCourse = selectCourseById(str);
                if(targetCourse==nullptr){
                    cout<<"加载到了不存在的课程数据!"<<endl;
                    return;
                }
                targetStudent->addCourses(targetCourse->id);
                targetCourse->addStudent(targetStudent->studentId);
            }
        }
        f1.close();
        f2.close();
        f3.close();
    }

    vector<Course> selectCourseByStudentId(const string& studentId){
        vector<Course>ret ;
        for(auto i = courses.begin();i<courses.end();i++){
            if(i->hasChosenStudents(studentId)){
                ret.push_back(*i);
            }
        }
        return ret;
    }

    vector<Student> selectStudentsByCourseId(const string& courseId){
        vector<Student>ret ;
        for(auto i = students.begin();i<students.end();i++){
            if(i->hasCourse(courseId)){
                ret.push_back(*i);
            }
        }
        return ret;
    }
    Course* selectCourseById(const string& id){

        for(auto i = courses.begin();i<courses.end();i++){
            if(i->id==id){
                return &(*i);
            }
        }
        return nullptr;
    }

    Course* selectCourseByName(const string& name){
        Course ret;
        for(auto i = courses.begin();i<courses.end();i++){
            if(i->name==name){
                return &(*i);
            }
        }
        return nullptr;
    }
    Student* selectStudentByStudentId(const string& studentId){
        Student ret;
        for(auto i = students.begin();i<students.end();i++){
            if(i->studentId==studentId){
                return &(*i);
            }
        }
        return nullptr;
    }

    Student* selectStudentByName(const string& name){
        Student ret;
        for(auto i = students.begin();i<students.end();i++){
            if(i->name==name){
                return &(*i);
            }
        }
        return nullptr;
    }

    bool addCourse(const Course& course){
        for(auto i = courses.begin();i<courses.end();i++){
            if(i->id==course.id){
                cout<<"添加失败，课程代码重复!"<<endl;
                return false;
            }
        }

        courses.push_back(course);
        cout<<"课程新增成功！"<<endl;
        return true;
    }
    bool addStudent(const Student& student){
        for(auto i = students.begin();i<students.end();i++){
            if(i->studentId==student.studentId){
                cout<<"增加失败！学号重复了！"<<endl;
                return false;
            }
        }
        students.push_back(student);
        cout<<"学生新增成功！"<<endl;
        return true;
    }
    bool deleteStudent(const Student& student){
        for(auto i = students.begin();i<students.end();i++){
            if(*i==student){
                students.erase(i);
                cout<<"删除成功！"<<endl;
                return true;
            }
        }
        cout<<"删除失败！"<<endl;
        return false;
    }
    bool deleteStudent(const Student* student){
        for(auto i = students.begin();i<students.end();i++){
            if(&(*i)==student){
                students.erase(i);
                cout<<"删除成功！"<<endl;
                return true;
            }
        }
        cout<<"删除失败！"<<endl;
        return false;
    }
    bool deleteCourse(const Course& course){
        for(auto i = courses.begin();i<courses.end();i++){
            if(*i==course){
                courses.erase(i);
                cout<<"删除成功！"<<endl;
                return true;
            }
        }
        cout<<"删除失败！"<<endl;
        return false;
    }
    bool deleteCourse(const Course* course){
        for(auto i = courses.begin();i<courses.end();i++){
            if(&(*i)==course){
                courses.erase(i);
                cout<<"删除成功！"<<endl;
                return true;
            }
        }
        cout<<"删除失败！"<<endl;
        return false;
    }
    void showStudents(vector<Student> s){
        cout<<"学生信息：："<<endl;
        for(auto i = s.begin();i<s.end();i++){
            cout<<*i<<endl;
            }
        }
    void showCourses(vector<Course> s){
        cout<<"课程信息：："<<endl;
        for(auto i = s.begin();i<s.end();i++){
            cout<<*i<<endl;
        }
    }
    void chooseCourse(){
        string str;
        cout<<"输入学生id"<<endl;
        cin>>str;
        Student *student = selectStudentByStudentId(str);
        if(student== nullptr){
            cout<<"没有这个学生!"<<endl;
            return;
        }
        cout<<"输入课程id"<<endl;
        cin>>str;
        Course *course = selectCourseById(str);
        if(course== nullptr){
            cout<<"没有这个课程!"<<endl;
            return;
        }
        student->addCourses(course->id);
        course->addStudent(student->studentId);
        cout<<"选课成功!"<<endl;
    }
    void modifyCourse(string id){
        Course *course = selectCourseById(id);
        if(course== nullptr){
            cout<<"未找到目标"<<endl;
            return;
        }
        cout<<"请输入课程名称"<<endl;
        cin>>course->name;
        cout<<"请输入课程性质"<<endl;
        cin>>course->type;
        cout<<"请输入课程学时"<<endl;
        cin>>course->studyTime;
        cout<<"请输入课程学分"<<endl;
        cin>>course->mark;
        cout<<"请输入开课学期"<<endl;
        cin>>course->startTime;
        cout<<"修改成功!"<<endl;
    }

    void modifyStudent(string id){
        Student *student = selectStudentByStudentId(id);
        if(student== nullptr){
            cout<<"未找到目标"<<endl;
            return;
        }
        cout<<"请输入姓名"<<endl;
        cin>>student->name;
        cout<<"请输入性别"<<endl;
        cin>>student->sex;
        cout<<"请输入年龄"<<endl;
        cin>>student->age;
        cout<<"请输入系别"<<endl;
        cin>>student->type;
        cout<<"请输入班级"<<endl;
        cin>>student->className;
        cout<<"请输入电话号码"<<endl;
        cin>>student->phoneNumber;
        cout<<"修改成功!"<<endl;
    }
};
void menu(){
    cout<<"1添加学生 2添加课程 3显示所有学生 4显示所有课程 5选课 6查看课程的所有学生 7查看学生的所有课程\n"
          " 8删除学生信息 9删除课程信息 10修改学生信息 11修改课程信息 \n"
          "12查找学生(通过学号) 13查找学生(通过姓名) 14查找课程(通过编号) 15查找课程(通过课程名称)"

          ;
}
string getId(){
    cout<<"请输入要查看的id"<<endl;
    string id;
    cin>>id;
    return id;
}
string getName(){
    cout<<"请输入要查看的名称"<<endl;
    string id;
    cin>>id;
    return id;
}
void seeStudentById(System system){
    Student *student =  system.selectStudentByStudentId(getId());
    if(student==nullptr){
        cout<<"未找到信息"<<endl;
    }else
        cout<<*student<<endl;

}
void seeStudentByName(System system){
    Student *student =  system.selectStudentByName(getName());
    if(student==nullptr){
        cout<<"未找到信息"<<endl;
    }else
        cout<<*student<<endl;

}
void seeCourseById(System system){
    Course *course =  system.selectCourseById(getId());
    if(course==nullptr){
        cout<<"未找到信息"<<endl;
    }else
        cout<<*course<<endl;

}
void seeCourseByName(System system){
    Course *course =  system.selectCourseByName(getName());
    if(course==nullptr){
        cout<<"未找到信息"<<endl;
    }else
        cout<<*course<<endl;

}
int main() {
    System system;
    while(true){
        menu();
        int option;
        cin>>option;
        switch (option) {
            case 1:system.addStudent(Student::create());break;
            case 2:system.addCourse(Course::create());break;
            case 3:system.showStudents(system.students);break;
            case 4:system.showCourses(system.courses);break;
            case 5:system.chooseCourse();break;
            case 6:system.showStudents(system.selectStudentsByCourseId(getId()));break;
            case 7:system.showCourses(system.selectCourseByStudentId(getId()));break;
            case 8:system.deleteStudent(system.selectStudentByStudentId(getId()));break;
            case 9:system.deleteCourse(system.selectCourseById(getId()));break;
            case 10:system.modifyStudent(getId());break;
            case 11:system.modifyCourse(getId());break;
            case 12:seeStudentById(system);break;
            case 13:seeStudentByName(system);break;
            case 14:seeCourseById(system);break;
            case 15:seeCourseByName(system);break;
            case 0:return 0;
        }
    }


    return 0;
}
