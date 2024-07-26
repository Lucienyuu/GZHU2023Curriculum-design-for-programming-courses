#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>

using namespace std;

// 最大学生数量
#define MAX_STUDENTS 100

// 学生类定义
class Student {
public:
    string id;          // 学号
    string name;        // 姓名
    string gender;      // 性别
    int age;            // 年龄
    string classId;     // 班号
    string major;       // 专业名称
    string department;  // 系别

    // 默认构造函数
    Student() {}

    // 参数化构造函数
    Student(string id, string name, string gender, int age, string classId, string major, string department)
        : id(id), name(name), gender(gender), age(age), classId(classId), major(major), department(department) {}

};

// 学生管理系统类定义
class StudentManagementSystem {
private:
    Student students[MAX_STUDENTS]; // 学生数组，存储所有学生信息
    int studentCount; // 当前学生数量
    string filename; // 文件名，用于存储学生信息

public:
    // 构造函数，初始化文件名和学生数量
    StudentManagementSystem(string filename) : filename(filename), studentCount(0) {}

    // 添加学生信息的方法
    void addStudent() {
        // 检查学生数量是否已达上限
        if (studentCount >= MAX_STUDENTS) {
            cout << "学生数量已满，无法添加更多学生。" << endl;
            return;
        }

        Student s; // 创建一个新的学生对象

        // 输入学号
        cout << "请输入学号（11位数字）：";
        cin >> s.id;
        while (s.id.length() != 11) { // 验证学号长度为11位数字
            cout << "学号必须为11位数字，请重新输入：";
            cin >> s.id;
        }

        // 输入姓名
        cout << "请输入姓名：";
        cin >> s.name;

        // 输入性别
        cout << "请输入性别（男/女）：";
        cin >> s.gender;

        // 输入年龄
        cout << "请输入年龄（15-50）：";
        cin >> s.age;
        while (s.age < 15 || s.age > 50) { // 验证年龄在15到50岁之间
            cout << "年龄必须在15到50岁之间，请重新输入：";
            cin >> s.age;
        }

        //输入班号
        cout << "请输入班号（三位数）：";
        cin >> s.classId;
        while (s.classId.length() != 3) { // 验证班号长度为3位数字
            cout << "班号必须为三位数字，请重新输入：";
            cin >> s.classId;
        }

        // 输入专业名称
        cout << "请输入专业名称：";
        cin >> s.major;

        // 输入系别
        cout << "请输入系别：";
        cin >> s.department;

        // 将新学生对象添加到学生数组中
        students[studentCount++] = s;

        cout << "学生信息已添加。" << endl;
    }

