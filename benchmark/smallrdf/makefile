CPP_SRCS += \
  src/RDF.cpp \
  src/RDFNTriplesParser.cpp \
  src/RDFNTriplesSerializer.cpp \

OBJS += \
  ./build/RDF.o \
  ./build/RDFNTriplesParser.o \
  ./build/RDFNTriplesSerializer.o \

CPP_DEPS += \
  ./build/RDF.d \
  ./build/RDFNTriplesParser.d \
  ./build/RDFNTriplesSerializer.d \

LIBS += \
  -lgtest \
  -lpthread

./build/%.o: ./src/%.cpp
	@mkdir -p ./build
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

clean:
	@rm -rf build
