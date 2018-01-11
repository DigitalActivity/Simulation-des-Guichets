# Simulation des Guichets en C++

Considérons les guichets de la gare centrale. Supposons qu'il y a cinq guichets. Lorsqu’un voyageur arrive,
il se peut qu'un guichet soit libre, auquel cas il pourra acheter son billet directement sans avoir à attendre. En
général, si tous les guichets sont occupés, le voyageur peut choisir la file la plus courte et attendre son tour.
Dans ce cas, il doit passer un temps total égal au temps de la transaction augmenté du temps d'attente. Afin
d'améliorer le service et de déterminer le nombre optimal de guichets, nous allons simuler l'opération des
guichets.

Un programme de simulation nous permettra de calculer le temps moyen passé par un voyageur à acheter un
billet en fonction de diverses conditions comme les intervalles de temps entre les arrivées des voyageurs, le
nombre de guichets et le nombre de file(s) (s'il n'y a pas une file par guichet).

Dans notre programme de simulation de la situation aux guichets, on caractérisera les voyageurs par deux
données:
- L'heure d'arrivée ;
- La durée de la transaction au guichet.

Nous ferons l'hypothèse que chacun agit indépendamment; nous aurons cinq guichets représentés par cinq
files d'attente différentes. Chaque élément d'une file d'attente sera un voyageur attendant d'être servi. Le
premier élément de chaque file représente un voyageur en train d'être servi. On ajoute chaque nouveau
voyageur à la file la plus courte. 