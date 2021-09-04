// Using the visitor pattenr to emulate double dispatch

#include <iostream>
#include <string>
#include <vector>

// forward declaration
struct Monster;

struct Weapon {
	virtual std::string description() const = 0;
	virtual ~Weapon() = default;
	virtual void apply_damage(Monster&) = 0;
};

// forward declaration
struct Axe;
struct Nuke;

struct Monster {
	virtual std::string description() const = 0;
	virtual ~Monster() = default;
	virtual void receive_attack(Axe&) = 0;
	virtual void receive_attack(Nuke&) = 0;
	virtual void receive_attack(Weapon&) {
		std::cout << "⟨generic weapon–monster interaction⟩\n";
	}
};

struct Axe : Weapon {
	std::string description() const override {
		return "an axe";
	}

	void apply_damage(Monster& monster) override {
		monster.receive_attack(*this);
	}
};

struct Nuke : Weapon {
	std::string description() const override {
		return "a tactical nuclear missile";
	}

	void apply_damage(Monster& monster) override {
		monster.receive_attack(*this);
	}
};

struct Spider : Monster {
	std::string description() const override {
		return "a scary spider";
	}

	void receive_attack(Axe&) override {
		std::cout << "You miss.\n";
	}

	void receive_attack(Nuke&) override {
		std::cout << "The spider is annihilated.\n";
	}

};

struct Troll : Monster {
	std::string description() const override {
		return "an ugly troll";
	}
	void receive_attack(Axe&) override {
		std::cout << "You hit the troll.\n";
	}
	void receive_attack(Nuke&) override {
		std::cout << "Trolls are immune to nuclear weapons, silly.\n";
	}
};


void hit(Weapon& weapon, Monster& monster) {
	weapon.apply_damage(monster);
}

int main() {
	Troll troll;
	Axe axe;
	Spider spider;
	Nuke nuke;

	std::vector<Monster*> monsters = { &troll, &spider };
	std::vector<Weapon*> weapons = { &axe, &nuke };

	for (auto* monster: monsters) {
		for (auto* weapon: weapons) {
			std::cout << "\nUsing "
			          << weapon->description()
			          << " against "
			          << monster->description()
			          << ":\n\t";
			hit(*weapon, *monster);
		}
	}
}
