import random

def Init_neurone(nbpoids, rang):
    poids = [random.randint(0, rang) for _ in range(nbpoids)]
    return {"poids": poids, "biais": random.randint(0, rang)}

def Out_neurone(neurone, entrees):
    somme = 0
    for i in range(len(neurone["poids"])):
        somme += neurone["poids"][i] * entrees[i]
        print(neurone["poids"][i], ' * ', entrees[i], end="")
        if i < len(neurone["poids"]) - 1:
            print(" + ", end="")
        else:
            print(" = ", somme, end="")
    if somme >= neurone["biais"]:
        print("  >= biais",neurone["biais"],"renvoie 1")
        return 1 
    else:
        print("  < biais",neurone["biais"])
        return 0

def Init_couche(nombre_neurone, nb_poids, rang):
    return [Init_neurone(nb_poids, rang) for _ in range(nombre_neurone)]

def Out_Couche(couche, entrees):
    return [Out_neurone(neurone, entrees) for neurone in couche]

def Init_Reseau_Neurone(nbcouches,liste_neurone):
    rang = 2
    nbpoids = 3
    Reseau = []
    for i in range (nbcouches):
        Reseau.append(Init_couche(liste_neurone[i],nbpoids,rang))
    return Reseau 


if __name__ == "__main__":
    rang = 2
    nbpoids = 3
    nombre_neurone = 5

    Couche = Init_couche(nombre_neurone, nbpoids, rang)
    print(Couche)
    entrees = [1, 0, 0]
    print(Out_Couche(Couche, entrees))