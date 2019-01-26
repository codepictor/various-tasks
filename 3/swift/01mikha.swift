//############################################################################
//Author: Artem Mikhalev
//############################################################################

import Foundation

class HyperCube {
	let dimension: Int

	var edgeLength: Double {
		didSet {
			print("Edge's length of hypercube has changed!", terminator: " ")
			print("oldValue = \(oldValue), newValue = \(self.edgeLength)")
		}
		willSet {
			if newValue <= 0.0 {
				fatalError("Warning! Edge's length can't be less or equal to zero!")
			}
		}
	}

	var volume: Double {
		get {
			return pow(self.edgeLength, Double(self.dimension))
		}
		set {
			self.edgeLength = pow(newValue, 1.0 / Double(self.dimension))
		}
	}

	init(dimension: Int, edgeLength: Double) {
		if dimension > 0 {
			self.dimension = dimension
		}
		else {
			fatalError("Dimension of the hypercube can't be less or equal to zero!")
		}

		if edgeLength > 0.0 {
			self.edgeLength = edgeLength
		}
		else {
			fatalError("Edge's length can't be less or equal to zero!")
		}
	}
}


var hyperCube = HyperCube(dimension: 4, edgeLength: 2.0)
print("Volume of hyper cube is equal to \(hyperCube.volume).")
hyperCube.edgeLength = 6.0
print("New volume of hyper cube is equal to \(hyperCube.volume).")
hyperCube.volume = 256.0

