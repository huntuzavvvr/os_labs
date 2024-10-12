#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char* argv[2]){
    (void)argc;
    (void)argv;
    std::vector<char> buf(1024);
    int a = read(STDIN_FILENO, buf.data(), buf.size());
    if (a == -1){
        perror("Empty file");
        return -1;
    }
    std::string data;
    
    data.append(buf.data(), a);
    std::string::size_type p1;
    int p2 = 0;
    std::vector<float> numbers;
    while((p1 = data.find(' ', p2)) != (std::string::npos)){
        numbers.push_back(std::stof(data.substr(p2, p1 - p2)));
        p2 = p1 + 1;
    }
    float num1 = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i){
        if (numbers[i] == 0){
            perror("Zero division");
            return -1;
        }
        num1 /= numbers[i];
    }
    std::cout << num1;
    return 0;
}