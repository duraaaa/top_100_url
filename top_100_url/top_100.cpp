#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <string>
#include <cstring>
#include <cstdio>
#include <ctime>
#include "heap.h"

using namespace std;

vector<Heap<string, long>> heap_partition(4);

void top_100_in_each_part(int tid, int start, int end){
    char buffer[1000];
    string t;
    FILE *file;
    for(int i=start; i<end; ++i){
        cout << i << endl;
        string path = "D:/qt_prj/top_100_url/data";
        char ch[10], _ch[5] = ".txt";
        sprintf(ch, "%d",i);
        path += ch;
        path += _ch;
        file = fopen(path.c_str(), "r");
        unordered_map<string, long> hash_table;
        Heap<string, long> heap_temp;
        while(fgets(buffer, 1000, file)){
            t = buffer;
            if(hash_table.find(t)==hash_table.end()) hash_table.insert(pair<string, long>(t, 1));
            else hash_table[t]++;
        }
        for(unordered_map<string, long>::iterator itr = hash_table.begin(); itr!=hash_table.end();++itr){
            heap_temp.push((*itr).first, (*itr).second);
        }
        for(int j=0; j<100; ++j){
            if(heap_temp.isEmpty()) break;
            Node<string, long> node = heap_temp.pop();
            heap_partition[tid].push(node.key, node.value);
        }
        fclose(file);
    }
}

int main(){
    FILE *file = fopen("D:/qt_prj/top_100_url/data_test_random_str.txt","r");

    string t;
    clock_t start, finish;
    start = clock();
    Heap<string, long> heap;
    vector<FILE*> classify_file(499);

    long cnt=0;
    for(int i=0; i<499; ++i){
        string path = "D:/qt_prj/top_100_url/data";
        char ch[10], _ch[5] = ".txt";
        sprintf(ch, "%d",i);
        path += ch;
        path += _ch;
        classify_file[i] = fopen(path.c_str(), "w");
    }
    char buffer[2000];
    map<string, int> buf_map;

    while(fgets(buffer,2000,file)){
        ++cnt;
        if(cnt%5000000==0) std::cout<<clock()-start<<endl;
        unsigned long long sum = 0;
        for(int i=0; i<1000; ++i){
            if(buffer[i]=='\n') break;
            sum=sum*31+buffer[i]-'a';
        }
        fputs(buffer, classify_file[sum%499]);
    }
    

    std::cout << "finish classify: "<< clock()-start <<endl;

    for(int i=0; i<499; ++i){
        fclose(classify_file[i]);
    }
    
    vector<thread*> th(4);
    for(int i=0; i<4; ++i){
        th[i] = new thread(top_100_in_each_part,i,i*125,i*125+125);
    }
    for(int i=0; i<4; ++i){
        th[i]->join();
    }
    for(int i=0; i<4; ++i){
        delete th[i];
    }

    for(int i=0; i<4; ++i){
        for(int j=0; j<100; ++j){
            if(heap_partition[i].isEmpty()) break;
            Node<string, long> node = heap_partition[i].pop();
            heap.push(node.key, node.value);
        }
    }

    for(int i=0; i<100; ++i){
        std::cout << (heap.pop()).value << endl;
    }
    
    std::cout << clock()-start<<endl;
    
    fclose(file);
}