if [ $1 = "all" ]; then
	for i in {0..43}
	do
		g++ "$i"_*.cpp -lglut -lGL -lGLU -o main.run
		echo "\nRunning Program $i"
		./main.run
		rm main.run
	done
else
	g++ $1_*.cpp -lglut -lGL -lGLU -o main.run
	./main.run
	rm main.run
fi