#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//---**********STRUCTS**********---
//STUDENT
typedef struct student{
    int id;
    char student_name[50];
    double avg_grade;
}Student;
//COURSE                
typedef struct course{
    char course_name[50];
    double avg_grade;
    int numofStudents;
    Student *enrolled_student;
}Course;
//School
typedef struct school{
    char school_name[50];
    Course* courses;
    int numofCourses;
}School;
//---Structs completed---

void create_student(Student* st){
    printf("Enter student id: ");
    scanf("%d", &st->id);
    printf("Enter student name: ");
    scanf("%49s", st->student_name);
    printf("Enter student grade: ");
    scanf("%lf", &st->avg_grade);
}
void create_course(Course* crs){
    int student_count;
    printf("Enter number of student: ");
    scanf("%d", &student_count);
    crs->numofStudents = student_count;
    crs->enrolled_student = (Student*)malloc(sizeof(Student)*student_count);
    for(int i=0; i<student_count; i++){
        create_student(&(crs->enrolled_student[i]));
    }
    printf("Enter course name: ");
    scanf("%s", &(*crs->course_name));
    printf("Enter course average grade: ");
    scanf("%lf", &crs->avg_grade);
}

void create_school(School* school){
    int num_of_courses;
    printf("Enter number of courses: ");
    scanf("%d", &num_of_courses);
    school->numofCourses = num_of_courses;
    school->courses = (Course*)malloc(sizeof(Course)*num_of_courses);
    for(int i=0; i<num_of_courses; i++){
        create_course(&school->courses[i]);
    }
    printf("Enter school name: ");
    scanf("%49s", school->school_name);
}
int is_student_incourse(int id, Course* course)
{   
    for(int i=0; i<course->numofStudents; i++){
        if(course->enrolled_student[i].id == id){
            return 1;
        }
    }
    return 0;
}

int is_student_inschool(int id, School* school)
{
    for(int i=0; i<school->courses->numofStudents; i++){
        if(school->courses->enrolled_student[i].id == id){
            return 1;
        }
    }

    return 0;
}

void print_student_courses(int id, School* school)
{
    for(int i=0; i<school->numofCourses; i++){
        for(int j=0; j<school->courses[i].numofStudents; j++){
            if(school->courses[i].enrolled_student[j].id == id){
                printf("%s\n", school->courses[i].course_name);
            }
        }
    }
}

void passed_students(Course* course)
{
    double passing_grade = course->avg_grade;
    printf("Students who passed %s\n: ", course->course_name);

    for(int i=0; i<course->numofStudents; i++)
    {
        if(course->enrolled_student[i].avg_grade > passing_grade){
            printf("%s\n", course->enrolled_student[i].student_name);
            printf("%d\n", course->enrolled_student[i].id);
            printf("Average Grade: %lf\n", course->enrolled_student[i].avg_grade);
        }
    }
}

int main(){
    Student student;
    //create_student(&student);
    //Printing student details
    //printf("%d\n",student.id);
    //printf("%s\n",student.student_name);
    //----------------------------------

    //Course initializing
    Course course;
    create_course(&course);
    //Printing course details
    printf("Number of students: %d\n", course.numofStudents);
    printf("Course name: %s\n", course.course_name);
    printf("Average grade: %lf\n", course.avg_grade);
    for(int i=0; i<course.numofStudents; i++){
        printf("Student id: %d\n", course.enrolled_student[i].id);
        printf("Student name: %s\n", course.enrolled_student[i].student_name);
    }
    //----------------------------------

    //School initializing
    School school;
    create_school(&school);


    //Check if student in course
    int id = 1;
    int result = is_student_incourse(id, &course);
    printf("Student's status about presence (1 - in the course; 0 - not): %d\n", result);

    //Check if student in school
    int school_result = is_student_inschool(id, &school);
    printf("Student's status about presence (1 - in the school; 0 - not): %d\n", school_result);

    //print all student courses
    print_student_courses(id, &school);

    //print all passed students
    passed_students(&course);


    //Memory deallocation
    free(course.enrolled_student);
    free(school.courses);
    return 0;
}