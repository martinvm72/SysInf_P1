# SysInf_P1
Martin Van Mollekot & Arthur Vandroogenbroek

## Commandes Makefile
### Principales:
* make all : Compile le projet entier
* make run : Excecute le projet compilé et génère les fichiers CSV (soyez sur d'avoir compilé le projet avant)
* make test : Test sur les implémentations de verrous
* make clean : Supprime les fichiers compilés et les CSV

### Extra:
* make mega : Super commande qui clean, compile, lance les tests et le projet et trace les graphes pour l'ensemble du projet
* make graphs : Trace les graphes python (nécessite d'avoir les CSV disponibles)
* make verrous : Compile les verrous
* make cleanOut : Supprime les fichiers compilés
* make cleanCSV : Supprime les CSV
* make cleanGraphes : #Supprime les graphes
* make basic : Compile les 3 problèmes avec l'implémentation lpthread
* make tSet : Compile les 3 problèmes avec l'implémentation test and set
* make t2Set : Compile les 3 problèmes avec l'implémentation test and test and set
* make bt2Set : Compile les 3 problèmes avec l'implémentation backoff test and test and set
* make outFolder : Créé les dossiers de sorties nécessaires avant la compilation du projet

## Comment utiliser les verrous

Chacun d'entre eux possède 4 foncions de mutex et 4 fonctions de sémaphores sembables aux fonctions de lpthread: 
| Fonctions | Argument | Sortie | Description |
| --- | --- | --- | --- |
| mutex_init | / | L'ID du mutex (int) OU -1 en cas d'erreur | Initialise le mutex |
| mutex_lock | L'ID du mutex | / | Verouille le mutex |
| mutex_unlock | L'ID du mutex | / | Déverouille le mutex |
| mutex_destroy | L'ID du mutex | / | Détruit le mutex |
| sem_init | La valeur initiale du sémaphore (int) | L'ID du sémaphore (int) OU -1 en cas d'erreur | Initialise le sémaphore à la valeur initiale |
| sem_lock | L'ID du sémaphore | / | Verouille le sémaphore |
| sem_unlock | L'ID du sémaphore | / | Déverouille le sémaphore |
| sem_destroy | L'ID du sémaphore | / | Détruit le sémaphore |


## Organisation des fichiers
´´´
Projet
│   Rapport.pdf
│   README.md
│   Makefile   
│
└───src
│   │   graphs.py       #Génère les graphes liés aux problèmes
│   │   graphs2_2.py    #Génère le graphe de performance des verrous
│   │   graphUnique.py  #Génère le graphe d'un seul problème au choix (utilisé pour générer les graphes du rapport)
│   │
│   └───scripts         #Scripts bash pour lancer les fichiers compilés
│   |   │   scriptCSV_all.sh    #Lance l'ensemble des scripts ci-dessous
│   |   │   scriptCSV_lpthread.sh
│   |   │   scriptCSV_ts.sh     #test and set
│   |   │   scriptCSV_tts.sh
│   |   │   scriptCSV_btts.sh
│   |   │   script2_2.sh        #tache 2.2: test des verrous
|   |
│   └───lpthread        #Problèmes implémentés avec les mutex/sémaphores de la librairie lpthread
│   |   │   philosophes.c
│   |   │   producer_consumer.c
│   |   │   readers_writers.c
│   |
│   └───test_and_set    #Problèmes implémentés nos mutex/sémaphores implémentés avec la logique "test and set"
│   |   │   test_and_set.c
│   |   │   philosophes.c
│   |   ...
│   |
│   └───test__and_test_and_set    #Problèmes implémentés nos mutex/sémaphores implémentés avec la logique "test and test and set"
│   |   ...
|   |
│   └───backoff_test__and_test_and_set    #Problèmes implémentés nos mutex/sémaphores implémentés avec la logique "backoff test and test and set"
│   |   ...
|   |
│   └───Tache2_2    #Programmes de test des 3 verrous
│   |   │   ts.c    #test and set
│   |   │   tts.c
│   |   │   btts.c
|   |
│   └───CSV    #Les CSV des mesures de performances de nos codes, rangés selon la même logique que les codes eux-mêmes
│   |   ...
|
|
└───output  #Fichiers compilés, rangés selon une logique similaires aux codes
    |
    └───lpthread
    |   │   philo.out  
    |   ...
    ...
´´´
## Infos supplémentaires sur les arguments des programmes
* philosophes.c : 1 argument, le nombre de threads
* producer_consumer.c : 2 arguments, le nombre de producteurs puis le nombre de consommateurs
* readers_writers.c : 2 arguments, le nombre d'écrivains puis le nombre de lecteurs
* tous les scripts : 1 argument, le nombre de threads maximum
