# SimpleJsonParser

A simple JSON parser implemented by C++17 that parses JSON files and print the parsed content.

Although there are many JSON parsers exist, most of them use raw pointers. The feature of this program is the utilization of smart pointers and a type-safe union, i.e., std::variant, to allocate and keep tokens with different data types.

## How to run

1. Build: `make`

2. Run: `./main`

## Demo

**JSON content**

```json
{
    "blog": "knok",
    "url": "https://knownoknow.net/",
    "content": ["linux", "docker", "algorithm", "..."],
    "uptime": 199
}
```

**Parse result**

```
{"blog": "knok", "content": ["linux", "docker", "algorithm", "..."], "uptime": 199, "url": "https://knownoknow.net/"}
```

## Memory leak detection

<p align="center">
  <img src="https://cdn.jsdelivr.net/gh/Avafly/ImageHostingService@master/uPic/SCR-20230921-osmw.png">
</p>

All heap memory was freed.