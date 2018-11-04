all: zork

zork: main.o room.o item.o container.o creature.o trigger.o
		g++ main.o room.o item.o container.o creature.o trigger.o -o zork

main.o: main.cpp
		g++ -c main.cpp

room.o: room.cpp
		g++ -c room.cpp

item.o: item.cpp
		g++ -c item.cpp

container.o: container.cpp
		g++ -c container.cpp

creature.o: creature.cpp
		g++ -c creature.cpp

trigger.o: trigger.cpp
		g++ -c trigger.cpp

clean:
		rm -rf *o zork

test: zork
		#./zork samples/roomsample.xml
		#./zork samples/itemsample.xml
		./zork samples/containersample.xml
		#./zork samples/creaturesample.xml
		#./zork samples/triggersample.xml

