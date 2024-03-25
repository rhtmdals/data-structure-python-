

class CacheSimulator:
    def __init__(self, cache_slots):
        self.cache_slots = cache_slots
        self.cache_hit = 0
        self.tot_cnt = 0
        self.cashe_list = []
    
    def do_sim(self, page):
        if page in self.cashe_list:  #hit
            self.cashe_list.remove(page)
            self.cashe_list.append(page)
            self.cache_hit += 1
            self.tot_cnt += 1
        
        else: #miss
            if len(self.cashe_list) < self.cache_slots:
                self.cashe_list.append(page)
            else:
                self.cashe_list.pop(0)
                self.cashe_list.append(page)
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
