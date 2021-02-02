CPP_SRCS += \
  src/RDF.cpp \
  src/RDFNTriplesParser.cpp \
  src/RDFNTriplesSerializer.cpp \
  benchmark.cpp

OBJS += \
  ./build/RDF.o \
  ./build/RDFNTriplesParser.o \
  ./build/RDFNTriplesSerializer.o \
  ./build/benchmark.o \

./build/%.o: ./smallrdf/src/%.cpp
	@mkdir -p ./build
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

./build/%.o: ./%.cpp
	@mkdir -p ./build
	g++ -O0 -g3 -Wall -Wno-write-strings -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -I src

all: benchmark run

benchmark: $(OBJS)
	g++ -o benchmark $(OBJS) $(LIBS)

run: 
	./benchmark

clean:
	@rm -rf build
	@rm -f benchmark
