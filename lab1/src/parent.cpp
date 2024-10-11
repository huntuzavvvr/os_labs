#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <sys/wait.h>
#include <filesystem>

std::string ParentRoutine(std::string filename){
    
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) || pipe(pipe2) == -1){
        perror("Error");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid == 0){
        if(dup2(pipe1[0], STDIN_FILENO) == -1){
            perror("Input error");
            exit(-1);
        }
        
        if (dup2(pipe1[1], STDOUT_FILENO) == -1){
            perror("Out error");
            exit(-1);
        }
        std::cout << 14141 << std::flush;
        if (execl("./lab1/child", "./lab1/child", nullptr) == -1){
            perror("Error");
            exit(-1);
        }
        close(pipe1[0]);

    }
    else{
        std::string temp;
        // std::string filename;
        // std::getline(std::cin, filename);
        if (!std::filesystem::exists(filename)){
            perror("File not found");
            exit(-1);
        }
        std::ifstream file(filename);
        std::getline(file, temp);

        if (temp.size() == 0){
            perror("Empty file");
            exit(-1);
        }
        if (!isdigit(temp[0])){
            perror("Incorrent input file");
            exit(-1);
        } 
        write(pipe1[1], temp.data(), temp.size());
        close(pipe1[1]);
        wait(nullptr);
        char result[128];
        int result_num = read(pipe1[0], result, sizeof(result));

        if (result_num < 0){
            perror("Empty");
        }
        
        if (result_num > 0){
            result[result_num] = '\0';
            std::cout << result << '\n';
            std::string str(result, result_num);
            return str;
        }

    }
    return "";
}