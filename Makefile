CC = gcc
FLAGS := -g0 -lpthread

CORES = `grep processor /proc/cpuinfo | wc -l` #Nombre de coeurs de la machine

SRC	:= src
S_T22 := $(SRC)/Tache2_2
S_LP := $(SRC)/lpthread
S_TS := $(SRC)/test_and_set
S_TTS := $(SRC)/test_and_test_and_set
S_BTTS := $(SRC)/backoff_test_and_test_and_set

OUT := output
O_T22 := $(OUT)/T22
O_LP := $(OUT)/lpthread
O_TS := $(OUT)/test_and_set
O_TTS := $(OUT)/test_and_test_and_set
O_BTTS := $(OUT)/backoff_test_and_test_and_set



.SILENT: #chuuut, rend les make silencieux
mega: #tout.
	make clean
	make all
	make run
	make test
	make graphs
	@echo "Bonne journée!"

all : #Compile le projet entier
	@echo "Compilation du projet en cours..."
	make outFolder
	make verrous
	make basic
	make tSet
	make t2Set
	make bt2Set
	@echo "Compilation terminée"

run: $(SRC)	#Lance le projet compilé entier
	@echo "Lancement du projet sur $$(( 2 * $(CORES) )) threads..."
	bash $</scripts/scriptCSV_all.sh 2 
	#$$(( 2 * $(CORES) ))
	@echo "Projet terminé - CSV générés"

graphs: $(SRC) #Créés les graphes, à utiliser après avoir créé les CSV
	@echo "Graphes en construction..."
	python3 $</graphs.py
	@echo "Graphes tracés"

clean: #Supprime tous les fichiers compilés & les CSV
	@echo "Nettoyage en cours..."
	make cleanOut
	make cleanCSV
	@echo "Nettoyage terminé"

cleanOut: #Supprime tous les fichiers compilés
	rm -rf $(OUT)

cleanCSV: $(SRC)/CSV #Supprime tous les fichiers CSV
	find $< -type f -delete

cleanGraphes: $(OUT)
	#find $< -type f -delete

test: $(S_T22) #Compile la tâche 2.2
	@echo "Tests des verrous en cours..."
	make verrous
	bash src/scripts/script2_2.sh $$(( 2 * $(CORES) ))
	@echo "Tests des verrous terminés"


verrous: $(S_T22)
	make outFolder
	$(CC) $</ts.c -o $(O_T22)/ts.out $(FLAGS)
	$(CC) $</ts.c -o $(O_T22)/tts.out $(FLAGS)
	$(CC) $</ts.c -o $(O_T22)/btts.out $(FLAGS)

basic: $(S_LP) #Compile les fichiers utilisant lpthread
	make outFolder
	$(CC) $</philosophes.c -o $(O_LP)/philo.out $(FLAGS)
	$(CC) $</producer_consumer.c -o $(O_LP)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers.c -o $(O_LP)/read_write.out $(FLAGS)

tSet: $(S_TS) #Compile les fichiers utilisant test and set
	make outFolder
	$(CC) $</philosophes_ts.c -o $(O_TS)/philo.out $(FLAGS)
	$(CC) $</producer_consumer_ts.c -o $(O_TS)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers_ts.c -o $(O_TS)/read_write.out $(FLAGS)

t2Set: $(S_TTS) #Compile les fichiers utilisant test and test and set
	make outFolder
	$(CC) $</philosophes_tts.c -o $(O_TTS)/philo.out $(FLAGS)
	$(CC) $</producer_consumer_tts.c -o $(O_TTS)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers_tts.c -o $(O_TTS)/read_write.out $(FLAGS)

bt2Set: $(S_BTTS) #Compile les fichiers utilisant backoff test and test and set
	make outFolder
	$(CC) $</philosophes_btts.c -o $(O_BTTS)/philo.out $(FLAGS)
	$(CC) $</producer_consumer_btts.c -o $(O_BTTS)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers_btts.c -o $(O_BTTS)/read_write.out $(FLAGS)

outFolder: #Créé les dossiers de sorties nécessaires avant la compilation du projet
	mkdir -p $(OUT)
	mkdir -p $(O_T22)
	mkdir -p $(O_LP)
	mkdir -p $(O_TS)
	mkdir -p $(O_TTS)
	mkdir -p $(O_BTTS)
	mkdir -p src/CSV/lpthread
	mkdir -p src/CSV/ts
	mkdir -p src/CSV/tts
	mkdir -p src/CSV/btts

# LANDO NORRIS <3