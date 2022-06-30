"""
hw04
učo: 469007
Ondřej Kostík
"""
"""
Vše je funkční, jediný nedostatek by měla být nutnost volat objekty pomocí
slovníků, tudíž například "woman['Mary'].get_age()" nebo
"clubs['club penguin'].members". Pro zjednodušení práce jsem si přidal k
__init__ dalších pár proměnných, ušetřilo mi to spoustu řádků navíc, kde bych
musel vytvářet dočasné proměnné pro jednotlivé funkce.
"""


class Woman:

    def __init__(self, name, born_year, hair_color):
        self.name = name
        self.born_year = int(born_year)
        self.hair_color = hair_color
        self.daughters = []
        self.daughters_names = []
        self.mother = None
        self.mother_at = None

    def get_age(self):      # find out woman's age
        age = 2017 - self.born_year
        return age

    def add_daughter(self, daughter):       # add a daughter
        self.daughters.append(daughter)
        self.daughters_names.append(daughter.name)


class Club:
    def __init__(self, name, established_year):
        self.name = name
        self.established_year = established_year
        self.members = []
        self.members_names = []

    def add_member(self, member):       # add a member
        self.members.append(member)
        self.members_names.append(member.name)


def load_from_file(self, file_name="people-data.txt"):      # loads file
    women, clubs = {}, {}
    section = "Women"
    with open(file_name) as f:
        for line in f.readlines():
            line = line.rstrip()
            if line == "# CHILDREN":        # selects section of file
                section = "Children"
                continue
            if line == "# CLUBS":
                section = "Clubs"
                continue
            if section == "Women":      # creates Woman objects
                w = line.split(",")
                women[w[0]] = Woman(w[0], w[1], w[2])
            elif section == "Children":     # adds children
                w = line.split("->")
                mother = women[w[0]]
                daughter = women[w[1]]
                mother.add_daughter(daughter)
            else:       # creates Club objects
                w = line.split(":")
                # print(w)
                member_names = w[1].split(",")
                # print(member_names)
                club_info = w[0].split(",")
                # print(club_info)
                name = club_info[0]
                # print(name)
                established_year = club_info[1]
                # print(established_year)
                members = []
                clubs[name] = Club(name, established_year)
                for member in member_names:     # adds club's members
                    if member != "":
                        clubs[name].members.append(women[member])
                        clubs[name].members_names.append(women[member].name)
    return women, clubs


def get_youngest_mother():     # finds the youngest mother ever
    max_year = 0
    youngest_mother = None
    for name, woman in women.items():
        if len(woman.daughters) > 0:
            if woman.born_year > max_year:
                max_year = woman.born_year
                youngest_mother = woman
    print(youngest_mother.name)


def last_born_offspring(woman):
    if len(woman.daughters) == 0:
        print(woman.name, "has no daughters")
    elif len(woman.daughters) == 1:
        print(woman.name, "has only one daughter,", woman.daughters[0].name)
    else:
        ages = []
        for i in range(len(woman.daughters)):
            ages.append(woman.daughters[i].get_age())
        x = my_min(ages)
        print(woman.name, "has these youngest daughters:")
        for i in range(len(ages)):
            if woman.daughters[i].get_age() == x:
                print(woman.daughters[i].name)


def get_common_members(club1, club2):       # finds common members of 2 clubs
    list1 = club1.members
    list2 = club2.members
    list3 = list(set(list1).intersection(list2))
    print("These clubs have these common members:")
    for i in range(len(list3)):
        print(list3[i].name)


def my_max(values):     # side function that finds the highest value in list
    max_value = 0
    for i in values:
        if max_value < i:
            max_value = i
    return max_value


def my_min(values):     # side function that finds the lowest value in list
    min_value = my_max(values)
    for i in values:
        if min_value > i:
            min_value = i
    return min_value


def get_youngest_mother():      # finds who was the youngest to become a mom
    womenlist = []
    mothersat = []
    for i in women.values():
        womenlist.append(i)
    # print(womenlist)
    for i in range(len(womenlist)):
        daughters = womenlist[i].daughters
        oldest = []
        if len(daughters) != 0:
            for h in range(len(daughters)):
                oldest.append(daughters[h].get_age())
            womenlist[i].mother_at = womenlist[i].get_age() - my_max(oldest)
    for i in range(len(womenlist)):
        if womenlist[i].mother_at is not None:
            mothersat.append(womenlist[i].mother_at)
    # print(mothersat)
    x = my_min(mothersat)
    for i in range(len(womenlist)):
        if womenlist[i].mother_at == x:
            print(womenlist[i].name, "at the age of", womenlist[i].mother_at)


women, clubs = load_from_file(0)
last_born_offspring(women['Mary'])
get_common_members(clubs['ahoj'],clubs['club penguin'])
get_youngest_mother()
