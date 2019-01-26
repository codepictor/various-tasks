class SingleList<T> {
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
}




class Queue<T> {
	var head: SingleList<T>?
	
	init() {
		head = nil
	}
	
	func push(_ addingValue: T) {
		if head != nil {
			head!.add(item: addingValue)
		}
		else {
			head = SingleList<T>(value: addingValue)
		}
	}
	
	func pop() {
		guard head != nil else {
	//		print("Warning. You try to pull out smth from empty queue.")
			return
		}
		
		head = head!.next
	}
	
	func show() {
		head?.dump()
	}
	
	func size() -> Int {
		if head != nil {
			return head!.size
		}
		else {
			return 0
		}
	}
	
	func front() -> T? {
		guard head != nil else {
//			print("Warning! You try to get the first element from empty queue.")
			return nil
		}
		
		return head!.value
	}
	
	func back() -> T? {
		guard head != nil else {
//			print("Warning! You try to get the last element from empty queue.")
			return nil
		}
		
		var currentNode = head
		while currentNode?.next != nil {
			currentNode = currentNode?.next
		}
		return currentNode?.value
	}
}





var q = Queue<Int>()
q.push(111)
q.push(222)
q.push(333)
q.push(444)
q.pop()
//q.pop()
//q.pop()
q.show()
var first = q.front()
var last = q.back()
//print(first!)
//print(last!)




