class Queue:
    def __init__(self):
        self.queue = [None]

    def sift_up(self, element):
        while self.queue[element // 2] != None and self.queue[element // 2] > self.queue[element]:
            self.queue[element // 2], self.queue[element] = self.queue[element], self.queue[element // 2]
            element = element // 2

    def sift_down(self, ind):
        if ind * 2

    def get_min(self):
        return self.queue[1]
    
    def add_element(self, element):
        self.queue.append(element)
        self.sift_up(len(self.queue) - 1)
    
    def delete_min(self):
        self.queue[1], self.queue[-1] = self.queue[-1], self.queue[1]
        self.sift_down(1)

queue = Queue()
queue.add_element(5)
queue.add_element(8)
print(queue.queue)
print(queue.get_min())
queue.add_element(2)
queue.add_element(6)
print(queue.get_min())