#include <iostream>

class Animal {
public:
	virtual void name() = 0;
};

class Dog : public Animal {
public:
	void name() override {
		std::cout << "Dog\n";	
	}
};

class Cat : public Animal {
public:
	void name() override {
		std::cout << "Cat\n";	
	}
};

class Pig : public Animal {
public:
	void name() override {
		std::cout << "Pig\n";	
	}
};

class AnimalFactory {
public:
	virtual Animal* createAnimal() = 0;
};

class DogFactory : public AnimalFactory {
public:
	Animal* createAnimal() override {
		return new Dog();
	}
};

class CatFactory : public AnimalFactory {
public:
	Animal* createAnimal() override {
		return new Cat();
	}
};

class PigFactory : public AnimalFactory {
public:
	Animal* createAnimal() override {
		return new Pig();
	}
};

int main() {
	CatFactory* cf = new CatFactory();
	Animal* a = cf->createAnimal();
	a->name();
	delete cf;
	delete a;
	return 0;
}