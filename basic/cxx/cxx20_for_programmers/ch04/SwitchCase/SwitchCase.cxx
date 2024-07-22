#include <iomanip>
#include <iostream>

int main() {
    int total{0};              
    int gradeCounter{0};
    int aCount{0};
    int bCount{0};
    int cCount{0};
    int dCount{0};
    int fCount{0};

    std::cout << "Enter the integer grades in the range 0-100.\n"
        << "Type the end-of-file indicator to terminate input:\n"
        << "   On UNIX/Linux/macOS type <Ctrl> d then press Enter\n"
        << "   On Windows type <Ctrl> z then press Enter\n";

    int grade;

    while (std::cin >> grade) { 
        total += grade;
        ++gradeCounter;
        
        switch (grade / 10) {                        
            case 9:     
            case 10:
                ++aCount;                              
                break;
                                                    
            case 8:
                ++bCount;
                break;
                                                    
            case 7:
                ++cCount;
                break;
                                                    
            case 6:
                ++dCount;
                break;
                                                    
            default:
                ++fCount;
                break;
        }                              
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nGrade Report:\n";

    if (gradeCounter != 0) {
        double average{static_cast<double>(total) / gradeCounter};

        std::cout << "Total of the " << gradeCounter << " grades entered is  " 
            << total << "\nClass average is " << average  
            << "\nNumber of students who recieved each grade: "
            << "\nA: " << aCount << "\nB: " << bCount << "\nC: " << cCount
            << "\nD: " << dCount << "\nF: " << fCount << "\n";
    } 
    else {
        std::cout << "No grades were entered\n";
    }

    return 0;
}