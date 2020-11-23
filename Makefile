#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

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


#all: outFolder $(IN_NAME)
#	@echo "Simple build of $(IN_NAME)"
#	$(CC) $(IN_NAME) -std=c99 -o $(OUT_FOLDER)/$(OUT_NAME)
#	@echo "Build completed. Output file: $(OUT_FOLDER)/$(OUT_NAME)"
.SILENT:

all :
	@echo "Complete build of the project in progress..."
	make outFolder
	make basic
	make tSet
	make t2Set
	make bt2Set
	@echo "Build completed. Output folder: $(OUT)"

run: $(SRC)
	bash $</scripts/scriptCSV_all.sh 32

clean:
	rm -fr $(OUT)
	@echo "Cleaning completed."

T22: $(SRC)
	make outFolder
	$(CC) $</Tache2_2.c -o $(O_LP)/T2_2.out $(FLAGS)

basic: $(S_LP)
	make outFolder
	$(CC) $</philosophes.c -o $(O_LP)/philo.out $(FLAGS)
	$(CC) $</producer_consumer.c -o $(O_LP)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers.c -o $(O_LP)/read_write.out $(FLAGS)

tSet: $(S_TS)
	make outFolder
	$(CC) $</philosophes_ts.c -o $(O_TS)/philo.out $(FLAGS)
	$(CC) $</producer_consumer_ts.c -o $(O_TS)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers_ts.c -o $(O_TS)/read_write.out $(FLAGS)

t2Set: $(S_TTS)
	make outFolder
	$(CC) $</philosophes_tts.c -o $(O_TTS)/philo.out $(FLAGS)
	$(CC) $</producer_consumer_tts.c -o $(O_TTS)/prod_cons.out $(FLAGS)
	$(CC) $</readers_writers_tts.c -o $(O_TTS)/read_write.out $(FLAGS)

bt2Set: $(S_BTTS)
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
