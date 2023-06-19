#include <iostream>

class Shape {
public:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	void draw() override {
		std::cout << "Circle Created.\n";	
	}
};

class Rect : public Shape {
public:
	void draw() override {
		std::cout << "Rect Created.\n";	
	}
};

class Triangle : public Shape {
public:
	void draw() override {
		std::cout << "Triangle Created.\n";	
	}
};

class ShapeFactory {
public:
	static Shape* createShap(const std::string& name) {
		if (name == "circle") {
			return new Circle();
		} else if (name == "rect") {
			return new Rect();
		} else if (name == "triangle") {
			return new Triangle();
		}
		return nullptr;
	}
};

int main() {
	Shape* s = ShapeFactory::createShap("rect");
	s->draw();
	delete s;
	return 0;
}