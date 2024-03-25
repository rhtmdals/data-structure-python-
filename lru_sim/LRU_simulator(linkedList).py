from linkedlist import *


class CacheSimulator:
    def __init__(self, cache_slots):
        self.cache_slots = cache_slots
        self.cache_hit = 0
        self.tot_cnt = 0
        self.cashe_list = LinkedListBasic()
    
    def do_sim(self, page):
        if self.cashe_list.count(page) > 0:  #동일한 값이 cashe_list내부에 존재하는 경우: HIT
            self.cashe_list.remove(page) #값 제거
            self.cashe_list.append(page) #head 부분에 값 추가
            self.cache_hit += 1
            self.tot_cnt += 1
        
        else: #miss
            if  self.cashe_list.size() < self.cache_slots: #캐쉬 슬롯보다 원소 수가 적은 경우
                self.cashe_list.append(page) #head부분에 값 추가
            else: #캐쉬 슬롯과 원소 수가 같은 경우
                self.cashe_list.removeTail() #tail부분 값 제거
                self.cashe_list.append(page) #head부분에 값 추가
            self.tot_cnt += 1
        
    def print_stats(self):
        print("cache_slot = ", self.cache_slots, "cache_hit = ", self.cache_hit, "hit ratio = ", self.cache_hit / self.tot_cnt)


if __name__ == "__main__":

    data_file = open("C:/Users/kevin/OneDrive/문서/GitHub/data-structure-python-/lru_sim/linkbench.trc")
    lines = data_file.readlines()
    for cache_slots in range(100, 1001, 100):
        cache_sim = CacheSimulator(cache_slots)
        for line in lines:
            page = line.split()[0]
            cache_sim.do_sim(page)

        cache_sim.print_stats()

