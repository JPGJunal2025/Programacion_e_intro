FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libeigen3-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

# Punto de trabajo
WORKDIR /app

# Copiamos TODO el código fuente
COPY src/ src/

# Creamos carpeta de ejecutables
RUN mkdir -p bin \
 && g++ src/mc/montecarlo.cpp -o bin/montecarlo \
 && g++ src/nn/neuralnet.cpp  -o bin/neuralnet  \
 && g++ src/main.cpp          -o bin/main

# bin/main será SIEMPRE el proceso que se ejecuta;
# lo que pase después son argumentos que le lleguen
ENTRYPOINT ["./bin/main"]
