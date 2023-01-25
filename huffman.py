import heapq
from collections import Counter

def huffman_code(text):
    freq_table = Counter(text)

    priority_queue = [[weight, [char, ""]] for char, weight in freq_table.items()]
    heapq.heapify(priority_queue)

    while len(priority_queue) > 1:
        lo = heapq.heappop(priority_queue)
        hi = heapq.heappop(priority_queue)
        for pair in lo[1:]:
            pair[1] = '0' + pair[1]
        for pair in hi[1:]:
            pair[1] = '1' + pair[1]
        heapq.heappush(priority_queue, [lo[0] + hi[0]] + lo[1:] + hi[1:])

    huffman_codes = {} 
    for char, code in priority_queue[0][1:]:
        huffman_codes[char] = code
    for char, code in huffman_codes.items():
        print(f"{char}: {code}")
        
    encoded_text = "".join([huffman_codes[c] for c in text])
    print(encoded_text)

if __name__ == "__main__":
    text = input()
    huffman_code(text)

