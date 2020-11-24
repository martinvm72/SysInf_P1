CC = gcc
FLAGS := -g0 -lpthread

SRC	:= src
OUT := output
S_LP := $(SRC)/lpthread
S_TS := $(SRC)/test_and_set
S_TTS := $(SRC)/test_and_test_and_set
S_BTTS := $(SRC)/backoff_test_and_test_and_set

OUT := output
O_LP := $(OUT)/lpthread
O_TS := $(OUT)/test_and_set
O_TTS := $(OUT)/test_and_test_and_set
O_BTTS := $(OUT)/backoff_test_and_test_and_set



.SILENT: #chuuut, rend les make silencieux
mega: #tout.
	make clean
	make all
	make run
	make graphs

all : #Compile le projet entier
	@echo "Complete build of the project in progress..."
	make outFolder
	make basic
	make tSet
	make t2Set
	make bt2Set
	@echo "Build completed. Output folder: $(OUT)"

run: $(SRC)	#
	bash $</scripts/scriptCSV_all.sh 16

graphs: $(SRC) #Créés les graphes, à utiliser après avoir créé les CSV
	python3 $</graphs.py

clean: #Supprime tous les fichiers compilés & les CSV
	make cleanOut
	make cleanCSV

cleanOut: $(OUT) #Supprime tous les fichiers compilés
	make outFolder
	find $< -type f -delete

cleanCSV: $(SRC)/CSV #Supprime tous les fichiers CSV
	find $< -type f -delete



T22: $(SRC) #Compile la tâche 2.2
	$(CC) $</Tache2_2.c -o $(O_LP)/T2_2.out $(FLAGS)

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

outFolder:
	mkdir -p $(OUT)
	mkdir -p $(O_LP)
	mkdir -p $(O_TS)
	mkdir -p $(O_TTS)
	mkdir -p $(O_BTTS)
