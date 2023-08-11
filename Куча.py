class Queue:
    def __init__(self):
        self.queue = [None]

    def sift_up(self, element):
        while self.queue[element // 2] != None and self.queue[element // 2] > self.queue[element]:
            self.queue[element // 2], self.queue[element] = self.queue[element], self.queue[element // 2]
            element = element // 2

    def sift_down(self, v):
        while True:
            if v * 2 <= len(self.queue):
                if v * 2 + 1 == len(self.queue):
                    max_idx = v * 2
                elif self.queue[v * 2] <= self.queue[v * 2 + 1]:
                    max_idx = v * 2
                else:
                    max_idx = v * 2 + 1
                
                if self.queue[v] > self.queue[max_idx]:
                    self.queue[v], self.queue[max_idx] = self.queue[max_idx], self.queue[v]
                    self.sift_down(max_idx)
                else:
                    break
            else:
                break

    def get_min(self):
        return self.queue[1]
    
    def add_element(self, element):
        self.queue.append(element)
        self.sift_up(len(self.queue) - 1)
    
    def delete_min(self):
        self.queue[1], self.queue[-1] = self.queue[-1], self.queue[1]
        self.queue.pop()
        self.sift_down(1)
queue = Queue()
queue.add_element(5)
queue.add_element(8)
queue.add_element(2)
queue.add_element(6)
queue.delete_min()
print(queue.queue)
queue.delete_min()
print(queue.queue)
print(queue.get_min())
