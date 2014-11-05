# Compilateur
CPP=g++

# Les différents répertoires contenant respectivement les fichiers :
# Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=Src
HEADDIR=Include
LIBDIR=Objet
BINDIR=Bin

# Les différentes options de compilations
# -fopenmp : pour le multithreading
# -g : mode debug  /  -O6 : optimisé
CFLAGS=-I Include -O6 -Wall -pedantic -fopenmp
# Les différents FrameWorks et bibliothèques pour le linkage
GLLIBS= -lstdc++

# Où trouver les différents sources *.cpp qu'il faudra compiler
# pour créer les objets correspondants
SRCPP= $(wildcard $(SRCDIR)/*.cpp)
OBJCPP= $(SRCPP:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o)

# L'éxécutable
all: MonExec

#Création de l'exécutable
MonExec: $(LIBDIR)/main.o $(OBJCPP)
	$(CPP) -o $(BINDIR)/$@ $^ $(CFLAGS) $(GLLIBS)

# Création de main.o
$(LIBDIR)/main.o: main.cpp
	mkdir -p $(BINDIR) $(LIBDIR)
	$(CPP) -o $@ -c $< $(CFLAGS)

# Création des différents *.o à partir des *.cpp
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(HEADDIR)/%.h
	$(CPP) -o $@ -c $< $(CFLAGS)

# Nettoyage des objets => Tout sera recompilé !
clean:
	rm $(LIBDIR)/*.o
	rmdir $(LIBDIR)

# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*
	rmdir $(BINDIR)
