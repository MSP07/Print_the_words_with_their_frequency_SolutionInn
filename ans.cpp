#include<bits/stdc++.h>
using namespace std;

map<string,int>getWordFrequencies(const string &filePath){
    ifstream file(filePath);
    map<string,int>frequencies;
    string word;
    if (file.is_open()) {
        while (file >> word) {
            frequencies[word]++;
        }
        file.close();
    } else {
        cerr << "Error 404!!! Can't open file" << endl;
    }
    return frequencies;
}

vector<pair<string,int>>selectionSort(const map<string,int> &frequencies){
    vector<pair<string,int>>wordFreq(frequencies.begin(),frequencies.end());
    int n = wordFreq.size();
    for(int i=0;i<n-1;i++){
        int maxIdx = i;
        for(int j = i+1;j<n;j++){
            if (wordFreq[j].second>wordFreq[maxIdx].second){
                maxIdx = j;
            }
        }
        swap(wordFreq[i],wordFreq[maxIdx]);
    }
    return wordFreq;
}
//SELECTION SORT
pair<string,int>usingSelectionSort(const map<string,int> &frequencies,int k){
    vector<pair<string,int>>sortedWords = selectionSort(frequencies);
    return sortedWords[k - 1]; 
}

int partition(vector<pair<string,int>> &arr,int low,int high){
    int pivot = arr[high].second; 
    int i = low - 1;
    for(int j=low;j<high;j++){
        if(arr[j].second >= pivot){ 
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}
//QUICK SELECT
pair<string,int>quickSelect(vector<pair<string,int>> &arr,int low,int high,int k) {
    if(low<=high){
        int pivotIndex = partition(arr,low,high);
        if(pivotIndex == k){
            return arr[pivotIndex];
        }else if(pivotIndex>k){
            return quickSelect(arr,low,pivotIndex-1,k);
        }else{
            return quickSelect(arr,pivotIndex+1,high,k);
        }
    }
    return {"", -1};
}

pair<string,int>usingQuickSelectQuickSelect(const map<string,int> &frequencies,int k){
    vector<pair<string,int>>wordFreq(frequencies.begin(),frequencies.end());
    return quickSelect(wordFreq,0,wordFreq.size()-1,k-1); 
}

//HASH TABLE AND MIN Heap
pair<string,int>usingHeap(const map<string,int> &frequencies,int k){
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>>pq;
    for(const auto &entry : frequencies){
        pq.push({entry.second,entry.first});
        if(pq.size()>k){
            pq.pop();
        }
    }
    return {pq.top().second,pq.top().first}; 
}

int main(){
  string filePath = "input.txt";//intended file with input texts
  int k = 3; 
  map<string,int>frequencies = getWordFrequencies(filePath);//first we calculate the frequencies
  pair<string,int>kthWordA = usingSelectionSort(frequencies,k);
  cout << "First Answer with Selection Sort: " << kthWordA.first << " -> " << kthWordA.second << endl;
  pair<string,int>kthWordB = usingQuickSelect(frequencies, k);
  cout << "Second Answer with Quick Select: " << kthWordB.first << " -> " << kthWordB.second << endl;
  pair<string,int>kthWordC = usingHeap(frequencies, k);
  cout << "Third Answer Using Heap: " << kthWordC.first  << " -> " << kthWordC.second << endl;
  return 0;
}
