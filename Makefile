# build by GNU make: make

CFLAGS=
LDFLAGS=

all: raw2wav

raw2wav: raw2wav.c 
	g++ -o $@ $< $(CFLAGS) $(LDFLASGS)
	
	
clean:
	rm -f raw2wav raw2wav.exe
	
