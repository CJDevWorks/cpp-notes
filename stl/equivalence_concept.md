Everywhere the standard library uses the Compare concept, uniqueness is determined by using the equivalence relation.

 In imprecise terms, two objects a and b are considered equivalent (not unique)

    if neither compares less than the other: !comp(a, b) && !comp(b, a).