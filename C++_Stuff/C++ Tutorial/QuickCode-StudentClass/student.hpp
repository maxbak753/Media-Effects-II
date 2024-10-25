// header guard
#ifndef STUDENT_HPP // file must have same name as class!
#define STUDENT_HPP

// Student Class
class Student { // file must have same name as class!
    public:
        static int number_of_students; // define in students.hpp
        static void print_number_of_students(); // define in students.hpp
        Student(); // constructor
        Student(std::string new_name, int new_id); // constructor (overloaded)

        void identify();

        void calculate_GPA(char array[]);

        // Setters & Getters

        void setName(std::string new_name);
        std::string getName();

        void setID(int new_id);
        int getID();

        void setGPA();
        double getGPA();

        void set_class_schedule();
        void print_class_schedule();

        void setPopularity(int new_popularity);
        int getPopularity();

        void setDorm(std::string new_dorm);
        std::string getDorm();

        // ------------------------------------
        void set_class_grades();
        void print_class_grades();

        void set_assignment_grades();
        void print_class_assignment_grades();

        // File IO ----------------------------
        void save_data(); // save basic data to file (automatically called in the destructor)
        void load_data(); // take info from the file & store it in respective class members
        ~Student(); // destructor

    private:
        std::string name;
        int id;
        double gpa;
        std::string class_schedule[6];
        int popularity;
        std::string dorm;
        std::map<const std::string, double> class_grades;
        std::vector<double> assignment_grades;
};

#endif