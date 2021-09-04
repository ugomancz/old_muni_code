// This one doesn't work.

#include <iostream>
#include <string>
#include <vector>

struct Weapon {
	virtual std::string description() const = 0;
	virtual ~Weapon() = default;
};

struct Monster {
	virtual std::string description() const = 0;
	virtual ~Monster() = default;
};

struct Axe : Weapon {
	std::string description() const override {
		return "an axe";
	}
};

struct Nuke : Weapon {
	std::string description() const override {
		return "a tactical nuclear missile";
	}
};

struct Spider : Monster {
	std::string description() const override {
		return "a scary spider";
	}
};

struct Troll : Monster {
	std::string description() const override {
		return "an ugly troll";
	}
};

void hit_impl(Weapon&, Monster&) {
	std::cout << "⟨generic weapon–monster interaction⟩\n";
}

void hit_impl(Axe&, Spider&) {
	std::cout << "You miss.\n";
}

void hit_impl(Nuke&, Spider&) {
	std::cout << "The spider is annihilated.\n";
}

void hit_impl(Axe&, Troll&) {
	std::cout << "You hit the troll.\n";
}

void hit_impl(Nuke&, Troll&) {
	std::cout << "Trolls are immune to nuclear weapons, silly.\n";
}

void hit(Weapon& weapon, Monster& monster) {
	hit_impl(weapon, monster);
}

int main() {
	Troll troll;
	Axe axe;

	// this works, of course
	hit_impl(axe, troll);

	// this doesn't
	hit(axe, troll);

	std::cout << "---\n";

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
			// no difference between hit and hit_impl
			hit(*weapon, *monster);
		}
	}
}
