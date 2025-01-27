FROM --platform=linux/amd64 ubuntu:22.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential python-is-python3 zlib1g-dev clang make pkg-config curl libboost-dev libfreetype-dev libharfbuzz-dev libboost-all-dev git

COPY . /repo
WORKDIR /repo
RUN sed -i 's/CPP_TESTS = True/CPP_TESTS = False/g' bootstrap.sh
RUN ./bootstrap.sh
RUN ./configure CUSTOM_CXXFLAGS="-D_GLIBCXX_USE_CXX11_ABI=0"
RUN make -j8
RUN clang++ /repo/mayhem/fuzz_rtrim.cpp -fsanitize=fuzzer,address -I /repo/include/mapnik/util/ -o /fuzz

FROM ubuntu:22.04 as package
COPY --from=builder /repo/utils/svg2png/svg2png /
COPY --from=builder /repo/src/*.so* /deps/
COPY --from=builder /fuzz /fuzz_rtrim
ENV LD_LIBRARY_PATH=/deps
