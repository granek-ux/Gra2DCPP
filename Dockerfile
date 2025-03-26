FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    git \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libogg-dev \
    libfreetype6-dev \
    libjpeg-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

RUN ls -l build/Gra2DProjekt

CMD ["./build/Gra2DProjekt"]