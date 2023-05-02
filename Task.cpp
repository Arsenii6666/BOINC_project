//
// Created by Dell on 02.05.2023.
//
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct result{
    int lenght;
    std::vector<int> order;
};



bool vector_contain_num(std::vector<int> array, int element);

int main(int argc, char** argv) {
    std::string InputFilename="";
    std::string OutputFilename="";
    std::vector<std::string> data;
    std::string word;
    std::fstream File;
    try
    {
        File.open(InputFilename);
    }
    catch (const std::exception&)
    {
        return 3;
    }
    int node_num;
    File>>node_num;
    std::vector<std::vector<int>> field;
    int num;
    for (int i=0; i<node_num; i++){
        std::vector<int> line;
        for (int j=0; j<node_num; j++){
            File>>num;
            line.push_back(num);
        }
        field.push_back(line);
    }
    std::vector<result> PreviousIteration;
    for (int i=0; i<node_num; i++) {
        PreviousIteration.push_back(result{0, std::vector<int>{i}});
    }
    for (int i=0; i<node_num; i++) {
        std::vector<result> CurrentIteration;
        for (int j=0; j<PreviousIteration.size(); j++){
            result PreviousResult=PreviousIteration[j];
            for (int k=0; k<node_num; k++){
                if (!vector_contain_num(PreviousResult.order, k)){
                    std::vector<int> new_order;
                    std::copy(PreviousResult.order.begin(), PreviousResult.order.end(), new_order.begin());
                    new_order.push_back(k);
                    CurrentIteration.push_back(result{
                        PreviousResult.lenght+field[PreviousResult.order.back()][k],
                        new_order
                        });
                }
            }
        }
        PreviousIteration=CurrentIteration;
    }
    result final=PreviousIteration[0];
    for (int i=0; i<PreviousIteration.size(); i++){
        if (PreviousIteration[i].lenght<final.lenght){
            final=PreviousIteration[i];
        }
    }
    std::ofstream outFile;
    outFile.open (OutputFilename);
    outFile << final.lenght<<"\n";
    for (int i=0; i<node_num;i++){
        outFile<<final.order[i];
    }
    outFile.close();
    return 0;
}

bool vector_contain_num(std::vector<int> array, int element){
    for (int i=0; i<array.size(); i++){
        if (element==array[i]){
            return true;
        }
    }
    return false;
}

