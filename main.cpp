#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;
class Student{
public:

    string studentId;//ѧ��
    string name;
    string sex;
    int age{};
    string type;//ϵ��
    string className;//�༶
    string phoneNumber;//�绰����
    vector<string> courses;

//    Student(const Student &Student) {
//        *this = Student;
//        courses.insert(courses.begin(),Student.courses.begin(),Student.courses.end());
//    }

    bool hasCourse(const string& courseId){
        cout<<"���ڲ��ҿγ�"<<courseId<<"  "<<courses.size()<<endl;

        for(auto i = courses.begin();i<courses.end();i++){
            cout<<"�γ���"+*i<<endl;
            if(courseId==*i){
                return true;
            }
        }
        return false;
    }

    Student() = default;

    static Student create(){
        Student student;
        cout<<"������ѧ��"<<endl;
        cin>>student.studentId;
        cout<<"����������"<<endl;
        cin>>student.name;
        cout<<"�������Ա�"<<endl;
        cin>>student.sex;
        cout<<"����������"<<endl;
        cin>>student.age;
        cout<<"������ϵ��"<<endl;
        cin>>student.type;
        cout<<"������༶"<<endl;
        cin>>student.className;
        cout<<"������绰����"<<endl;
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

    string id;//�γ̴���
    string name;//�γ�����
    string type;//�γ�����
    int studyTime{};//ѧʱ
    int mark{};//ѧ��
    string startTime;//����ѧ��
    int chosenStudentNumber{};//ѡ������
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

        cout<<"������γ̴���"<<endl;
        cin>>course.id;
        cout<<"������γ�����"<<endl;
        cin>>course.name;
        cout<<"������γ�����"<<endl;
        cin>>course.type;
        cout<<"������γ�ѧʱ"<<endl;
        cin>>course.studyTime;
        cout<<"������γ�ѧ��"<<endl;
        cin>>course.mark;
        cout<<"�����뿪��ѧ��"<<endl;
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
            cout<<"�ļ�����ʧ��"<<endl;
            return;
        }
        Course course;

        while(f1>>course){

            courses.push_back(course);
        }
        ifstream f2("students.txt");
        if(!f2.is_open()){
            cout<<"�ļ�����ʧ��"<<endl;
            return;
        }
        Student student;

        while(f2>>student){

            students.push_back(student);
        }

        ifstream f3("chosen.txt");
        if(!f3.is_open()){
            cout<<"�ļ�����ʧ��"<<endl;
            return;
        }
        string str;
        while(f3>>str){
            Student *targetStudent = selectStudentByStudentId(str);
            if(targetStudent== nullptr){
                cout<<"���ص��˲����ڵ�ѧ������!"<<endl;
                return;
            }

            while(f3>>str){//���ڽ���ѧ���Ϳγ̵Ĺ�ϵ
                if(str=="///"){
                    break;
                }
                Course *targetCourse = selectCourseById(str);
                if(targetCourse==nullptr){
                    cout<<"���ص��˲����ڵĿγ�����!"<<endl;
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
                cout<<"���ʧ�ܣ��γ̴����ظ�!"<<endl;
                return false;
            }
        }

        courses.push_back(course);
        cout<<"�γ������ɹ���"<<endl;
        return true;
    }
    bool addStudent(const Student& student){
        for(auto i = students.begin();i<students.end();i++){
            if(i->studentId==student.studentId){
                cout<<"����ʧ�ܣ�ѧ���ظ��ˣ�"<<endl;
                return false;
            }
        }
        students.push_back(student);
        cout<<"ѧ�������ɹ���"<<endl;
        return true;
    }
    bool deleteStudent(const Student& student){
        for(auto i = students.begin();i<students.end();i++){
            if(*i==student){
                students.erase(i);
                cout<<"ɾ���ɹ���"<<endl;
                return true;
            }
        }
        cout<<"ɾ��ʧ�ܣ�"<<endl;
        return false;
    }
    bool deleteStudent(const Student* student){
        for(auto i = students.begin();i<students.end();i++){
            if(&(*i)==student){
                students.erase(i);
                cout<<"ɾ���ɹ���"<<endl;
                return true;
            }
        }
        cout<<"ɾ��ʧ�ܣ�"<<endl;
        return false;
    }
    bool deleteCourse(const Course& course){
        for(auto i = courses.begin();i<courses.end();i++){
            if(*i==course){
                courses.erase(i);
                cout<<"ɾ���ɹ���"<<endl;
                return true;
            }
        }
        cout<<"ɾ��ʧ�ܣ�"<<endl;
        return false;
    }
    bool deleteCourse(const Course* course){
        for(auto i = courses.begin();i<courses.end();i++){
            if(&(*i)==course){
                courses.erase(i);
                cout<<"ɾ���ɹ���"<<endl;
                return true;
            }
        }
        cout<<"ɾ��ʧ�ܣ�"<<endl;
        return false;
    }
    void showStudents(vector<Student> s){
        cout<<"ѧ��       ����      �Ա�      ����      ϵ��      �༶      �绰����"<<endl;
        for(auto i = s.begin();i<s.end();i++){
            cout<<*i<<endl;
            }
        }
    void showCourses(vector<Course> s){
        cout<<"�γ̴���     �γ�����        �γ�����        ѧʱ      ѧ��      ��ѧѧ��        ѡ������"<<endl;
        for(auto i = s.begin();i<s.end();i++){
            cout<<*i<<endl;
        }
    }
    void chooseCourse(){
        string str;
        cout<<"����ѧ��id"<<endl;
        cin>>str;
        Student *student = selectStudentByStudentId(str);
        if(student== nullptr){
            cout<<"û�����ѧ��!"<<endl;
            return;
        }
        cout<<"����γ�id"<<endl;
        cin>>str;
        Course *course = selectCourseById(str);
        if(course== nullptr){
            cout<<"û������γ�!"<<endl;
            return;
        }
        student->addCourses(course->id);
        course->addStudent(student->studentId);
        cout<<"ѡ�γɹ�!"<<endl;
    }
    void modifyCourse(string id){
        Course *course = selectCourseById(id);
        if(course== nullptr){
            cout<<"δ�ҵ�Ŀ��"<<endl;
            return;
        }
        cout<<"������γ�����"<<endl;
        cin>>course->name;
        cout<<"������γ�����"<<endl;
        cin>>course->type;
        cout<<"������γ�ѧʱ"<<endl;
        cin>>course->studyTime;
        cout<<"������γ�ѧ��"<<endl;
        cin>>course->mark;
        cout<<"�����뿪��ѧ��"<<endl;
        cin>>course->startTime;
        cout<<"�޸ĳɹ�!"<<endl;
    }

