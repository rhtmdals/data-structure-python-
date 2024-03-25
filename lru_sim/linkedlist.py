class ListNode:
    def __init__(self, newItem, nextNode = None, prevNode = None):
        self.item = newItem
        self.next = nextNode
        self.prev = prevNode


class LinkedListBasic:
    def __init__(self):
        self.__head = ListNode("Dummy") #head와 tail에 dummy값 입력
        self.__tail = ListNode("Dummy")
        self.__tail.prev = self.__head
        self.__head.next = self.__tail
        self.__numItems = 0

    def append(self, newItem): #head위치에 새로운 값 삽입
        newNode = ListNode(newItem)
        self.__head.next.prev = newNode
        newNode.next = self.__head.next     
        self.__head.next = newNode
        newNode.prev = self.__head
        self.__numItems += 1

    def removeTail(self): #tail과 가장 가까운 값 제거
        self.__tail.prev.prev.next = self.__tail
        self.__tail.prev = self.__tail.prev.prev
        self.__numItems -= 1
    
    def size(self) -> int: #아이템 수 리턴
        return self.__numItems
    
    def count(self, x): #동일한 값 갯수 리턴
        if self.__numItems == 0:
            return 0
        cnt = 0
        curr = self.__head.next
        while curr != None:
            if curr.item == x:
                return 1
            curr = curr.next
        return cnt
    
    def printList(self):
        curr = self.__head.next
        for element in self:
            print(curr.item, end = ' ')
            curr = curr.next
        print()

    def remove(self, x): #가장 처음 나타나는 x값 제거
        curr = self.__findNode(x)
        curr.prev.next, curr.next.prev = curr.next, curr.prev
        self.__numItems -= 1
    
    def __findNode(self, x): #x가 어느 노드에 있는지 탐색 후 리턴
        curr = self.__head.next #0번 노드
        while curr != None:
            if curr.item == x:
                return curr
            else:
                curr = curr.next
        return None 
    

    def __iter__(self): #이터레이터
        self.__current = self.__head.next
        return self

    def __next__(self):
        if self.__current is None:
            raise StopIteration
        else:
            item = self.__current.item
            self.__current = self.__current.next
            return item