    // 修改学生信息的方法
    void modifyStudent() {
        string id;
        cout << "请输入要修改的学生学号（输入0返回主菜单）: ";
        cin >> id;

        if (id == "0") {
            return;  // 返回主菜单
        }

        bool found = false;

        // 遍历学生数组，查找匹配的学生
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                found = true;
                // 显示该学生的信息
                cout << "找到学号为 " << id << " 的学生信息：" << endl;
                displayStudent(students[i]);

                char confirm;
                cout << "您确定要修改该学生的信息吗？（Y/N）：";
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y') {
                    int choice;
                    while (true) {
                        cout << "\n请选择要修改的信息（可多次选择，输入0结束）:" << endl;
                        cout << "1. 姓名" << endl;
                        cout << "2. 性别" << endl;
                        cout << "3. 年龄" << endl;
                        cout << "4. 班号" << endl;
                        cout << "5. 专业名称" << endl;
                        cout << "6. 系别" << endl;
                        cout << "请输入选择: ";
                        cin >> choice;

                        if (choice == 0) break;

                        switch (choice) {
                        case 1:
                            // 修改姓名
                            cout << "请输入新的姓名: ";
                            cin >> students[i].name;
                            break;

                        case 2:
                            // 修改性别
                            cout << "请输入新的性别: ";
                            cin >> students[i].gender;
                            break;

                        case 3:
                            // 修改年龄，确保在15到50岁之间
                            while (true) {
                                cout << "请输入新的年龄（15~50岁）: ";
                                cin >> students[i].age;
                                if (students[i].age >= 15 && students[i].age <= 50) break;
                                cout << "年龄必须在15到50岁之间，请重新输入。" << endl;
                            }
                            break;
                        case 4:
                            // 修改班号
                            while (true) {
                                cout << "请输入新的班号（3位数字）：";
                                cin >> students[i].classId;
                                while (students[i].classId.length() != 3) { 
                                    cout << "班号必须为3位数字，请重新输入：";
                                    cin >> students[i].classId;
                                }
                                break;
                            }
                            break;
                            
                        case 5:
                            // 修改专业名称
                            cout << "请输入新的专业名称: ";
                            cin >> students[i].major;
                            break;
                        case 6:
                            // 修改系别
                            cout << "请输入新的系别: ";
                            cin >> students[i].department;
                            break;
                        default:
                            cout << "无效选择，请重试。" << endl;
                            continue; // 重新进入选择循环

                        }
                        cout << "信息修改成功。" << endl;
                    }
                    return;
                }
                else {
                    cout << "修改操作已取消。" << endl;
                }
                break; // 已经找到并处理了该学生信息，退出循环
            }
        }
        if (!found) {
            cout << "未找到该学号的学生。" << endl;
        }
    }

    // 删除学生信息
    void deleteStudent() {
        if (studentCount == 0) {
            cout << "当前没有学生信息可供删除。" << endl;
            return;
        }

        string id;
        cout << "请输入要删除的学生学号（输入0返回主菜单）：";
        cin >> id;

        if (id == "0") {
            return;  // 返回主菜单
        }

        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                found = true;
                // 显示该学生的信息
                cout << "找到学号为 " << id << " 的学生信息：" << endl;
                displayStudent(students[i]);

                char confirm;
                cout << "您确定要删除该学生的信息吗？（Y/N）：";
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y') {
                    // 删除该学生，将后面的学生信息前移
                    for (int j = i; j < studentCount - 1; ++j) {
                        students[j] = students[j + 1];
                    }
                    studentCount--;
                    cout << "学号为 " << id << " 的学生信息已删除。" << endl;
                }
                else {
                    cout << "删除操作已取消。" << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "未找到学号为 " << id << " 的学生。" << endl;
        }
    }

    void searchStudent() {
        int choice;
        while (true) {
            cout << "\n查询学生信息：" << endl;
            cout << "1. 按学号查询" << endl;
            cout << "2. 按姓名查询" << endl;
            cout << "3. 按性别查询" << endl;
            cout << "4. 按班号查询" << endl;
            cout << "0. 返回主菜单" << endl;
            cout << "请输入选择: ";
            cin >> choice;

            switch (choice) {
            case 0:
                return;  // 返回主菜单
            case 1:
                searchById();
                break;
            case 2:
                searchByName();
                break;
            case 3:
                searchByGender();
                break;
            case 4:
                searchByClassId();
                break;
            default:
                cout << "无效选择，请重新输入。" << endl;
                break;
            }
        }
    }

    // 按学号查询学生信息
    void searchById() {
        string id;
        cout << "请输入要查询的学生学号：";
        cin >> id;

        // 查找学生并输出信息
        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == id) {
                if (!found) {
                    cout << "\n查询结果：" << endl;
                    cout << setw(12) << left << "学号" << setw(12) << left << "姓名" << setw(6) << left << "性别"
                        << setw(6) << left << "年龄" << setw(6) << left << "班号" << setw(24) << left << "专业"
                        << setw(6) << left << "系别" << endl;
                }
                displayStudent(students[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "未找到学号为 " << id << " 的学生。" << endl;
        }
    }

    // 按姓名查询学生信息
    void searchByName() {
        string name;
        cout << "请输入要查询的学生姓名：";
        cin >> name;

        // 查找学生并输出信息
        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].name == name) {
                if (!found) {
                    cout << "\n查询结果：" << endl;
                    cout << setw(12) << left << "学号" << setw(12) << left << "姓名" << setw(6) << left << "性别"
                        << setw(6) << left << "年龄" << setw(6) << left << "班号" << setw(24) << left << "专业"
                        << setw(6) << left << "系别" << endl;
                }
                displayStudent(students[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "未找到姓名为 " << name << " 的学生。" << endl;
        }
    }

    // 按性别查询学生信息
    void searchByGender() {
        string gender;
        cout << "请输入要查询的学生性别（男/女）：";
        cin >> gender;

        // 查找学生并输出信息
        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].gender == gender) {
                if (!found) {
                    cout << "\n查询结果：" << endl;
                    cout << setw(12) << left << "学号" << setw(12) << left << "姓名" << setw(6) << left << "性别"
                        << setw(6) << left << "年龄" << setw(6) << left << "班号" << setw(24) << left << "专业"
                        << setw(6) << left << "系别" << endl;
                }
                displayStudent(students[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "未找到性别为 " << gender << " 的学生。" << endl;
        }
    }

    // 按班号查询学生信息
    void searchByClassId() {
        string classId;
        cout << "请输入要查询的班号：";
        cin >> classId;

        // 查找学生并输出信息
        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].classId == classId) {
                if (!found) {
                    cout << "\n查询结果：" << endl;
                    cout << setw(12) << left << "学号" << setw(12) << left << "姓名" << setw(6) << left << "性别"
                        << setw(6) << left << "年龄" << setw(6) << left << "班号" << setw(24) << left << "专业"
                        << setw(6) << left << "系别" << endl;
                }
                displayStudent(students[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "未找到班号为 " << classId << " 的学生。" << endl;
        }
    }

    // 显示单个学生的信息
    void displayStudent(const Student& student) {
        cout << setw(12) << left << student.id << setw(12) << left << student.name << setw(6) << left << student.gender
            << setw(6) << left << student.age << setw(6) << left << student.classId << setw(24) << left << student.major
            << setw(6) << left << student.department << endl;
    }


    void statisticsByGender() {
        int maleCount = 0, femaleCount = 0;

        // 统计男女生人数
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].gender == "男") {
                maleCount++;  // 如果是男生，男生人数加一
            }
            else if (students[i].gender == "女") {
                femaleCount++;  // 如果是女生，女生人数加一
            }
        }

        // 输出统计结果
        cout << "男生人数: " << maleCount << endl;
        cout << "女生人数: " << femaleCount << endl;
    }

    void statistics() {
        int choice;

        // 输出菜单选项供用户选择
        cout << "统计学生信息子菜单（输入0返回主菜单）：" << endl;
        cout << "1. 按性别统计" << endl;
        cout << "2. 按班号统计" << endl;
        cout << "3. 按年龄统计" << endl;
        cout << "4. 按系别统计" << endl;
        cout << "请输入选择：";

        // 用户输入选择
        cin >> choice;

        if (choice == 0) {
            return;  // 返回主菜单
        }

        // 根据用户选择调用相应的统计函数
        switch (choice) {
        case 1:
            statisticsByGender();  // 调用按性别统计函数
            break;
        case 2:
            statisticsByClassId();  // 调用按班号统计函数
            break;
        case 3:
            statisticsByAge();  // 调用按年龄统计函数
            break;
        case 4:
            statisticsByDepartment();  // 调用按系别统计函数
            break;
        default:
            cout << "无效选择。" << endl;  // 输入无效选项时输出提示信息
        }
    }

    void statisticsByClassId() {
        const int MAX_CLASS_ID = 999;  // 最大班号
        const int MIN_CLASS_ID = 100;  // 最小班号

        // 数组用来存储每个班级的学生人数，索引从100到999，共900个班级
        int classCounts[MAX_CLASS_ID - MIN_CLASS_ID + 1] = { 0 };

        // 统计每个班级的学生人数
        for (int i = 0; i < studentCount; ++i) {
            int classId = stoi(students[i].classId);  // 将班号转换为整数

            // 确保班号在有效范围内
            if (classId >= MIN_CLASS_ID && classId <= MAX_CLASS_ID) {
                // 使用班号减去最小班号作为数组索引，统计学生人数
                classCounts[classId - MIN_CLASS_ID]++;
            }
        }

        // 输出班级学生人数统计结果
        for (int i = 0; i <= MAX_CLASS_ID - MIN_CLASS_ID; ++i) {
            int classId = i + MIN_CLASS_ID;  // 计算班号

            if (classCounts[i] > 0) {
                cout << "班号 " << classId << " 的学生人数: " << classCounts[i] << endl;
            }
        }
    }

    void statisticsByAge() {
        int ageCounts[51] = { 0 };  // 年龄范围 0~50

        // 统计各个年龄段的学生人数
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].age >= 0 && students[i].age <= 50) {
                ageCounts[students[i].age]++;  // 对应年龄段的学生人数加一
            }
        }

        // 输出年龄段学生人数统计结果（只统计合法年龄范围 15~50）
        for (int i = 15; i <= 50; ++i) {
            if (ageCounts[i] > 0) {
                cout << i << " 岁的学生人数: " << ageCounts[i] << endl;
            }
        }
    }

    void statisticsByDepartment() {
        struct Department {
            string name;  // 系别名称
            int count;    // 系别学生人数统计
        };
        Department departments[MAX_STUDENTS];  // 存储各系别学生人数的数组
        int departmentCount = 0;  // 系别计数器，记录不同系别的数量

        // 遍历所有学生
        for (int i = 0; i < studentCount; ++i) {
            bool found = false;
            // 检查当前学生的系别是否已经在数组中统计过
            for (int j = 0; j < departmentCount; ++j) {
                if (departments[j].name == students[i].department) {  // 如果找到相同的系别
                    departments[j].count++;  // 系别人数加一
                    found = true;  // 标记为找到
                    break;  // 跳出循环，继续处理下一个学生
                }
            }
            // 如果当前学生的系别是新的，进行统计
            if (!found) {
                departments[departmentCount].name = students[i].department;  // 记录新的系别名称
                departments[departmentCount].count = 1;  // 初始化该系别的人数为1
                departmentCount++;  // 系别数量加一
            }
        }

        // 输出每个系别的学生人数统计
        for (int i = 0; i < departmentCount; ++i) {
            cout << "系别 " << departments[i].name << " 的学生人数: " << departments[i].count << endl;
        }
    }

    
    void loadFromFile() {
        ifstream file;
        while (true) {
            file.open(filename);  // 尝试打开文件
            if (!file.is_open()) {  // 如果文件无法打开
                cout << "无法打开文件，请重新输入文件路径: ";
                cin >> filename;  // 让用户重新输入文件路径
            }
            else {
                break;  // 文件成功打开，跳出循环
            }
        }

        string id, name, gender, classId, major, department;
        int age;
        studentCount = 0;  // 重置学生计数
        int previewCount = 5;  // 预览前几条学生信息
        int count = 0;  // 记录实际预览的学生数量

        // 临时存储读取到的学生信息，用于用户确认
        Student tempStudents[MAX_STUDENTS];

        // 循环读取文件中的学生信息
        while (file >> id >> name >> gender >> age >> classId >> major >> department) {
            if (studentCount >= MAX_STUDENTS) {  // 检查学生数量是否已达到最大值
                cout << "学生数量已达到最大值，无法加载更多学生信息。" << endl;
                break;
            }
            tempStudents[studentCount++] = Student(id, name, gender, age, classId, major, department);

            if (count < previewCount) {
                cout << "学生信息 " << count + 1 << ": ";
                cout << id << " " << name << " " << gender << " "
                    << age << " " << classId << " " << major << " " << department << endl;
                ++count;
            }
        }

        file.close();  // 关闭文件

        // 询问用户导入的信息是否正确
        char confirm;
        cout << "以上为文件中的前 " << count << " 条学生信息，您确定导入这些信息吗？（Y/N）：";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            // 如果用户确认信息正确，则将临时存储的学生信息转移到正式数组中
            for (int i = 0; i < studentCount; ++i) {
                students[i] = tempStudents[i];
            }
            cout << "学生信息加载完毕，共加载 " << studentCount << " 条信息。" << endl;
        }
        else {
            // 如果用户确认信息不正确，则清空临时数组和学生计数器，并重新输入文件路径
            cout << "导入操作已取消，请重新输入文件路径。" << endl;
            studentCount = 0;  // 重置学生计数
            filename = "";  // 清空文件名
            loadFromFile();  // 递归调用重新加载文件
        }
    }

    void saveToFile() {
        ofstream file;
        while (true) {
            file.open(filename);  // 尝试打开文件
            if (!file.is_open()) {  // 如果文件无法打开
                cout << "无法打开文件，请重新输入文件路径: ";
                cin >> filename;  // 让用户重新输入文件路径
            }
            else {
                break;  // 文件成功打开，跳出循环
            }
        }

        // 遍历学生数组，将每个学生的信息写入文件
        for (int i = 0; i < studentCount; ++i) {
            file << students[i].id << " " << students[i].name << " " << students[i].gender << " "
                << students[i].age << " " << students[i].classId << " " << students[i].major << " "
                << students[i].department << endl;
        }

        file.close();  // 关闭文件
        cout << "学生信息已保存到文件。" << endl;
    }

    void menu() {
        int choice;
        while (true) {
            cout << "\n学生管理系统菜单:" << endl;
            cout << "1. 添加学生" << endl;
            cout << "2. 删除学生" << endl;
            cout << "3. 修改学生" << endl;
            cout << "4. 查询学生" << endl;
            cout << "5. 统计学生" << endl;
            cout << "6. 显示所有学生信息" << endl;
            cout << "7. 退出" << endl;
            cout << "请输入选择: ";
            cin >> choice;
            switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: modifyStudent(); break;
            case 4: searchStudent(); break;
            case 5: statistics(); break;
            case 6: displayAllStudents(); break;
            case 7: saveToFile(); return;
            default: cout << "无效选择，请重试。" << endl;
            }
        }
    }

    // 显示所有学生信息
    void displayAllStudents() {
        if (studentCount == 0) {
            cout << "没有学生信息。" << endl;
            return;
        }
        cout << "所有学生信息：" << endl;
        for (int i = 0; i < studentCount; ++i) {
            displayStudent(students[i]);
        }
    }
};

int main() {
    // 获取用户输入的文件路径名
    string filename;
    cout << "请输入学生信息文件路径名：";
    cin >> filename; // 接收用户输入的文件路径名

    // 实例化学生管理系统，指定数据保存文件名
    StudentManagementSystem sms(filename);

    // 从文件加载学生信息
    sms.loadFromFile();

    // 显示菜单
    sms.menu(); // 调用管理系统菜单函数，进入系统操作

    return 0; // 返回主函数，正常结束程序运行
};

