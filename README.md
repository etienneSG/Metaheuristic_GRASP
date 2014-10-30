MPRO - Metaheuristic
=====

GRASP Methods

Projet du cours Metaheuristique enseigné au MPRO (2014-2015)

=====
Notes pour la compilation :

En cas d'échec, créer manuellement les dossiers Objet, Bin et TestCases/Output,
puis lancer normalement la compilation.

Pour Compiler sous un système Windows, utilisez le CmakeLists. Attention, son
utilisation peut entraîner quelques bogues contrairement à celle du Makefile
pour les systèmes Unix.

====
Notes pour l'execution:

Liste des arguments (dans cet ordre) :

1) Chemin_Relatif_Fichier_Instance (Contient le chemin du fichier d'instance
depuis le répertoire de lancement de l'exécutable.)

2) Pas d'argument (lance la méthode GRASP) ou GeneralStats (lance le module
générant des statistiques à propos de la construction gloutonne/aléatoire et des
recherches locales)

====
Notes pour le debug et le suivi pas à pas:

Afin d'effectuer un suivi pas à pas plus aisé du programme, il est conseillé de
commenter toutes les lignes dirgeant une parallélisation des calculs.

====
Scripts disponibles:

Le script RunCapX est un script bash. Il nettoie le répertoire, compile le
projet et lance l'ensemble des instances de test. Les fichiers d'output de
chacun de ces tests se retrouvent dans TestCases/Output.

Le script GeneralStats est un script bash. Il nettoie le répertoire, compile le
projet et lance le module générant des statistiques à propos de la construction
gloutonne/aléatoire et des recherches locales. Le fichier d'output de ce module
se retrouve dans TestCases/Output.

