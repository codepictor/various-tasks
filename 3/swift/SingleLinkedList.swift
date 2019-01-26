class SingleList<T: Comparable> {
    var value: T
    var next: SingleList<T>?
    var size: Int {
        get {
            var i = 1
            var currentElement: SingleList<T>? = self
            
            while currentElement?.next != nil {
                currentElement = currentElement?.next
                i += 1
            }
            return i
        }
    }
    
    
    init (value: T) {
        self.value = value
        self.next = nil
    }

    
    func dump() {
        var currentElement: SingleList<T>? = self
        var i = 0
        print("--------------------------------------")
        print("[\(i)] = \(currentElement!.value)")
        
        while currentElement?.next != nil {
            currentElement = currentElement?.next
            i += 1
            print("[\(i)] = \(currentElement!.value)")
        }
        
        print("--------------------------------------")
    }
    
    
    func add(item: T) {
        if self.next != nil {
            var currentElement = next
            while currentElement?.next != nil {
                currentElement = currentElement?.next
            }
            currentElement?.next = SingleList<T>(value: item)
        } else {
            self.next = SingleList<T>(value: item)
        }
    }
    
    
    // the first element in the list has index 0
    func insert(index: Int, item: T) {
        if index <= 0 || index > self.size {
//            print("Incorrect index of inserting element")
            return
        }
        
        var currentElement: SingleList<T>? = self
        var i = 1
        
        while i < index {
            currentElement = currentElement?.next
            i += 1
        }
        
        let aux = currentElement?.next
        currentElement?.next = SingleList<T>(value: item)
        currentElement = currentElement?.next
        currentElement?.next = aux
    }
    
    
    func remove(index: Int) {
        if index <= 0 || index >= self.size {
//            print("Incorrect index of removing element")
            return
        }
        
        var currentElement: SingleList<T>? = self
        var i = 1
        
        while i < index {
            currentElement = currentElement?.next
            i += 1
        }
        
        let removingElement = currentElement?.next
        currentElement?.next = removingElement?.next
    }
    
    
    func find(value: T) -> Int {
        var currentElement: SingleList<T>? = self
        var i = 0
//        let searchingElement = SingleList<T>(value: value)
        
        while currentElement != nil {
            if value == currentElement?.value {
                break
            }
            
            currentElement = currentElement?.next
            i += 1
        }
        
        if i == self.size {
            return -1
        } 
        return i
    }
    
    
    func checkCycle() -> Bool {
        var fast: SingleList<T>? = self
        var slow: SingleList<T>? = self
        
        while fast != nil {
            fast = fast?.next
            fast = fast?.next
            slow = slow?.next
            
            if fast === slow && fast != nil {
                return true
            }
        }
        
        return false
    }
    
    
    func reverse() -> SingleList<T> {
        var previousElement: SingleList<T>? = nil
        var currentElement: SingleList<T>? = self
        var nextElement: SingleList<T>? = self.next
        
        while currentElement != nil {
            nextElement = currentElement!.next
            currentElement!.next = previousElement
            previousElement = currentElement
            currentElement = nextElement
        }
        
        return previousElement!
    }
}


//print("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$")

var list = SingleList<Int>(value: 0)
list.add(item: 1)
list.add(item: 2)
list.add(item: 3)
list.add(item: 4)
list.insert(index: 2, item: 12)
list.remove(index: 4)
list.dump()
//print(list.find(value: 2))

var isCycle = list.checkCycle()
print(isCycle)


var reversedList = list.reverse()
reversedList.dump()

var currentElement: SingleList<Int>? = reversedList
while currentElement?.next != nil {
    currentElement = currentElement?.next
}
currentElement?.next = reversedList.next
isCycle = reversedList.checkCycle()
print(isCycle)

