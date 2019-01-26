
protocol Food {
	var nutritionalValue: Double { get }
}

protocol Animal {
	mutating func eat(food: Food)
	mutating func sleep()
	mutating func hunt() -> Bool
	var energy: Double { get set }
}

extension Animal {
 	mutating func eat(food: Food) {
		energy += food.nutritionalValue
	}
	
	mutating func sleep() {
		energy += 20.0
	}
	
	mutating func hunt () -> Bool {
		if energy < 14.0 {
			return false
		}
		energy -= 14.0
		
		// there is nice random here :) sandbox doesn't support arc4random_uniform()
		if Int(energy) % 3 == 0 {
			return true
		}
		return false
	}
}


struct Grass: Food {
	let nutritionalValue: Double = 20.0
}

struct Cow: Animal, Food {
	let nutritionalValue: Double = 65.0
	var energy: Double = 0.0
	
	mutating func reproduce() -> Cow? {
		if energy >= 20.0 {
			energy -= 20.0
			return Cow(energy: 0.0)
		}
		else {
			return nil
		}
	}
}

struct Tiger: Animal {
	var energy: Double = 0.0
	
	mutating func reproduce() -> Tiger? {
		if energy >= 25.0 {
			energy -= 25.0
			return Tiger(energy: 0.0)
		}
		else {
			return nil
		}
	}
}

// ---------------------------------------------------------------------


var grass: Grass? = Grass()
var cow1: Cow? = Cow(energy: 100.0)
cow1?.sleep()
// cow1 will not hunt on nonexisting grass
if grass != nil && (cow1?.hunt() == true) {
	cow1?.eat(food: grass!)
}

var cow2 = cow1?.reproduce()
if cow2 != nil {
	print("cow2 was successfully created!")
}
else {
	print("cow2 wasn't created. cow1 didn't have enough energy.")
}


var tiger = Tiger(energy: 30.0)
// the tiger will not hunt on nonexisting cow
if cow1 != nil && tiger.hunt() {
	tiger.eat(food: cow1!)
	cow1 = nil
	print("cow1 has been successfully eaten by tiger!")
}
else {
	print("The tiger is bad hunter!")
}

print("Energy of the tiger is equal to \(tiger.energy)")
