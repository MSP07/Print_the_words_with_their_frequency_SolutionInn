from collections import Counter
import heapq

# Get word frequencies from file
def get_word_frequencies(file_path):
    with open(file_path,'r') as file:
        text = file.read()
    words = text.split()  
    frequencies = Counter(words)  
    return frequencies

# Selection Sort
def selection_sort(words_with_freq):
    n = len(words_with_freq)
    for i in range(n-1):
        max_idx = i
        for j in range(i+1,n):
            if words_with_freq[j][1] > words_with_freq[max_idx][1]: 
                max_idx = j
        words_with_freq[i], words_with_freq[max_idx] = words_with_freq[max_idx], words_with_freq[i]
    return words_with_freq

def using_selection_sort(frequencies,k):
    words_with_freq = list(frequencies.items())  
    sorted_words = selection_sort(words_with_freq) 
    return sorted_words[k - 1]  

#Quick Select
def partition(arr,low,high):
    pivot = arr[high][1]  
    i = low-1
    for j in range(low,high):
        if arr[j][1]>=pivot:  
            i += 1
            arr[i],arr[j] = arr[j],arr[i]
    arr[i+1],arr[high] = arr[high],arr[i+1]
    return i + 1

def quick_select(arr,low,high,k):
    if low <= high:
        pivot_index = partition(arr,low,high)
        if pivot_index == k:
            return arr[pivot_index]
        elif pivot_index>k:
            return quick_select(arr,low,pivot_index-1,k)
        else:
            return quick_select(arr,pivot_index+1,high,k)
    return None

def using_quick_select(frequencies,k):
    words_with_freq = list(frequencies.items())  
    return quick_select(words_with_freq,0,len(words_with_freq)-1,k-1)  
#Using heap
def using_heap(frequencies,k):
    pq = []
    for word,freq in frequencies.items():
        heapq.heappush(pq,(freq,word)) 
        if len(pq)>k:
            heapq.heappop(pq)  
    top = heapq.heappop(pq)
    return (top[1],top[0]) 

# Main Function
if __name__ == "__main__":
    file_path = "input.txt"  
    k = 3  
    frequencies = get_word_frequencies(file_path)
    kth_word_a = using_selection_sort(frequencies,k)
    print(f"Using Selection Sort: {kth_word_a}")
    kth_word_b = using_quick_select(frequencies,k)
    print(f"Using Quick Select: {kth_word_b}")
    kth_word_c = using_heap(frequencies,k)
    print(f"Using Hash Table and Heap: {kth_word_c}")