    void modifyStudent(string id){
        Student *student = selectStudentByStudentId(id);
        if(student== nullptr){
            cout<<"δ�ҵ�Ŀ��"<<endl;
            return;
        }
        cout<<"����������"<<endl;
        cin>>student->name;
        cout<<"�������Ա�"<<endl;
        cin>>student->sex;
        cout<<"����������"<<endl;
        cin>>student->age;
        cout<<"������ϵ��"<<endl;
        cin>>student->type;
        cout<<"������༶"<<endl;
        cin>>student->className;
        cout<<"������绰����"<<endl;
        cin>>student->phoneNumber;
        cout<<"�޸ĳɹ�!"<<endl;
    }
};
void menu(){
    cout<<"1���ѧ�� 2��ӿγ� 3��ʾ����ѧ�� 4��ʾ���пγ� 5ѡ�� 6�鿴�γ̵�����ѧ�� 7�鿴ѧ�������пγ�\n"
          " 8ɾ��ѧ����Ϣ 9ɾ���γ���Ϣ 10�޸�ѧ����Ϣ 11�޸Ŀγ���Ϣ \n"
          "12����ѧ��(ͨ��ѧ��) 13����ѧ��(ͨ������) 14���ҿγ�(ͨ�����) 15���ҿγ�(ͨ���γ�����)"

          ;
}
string getId(){
    cout<<"������Ҫ�鿴��id"<<endl;
    string id;
    cin>>id;
    return id;
}
string getName(){
    cout<<"������Ҫ�鿴������"<<endl;
    string id;
    cin>>id;
    return id;
}
void seeStudentById(System system){
    Student *student =  system.selectStudentByStudentId(getId());
    if(student==nullptr){
        cout<<"δ�ҵ���Ϣ"<<endl;
    }else
        cout<<*student<<endl;

}
void seeStudentByName(System system){
    Student *student =  system.selectStudentByName(getName());
    if(student==nullptr){
        cout<<"δ�ҵ���Ϣ"<<endl;
    }else
        cout<<*student<<endl;

}
void seeCourseById(System system){
    Course *course =  system.selectCourseById(getId());
    if(course==nullptr){
        cout<<"δ�ҵ���Ϣ"<<endl;
    }else
        cout<<*course<<endl;

}
void seeCourseByName(System system){
    Course *course =  system.selectCourseByName(getName());
    if(course==nullptr){
        cout<<"δ�ҵ���Ϣ"<<endl;
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
