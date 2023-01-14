import urllib.request


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None]*self.size 


    def hash_string(self, string, i=0):
        bin_list = []
        for char in string:
            bin_list += f'{ord(char):08b}'
        binary = ''.join(bin_list)
        def h1(k):
            return (k % self.size) 
        def h2(k, i):
            return (i + (k % (self.size-2)))
        def h(k, i):
            return (h1(h2(k, i))) 
        return h(int(binary, 2), i)


    def dehash_string(self, hash):

        def fill_zeros(num):
            while not len(num) % 8 == 0:
               num = '0' + num
            return num

        def split_bin(num):
            octets_list = []
            for i in range(int(len(num)/8)):
                octet = num[i*8:(i+1)*8]
                octets_list += [octet]
            return octets_list

        final_string = ''
        hash_to_bin = fill_zeros(bin(hash)[2:])
        binary = split_bin(hash_to_bin)
        for octet in binary:
            final_string += chr(int(octet, 2))
        return final_string


    def insert(self, value, key):
        print(key)
        i = 0
        index = self.hash_string(key, i)
        while self.table[index] is not None:
            #print(i, index)
            i += 1
            index = self.hash_string(key, i)
        self.table[index] = value


    def search(self, key):
        for i in range(self.size):
            index = self.hash_string(key, i)
            if self.table[index] is not None and self.table[index][0] == key:
                return self.table[index][1]
        return None


    def delete(self, key):
        for i in range(self.size):
            index = self.hash_string(key,i)
            if self.table[index] is not None and self.table[index][0] == key:
                self.table[index] = 'DEL'
                return


if __name__ == "__main__":
    file_url = 'https://inf.ug.edu.pl/~mmiotk/nazwiska.txt'
    data = [line.decode('utf-8').strip() for line in urllib.request.urlopen(file_url)]
    hashes = []
    i = 1
    hash_table = HashTable(len(data))
    for line in data:
        print(f'num:{i}')
        i+=1
        v, k = line.split(' ')
        hash_table.insert(v, k)
