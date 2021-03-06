Erste Schritte ein Repository anlegen
--------------------------------------

Eine ausführliche Beschreibung kann hier gefunden werden: [Git Grundlagen ein Git Repository anlegen](http://git-scm.com/book/de/Git-Grundlagen-Ein-Git-Repository-anlegen)

### Festlegung der eigenen Identität

Damit Änderungen am Quellcode eindeutig nachvollzogen werden können muss die Identität festgelegt werden:

    $ git config --global user.name "John Doe"
    $ git config --global user.email johndoe@example.com


### Einrichten eines github Zugangs

Zur Veranschaulichung wird ein Zugang auf [github.com](http://github.com) eingerichtet.


### Erstellen eines git Repositories aus bereits vorhandenem Quellcode

Es wird ein einfaches Hello World Programm erstellt und und dies in git importiert

Ein leeres git Repository erzeugen

    $ git init

Hello World unter Versionsverwaltung stellen:

    $ git add hello.c
    $ git add HelloWorld.sln
    $ git add HelloWorld\HelloWorld.vcxproj

### Den aktuellen Status prüfen

    $ git status 

### Die Dateien commiten

    $ git commit -m "initial commit"

### Eine Datei verändern und erneut den Status prüfen

    $ git status

### Eine Datei löschen

    $ rm HelloWorld.c
    $ git status
    
### Wiederherstellen der Datei:

    $ git checkout HelloWorld.c

### Anzeige git log

    $ git log

### Anzeige des Logs einer Datei:

    $ git log README.md

### Verwendung von WinMerge als Diff-Tool
Das Tool WinMerge in einer Portable Variante kann hier bezogen werden: [portableapps](http://portableapps.com/de/apps/utilities/winmerge_portable) 
An der DHBW kann das Tool z.B. unter M:\ installiert werden. Anschließend sind in der git Konsole die folgenden Befehle auszuführen.

    $ git config --global diff.tool winmerge
    $ git config --replace --global difftool.winmerge.cmd "\"M:\tools\WinMergePortable\WinMergePortable.exe\" -e -u -dl \"Base\" -dr \"Mine\" \$REMOTE \$LOCAL"
    $ git config --global difftool.prompt false


Durchsprache der Lösung
=======================

### Hinzufügen eines entfernten Repositories
Sie können das Repository mit der Lösung wie folgt hinzufügen

    $ git remote add loesung https://github.com/dhbw-fn-micro/loesung_1.git
    $ git fetch --all
    $ git remote 
    $ git remote -v
    $ git branch
    $ git branch -a
    
### Vergleichen der Lösung
Sie können die Lösung mit Ihrem Code wie folgt vergleichen

    $ git difftool   master..loesung/solution

### Mergen der der Lösung
Sie können die Lösung mit Ihrem Code wie folgt zusammenführen

    $ git merge loesung/solution 


