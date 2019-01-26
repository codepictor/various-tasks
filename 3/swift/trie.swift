class Node {
	var letter: Character
	var children = [Node]()
	var parent: Node?
	var isValue: Bool
	var isLeaf: Bool
	
	init(_ letter: Character, _ parent: Node?) {
		self.letter = letter
		self.parent = parent
		self.isValue = false
		self.isLeaf = true
	}
	
	deinit {
		children.removeAll()
	}
	
	func descend(_ str: inout String) -> Node {
		if str.isEmpty {
			return self
		}
		
		let currentLetter = str[str.startIndex]
		for child in children {
			if child.letter == currentLetter {
				str.remove(at: str.startIndex)
				return child.descend(&str)
			}
		}
		
		return self
	}
	
	func climbAndRemove() {
		if !self.isValue && self.isLeaf {
			if let parentNode = parent {
				parentNode.removeNode(self)
				parentNode.climbAndRemove()
			}
		}
	}
	
	func removeNode(_ node: Node) {
		let lastIndex = children.count - 1
		for i in 0...lastIndex {
			if children[i] === node {
				children.remove(at: i)
				break
			}
		}
	}
	
	func append(_ str: inout String) {
		if str.isEmpty {
			isValue = true
			return
		}
		
		let currentLetter = str[str.startIndex]
		str.remove(at: str.startIndex)
		children.append(Node(currentLetter, self))
		children[children.count - 1].isLeaf = false
		children[children.count - 1].append(&str)
	}
	
	func dump(_ currentString: inout String) {
		if parent != nil {
			currentString.append(letter)
		}
		if isValue {
			print(currentString)
		}
		
		for child in children {
			child.dump(&currentString)
		}
		if parent != nil {
			currentString.remove(at: currentString.index(before: currentString.endIndex))
		}
	}
}


class Trie {
	var root: Node
	
	init() {
		root = Node("!", nil)
	}
	
	// 1 - word exists, 0 - not
	func checkExistence(_ str: String) -> Bool {
		var strCopy = str
		let subRoot = root.descend(&strCopy)
		
		if strCopy.isEmpty && subRoot.isValue {
			return true
		}
		return false
	}
	
	// 0 - success, 1 - inserting word exists
	func insert(_ str: String) -> Bool {
		var strCopy = str
		let subRoot = root.descend(&strCopy)
		if strCopy.isEmpty {
			if subRoot.isValue {
				return true
			} else {
				subRoot.isValue = true
				return false
			}
		}
		
		subRoot.append(&strCopy)
		return false
	}
	
	// 0 - success, 1 - removing word doesn't exist
	func remove(_ str: String) -> Bool {
		var strCopy = str
		let subRoot = root.descend(&strCopy)
		if strCopy.isEmpty {
			if subRoot.isValue {
				subRoot.isValue = false
				if subRoot.isLeaf {
					subRoot.climbAndRemove()
				}
			} else {
				return true
			}
		}
		
		return true
	}
	
	func findCompletions(_ str: String) {
		print("-----------------------------------")
		print("\(str):")
		var strCopy = str
		let subRoot = root.descend(&strCopy)
		
		if strCopy.isEmpty {
			strCopy = str
			if !strCopy.isEmpty {
				strCopy.remove(at: strCopy.index(before: strCopy.endIndex))
			}
			subRoot.dump(&strCopy)
		}
		
		print("-----------------------------------")
	}
}



//------------------------------------------------------------------------------

var trie = Trie()
var aux = true
/*aux = trie.insert("abc")
aux = trie.insert("aaaa")
aux = trie.insert("ab")
aux = trie.insert("abcde")
aux = trie.insert("zz")
aux = trie.insert("zxz")
aux = trie.remove("zxz")
aux = trie.remove("ab")
//print("Trie was successfully created!")

//print(trie.checkExistence("abc"))
trie.findCompletions("a")
*/

aux = trie.insert("tree")
aux = trie.insert("tea")
aux = trie.insert("tiny")
aux = trie.insert("telescope")
aux = trie.insert("bird")

trie.findCompletions("")
trie.findCompletions("t")
trie.findCompletions("te")

