# Perfect number
A number is considered a perfect number when the sum of its divisors (excluding the number itself) are equal to the number itself.

As an example:

> 6 is divisible by 1, 2 and 3
>
> 1 + 2 + 3 = 6
>
> Then 6 is a perfect number

## Build

### CMake
Run this once
```
mkdir build
```

Run this a the root of this project
```
cd build
cmake ..
cmake --build .
```

### Docker
```
docker build -f gcc.Dockerfile -t perfect --rm .
```

## Run

### CMake
When you have build with CMake, inside the build directory you'll find an executable called _"perfect"_.
```
perfect 1 2 6 28 600
```

### Docker
```
docker run -it --rm --name perfect 1 2 6 28 600
```
